/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef M4_SHARED_H
#define M4_SHARED_H

#include <stdint.h>
#include <stddef.h>

#define M4_BOOT_ADDRESS 0x15080000UL
#define M4_SHARED_MAGIC 0x4d344951UL
#define M7_FLASH_ABI 0x4d374331UL
#define M4_SHARED_WORDS 64U
#define INFERENCE_WIDTH 160U
#define INFERENCE_HEIGHT 120U
#define INFERENCE_FRAME_BYTES (INFERENCE_WIDTH * INFERENCE_HEIGHT)

/* Single outstanding request. Payload ownership transfers with sequence + DMB.
   M7 maps shared control/snapshots as Normal non-cacheable, shareable memory. */
typedef struct {
    uint32_t magic;
    uint32_t clock_hz;
    uint32_t ready;
    uint32_t heartbeat;
    uint32_t request;
    uint32_t response;
    uint32_t fault;
    uint32_t cfsr;
    uint32_t cpuid;
    uint32_t vtor;
    uint32_t input[M4_SHARED_WORDS];
    uint32_t output[M4_SHARED_WORDS];
    uint32_t boot_status;
    uint32_t boot_checks;
    uint32_t boot_errors;
    uint32_t person_init;
    uint32_t person_control; /* bit0 enabled, upper bits toggle generation */
    uint32_t snapshot_request; /* M7 owns request/released; M4 owns ready/data */
    uint32_t snapshot_ready;
    uint32_t snapshot_released;
    uint32_t snapshot_frame;
    uint32_t snapshot_tick;
    uint32_t copy_cycles;
    uint32_t result_version; /* odd while M7 writes, even when published */
    uint32_t result_control;
    uint32_t result_frame;
    uint32_t result_tick;
    uint32_t result_scores;
    uint32_t result_flags;
    /* Unused diagnostic slots retained only to keep the fixed-word layout. */
    uint32_t reserved_diag[15];
    /* OpenOCD SWD flash handshakes use fixed absolute addresses, so the four
       words below must stay at byte offsets 680..695.  See n32h7x_cmsisdap.tcl
       (n32h7x_stop_m4_camera / n32h7x_quiesce_cached_m7). */
    uint32_t flash_pause;
    uint32_t flash_paused;
    uint32_t m7_flash_paused;
    uint32_t m7_flash_abi;
    uint32_t m7_clock_hz;
    uint32_t m7_cache_ccr;
    uint32_t result_copy_us;
    uint32_t result_preprocess_us;
    uint32_t result_invoke_us;
    uint32_t sdram_status; /* M7 startup self-test; 0=SDRAM ready. */
    /* Removed audio/boot-reboot fields, retained as padding so the struct and
       the OpenOCD ABI keep their historical size/offsets. */
    uint32_t reserved[52];
} m4_shared_t;

/* OpenOCD uses these fixed offsets before reusing the AXI DMA workspace. */
#ifdef __cplusplus
static_assert(offsetof(m4_shared_t, flash_pause) == 680, "Flash handshake ABI");
static_assert(offsetof(m4_shared_t, flash_paused) == 684, "Flash handshake ABI");
static_assert(offsetof(m4_shared_t, m7_flash_paused) == 688, "M7 flash ABI");
static_assert(offsetof(m4_shared_t, m7_flash_abi) == 692, "M7 flash ABI");
static_assert(sizeof(m4_shared_t) <= 1024, "Shared RAM overflow");
#else
_Static_assert(offsetof(m4_shared_t, flash_pause) == 680, "Flash handshake ABI");
_Static_assert(offsetof(m4_shared_t, flash_paused) == 684, "Flash handshake ABI");
_Static_assert(offsetof(m4_shared_t, m7_flash_paused) == 688, "M7 flash ABI");
_Static_assert(offsetof(m4_shared_t, m7_flash_abi) == 692, "M7 flash ABI");
_Static_assert(sizeof(m4_shared_t) <= 1024, "Shared RAM overflow");
#endif

extern volatile m4_shared_t g_m4_shared;
extern uint8_t g_inference_shared[INFERENCE_FRAME_BYTES];

void m4_service_mailbox(void);
void camera_main(void);

static inline uint32_t m4_test_word(uint32_t sequence, uint32_t index)
{
    return 0xa53c96e1UL ^ sequence ^ (index * 0x01010101UL);
}

static inline uint32_t m4_test_reply(uint32_t word)
{
    return ((word << 7) | (word >> 25)) ^ 0x739ac5e2UL;
}

#endif
