/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"
#include "m4_boot.h"
#include "m4_shared.h"
#include "m7_cache.h"
#include "person_detector.h"
#include <string.h>

uint8_t g_inference_shared[INFERENCE_FRAME_BYTES]
    __attribute__((section(".inference_shared"), aligned(32)));
static uint8_t g_inference_private[INFERENCE_FRAME_BYTES]
    __attribute__((section(".inference_private"), aligned(32)));

/* Compact run counters, readable through SWD (see `make benchmark`). */
typedef struct {
    uint32_t init_cycles;       /* +0  detector startup time */
    uint32_t init_error;        /* +4  0 when the model is ready */
    uint32_t input_type;        /* +8  model input tensor type */
    uint32_t output_type;       /* +12 model output tensor type */
    uint32_t sdram_status;      /* +16 0 when SDRAM is ready */
    uint32_t arena_bytes;       /* +20 tensor arena usage */
    uint32_t invoke_last_cycles;/* +24 last inference duration */
    uint32_t invoke_max_cycles; /* +28 worst observed duration */
    uint32_t scores;            /* +32 person/no_person int8 pair */
    uint32_t frames_ok;         /* +36 successful inference frames */
    uint32_t preprocess_cycles; /* +40 last preprocessing duration */
    uint32_t invoke_cycles;     /* +44 last TFLM invoke duration */
} model_benchmark_t;
volatile model_benchmark_t g_model_benchmark
    __attribute__((section(".m7_diagnostics"), aligned(32)));

static uint32_t request_snapshot(void)
{
    uint32_t next = g_m4_shared.snapshot_request + 1U;
    if (next == 0U) next = 1U;
    __DMB();
    g_m4_shared.snapshot_request = next;
    return next;
}

static void inference_cycle(void)
{
    static uint32_t ticket;
    static uint32_t requested_control;
    uint32_t control = g_m4_shared.person_control;
    if (g_m4_shared.person_init != 0U || (control & 1U) == 0U) return;
    if (ticket == 0U) {
        requested_control = control;
        ticket = request_snapshot();
        return;
    }
    if (g_m4_shared.snapshot_ready != ticket) return;
    __DMB();
    const uint32_t frame_control = requested_control;
    uint32_t frame = g_m4_shared.snapshot_frame;
    uint32_t tick = g_m4_shared.snapshot_tick;
    uint32_t started = DWT_CYCCNT;
    memcpy(g_inference_private, g_inference_shared, sizeof(g_inference_private));
    g_m4_shared.copy_cycles = DWT_CYCCNT - started;
    __DMB();
    g_m4_shared.snapshot_released = ticket;
    ticket = 0U;
    /* A toggle invalidates any snapshot or result from the preceding session. */
    if (g_m4_shared.person_control != frame_control) return;
    /* The private copy is immutable while M4 prepares the next shared frame. */
    ticket = request_snapshot();
    int8_t person = 0, no_person = 0;
    started = DWT_CYCCNT;
    int ok = person_detector_run_gray8(g_inference_private,
        INFERENCE_WIDTH, INFERENCE_HEIGHT, &person, &no_person);
    uint32_t elapsed = DWT_CYCCNT - started;
    g_model_benchmark.invoke_last_cycles = elapsed;
    if (elapsed > g_model_benchmark.invoke_max_cycles)
        g_model_benchmark.invoke_max_cycles = elapsed;
    g_model_benchmark.scores = (uint8_t)person | ((uint32_t)(uint8_t)no_person << 8);
    if (ok) ++g_model_benchmark.frames_ok;
    g_model_benchmark.preprocess_cycles = person_preprocess_cycles;
    g_model_benchmark.invoke_cycles = person_invoke_cycles;
    if (g_m4_shared.person_control != frame_control) return;
    ++g_m4_shared.result_version;
    __DMB();
    g_m4_shared.result_control = frame_control;
    g_m4_shared.result_frame = frame;
    g_m4_shared.result_tick = tick;
    g_m4_shared.result_scores = g_model_benchmark.scores;
    g_m4_shared.result_flags = ok ? (1U | (person > no_person ? 2U : 0U)) : 0U;
    uint32_t cycles_per_us = SystemCoreClock / 1000000U;
    g_m4_shared.result_copy_us = g_m4_shared.copy_cycles / cycles_per_us;
    g_m4_shared.result_preprocess_us = person_preprocess_cycles / cycles_per_us;
    g_m4_shared.result_invoke_us = person_invoke_cycles / cycles_per_us;
    __DMB();
    ++g_m4_shared.result_version;
}

int main(void)
{
    SCB->VTOR = 0x15000000UL;
    __DSB();
    __ISB();
    /* M7 owns chip-wide setup; only M4 touches camera/JPEG/UART afterwards. */
    PWR_Configuration();
    RCC_Configuration();
    GPIO_Configuration();
    DMA_Configuration();
    I2C_Configuration();
    USART_Configuration();
    DVP_Configuration();
    SysTick_Config(600000U);
    NVIC_Configuration();
    CPU_DELAY_INTI();
    /* Initialise SDRAM before M4/cache start. */
    SDRAM_Configuration();
    g_model_benchmark.sdram_status = board_sdram_status();
    uint32_t started = DWT_CYCCNT;
    int initialized = person_detector_init();
    g_model_benchmark.init_cycles = DWT_CYCCNT - started;
    g_model_benchmark.init_error = initialized ? 0U
        : (uint32_t)person_detector_init_error;
    g_model_benchmark.input_type = person_detector_input_type;
    g_model_benchmark.output_type = person_detector_output_type;
    g_model_benchmark.arena_bytes = person_arena_bytes;
    m4_start();
    if (g_m4_status == 1U) {
        m7_cache_enable();
        __DMB();
        g_m4_shared.person_init = g_model_benchmark.init_error;
    }
    uint32_t heartbeat_tick = 0U;
    extern volatile uint32_t mwTick;
    for (;;) {
        m7_flash_poll();
        m4_poll();
        g_m4_shared.boot_status = g_m4_status;
        g_m4_shared.boot_checks = g_m4_checks;
        g_m4_shared.boot_errors = g_m4_errors;
        if ((uint32_t)(mwTick - heartbeat_tick) >= 200U) {
            heartbeat_tick = mwTick;
            GPIO_TogglePin(GPIOI, GPIO_PIN_8);
        }
        if (g_m4_status == 2U) inference_cycle();
        /* Keep the M7-owned AXI/peripheral clocks active while M4 captures. */
        __NOP();
    }
}
