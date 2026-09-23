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
 * @file n32h7xx_vrefbuf.h
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H7XX_VREFBUF_H__
#define __N32H7XX_VREFBUF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h7xx.h"

/** VREFBUF Register list**/
#define VREFBUF_STS_REG_ADDR                     ((uint32_t)AFEC_BASE + 0x34U)
#define VREFBUF_CTRL1_REG_ADDR                   ((uint32_t)AFEC_BASE + 0x48U)
#define VREFBUF_CTRL2_REG_ADDR                   ((uint32_t)AFEC_BASE + 0xDCU)
#define VREFBUF_TRIM1_REG_ADDR                   ((uint32_t)AFEC_BASE + 0x28U)
#define VREFBUF_TRIM2_REG_ADDR                   ((uint32_t)AFEC_BASE + 0xE8U)

#define VREFBUF_EN_CTRL                          ((uint32_t)AFEC_BASE + 0x3CU)  

/** VREFBUF_Exported_Constants **/
#define VREFBUF_EN_MASK                           (VREFBUF_CTRL1_EN)
#define VREFBUF_HIM_EN_MASK                       (VREFBUF_CTRL1_HIM)

#define VREFBUF_VOLTAGE_SCALE_MASK                (VREFBUF_CTRL2_VLSEL)
#define VREFBUF_VOLTAGE_SCALE_2_5V                ((uint32_t)0x00000000U)
#define VREFBUF_VOLTAGE_SCALE_2_048V              (VREFBUF_CTRL2_VLSEL_0)
#define VREFBUF_VOLTAGE_SCALE_1_8V                (VREFBUF_CTRL2_VLSEL_1)
#define VREFBUF_VOLTAGE_SCALE_1_5V                (VREFBUF_CTRL2_VLSEL_1 | VREFBUF_CTRL2_VLSEL_0)

#define VREFBUF_READY_MASK                        (VREFBUF_STS_RDY)

/** VREFBUF_Trimming_Constants **/
#define VREFBUF_TRIMING_2_5V_POS                  ((uint8_t)16U)
#define VREFBUF_TRIMING_2_5V_MASK                 (VREFBUF_TRIM1_2_5V_MASK)
#define VREFBUF_TRIMING_2_0V_POS                  ((uint8_t)22U)
#define VREFBUF_TRIMING_2_0V_MASK                 (VREFBUF_TRIM1_2_048V_MASK)
#define VREFBUF_TRIMING_1_8V_POS                  ((uint8_t)0U)
#define VREFBUF_TRIMING_1_8V_MASK                 (VREFBUF_TRIM1_1_8V_MASK)
#define VREFBUF_TRIMING_1_5V_POS                  ((uint8_t)8U)
#define VREFBUF_TRIMING_1_5V_MASK                 (VREFBUF_TRIM1_1_5V_MASK)
/** VREFBUF_Exported_Functions **/

void VREFBUF_Enable(FunctionalState Cmd);
void VREFBUF_EnableHIM(FunctionalState Cmd);
void VREFBUF_SetVoltageScale(uint32_t Scale);
uint32_t VREFBUF_GetVoltageScale(void);
FlagStatus VREFBUF_IsVREFReady(void);


void VREFBUF_SetTrimming(uint32_t Value);

#ifdef __cplusplus
}
#endif

#endif /*__N32H7XX_VREFBUF_H__ */


