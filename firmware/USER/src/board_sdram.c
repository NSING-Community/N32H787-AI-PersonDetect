/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "board_sdram.h"
#include "n32h7xx.h"
#include "n32h7xx_gpio.h"
#include "n32h7xx_rcc.h"
#include "n32h7xx_sdram.h"

/* N32H787 HMI V1.1, IS42S32800J-6BLI. Same 57 AF0 pins as the tested bench. */
#define SD_PIN(port, pin) {GPIO##port, GPIO_PIN_##pin, AFIO_HIGH_SPEED_IO_P##port##pin}
static const struct {
    GPIO_Module *port;
    uint32_t pin;
    AFIO_HIGH_SPEED_PIN hs;
} pins[] = {
    SD_PIN(F, 0), SD_PIN(F, 1), SD_PIN(F, 2), SD_PIN(F, 3),
    SD_PIN(F, 4), SD_PIN(F, 5), SD_PIN(F, 12), SD_PIN(F, 13),
    SD_PIN(F, 14), SD_PIN(F, 15), SD_PIN(G, 0), SD_PIN(G, 1), SD_PIN(G, 2),
    SD_PIN(G, 4), SD_PIN(G, 5), /* BA0, BA1 */
    SD_PIN(D, 14), SD_PIN(D, 15), SD_PIN(D, 0), SD_PIN(D, 1),
    SD_PIN(E, 7), SD_PIN(E, 8), SD_PIN(E, 9), SD_PIN(E, 10),
    SD_PIN(E, 11), SD_PIN(E, 12), SD_PIN(E, 13), SD_PIN(E, 14), SD_PIN(E, 15),
    SD_PIN(D, 8), SD_PIN(D, 9), SD_PIN(D, 10),
    SD_PIN(H, 8), SD_PIN(H, 9), SD_PIN(H, 10), SD_PIN(H, 11),
    SD_PIN(H, 12), SD_PIN(H, 13), SD_PIN(H, 14), SD_PIN(H, 15),
    SD_PIN(I, 0), SD_PIN(I, 1), SD_PIN(I, 2), SD_PIN(I, 3),
    SD_PIN(I, 6), SD_PIN(I, 7), SD_PIN(I, 9), SD_PIN(I, 10),
    SD_PIN(E, 0), SD_PIN(E, 1), SD_PIN(I, 4), SD_PIN(I, 5), /* DQM */
    SD_PIN(C, 2), SD_PIN(C, 0), SD_PIN(F, 11), SD_PIN(G, 15),
    SD_PIN(H, 2), SD_PIN(G, 8)
};

static uint32_t status = UINT32_MAX;
volatile uint32_t g_sdram_error_address, g_sdram_error_expected, g_sdram_error_actual;

uint32_t board_sdram_status(void) { return status; }

static void delay_us(uint32_t hz, uint32_t us)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->LAR = 0xc5acce55U;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    __DSB(); __ISB();
    uint32_t start = DWT->CYCCNT;
    while ((uint32_t)(DWT->CYCCNT - start) < (hz / 1000000U) * us) {
        /* Keep the wait live if a debugger detaches during startup. */
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    }
}

static void command(uint32_t opcode, uint32_t address)
{
    SDRAM_EnableClock(ENABLE);
    SDRAM_SetOperationCode(opcode);
    SDRAM_SetDeviceSelect(SDRAM_CS_SDRAM1_ONLY);
    SDRAM_SetBank(SDRAM_BANKADD_1);
    SDRAM_SetAddress(address);
    (void)SDRAM->OR;
    __DSB();
}

static bool check_word(volatile uint32_t *p, uint32_t expected)
{
    __DSB();
    SDRAM->CBO = 0;
    (void)SDRAM->CBO;
    __DSB();
    uint32_t actual = *p;
    if (actual == expected) return true;
    g_sdram_error_address = (uint32_t)p;
    g_sdram_error_expected = expected;
    g_sdram_error_actual = actual;
    return false;
}

static bool self_test(void)
{
    volatile uint32_t *p = (volatile uint32_t *)BOARD_SDRAM_BASE;
    const uint32_t words = BOARD_SDRAM_BYTES / 4U;
    /* Sparse address-line test across the entire device, then 4 KiB per bank.
       Full-capacity stress/retention testing remains in the standalone bench. */
    p[0] = 0x55555555U;
    for (uint32_t bit = 1; bit < words; bit <<= 1) p[bit] = 0xaaaaaaaaU;
    for (uint32_t test = 1; test < words; test <<= 1) {
        p[test] = 0x55555555U;
        if (!check_word(p, 0x55555555U)) return false;
        for (uint32_t bit = 1; bit < words; bit <<= 1)
            if (!check_word(p + bit, bit == test ? 0x55555555U : 0xaaaaaaaaU)) return false;
        p[test] = 0xaaaaaaaaU;
    }
    for (uint32_t base = 0; base < words; base += words / 4U) {
        for (unsigned pass = 0; pass < 2; ++pass) {
            for (uint32_t i = 0; i < 1024; ++i) {
                uint32_t value = 0x5aa53cc3U ^ ((base + i) * 0x9e3779b9U);
                p[base + i] = pass ? ~value : value;
            }
            __DSB();
            for (uint32_t i = 0; i < 1024; ++i) {
                uint32_t value = 0x5aa53cc3U ^ ((base + i) * 0x9e3779b9U);
                if (!check_word(p + base + i, pass ? ~value : value)) return false;
            }
        }
    }
    p[words - 1U] = 0x12345678U;
    return check_word(p + words - 1U, 0x12345678U);
}

