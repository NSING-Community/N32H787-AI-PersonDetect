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
 * @file n32h7xx_iwdg.h
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H7XX_IWDG_H__
#define __N32H7XX_IWDG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h7xx.h"

typedef enum 
{
    IWDG_PVU_FLAG  = IWDG_STS_PVU,
    IWDG_CRVU_FLAG = IWDG_STS_CRVU,
    IWDG_FRZF_FLAG = IWDG_STS_FRZF,
}IWDG_STATUS_FLAG;

/** KEY register bit mask **/
#define KEY_ReloadKey                      ((uint16_t)0xAAAA)
#define KEY_EnableKey                      ((uint16_t)0xCCCC)
#define IWDG_FREEZE                        ((uint16_t)0x4567)
#define IWDG_UNFREEZE                      ((uint16_t)0x89AB)

/** PREDIV and RELV register write permission **/
typedef enum 
{
    IWDG_WRITE_ENABLE  = 0x5555,
    IWDG_WRITE_DISABLE = 0x0000
}IWDOG_WRITE_CONFIG;

#define IWDG_PRESCALER_DIV4    ((uint8_t)0x00)
#define IWDG_PRESCALER_DIV8    (IWDG_PREDIV_PD0)
#define IWDG_PRESCALER_DIV16   (IWDG_PREDIV_PD1)
#define IWDG_PRESCALER_DIV32   (IWDG_PREDIV_PD1 | IWDG_PREDIV_PD0)
#define IWDG_PRESCALER_DIV64   (IWDG_PREDIV_PD2)
#define IWDG_PRESCALER_DIV128  (IWDG_PREDIV_PD2 | IWDG_PREDIV_PD0)
#define IWDG_PRESCALER_DIV256  (IWDG_PREDIV_PD2 | IWDG_PREDIV_PD1 | IWDG_PREDIV_PD0)


void IWDG_WriteConfig(IWDG_Module* IWDGx,IWDOG_WRITE_CONFIG IWDG_WriteAccess);
void IWDG_SetPrescalerDiv(IWDG_Module* IWDGx,uint8_t IWDG_Prescaler);
void IWDG_CntReload(IWDG_Module* IWDGx,uint16_t Reload);
void IWDG_ReloadKey(IWDG_Module* IWDGx);
void IWDG_Enable(IWDG_Module* IWDGx);
void IWDG_Freeze_Enable(IWDG_Module* IWDGx,FunctionalState Cmd);
FlagStatus IWDG_GetStatus(IWDG_Module* IWDGx,IWDG_STATUS_FLAG IWDG_FLAG);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* __N32H76X_IWDG_H__ */
