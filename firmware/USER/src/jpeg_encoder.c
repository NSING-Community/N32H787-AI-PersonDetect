/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "jpeg_encoder.h"
#include "ov5640.h"

#include "n32h7xx_pwr.h"
#include "n32h7xx_rcc.h"
#include <string.h>

#define JPEG_WIDTH OV5640_WIDTH
#define JPEG_HEIGHT OV5640_HEIGHT
#define JPEG_GRAY_BYTES (JPEG_WIDTH * JPEG_HEIGHT)
#define JPEG_OUTPUT_CAPACITY (64U * 1024U)
#define JPEG_QUALITY 80U
#define JPEG_RBC_BLOCK_LINES 3U
#define JPEG_RBC_BUFFER_BYTES (JPEG_WIDTH * 8U * JPEG_RBC_BLOCK_LINES)
#define JPEG_WAIT_CYCLES (SystemCoreClock / 5U)
#define JPEG_DMA_ERRORS (SGDMA_INTSTS_WDATAERREN | SGDMA_INTSTS_RDATAERR | \
                         SGDMA_INTSTS_WDESCERR | SGDMA_INTSTS_RDESCERR)

/* Output/RBC/descriptors use AXI SRAM1; SGDMA reads the AHB camera frame. */
static uint8_t g_jpeg_output[JPEG_OUTPUT_CAPACITY]
    __attribute__((section(".camera_dma"), aligned(32)));
static uint8_t g_jpeg_rbc_buffer[JPEG_RBC_BUFFER_BYTES]
    __attribute__((section(".camera_dma"), aligned(32)));

/* SGDMA reads descriptors from AXI SRAM. The vendor example uses memory mode,
   which lets P2H update blk_used with the exact variable output length. */
static SGDMA_H2P_InitType g_h2p __attribute__((section(".camera_dma"), aligned(8)));
static SGDMA_P2H_InitType g_p2h __attribute__((section(".camera_dma"), aligned(8)));

static uint8_t g_initialized;
static uint32_t g_last_cycles;
static uint32_t g_last_color_cycles;
static uint32_t g_last_bytes;
static uint32_t g_last_h2p_status;
static uint32_t g_last_p2h_status;

static void configure_descriptors(const uint8_t *gray8)
{
    memset(&g_h2p, 0, sizeof(g_h2p));
    g_h2p.h2p_desc.desc_flags.bits.startframe = BITEQ1;
    g_h2p.h2p_desc.desc_flags.bits.endframe = BITEQ1;
    g_h2p.h2p_desc.blk_size = JPEG_GRAY_BYTES;
    g_h2p.h2p_desc.blk_addr_low = (uint32_t)gray8;
    g_h2p.max_burstsize = 0x80U;
    g_h2p.SGlist_size = 1U;
    g_h2p.desclist_type = SGDMA_DESCLIST_LIST;
    g_h2p.descstored_type = SGDMA_DESC_MEMORY;
    g_h2p.DMA_EOF_type = SGDMA_EOF_PAUSEDMA;
    g_h2p.DMA_burst_type = SGDMA_BURST_INCR;

    memset(&g_p2h, 0, sizeof(g_p2h));
    g_p2h.p2h_desc.desc_flags.bits.startframe = BITEQ1;
    g_p2h.p2h_desc.desc_flags.bits.endframe = BITEQ1;
    g_p2h.p2h_desc.blk_size = JPEG_OUTPUT_CAPACITY;
    g_p2h.p2h_desc.blk_addr_low = (uint32_t)g_jpeg_output;
    g_p2h.max_burstsize = 0x80U;
    g_p2h.SGlist_size = 1U;
    g_p2h.desclist_type = SGDMA_DESCLIST_LIST;
    g_p2h.descstored_type = SGDMA_DESC_MEMORY;
    g_p2h.DMA_EOF_type = SGDMA_EOF_PAUSEDMA;
    g_p2h.DMA_burst_type = SGDMA_BURST_INCR;
}

void jpeg_encoder_stop(void)
{
    if (!g_initialized) return;
    SGDMA_Reset(JPEG_SGDMA_H2P);
    SGDMA_Reset(JPEG_SGDMA_P2H);
    JPEGRBC_Enable(DISABLE);
    JPEG_ENC->CTRL &= ~JPEGENC_CTRL_EN;
    __DSB();
    g_initialized = 0U;
}

