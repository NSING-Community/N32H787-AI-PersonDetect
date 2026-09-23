/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file camera_app.c
 * @brief M4 camera application: OV5640 QVGA Y8 capture, person
 *        presence detection snapshots and the serial capture protocol.
 *
 * Serial commands (USART1, 921600 8N1):
 *   C - capture one frame; reply uses the 'OV56' binary protocol:
 *       'OV56' + width(u16 LE) + height(u16 LE) + format(u32 LE) +
 *       length(u32 LE), followed by the payload.
 *       format 3 = grayscale JPEG, format 9 = raw Y8;
 *       formats 8/10 append the 44-byte detection metadata header.
 *   N - toggle the presence detector on/off (LED on PB3 follows verdict).
 *   J - toggle JPEG encoding on/off.
 */

#include "main.h"
#include <stdint.h>
#include "ov5640.h"
#include "camera_color.h"
#include "m4_shared.h"
#include "jpeg_encoder.h"

#define CAMERA_WIDTH OV5640_WIDTH
#define CAMERA_HEIGHT OV5640_HEIGHT
#define CAMERA_BPP 1U
#define CAMERA_FRAME_BYTES (CAMERA_WIDTH * CAMERA_HEIGHT * CAMERA_BPP)
#define CAMERA_CAPTURE_TIMEOUT_MS 1000U
#define UART_BAUD 921600U

extern __IO uint32_t mwTick;

/* DVP2 has its own frame-buffer AHB writer; it captures a QVGA Y8 byte
   stream into this AXI SRAM buffer. */
static uint8_t g_camera_frame[CAMERA_FRAME_BYTES]
    __attribute__((section(".camera_frame"), aligned(32)));

/* Minimal camera telemetry, used by the CAPTURE-FAIL reply. */
static volatile struct {
    uint32_t attempts;
    uint32_t successes;
    uint32_t last_intsts;
    uint32_t elapsed_ms;
    uint32_t ov_probe;
    uint32_t ov_id;
    uint32_t i2c_status;
    uint32_t configured;
    uint32_t dimensions;
    uint32_t format_polarity;
    uint32_t mclk_hz;
    uint32_t registers_written;
} g_cam;

/* ------------------------------------------------------------------ UART -- */

static void usart1_send_byte(uint8_t byte)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXDE) == RESET) {
    }
    USART_SendData(USART1, byte);
}

static void usart1_send_data(const uint8_t *data, uint32_t length)
{
    while (length-- != 0U) {
        usart1_send_byte(*data++);
    }
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXC) == RESET) {
    }
}

static void usart1_send_text(const char *text)
{
    while (*text != '\0') {
        usart1_send_byte((uint8_t)*text++);
    }
}

static void usart1_send_hex32(uint32_t value)
{
    static const char digits[] = "0123456789ABCDEF";
    usart1_send_text("0x");
    for (int shift = 28; shift >= 0; shift -= 4) {
        usart1_send_byte((uint8_t)digits[(value >> (uint32_t)shift) & 0xFU]);
    }
}

static void usart1_send_dec(uint32_t value)
{
    char buffer[10];
    uint32_t index = 0U;
    if (value == 0U) {
        usart1_send_byte('0');
        return;
    }
    while (value != 0U && index < sizeof(buffer)) {
        buffer[index++] = (char)('0' + (value % 10U));
        value /= 10U;
    }
    while (index != 0U) {
        usart1_send_byte((uint8_t)buffer[--index]);
    }
}

/* --------------------------------------------------------------- Capture -- */

#define CAPTURE_ATTEMPT_FLAGS (DVP_FLAG_M1TC | DVP_FLAG_M1FO | \
    DVP_FLAG_AHBERR1 | DVP_FLAG_M1O | DVP_FLAG_CERR | DVP_FLAG_SERR | DVP_FLAG_M1S)

static uint8_t g_capture_active;
static int g_capture_result;
static uint32_t g_capture_started, g_capture_tick, g_capture_cycles;

static void dvp2_start_capture(void);
static void dvp2_poll_capture(void);

static uint32_t usart1_current_baud(void)
{
    return UART_BAUD;
}