bool SDRAM_Configuration(void)
{
    if (status == 0U) return true;
    if ((SCB->CCR & SCB_CCR_DC_Msk) || (RCC->M4RSTREL & RCC_M4RSTREL_EN)) {
        status = 2U;
        return false;
    }
    status = 1U;
    RCC_ConfigHse(RCC_HSE_ENABLE);
    if (RCC_WaitHseStable() != SUCCESS) return false;
    if (RCC_ConfigPll3(RCC_PLL_SRC_HSE, HSE_VALUE,
                      (uint64_t)BOARD_SDRAM_HZ * 5U, ENABLE) != SUCCESS) return false;
    RCC_ConfigPLL3ADivider(RCC_PLLA_DIV5);
    RCC_ClocksTypeDef clocks = {0};
    RCC_GetClocksFreqValue(&clocks);
    if (clocks.PLL3AClkFreq != BOARD_SDRAM_HZ) return false;
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOC | RCC_AHB5_PERIPHEN_M7_GPIOD |
        RCC_AHB5_PERIPHEN_M7_GPIOE | RCC_AHB5_PERIPHEN_M7_GPIOF |
        RCC_AHB5_PERIPHEN_M7_GPIOG | RCC_AHB5_PERIPHEN_M7_GPIOH, ENABLE);
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_GPIOI | RCC_AHB5_PERIPHEN_M7_AFIO, ENABLE);
    GPIO_InitType gpio;
    GPIO_InitStruct(&gpio);
    gpio.GPIO_Mode = GPIO_MODE_AF_PP;
    gpio.GPIO_Alternate = GPIO_AF0;
    gpio.GPIO_Pull = GPIO_NO_PULL;
    gpio.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    gpio.GPIO_Current = GPIO_DC_2mA;
    for (unsigned i = 0; i < sizeof(pins) / sizeof(pins[0]); ++i) {
        gpio.Pin = pins[i].pin;
        GPIO_InitPeripheral(pins[i].port, &gpio);
        AFIO_ConfigHSMODE(pins[i].port, pins[i].pin, ENABLE);
        AFIO_ConfigHSMODEVREFRemap(pins[i].hs, ENABLE);
        AFIO_ConfigHSPortDSNRemap(pins[i].hs, ENABLE);
        AFIO_ConfigHSPortDSPRemap(pins[i].hs, ENABLE);
    }
    RCC_ConfigSDRAMMemClk(RCC_SDRAMMEMCLK_SRC_PLL3A, RCC_SDRAMMEMCLK_AXIDIV1);
    RCC_EnableAXIPeriphClk4(RCC_AXI_PERIPHEN_M7_SDRAM | RCC_AXI_PERIPHEN_M7_SDRAMLP, ENABLE);
    SDRAM_DeInit();
    RCC_ConfigSDRAMDelay(RCC_SDRAM_DELAY_0_2NS);
    RCC_EnableSDRAMDelayChain(ENABLE);
    SDRAM_EnableAddressRemap(DISABLE);
    /* N32H7xx UM 6.6.7-13: registers encode cycles - 1.
       IS42S32800J-6 Rev C p16, validated at 133MHz in the standalone bench:
       RAS/RC/RRD/RP/WR/RFC/RCD = 6/9/2/3/2/9/3 cycles.
       Keep CL3 and one extra cycle on RC/RFC; BL2 = 64 / bus width. */
    SDRAM_TimingType timing = {5, 8, 1, 2, 1, 8, 2};
    SDRAM_TimingInit(&timing);
    SDRAM_RefreshIntervalInit(BOARD_SDRAM_REFRESH_CYCLES);
    SDRAM_SetDeviceAddress(SDRAM_DEVICE_1, BOARD_SDRAM_BASE, ~(BOARD_SDRAM_BYTES - 1U));
    SDRAM_EnableDevice(SDRAM_DEVICE_2, DISABLE);
    SDRAM_EnableDevice(SDRAM_DEVICE_1, ENABLE);
    SDRAM_EnableRefreshCMD(SDRAM_DEVICE_1, DISABLE);
    SDRAM_EnableAutoPrecharge(SDRAM_DEVICE_1, DISABLE);
    SDRAM_EnablePrefetchRead(SDRAM_DEVICE_1, DISABLE);
    SDRAM_EnableSOM(SDRAM_DEVICE_1, ENABLE);
    SDRAM_EnableBankInterleave(SDRAM_DEVICE_1, DISABLE);
    SDRAM_ConfigBusWidth(SDRAM_DEVICE_1, SDRAM_DEVICE_BUSWID_32BITS);
    SDRAM_ConfigBurstLength(SDRAM_DEVICE_1, SDRAM_DEVICE_BURSTLEN_2);
    SDRAM_ConfigCASLatency(SDRAM_DEVICE_1, SDRAM_DEVICE_CASLTCY_3);
    SDRAM_ConfigAddress(SDRAM_DEVICE_1, SDRAM_BANK4_ROW4096_COL512);
    SDRAM_EnableWriteProtection(SDRAM_DEVICE_1, DISABLE);
    command(SDRAM_OPCODE_NONE, 0);
    delay_us(clocks.M7ClkFreq, 1000);
    command(SDRAM_OPCODE_PRECHRG, 0);
    for (unsigned i = 0; i < 8; ++i) command(SDRAM_OPCODE_REFRESH, 0);
    command(SDRAM_OPCODE_LOADMODE, 0x31);
    delay_us(clocks.M7ClkFreq, 1000);
    SDRAM_EnableRefreshCMD(SDRAM_DEVICE_1, ENABLE);
    status = self_test() ? 0U : 3U;
    return status == 0U;
}
