/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef M4_BOOT_H
#define M4_BOOT_H

#include <stdint.h>

/* 0=off, 1=waiting, 2=verified, 0xe1..=startup/runtime failure. */
extern volatile uint32_t g_m4_status;
extern volatile uint32_t g_m4_checks;
extern volatile uint32_t g_m4_errors;
void m4_start(void);
void m4_poll(void);

#endif
