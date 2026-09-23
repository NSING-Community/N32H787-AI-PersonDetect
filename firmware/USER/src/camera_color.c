/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "camera_color.h"

void gray8_downsample2(const uint8_t *source, uint8_t *dest,
                      uint32_t width, uint32_t height)
{
    if (!source || !dest || (width & 1U) || (height & 1U)) return;
    for (uint32_t y = 0U; y < height; y += 2U) {
        const uint8_t *row = source + (size_t)y * width;
        for (uint32_t x = 0U; x < width; x += 2U) {
            *dest++ = ((uint32_t)row[x] + row[x + 1U] +
                       row[width + x] + row[width + x + 1U] + 2U) / 4U;
        }
    }
}
