/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "person_preprocess.h"
#include <stddef.h>

void person_preprocess_gray8(const uint8_t *pixels, uint32_t width,
                            uint32_t height, const int8_t quantize[256],
                            int8_t *output)
{
    if (!pixels || !quantize || !output || !width || !height) return;
    const uint32_t side = width < height ? width : height;
    const uint32_t left = (width - side) / 2U;
    const uint32_t top = (height - side) / 2U;
    uint32_t bounds[PERSON_INPUT_SIDE + 1U];
    for (uint32_t i = 0; i <= PERSON_INPUT_SIDE; ++i)
        bounds[i] = (uint64_t)i * side / PERSON_INPUT_SIDE;

    for (uint32_t dy = 0; dy < PERSON_INPUT_SIDE; ++dy) {
        const uint32_t y0 = top + bounds[dy];
        uint32_t y1 = top + bounds[dy + 1U];
        if (y1 <= y0) y1 = y0 + 1U;
        for (uint32_t dx = 0; dx < PERSON_INPUT_SIDE; ++dx) {
            const uint32_t x0 = left + bounds[dx];
            uint32_t x1 = left + bounds[dx + 1U];
            if (x1 <= x0) x1 = x0 + 1U;
            uint32_t sum = 0U;
            for (uint32_t y = y0; y < y1; ++y) {
                const uint8_t *row = pixels + (size_t)y * width;
                for (uint32_t x = x0; x < x1; ++x) sum += row[x];
            }
            output[dy * PERSON_INPUT_SIDE + dx] =
                quantize[sum / ((y1 - y0) * (x1 - x0))];
        }
    }
}
