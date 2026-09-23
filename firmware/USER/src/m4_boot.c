/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "n32h7xx.h"
#include "n32h7xx_rcc.h"
#include "m4_boot.h"
#include "m4_shared.h"
#include "board_sdram.h"

volatile m4_shared_t g_m4_shared
    __attribute__((section(".m4_shared"), aligned(32)));
volatile uint32_t g_m4_status;
volatile uint32_t g_m4_checks;
volatile uint32_t g_m4_errors;
extern volatile uint32_t mwTick;
static uint32_t request_time;
static uint32_t last_heartbeat;

static void submit_request(void)
{
    uint32_t sequence = g_m4_shared.request + 1U;
    if (sequence == 0U) sequence = 1U;
    for (uint32_t i = 0; i < M4_SHARED_WORDS; ++i) {
        g_m4_shared.input[i] = m4_test_word(sequence, i);
    }
    __DMB();
    g_m4_shared.request = sequence;
    request_time = mwTick;
}

void m4_start(void)
{
    const volatile uint32_t *vectors = (const uint32_t *)M4_BOOT_ADDRESS;
    RCC_ClocksTypeDef clocks;
    /* Do not overwrite memory owned by a core left running by a core-only reset. */
    if ((RCC->M4RSTREL & RCC_RSTEN_M4REL) != 0U ||
        (SCB->CCR & SCB_CCR_DC_Msk) != 0U) {
        g_m4_status = 0xe4U;
        return;
    }
    if (vectors[0] != 0x30022000UL || (vectors[1] & 1U) == 0U ||
        vectors[1] < M4_BOOT_ADDRESS || vectors[1] >= M4_BOOT_ADDRESS + 0x80000U) {
        g_m4_status = 0xe1U;
        return;
    }
    RCC_EnableCFG2PeriphClk1(RCC_CFG2_PERIPHEN_M7_SRAM1 |
                           RCC_CFG2_PERIPHEN_M4_SRAM1 |
                           RCC_CFG2_PERIPHEN_M7_SRAM2 |
                           RCC_CFG2_PERIPHEN_M4_SRAM2 |
                           RCC_CFG2_PERIPHEN_M4_SRAM3, ENABLE);
    RCC_EnableAXIPeriphClk3(RCC_AXI_PERIPHEN_M4_TASRAM2, ENABLE);
    RCC_EnableAXIPeriphClk2(RCC_AXI_PERIPHEN_M4_DVP2APB |
                           RCC_AXI_PERIPHEN_M4_DVP2, ENABLE);
    RCC_EnableAPB2PeriphClk2(RCC_APB2_PERIPHEN_M4_I2C4, ENABLE);
    RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M4_USART1, ENABLE);
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M4_GPIOA |
        RCC_AHB5_PERIPHEN_M4_GPIOB | RCC_AHB5_PERIPHEN_M4_GPIOC |
        RCC_AHB5_PERIPHEN_M4_GPIOD | RCC_AHB5_PERIPHEN_M4_GPIOE |
        RCC_AHB5_PERIPHEN_M4_GPIOF | RCC_AHB5_PERIPHEN_M4_GPIOG |
        RCC_AHB5_PERIPHEN_M4_GPIOH, ENABLE);
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M4_GPIOI, ENABLE);
    RCC_ConfigM4SystickClkDivider(RCC_STCLK_DIV1);
    RCC_GetClocksFreqValue(&clocks);
    volatile uint32_t *words = (volatile uint32_t *)&g_m4_shared;
    for (uint32_t i = 0; i < sizeof(g_m4_shared) / sizeof(uint32_t); ++i) {
        words[i] = 0U;
    }
    g_m4_shared.clock_hz = clocks.M4ClkFreq;
    g_m4_shared.magic = M4_SHARED_MAGIC;
    g_m4_shared.person_init = 0xffffffffU;
    g_m4_shared.sdram_status = board_sdram_status();
    submit_request();
    g_m4_status = 1U;
    __DSB();
    RCC_EnableCM4(M4_BOOT_ADDRESS);
    __DSB();
}

void m4_poll(void)
{
    if (g_m4_status != 1U && g_m4_status != 2U) return;
    if (g_m4_shared.fault != 0U) {
        g_m4_status = 0xe3U;
        ++g_m4_errors;
        return;
    }
    if (g_m4_shared.ready == M4_SHARED_MAGIC &&
        g_m4_shared.response == g_m4_shared.request &&
        g_m4_shared.heartbeat != last_heartbeat) {
        __DMB();
        uint32_t sequence = g_m4_shared.request;
        for (uint32_t i = 0; i < M4_SHARED_WORDS; ++i) {
            if (g_m4_shared.output[i] != m4_test_reply(m4_test_word(sequence, i))) {
                g_m4_status = 0xe3U;
                ++g_m4_errors;
                return;
            }
        }
        ++g_m4_checks;
        last_heartbeat = g_m4_shared.heartbeat;
        g_m4_status = 2U;
        submit_request();
    } else if ((uint32_t)(mwTick - request_time) > 5000U) {
        g_m4_status = 0xe2U;
        ++g_m4_errors;
    }
}
