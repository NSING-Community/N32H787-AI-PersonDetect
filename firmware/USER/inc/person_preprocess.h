/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PERSON_PREPROCESS_H
#define PERSON_PREPROCESS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PERSON_INPUT_SIDE 96U
void person_preprocess_gray8(const uint8_t *pixels, uint32_t width,
                            uint32_t height, const int8_t quantize[256],
                            int8_t *output);

#ifdef __cplusplus
}
#endif
#endif
