/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"
#include "ov5640.h"
#include "ov5640_dvp_gray8.h"

#define OV5640_I2C_ADDRESS 0x3CU
#define I2C4_WAIT_LIMIT 100000U
#define I2C4_SADR_7BIT(address) ((uint32_t)(address) << 1U)

static int i2c4_wait(uint32_t wanted, volatile uint32_t *status)
{
    for (uint32_t count = 0U; count < I2C4_WAIT_LIMIT; ++count) {
        const uint32_t flags = I2C4->STSINT;
        *status = flags;
        if ((flags & (I2C_FLAG_NAKF | I2C_FLAG_BSER | I2C_FLAG_ABLO |
                      I2C_FLAG_TMOUT)) != 0U) {
            return 0;
        }
        if ((flags & wanted) != 0U) {
            return 1;
        }
    }
    return 0;
}

static int ov5640_read_reg(uint16_t reg, uint8_t *value,
                           volatile uint32_t *i2c_status)
{
    I2C_ClrFlag(I2C4, I2C_FLAG_NAKF | I2C_FLAG_STOPF | I2C_FLAG_BSER |
                           I2C_FLAG_ABLO | I2C_FLAG_TMOUT);
    I2C_EnableAutomaticEnd(I2C4, DISABLE);
    I2C_EnableReload(I2C4, DISABLE);
    I2C_ConfigSendAddress(I2C4, I2C4_SADR_7BIT(OV5640_I2C_ADDRESS),
                          I2C_DIRECTION_SEND);
    I2C_SetTransferByteNumber(I2C4, 2U);
    I2C_GenerateStart(I2C4, ENABLE);
    if (!i2c4_wait(I2C_FLAG_WRAVL, i2c_status)) goto fail;
    I2C_SendData(I2C4, (uint8_t)(reg >> 8));
    if (!i2c4_wait(I2C_FLAG_WRAVL, i2c_status)) goto fail;
    I2C_SendData(I2C4, (uint8_t)reg);
    if (!i2c4_wait(I2C_FLAG_TFC, i2c_status)) goto fail;

    I2C_ConfigSendAddress(I2C4, I2C4_SADR_7BIT(OV5640_I2C_ADDRESS),
                          I2C_DIRECTION_RECV);
    I2C_SetTransferByteNumber(I2C4, 1U);
    I2C_EnableAutomaticEnd(I2C4, ENABLE);
    I2C_GenerateStart(I2C4, ENABLE);
    if (!i2c4_wait(I2C_FLAG_RDAVL, i2c_status)) goto fail;
    *value = I2C_RecvData(I2C4);
    if (!i2c4_wait(I2C_FLAG_STOPF, i2c_status)) goto fail;
    I2C_ClrFlag(I2C4, I2C_FLAG_STOPF);
    return 1;

fail:
    I2C_GenerateStop(I2C4, ENABLE);
    I2C_ClrFlag(I2C4, I2C_FLAG_NAKF | I2C_FLAG_STOPF | I2C_FLAG_BSER |
                           I2C_FLAG_ABLO | I2C_FLAG_TMOUT);
    return 0;
}

int ov5640_write_reg(uint16_t reg, uint8_t value)
{
    uint32_t ignored_status = 0U;

    I2C_ClrFlag(I2C4, I2C_FLAG_NAKF | I2C_FLAG_STOPF | I2C_FLAG_BSER |
                           I2C_FLAG_ABLO | I2C_FLAG_TMOUT);
    I2C_EnableAutomaticEnd(I2C4, ENABLE);
    I2C_EnableReload(I2C4, DISABLE);
    I2C_ConfigSendAddress(I2C4, I2C4_SADR_7BIT(OV5640_I2C_ADDRESS),
                          I2C_DIRECTION_SEND);
    I2C_SetTransferByteNumber(I2C4, 3U);
    I2C_GenerateStart(I2C4, ENABLE);
    if (!i2c4_wait(I2C_FLAG_WRAVL, &ignored_status)) goto fail;
    I2C_SendData(I2C4, (uint8_t)(reg >> 8));
    if (!i2c4_wait(I2C_FLAG_WRAVL, &ignored_status)) goto fail;
    I2C_SendData(I2C4, (uint8_t)reg);
    if (!i2c4_wait(I2C_FLAG_WRAVL, &ignored_status)) goto fail;
    I2C_SendData(I2C4, value);
    if (!i2c4_wait(I2C_FLAG_STOPF, &ignored_status)) goto fail;
    I2C_ClrFlag(I2C4, I2C_FLAG_STOPF);
    return 1;

fail:
    I2C_GenerateStop(I2C4, ENABLE);
    I2C_ClrFlag(I2C4, I2C_FLAG_NAKF | I2C_FLAG_STOPF | I2C_FLAG_BSER |
                           I2C_FLAG_ABLO | I2C_FLAG_TMOUT);
    return 0;
}

void ov5640_probe(volatile uint32_t *probe_status, volatile uint32_t *chip_id,
                  volatile uint32_t *i2c_status)
{
    uint8_t id_high = 0U;
    uint8_t id_low = 0U;
    const int high_ok = ov5640_read_reg(0x300AU, &id_high, i2c_status);
    const int low_ok = ov5640_read_reg(0x300BU, &id_low, i2c_status);

    *chip_id = ((uint32_t)id_high << 8U) | id_low;
    *probe_status = (high_ok && low_ok) ? (*chip_id == 0x5640U ? 2U : 1U)
                                         : 0U;
}

void ov5640_configure_gray8(volatile uint32_t *configured,
                                    volatile uint32_t *dimensions,
                                    volatile uint32_t *format_polarity,
                                    volatile uint32_t *mclk_hz,
                                    volatile uint32_t *registers_written,
                                    volatile uint32_t *i2c_status)
{
    const uint32_t total = sizeof(ov5640_settings) / sizeof(ov5640_settings[0]);
    RCC_ClocksTypeDef clocks;
    uint8_t width_h, width_l, height_h, height_l, format, polarity;
    uint32_t written = 0U;

    *configured = 0U;
    for (uint32_t index = 0U; index < total; ++index) {
        if (!ov5640_write_reg(ov5640_settings[index].reg,
                              ov5640_settings[index].value)) {
            break;
        }
        ++written;
    }
    *registers_written = written;
    if (written != total) return;

    SysTick_Delayms(100U);
    RCC_GetClocksFreqValue(&clocks);
    *mclk_hz = clocks.AXIClkFreq / 16U;
    if (!ov5640_read_reg(0x3808U, &width_h, i2c_status) ||
        !ov5640_read_reg(0x3809U, &width_l, i2c_status) ||
        !ov5640_read_reg(0x380AU, &height_h, i2c_status) ||
        !ov5640_read_reg(0x380BU, &height_l, i2c_status) ||
        !ov5640_read_reg(0x4300U, &format, i2c_status) ||
        !ov5640_read_reg(0x4740U, &polarity, i2c_status)) return;

    *dimensions = ((uint32_t)width_h << 24U) | ((uint32_t)width_l << 16U) |
                  ((uint32_t)height_h << 8U) | height_l;
    *format_polarity = ((uint32_t)format << 8U) | polarity;
    *configured = *dimensions == ((OV5640_WIDTH << 16U) | OV5640_HEIGHT) &&
                  *format_polarity == 0x00001023U;
}
