/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CAMERA_COLOR_H
#define CAMERA_COLOR_H

#include <stddef.h>
#include <stdint.h>

void gray8_downsample2(const uint8_t *source, uint8_t *dest,
                      uint32_t width, uint32_t height);

#endif
