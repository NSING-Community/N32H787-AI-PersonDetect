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
 * @file system_n32h7xx.h
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __SYSTEM_N32H7XX_H__
#define __SYSTEM_N32H7XX_H__

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/** _System */

 /** Power supply source configuration **/
#define PWR_SUPPLY_MODE_MASK               (PWR_SYSCTRL4_MLDOEN | PWR_SYSCTRL4_DCDCEN | PWR_SYSCTRL4_VCORESRC | PWR_SYSCTRL4_DCDCFRCEN)    
#define PWR_LDO_SUPPLY                     (PWR_SYSCTRL4_MLDOEN)             /* Core domains are supplied from the LDO  */
#define PWR_DIRECT_SMPS_SUPPLY             (PWR_SYSCTRL4_DCDCEN)             /* Core domains are supplied from the SMPS */ 
#define PWR_EXTERNAL_SOURCE_SUPPLY         (PWR_SYSCTRL4_VCORESRC)           /* The SMPS and the LDO are Bypassed. The Core domains are supplied from an external source */

 /** NRST Analog and Digital Filter configuration **/
#define PWR_RST_AGFBPEN_MAST              (PWR_SYSCTRL1_AGF_ARSTOBP)
#define PWR_RST_DGFBPEN_MAST              (PWR_SYSCTRL1_NRST_DGFBP)
#define PWR_RST_DGF_CNT_MAST              (PWR_SYSCTRL1_NRST_DGFCNT)
#define PWR_RST_DGF_CNT_DEFAULT           ((uint32_t)0x200000U)

extern uint32_t SystemCoreClock; /* System Clock Frequency (Core Clock) */

extern void SystemInit(void);
#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_N32H7XX_H__ */
