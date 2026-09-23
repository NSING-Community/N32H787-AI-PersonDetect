/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "n32h7xx.h"
#include "m4_shared.h"
#include "n32h7xx_dvp.h"
#include "jpeg_encoder.h"

volatile m4_shared_t g_m4_shared
    __attribute__((section(".m4_shared"), aligned(32)));
static uint32_t ram_vectors[256]
    __attribute__((section(".m4_vectors"), aligned(1024)));
extern const uint32_t g_pfnVectors[];
static volatile uint32_t data_cookie = 0x1234abcdUL;
static volatile uint32_t bss_cookie;
uint32_t SystemCoreClock;
extern volatile uint32_t mwTick;
uint8_t g_inference_shared[INFERENCE_FRAME_BYTES]
    __attribute__((section(".inference_shared"), aligned(32)));

/* M7 owns clocks/power. Do not run the shared vendor clock/TCM setup here. */
void SystemInit(void)
{
    SCB->CPACR |= (3UL << 20) | (3UL << 22);
    /* Keep interrupt entry independent of Flash while M7 runs FlashOS. */
    for (uint32_t i = 0; i < 256U; ++i) ram_vectors[i] = g_pfnVectors[i];
    SCB->VTOR = (uint32_t)ram_vectors;
    __DSB();
    __ISB();
}

void SysTick_Handler(void)
{
    ++g_m4_shared.heartbeat;
    ++mwTick;
}

void m4_service_mailbox(void)
{
    /* Called between captures/transfers. Stop all masters before FlashOS. */
    if (g_m4_shared.flash_pause == M4_SHARED_MAGIC) {
        DVP_EnablePort(DVP2, DISABLE);
        DVP_EnableBuffer1(DVP2, DISABLE);
        jpeg_encoder_stop();
        __disable_irq();
        __DSB();
        g_m4_shared.flash_paused = M4_SHARED_MAGIC;
        __DSB();
        /* FlashOS still needs the shared bus clocks while this core is parked. */
        for (;;) __NOP();
    }
    uint32_t sequence = g_m4_shared.request;
    if (sequence != g_m4_shared.response) {
        __DMB();
        for (uint32_t i = 0; i < M4_SHARED_WORDS; ++i)
            g_m4_shared.output[i] = m4_test_reply(g_m4_shared.input[i]);
        __DMB();
        g_m4_shared.response = sequence;
    }
}

void HardFault_Handler(void)
{
    g_m4_shared.cfsr = SCB->CFSR;
    __DMB();
    g_m4_shared.fault = 0x48464c54UL;
    for (;;) __WFI();
}

int main(void)
{
    g_m4_shared.cpuid = SCB->CPUID;
    g_m4_shared.vtor = SCB->VTOR;
    if (g_m4_shared.magic != M4_SHARED_MAGIC || data_cookie != 0x1234abcdUL ||
        bss_cookie != 0U || g_m4_shared.clock_hz < 1000U ||
        SysTick_Config(g_m4_shared.clock_hz / 1000U) != 0U) {
        g_m4_shared.fault = 1U;
        for (;;) __WFI();
    }
    bss_cookie = 1U;
    SystemCoreClock = g_m4_shared.clock_hz;
    __DMB();
    g_m4_shared.ready = M4_SHARED_MAGIC;
    camera_main();
    for (;;) __WFI();
}