static void dvp2_start_capture(void)
{
    if (g_capture_active) return;
    g_capture_active = 1U;
    g_capture_result = 0;
    g_capture_started = DWT_CYCCNT;
    g_capture_tick = mwTick;
    ++g_cam.attempts;
    MMU_EnableModuleMemory(MMU_MEMORY_DVP2, ENABLE);
    DVP_EnablePort(DVP2, DISABLE);
    DVP_EnableBuffer1(DVP2, DISABLE);
    DVP_ClearFlag(DVP2, CAPTURE_ATTEMPT_FLAGS);
    DVP_SetBuffer1Address(DVP2, (uint32_t)g_camera_frame);
    DVP_SetBufferSize(DVP2, CAMERA_FRAME_BYTES);
    DVP_EnableAcross1KBoundary(DVP2, ENABLE);
    DVP2->CTRL |= DVP_CAPTURE_MODE_SINGLE;
    DVP_EnableBuffer1(DVP2, ENABLE);
    DVP_EnablePort(DVP2, ENABLE);
}

static void dvp2_poll_capture(void)
{
    if (!g_capture_active || g_capture_result != 0) return;
    const uint32_t flags = DVP2->INTSTS;
    /* M1O precedes normal single-shot completion and is not a FIFO error. */
    if (flags & (DVP_FLAG_M1FO | DVP_FLAG_AHBERR1 |
                 DVP_FLAG_CERR | DVP_FLAG_SERR)) {
        g_capture_result = -1;
    } else if (flags & DVP_FLAG_M1TC) {
        g_capture_result = 1;
    } else if ((uint32_t)(mwTick - g_capture_tick) >= CAMERA_CAPTURE_TIMEOUT_MS) {
        g_capture_result = -1;
    }
    if (g_capture_result != 0) {
        g_capture_cycles = DWT_CYCCNT - g_capture_started;
        DVP_EnablePort(DVP2, DISABLE);
        DVP_EnableBuffer1(DVP2, DISABLE);
    }
}

static int dvp2_capture_one_frame(void)
{
    /* Consume a capture started during JPEG TX, or start one when idle. */
    dvp2_start_capture();
    while (g_capture_result == 0) dvp2_poll_capture();
    const int captured = g_capture_result > 0;

    g_cam.last_intsts = DVP2->INTSTS;
    g_cam.elapsed_ms = g_capture_cycles / (SystemCoreClock / 1000U);

    DVP_EnablePort(DVP2, DISABLE);
    DVP_EnableBuffer1(DVP2, DISABLE);
    DVP_ClearFlag(DVP2, CAPTURE_ATTEMPT_FLAGS);
    g_capture_active = 0U;

    if (captured) ++g_cam.successes;
    return captured;
}

/* While a JPEG payload streams out, arm the next capture with ~100 ms of
   wire time remaining so capture and transmission overlap.  Raw Y8 has no
   independent payload buffer, so it stays frozen until fully sent. */
static void usart1_send_camera_data(const uint8_t *data, uint32_t length,
                                    int overlap_capture)
{
    const uint32_t capture_at = usart1_current_baud() / 100U;
    while (length != 0U) {
        if (overlap_capture && length <= capture_at) {
            dvp2_start_capture();
            overlap_capture = 0;
        }
        dvp2_poll_capture();
        usart1_send_byte(*data++);
        --length;
    }
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXC) == RESET) {
        dvp2_poll_capture();
    }
}

/* ----------------------------------------------------------- Detection -- */

#define PERSON_FLAG_VALID 0x01U
#define PERSON_FLAG_PRESENT 0x02U

/* Defined with the rest of the command handling, below the capture loop, but
   the loop polls for commands from between its stages. */
static void usart1_poll_command(void);

/* Whether every fetched frame is also offered to the person detector.  'N'
   toggles it. */
static uint8_t g_person_enabled = 1U;
static uint8_t g_jpeg_enabled = 1U;

static uint8_t g_published_flags;
static uint8_t g_published_person_score;
static uint8_t g_published_no_person_score;
static uint32_t g_published_sequence;
static uint32_t g_result_copy_us;
static uint32_t g_result_preprocess_us;
static uint32_t g_result_invoke_us;
static uint32_t g_result_frame;
static uint32_t g_result_tick;

