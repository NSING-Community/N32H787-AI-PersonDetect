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
 * @file n32h7xx_wwdg.h
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H7XX_WWDG_H__
#define __N32H7XX_WWDG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h7xx.h"

#define WWDG_PRESCALER_DIV1             ((uint32_t)0x00000000)
#define WWDG_PRESCALER_DIV2             ((uint32_t)WWDG_CFG_TIMERB0)
#define WWDG_PRESCALER_DIV4             ((uint32_t)WWDG_CFG_TIMERB1)
#define WWDG_PRESCALER_DIV8             ((uint32_t)(WWDG_CFG_TIMERB1 | WWDG_CFG_TIMERB0))


/** EWINT bit **/
#define EARLY_WAKEUP_INT                (WWDG_CFG_EWINT)
#define EARLY_WAKEUP_FLAG               (WWDG_STS_EWINTF)

/** CTRL register bit mask **/
#define CTRL_ACTB_SET                   ((uint32_t)WWDG_CTRL_ACTB)

/* CFG register bit mask **/
#define CFG_TIMERB_MASK                 ((uint32_t)0xFFFF3FFFU)
#define CFG_W_MASK                      ((uint32_t)0xFFFFC000U)
#define BIT_MASK                        ((uint16_t)0x3FFF)


void WWDG_DeInit(WWDG_Module* WWDGx);
void WWDG_SetPrescalerDiv(WWDG_Module* WWDGx,uint32_t WWDG_Prescaler);
void WWDG_SetWValue(WWDG_Module* WWDGx,uint16_t WindowValue);
void WWDG_EnableInt(WWDG_Module* WWDGx);
void WWDG_SetCnt(WWDG_Module* WWDGx,uint16_t Counter);
void WWDG_Enable(WWDG_Module* WWDGx,uint16_t Counter);
FlagStatus WWDG_GetEWINTF(WWDG_Module* WWDGx);
void WWDG_ClrEWINTF(WWDG_Module* WWDGx);

#ifdef __cplusplus
}
#endif

#endif /* __N32H78X__WWDG_H */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
