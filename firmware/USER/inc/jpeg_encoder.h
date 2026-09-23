/**
 * Copyright (c) 2025, Nations Technologies Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
*\*\file bsp_jpegenc.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
**/

#ifndef JPEG_ENCODER_H
#define JPEG_ENCODER_H

#include "n32h7xx_jpeg.h"
#include <stdint.h>

/* Configures the vendor JPEG ENC tables for single-component Y8 input. */
void jpeg_encoder_config_tables(uint32_t frame_width, uint32_t frame_height,
                                uint32_t quality);

/* Powers the JPEG engine using AXI SRAM only. Requires graphics power and DWT. */
int jpeg_encoder_init(void);
void jpeg_encoder_stop(void);

/* Encodes an OV5640_WIDTH x OV5640_HEIGHT Y8 frame with JPEG RBC/ENC
   and SGDMA, preserving the source. Output is valid until the next call. */
int jpeg_encoder_encode_gray8(const uint8_t *gray8,
                                 uint8_t **jpeg_data, uint32_t *jpeg_size);

void jpeg_encoder_get_diagnostics(uint32_t *color_cycles, uint32_t *last_cycles, uint32_t *last_bytes,
                                  uint32_t *h2p_status, uint32_t *p2h_status);

#endif /* JPEG_ENCODER_H */