static void person_indicator_set(int person_present)
{
    /* PB3 is active-low: lit means a person is present. */
    if (person_present) {
        GPIO_ResetBits(GPIOB, GPIO_PIN_3);
    } else {
        GPIO_SetBits(GPIOB, GPIO_PIN_3);
    }
}

static void person_detector_toggle(void)
{
    if (g_m4_shared.person_init != 0U) {
        usart1_send_text("person-unavailable init_error=");
        usart1_send_dec(g_m4_shared.person_init);
        usart1_send_text("\r\n");
        return;
    }
    g_person_enabled = (uint8_t)(g_person_enabled == 0U ? 1U : 0U);
    g_m4_shared.person_control = ((g_m4_shared.person_control + 2U) & ~1U) |
        g_person_enabled;
    __DMB();
    g_published_flags = 0U;
    if (g_person_enabled == 0U) {
        /* With nothing classifying, the LED's state would be stale. */
        person_indicator_set(0);
    }
    usart1_send_text(g_person_enabled != 0U ? "person-on\r\n"
                                            : "person-off\r\n");
}

/* Capture and offer at most one snapshot per M7 request. Never wait for M7. */
static void person_detection_cycle(void)
{
    if (!dvp2_capture_one_frame()) {
        return;
    }
    ++g_published_sequence;
    if (g_published_sequence == 0U) ++g_published_sequence;
    uint32_t request = g_m4_shared.snapshot_request;
    if (g_person_enabled && request != g_m4_shared.snapshot_ready) {
        __DMB();
        _Static_assert(CAMERA_WIDTH == 2U * INFERENCE_WIDTH &&
                       CAMERA_HEIGHT == 2U * INFERENCE_HEIGHT,
                       "Preview must be twice the inference snapshot size");
        gray8_downsample2(g_camera_frame, g_inference_shared,
                            CAMERA_WIDTH, CAMERA_HEIGHT);
        g_m4_shared.snapshot_frame = g_published_sequence;
        g_m4_shared.snapshot_tick = mwTick;
        __DMB();
        g_m4_shared.snapshot_ready = request;
    }
}

static void read_inference_result(void)
{
    if (!g_person_enabled) {
        g_published_flags = 0U;
        person_indicator_set(0);
        return;
    }
    uint32_t version = g_m4_shared.result_version;
    if (version & 1U) return;
    __DMB();
    uint32_t control = g_m4_shared.result_control;
    uint32_t frame = g_m4_shared.result_frame;
    uint32_t tick = g_m4_shared.result_tick;
    uint32_t scores = g_m4_shared.result_scores;
    uint32_t flags = g_m4_shared.result_flags;
    uint32_t copy_us = g_m4_shared.result_copy_us;
    uint32_t preprocess_us = g_m4_shared.result_preprocess_us;
    uint32_t invoke_us = g_m4_shared.result_invoke_us;
    __DMB();
    /* A concurrent publication defers the update instead of stalling video. */
    if (version != g_m4_shared.result_version) return;
    if (control != g_m4_shared.person_control) flags = 0U;
    g_published_flags = flags;
    g_published_person_score = scores;
    g_published_no_person_score = scores >> 8;
    g_result_frame = frame;
    g_result_tick = tick;
    g_result_copy_us = copy_us;
    g_result_preprocess_us = preprocess_us;
    g_result_invoke_us = invoke_us;
    person_indicator_set((flags & PERSON_FLAG_PRESENT) != 0U);
}

static void write_le32(uint8_t *out, uint32_t value)
{
    for (uint32_t i = 0; i < 4U; ++i) out[i] = value >> (8U * i);
}

/* Reply to 'C' with the latest frame using the OV56 binary protocol.
   Format 9 is raw Y8, format 3 is grayscale JPEG.  Formats 10/8 extend the
   header to 44 bytes with the detection verdict and async timing. */
