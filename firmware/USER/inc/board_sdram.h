/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BOARD_SDRAM_H
#define BOARD_SDRAM_H

#include <stdbool.h>
#include <stdint.h>

#define BOARD_SDRAM_BASE 0xc0000000U
#define BOARD_SDRAM_BYTES (32U * 1024U * 1024U)
#define BOARD_SDRAM_HZ 133000000U
#define BOARD_SDRAM_REFRESH_CYCLES 1872U

#ifdef __cplusplus
extern "C" {
#endif
/* M7 cold-start only, before M4 and DCache. Destructive startup self-test.
   No buffers/heap are allocated here; m7_cache_enable adds the WBWA mapping.
   Future DMA/M4 users must arrange cache maintenance or non-cacheable regions. */
bool SDRAM_Configuration(void);
/* 0=ready, 1=clock failure, 2=unsafe init, 3=readback failure, UINT32_MAX=unused. */
uint32_t board_sdram_status(void);
#ifdef __cplusplus
}
#endif
#endif
