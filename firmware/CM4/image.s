/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

/* The normal M7 flash command programs both cores in one verified image. */
.section .cm4_image,"a",%progbits
.balign 4
.incbin "build/cm4/n32h787_person_detect_demo_CM4.bin"
