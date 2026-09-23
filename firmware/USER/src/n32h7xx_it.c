/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file n32h7xx_it.c
 * @author N32cube
 */

/* NTFx CODE START */
#include "n32h7xx_it.h"
#include "n32h7xx.h"
/* NTFx CODE END */

/* NTFx CODE START */
extern __IO uint32_t mwTick;

typedef struct
{
    uint32_t magic;
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t xpsr;
    uint32_t exc_return;
    uint32_t cfsr;
    uint32_t hfsr;
    uint32_t mmfar;
    uint32_t bfar;
} HardFaultInfo;

/* Retained for SWD inspection while the handler is halted in its loop. */
volatile HardFaultInfo g_hardfault_info
    __attribute__((section(".m7_diagnostics"), aligned(32)));

__attribute__((used, noinline)) static void hardfault_capture(uint32_t *stacked,
                                                               uint32_t exc_return)
{
    /* Core registers start at SP; the optional FP extension follows them. */
    g_hardfault_info.r0 = stacked[0];
    g_hardfault_info.r1 = stacked[1];
    g_hardfault_info.r2 = stacked[2];
    g_hardfault_info.r3 = stacked[3];
    g_hardfault_info.r12 = stacked[4];
    g_hardfault_info.lr = stacked[5];
    g_hardfault_info.pc = stacked[6];
    g_hardfault_info.xpsr = stacked[7];
    g_hardfault_info.exc_return = exc_return;
    g_hardfault_info.cfsr = SCB->CFSR;
    g_hardfault_info.hfsr = SCB->HFSR;
    g_hardfault_info.mmfar = SCB->MMFAR;
    g_hardfault_info.bfar = SCB->BFAR;
    __DMB();
    g_hardfault_info.magic = 0x48464C54U; /* "HFLT" */
}
/**
 * @brief  This function handles NMI exception.
 */
void NMI_Handler(void)
{
/* NTFx CODE END */

}
/* NTFx CODE START */
/**
 * @brief  This function handles Hard Fault exception.
 */
__attribute__((naked)) void HardFault_Handler(void)
{
    __asm volatile(
        "tst lr, #4                     \n"
        "ite eq                         \n"
        "mrseq r0, msp                  \n"
        "mrsne r0, psp                  \n"
        "mov r1, lr                     \n"
        "bl hardfault_capture            \n"
        "1: bl m7_flash_poll            \n"
        "b 1b                           \n");
}
/* NTFx CODE START */
/**
 * @brief  This function handles Memory Manage exception.
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
/* NTFx CODE END */

    }
}
/* NTFx CODE START */
/**
 * @brief  This function handles Bus Fault exception.
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
/* NTFx CODE END */

    }
}
/* NTFx CODE START */
/**
 * @brief  This function handles Usage Fault exception.
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
/* NTFx CODE END */

    }
}
/* NTFx CODE START */
/**
 * @brief  This function handles SVCall exception.
 */
void SVC_Handler(void)
{
/* NTFx CODE END */

}
/* NTFx CODE START */
/**
 * @brief  This function handles Debug Monitor exception.
 */
void DebugMon_Handler(void)
{
/* NTFx CODE END */

}
/* NTFx CODE START */
/**
 * @brief  This function handles SysTick Handler.
 */
void SysTick_Handler(void)
{
    mwTick++;
/* NTFx CODE END */

}