int jpeg_encoder_init(void)
{
    JPEGRBC_InitType rbc;
    const uint32_t started = DWT_CYCCNT;

    g_initialized = 0U;
    /* The camera already powers the shared graphics domain. Never wait forever
       in the vendor power helper or silently enable a cache-incoherent path. */
    if ((PWR->SYSCTRL3 & PWR_SYSCTRL3_GRC_PWRRDY) == 0U) {
        return 0;
    }
#ifdef CORE_CM4
    RCC_EnableAXIPeriphClk1(RCC_AXI_PERIPHEN_M4_JPEGE |
                           RCC_AXI_PERIPHEN_M4_JPEGELP, ENABLE);
#else
    if ((SCB->CCR & (SCB_CCR_DC_Msk | SCB_CCR_IC_Msk)) != 0U) return 0;
    RCC_EnableAXIPeriphClk1(RCC_AXI_PERIPHEN_M7_JPEGE |
                             RCC_AXI_PERIPHEN_M7_JPEGELP, ENABLE);
#endif
    PWR->IPMEMCTRL &= ~PWR_IPMEMCTRL_JPEG_PWREN;
    while ((PWR->IPMEMCTRLSTS & PWR_IPMEMCTRLSTS_JPEG_PWRRDY) == 0U) {
        if ((uint32_t)(DWT_CYCCNT - started) >= JPEG_WAIT_CYCLES) return 0;
    }
    JPEG_ConfigType(JPEG_ENCODE);
    JPEGRBC_Enable(DISABLE);
    /* SDK 1.2 JPEGENC_Enable(DISABLE) clears HSEL rather than CTRL. */
    JPEG_ENC->CTRL &= ~JPEGENC_CTRL_EN;
    JPEG_ENC->CTRL |= JPEGENC_CTRL_ERST;
    __DSB();
    JPEG_ENC->CTRL &= ~JPEGENC_CTRL_ERST;
    jpeg_encoder_config_tables(JPEG_WIDTH, JPEG_HEIGHT, JPEG_QUALITY);
    JPEGENC_Enable(ENABLE);

    memset(&rbc, 0, sizeof(rbc));
    rbc.pixel_format = JPEGRBC_MONOCHROME;
    rbc.sample_order = JPEGRBC_MSBSAMPLE;
    rbc.frame_width = JPEG_WIDTH;
    rbc.frame_height = JPEG_HEIGHT;
    rbc.component0names = 0U;
    rbc.component1names = 1U;
    rbc.component2names = 2U;
    /* C0EADD stores block-line count minus one, not a byte end address. */
    rbc.C0startaddress = (uint32_t)g_jpeg_rbc_buffer;
    rbc.C0buffersize = JPEG_RBC_BLOCK_LINES - 1U;
    if (JPEGRBC_Init(&rbc) != SUCCESS) {
        return 0;
    }
    JPEGRBC_Enable(ENABLE);
    g_initialized = 1U;
    return 1;
}

int jpeg_encoder_encode_gray8(const uint8_t *gray8, uint8_t **jpeg_data,
                                 uint32_t *jpeg_size)
{
    const uint32_t started = DWT_CYCCNT;
    uint32_t size;

    g_last_color_cycles = 0U;
    if (g_initialized == 0U || gray8 == NULL || jpeg_data == NULL || jpeg_size == NULL) {
        return 0;
    }
    configure_descriptors(gray8);
    SGDMA_H2P_Init(&g_h2p);
    SGDMA_P2H_Init(&g_p2h);
    __DSB();
    SGDMA_Start(JPEG_SGDMA_P2H);
    SGDMA_Start(JPEG_SGDMA_H2P);

    while (SGDMAx_GetFlagStatus(JPEG_SGDMA_H2P, SGDMA_INTSTS_BUSY) == SET ||
           SGDMAx_GetFlagStatus(JPEG_SGDMA_P2H, SGDMA_INTSTS_BUSY) == SET) {
        if ((uint32_t)(DWT_CYCCNT - started) >= JPEG_WAIT_CYCLES ||
            ((JPEG_SGDMA_H2P->INTSTS | JPEG_SGDMA_P2H->INTSTS) & JPEG_DMA_ERRORS)) {
            goto failed;
        }
    }

    g_last_h2p_status = JPEG_SGDMA_H2P->INTSTS;
    g_last_p2h_status = JPEG_SGDMA_P2H->INTSTS;
    __DSB();
    size = *(volatile uint32_t *)&g_p2h.p2h_desc.blk_used;
    g_last_cycles = DWT_CYCCNT - started;
    g_last_bytes = size;
    if (((g_last_h2p_status | g_last_p2h_status) & JPEG_DMA_ERRORS) ||
        size < 4U || size > JPEG_OUTPUT_CAPACITY ||
        g_jpeg_output[0] != 0xFFU || g_jpeg_output[1] != 0xD8U ||
        g_jpeg_output[size - 2U] != 0xFFU || g_jpeg_output[size - 1U] != 0xD9U) {
        goto failed;
    }
    *jpeg_data = g_jpeg_output;
    *jpeg_size = size;
    return 1;

failed:
    g_last_h2p_status = JPEG_SGDMA_H2P->INTSTS;
    g_last_p2h_status = JPEG_SGDMA_P2H->INTSTS;
    g_last_cycles = DWT_CYCCNT - started;
    g_last_bytes = 0U;
    SGDMA_Reset(JPEG_SGDMA_H2P);
    SGDMA_Reset(JPEG_SGDMA_P2H);
    g_initialized = 0U;
    return 0;
}

void jpeg_encoder_get_diagnostics(uint32_t *color_cycles, uint32_t *last_cycles, uint32_t *last_bytes,
                                  uint32_t *h2p_status, uint32_t *p2h_status)
{
    *color_cycles = g_last_color_cycles;
    *last_cycles = g_last_cycles;
    *last_bytes = g_last_bytes;
    *h2p_status = g_last_h2p_status;
    *p2h_status = g_last_p2h_status;
}
