/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __OV5640_H__
#define __OV5640_H__

#include <stdint.h>

#define OV5640_WIDTH 320U
#define OV5640_HEIGHT 240U

int ov5640_write_reg(uint16_t reg, uint8_t value);

void ov5640_probe(volatile uint32_t *probe_status, volatile uint32_t *chip_id,
                  volatile uint32_t *i2c_status);

void ov5640_configure_gray8(volatile uint32_t *configured,
                                    volatile uint32_t *dimensions,
                                    volatile uint32_t *format_polarity,
                                    volatile uint32_t *mclk_hz,
                                    volatile uint32_t *registers_written,
                                    volatile uint32_t *i2c_status);

#endif /* __OV5640_H__ */