static void send_latest_frame(void)
{
    uint8_t header[44] = {
        'O', 'V', '5', '6', CAMERA_WIDTH & 0xFFU, CAMERA_WIDTH >> 8U,
        CAMERA_HEIGHT & 0xFFU, CAMERA_HEIGHT >> 8U,
        0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    };
    uint32_t header_length = 16U;
    uint8_t *payload = g_camera_frame;
    uint32_t payload_length = CAMERA_FRAME_BYTES;

    if (g_published_sequence == 0U) {
        /* A host polling before the loop's first cycle gets one capture. */
        person_detection_cycle();
        if (g_published_sequence == 0U) {
            usart1_send_text("CAPTURE-FAIL intsts=");
            usart1_send_hex32(g_cam.last_intsts);
            usart1_send_text(" elapsed_ms=");
            usart1_send_dec(g_cam.elapsed_ms);
            usart1_send_text("\r\n");
            return;
        }
    }
    if (g_jpeg_enabled) {
        /* Lazy init keeps boot independent of the encoder; failure preserves
           the raw Y8 payload and disables JPEG for the session. */
        if (jpeg_encoder_init() &&
            jpeg_encoder_encode_gray8(payload, &payload, &payload_length)) {
            header[8] = 3U;
        } else {
            g_jpeg_enabled = 0U;
        }
    }
    header[12] = (uint8_t)payload_length;
    header[13] = (uint8_t)(payload_length >> 8U);
    header[14] = (uint8_t)(payload_length >> 16U);
    header[15] = (uint8_t)(payload_length >> 24U);
    read_inference_result();
    if (g_person_enabled) {
        /* Formats 10/8 extend async metadata with copy/preprocess/invoke us. */
        header[8] = header[8] == 3U ? 8U : 10U;
        header[16] = g_published_person_score;
        header[17] = g_published_no_person_score;
        header[18] = 0U;
        header[19] = g_published_flags;
        write_le32(header + 20, g_published_sequence);
        write_le32(header + 24, g_result_frame);
        write_le32(header + 28, mwTick - g_result_tick);
        write_le32(header + 32, g_result_copy_us);
        write_le32(header + 36, g_result_preprocess_us);
        write_le32(header + 40, g_result_invoke_us);
        header_length = 44U;
    }
    usart1_send_data(header, header_length);
    usart1_send_camera_data(payload, payload_length,
                            header[8] == 3U || header[8] == 8U);
}

/* -------------------------------------------------------------- Commands -- */

/* Handle at most one pending command byte.  Called from the main loop only so
   two transmitters can never interleave. */
static void usart1_poll_command(void)
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXDNE) != SET) {
        return;
    }
    const uint8_t command = (uint8_t)USART_ReceiveData(USART1);
    if (command == 'C') {
        send_latest_frame();
    } else if (command == 'N') {
        person_detector_toggle();
    } else if (command == 'J') {
        g_jpeg_enabled = (uint8_t)(g_jpeg_enabled == 0U ? 1U : 0U);
        usart1_send_text(g_jpeg_enabled ? "jpeg-on\r\n" : "jpeg-off\r\n");
    }
}

/**
 * @brief  M4 camera main program.
 */
void camera_main(void)
{
    CPU_DELAY_INTI();

    /* OV5640 RESETB is active-low. Generate a real reset pulse rather than
       merely relying on PG6's power-up default, then allow SCCB to settle. */
    GPIO_ResetBits(GPIOG, GPIO_PIN_6);
    SysTick_Delayms(5);
    GPIO_SetBits(GPIOG, GPIO_PIN_6);
    SysTick_Delayms(50);
    ov5640_probe(&g_cam.ov_probe, &g_cam.ov_id, &g_cam.i2c_status);
    if (g_cam.ov_probe == 2U) {
        ov5640_configure_gray8(&g_cam.configured, &g_cam.dimensions,
                               &g_cam.format_polarity, &g_cam.mclk_hz,
                               &g_cam.registers_written, &g_cam.i2c_status);
    }

    /* Enable by policy, not a one-time sample of M7's asynchronous init.
       M7 waits for person_init == 0 before requesting any snapshots. */
    g_person_enabled = 1U;
    g_m4_shared.person_control = 2U | g_person_enabled;
    __DMB();
    person_indicator_set(0);

    while (1) {
        m4_service_mailbox();
        /* Answer whatever is pending before starting another capture, so a
           request is never held up by a cycle that has not begun yet. */
        usart1_poll_command();
        person_detection_cycle();
        read_inference_result();
    }
}
