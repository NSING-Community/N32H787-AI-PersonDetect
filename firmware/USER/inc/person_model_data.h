/*
 * Copyright (c) 2025 Nations Technologies Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <cstddef>

/* Read directly from Flash. See .person_model in the linker script. */
extern const unsigned char g_person_model_data[];
extern const std::size_t g_person_model_data_len;
