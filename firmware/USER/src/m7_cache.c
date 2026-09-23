/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "n32h7xx.h"
#include "m4_shared.h"
#include "m7_cache.h"
#include "board_sdram.h"

#if !defined(__DCACHE_PRESENT) || __DCACHE_PRESENT != 1U
#error M7 requires the CMSIS D-Cache feature macro
#endif

static void region(uint32_t index, uint32_t address, uint32_t size_log2,
                   uint32_t attributes)
{
    MPU->RNR = index;
    MPU->RBAR = address;
    MPU->RASR = attributes | ((size_log2 - 1U) << MPU_RASR_SIZE_Pos) |
                MPU_RASR_ENABLE_Msk;
}

void m7_cache_enable(void)
{
    /* Cold boot must not clean uninitialised cache ways. */
    if (SCB->CCR & SCB_CCR_DC_Msk) SCB_DisableDCache();
    __DMB();
    MPU->CTRL = 0U;
    for (uint32_t i = 0; i < ((MPU->TYPE >> 8) & 0xffU); ++i) {
        MPU->RNR = i;
        MPU->RASR = 0U;
    }
    const uint32_t rw = 3U << MPU_RASR_AP_Pos;
    const uint32_t normal = 1U << MPU_RASR_TEX_Pos;
    const uint32_t nc = rw | normal | MPU_RASR_S_Msk | MPU_RASR_XN_Msk;
    const uint32_t wb = normal | MPU_RASR_C_Msk | MPU_RASR_B_Msk;
    /* M4 code/data, mailbox and snapshot; M7 never executes in AHB SRAM. */
    region(0, 0x30000000U, 19U, nc);
    /* DVP/JPEG DMA workspace, with an overriding M7-only 8 KiB region. */
    region(1, 0x24000000U, 19U, nc);
    region(2, 0x2401e000U, 13U, rw | wb | MPU_RASR_XN_Msk);
    /* This board's Flash mapping returned displaced words on D-cache fills.
       Keep Flash uncached until its burst configuration is verified. */
    region(3, 0x15000000U, 21U, (6U << MPU_RASR_AP_Pos) | normal);
    if (board_sdram_status() == 0U)
        region(4, BOARD_SDRAM_BASE, 25U, rw | wb | MPU_RASR_XN_Msk);
    MPU->CTRL = MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_ENABLE_Msk;
    __DSB();
    __ISB();
    SCB_EnableDCache();
    g_m4_shared.m7_cache_ccr = SCB->CCR;
    g_m4_shared.m7_clock_hz = SystemCoreClock;
    __DMB();
    g_m4_shared.m7_flash_abi = M7_FLASH_ABI;
}

void m7_flash_poll(void)
{
    if (g_m4_shared.flash_pause != M4_SHARED_MAGIC) return;
    /* Called only between inferences. M4 independently stops its bus masters.
       Ack is non-cacheable and becomes visible only after writeback completes. */
    __disable_irq();
    if (SCB->CCR & SCB_CCR_DC_Msk) SCB_DisableDCache();
    if (SCB->CCR & SCB_CCR_IC_Msk) SCB_DisableICache();
    __DSB();
    g_m4_shared.m7_flash_paused = M4_SHARED_MAGIC;
    __DSB();
    for (;;) __NOP();
}
