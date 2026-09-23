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
 * @file n32h7xx_comp.h
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H7XX_COMP_H__
#define __N32H7XX_COMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h7xx.h"
#include <stdbool.h>


/** COMP_Exported_Types **/

typedef enum
{
    COMP1 = 0,
    COMP2 = 1,
    COMP3 = 2,
    COMP4 = 3
} COMPX;


typedef enum {
  COMPX_CTRL_INMSEL_RES          = (0x7U << 1),
  /*comp1 inm sel*/
  COMP1_CTRL_INMSEL_PB1          = (0x0U << 1),
  COMP1_CTRL_INMSEL_PC4          = (0x1U << 1),
  COMP1_CTRL_INMSEL_DAC1_IOUT    = (0x2U << 1),
  COMP1_CTRL_INMSEL_DAC2_IOUT    = (0x3U << 1),
  COMP1_CTRL_INMSEL_DAC3_IOUT    = (0x4U << 1),
  COMP1_CTRL_INMSEL_DAC4_IOUT    = (0x5U << 1),
  COMP1_CTRL_INMSEL_DAC5_IOUT    = (0x6U << 1),
  COMP1_CTRL_INMSEL_DAC6_IOUT    = (0x7U << 1),
  COMP1_CTRL_INMSEL_VREF1        = (0x8U << 1),
  COMP1_CTRL_INMSEL_PF3          = (0x9U << 1),
  /*comp2 inm sel*/
  COMP2_CTRL_INMSEL_PE7          = (0x0U << 1),
  COMP2_CTRL_INMSEL_PE10         = (0x1U << 1),
  COMP2_CTRL_INMSEL_DAC1_IOUT    = (0x2U << 1),
  COMP2_CTRL_INMSEL_DAC2_IOUT    = (0x3U << 1),
  COMP2_CTRL_INMSEL_DAC3_IOUT    = (0x4U << 1),
  COMP2_CTRL_INMSEL_DAC4_IOUT    = (0x5U << 1),
  COMP2_CTRL_INMSEL_DAC5_IOUT    = (0x6U << 1),
  COMP2_CTRL_INMSEL_DAC6_IOUT    = (0x7U << 1),
  COMP2_CTRL_INMSEL_VREF2        = (0x8U << 1),
  COMP2_CTRL_INMSEL_PF6          = (0x9U << 1),
  /*comp3 inm sel*/
  COMP3_CTRL_INMSEL_PF1          = (0x0U << 1),
  COMP3_CTRL_INMSEL_PF14         = (0x1U << 1),
  COMP3_CTRL_INMSEL_DAC1_IOUT    = (0x2U << 1),
  COMP3_CTRL_INMSEL_DAC2_IOUT    = (0x3U << 1),
  COMP3_CTRL_INMSEL_DAC3_IOUT    = (0x4U << 1),
  COMP3_CTRL_INMSEL_DAC4_IOUT    = (0x5U << 1),
  COMP3_CTRL_INMSEL_DAC5_IOUT    = (0x6U << 1),
  COMP3_CTRL_INMSEL_DAC6_IOUT    = (0x7U << 1),

  /*comp4 inm sel*/
  COMP4_CTRL_INMSEL_PH9          = (0x0U << 1),
  COMP4_CTRL_INMSEL_PH6          = (0x1U << 1),
  COMP4_CTRL_INMSEL_DAC1_IOUT    = (0x2U << 1),
  COMP4_CTRL_INMSEL_DAC2_IOUT    = (0x3U << 1),
  COMP4_CTRL_INMSEL_DAC3_IOUT    = (0x4U << 1),
  COMP4_CTRL_INMSEL_DAC4_IOUT    = (0x5U << 1),
  COMP4_CTRL_INMSEL_DAC5_IOUT    = (0x6U << 1),
  COMP4_CTRL_INMSEL_DAC6_IOUT    = (0x7U << 1),
  COMP4_CTRL_INMSEL_PH8          = (0x8U << 1)
}COMP_CTRL_INMSEL;

typedef enum {
  COMPX_CTRL_INPSEL_RES         = (0xFU << 5),
  /*comp1 inp sel*/
  COMP1_CTRL_INPSEL_PB0         = (0x0U << 5),
  COMP1_CTRL_INPSEL_PB2         = (0x1U << 5),
  COMP1_CTRL_INPSEL_DAC1_IOUT   = (0x2U << 5),
  COMP1_CTRL_INPSEL_DAC2_IOUT   = (0x3U << 5),
  COMP1_CTRL_INPSEL_DAC3_IOUT   = (0x4U << 5),
  COMP1_CTRL_INPSEL_DAC4_IOUT   = (0x5U << 5),
  COMP1_CTRL_INPSEL_DAC5_IOUT   = (0x6U << 5),
  COMP1_CTRL_INPSEL_DAC6_IOUT   = (0x7U << 5),
  COMP1_CTRL_INPSEL_VREF1       = (0x8U << 5),
  COMP1_CTRL_INPSEL_PF5         = (0x9U << 5),
  /*comp2 inp sel*/
  COMP2_CTRL_INPSEL_PE9         = (0x0U << 5),
  COMP2_CTRL_INPSEL_PE11        = (0x1U << 5),
  COMP2_CTRL_INPSEL_DAC1_IOUT   = (0x2U << 5),
  COMP2_CTRL_INPSEL_DAC2_IOUT   = (0x3U << 5),
  COMP2_CTRL_INPSEL_DAC3_IOUT   = (0x4U << 5),
  COMP2_CTRL_INPSEL_DAC4_IOUT   = (0x5U << 5),
  COMP2_CTRL_INPSEL_DAC5_IOUT   = (0x6U << 5),
  COMP2_CTRL_INPSEL_DAC6_IOUT   = (0x7U << 5),
  COMP2_CTRL_INPSEL_VREF2       = (0x8U << 5),
  COMP2_CTRL_INPSEL_PB2         = (0x9U << 5),
  COMP2_CTRL_INPSEL_PF7         = (0xAU << 5),
  /*comp3 inp sel*/
  COMP3_CTRL_INPSEL_PF2         = (0x0U << 5),
  COMP3_CTRL_INPSEL_PF15        = (0x1U << 5),
  COMP3_CTRL_INPSEL_DAC1_IOUT   = (0x2U << 5),
  COMP3_CTRL_INPSEL_DAC2_IOUT   = (0x3U << 5),
  COMP3_CTRL_INPSEL_DAC3_IOUT   = (0x4U << 5),
  COMP3_CTRL_INPSEL_DAC4_IOUT   = (0x5U << 5),
  COMP3_CTRL_INPSEL_DAC5_IOUT   = (0x6U << 5),
  COMP3_CTRL_INPSEL_DAC6_IOUT   = (0x7U << 5),

  /*comp4 inp sel*/
  COMP4_CTRL_INPSEL_PH10        = (0x0U << 5),
  COMP4_CTRL_INPSEL_PH7         = (0x1U << 5),
  COMP4_CTRL_INPSEL_DAC1_IOUT   = (0x2U << 5),
  COMP4_CTRL_INPSEL_DAC2_IOUT   = (0x3U << 5),
  COMP4_CTRL_INPSEL_DAC3_IOUT   = (0x4U << 5),
  COMP4_CTRL_INPSEL_DAC4_IOUT   = (0x5U << 5),
  COMP4_CTRL_INPSEL_DAC5_IOUT   = (0x6U << 5),
  COMP4_CTRL_INPSEL_DAC6_IOUT   = (0x7U << 5),
  COMP4_CTRL_INPSEL_PF15        = (0x8U << 5),
  COMP4_CTRL_INPSEL_PF10        = (0x9U << 5)
}COMP_CTRL_INPSEL;

/*comp hysteresis level select*/
typedef enum
{
    COMP_CTRL_HYST_NO    = (0x0U << 14),
    COMP_CTRL_HYST_LOW   = (0x1U << 14),
    COMP_CTRL_HYST_MID   = (0x2U << 14),
    COMP_CTRL_HYST_HIGH  = (0x3U << 14)
} COMP_CTRL_HYST;

/*comp Blking source select*/
typedef enum
{
    COMP_CTRL_BLKING_NO            = (0x0U << 16 ),
    COMP_CTRL_BLKING_ATIM1_OC5     = (0x0U << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_GTIMB1_OC5    = (0x1U << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_GTIMB2_OC5    = (0x2U << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_ATIM2_OC5     = (0x3U << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_ATIM3_OC5     = (0x4U << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_ATIM4_OC1     = (0x5U << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_GTIMB3_OC5    = (0x6U << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_GTIMA4_OC5    = (0x7U << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_GTIMA2_OC3    = (0x8U << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_GTIMA1_OC3    = (0x9U << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_GTIMA3_OC3    = (0xAU << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_GTIMA5_OC3    = (0xBU << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_GTIMA6_OC3    = (0xCU << 16 | COMP1_CTRL_BLKINGEN),
    COMP_CTRL_BLKING_GTIMA7_OC3    = (0xDU << 16 | COMP1_CTRL_BLKINGEN)
} COMP_CTRL_BLKING;

/** COMP_Exported_Constants **/

/** COMPx_CTRL **/
#define COMP_CTRL_OUT_MASK                          (COMP1_CTRL_OUT)

#define COMP_CTRL_BLKING_MASK                       (COMP1_CTRL_BLKING | COMP1_CTRL_BLKINGEN)

#define COMP_CTRL_HYST_MASK                         (COMP1_CTRL_HYST)

#define COMP_POL_MASK                               (COMP1_CTRL_POL)
#define COMP_OUTPOL_FLIP                            (COMP1_CTRL_POL)
#define COMP_OUTPOL_NFLIP                           (0x00000000U)

#define COMP_CTRL_INPSEL_MASK                       (COMP1_CTRL_INPSEL) /*MAX INPSEL BIT.*/

#define COMP_CTRL_INMSEL_MASK                       (COMP1_CTRL_INMSEL) /*MAX INMSEL BIT.*/

#define COMP_CTRL_EN_MASK                           (COMP1_CTRL_EN)

/** COMPx_FILC **/

#define COMP_VFLAG_P                                (COMP1_FILC_VP_FLAG) /*using DAC stable value as Comparator's positive input.*/    
#define COMP_VFLAG_N                                (COMP1_FILC_VN_FLAG) /*using DAC stable value as Comparator's negetive input.*/ 
#define COMP_FILC_SAMPW_MASK                        (COMP1_FILC_SAMPW) /*Low filter sample window size. Number of samples to monitor is SAMPWIN+1.*/
#define COMP_FILC_THRESH_MASK                       (COMP1_FILC_THRESH)/*For proper operation, the value of THRESH must be greater than SAMPWIN / 2.*/
#define COMP_FILC_FILEN_MASK                        (COMP1_FILC_FILEN) /*Filter enable.*/

/** COMPx_FILP **/
#define COMP_FILCLKCR_CLKPSC_MASK                   (COMP1_FILP_CLKPSC)/*Low filter sample clock prescale. Number of system clocks between samples = CLK_PRE_CYCLE + 1, e.g.*/


/** COMP_LPMODE **/
#define COMP_LPMODE_LP_EN_MASK                      (COMP_LPR_CLKSEL)

/** COMP_WINMODE  **/
#define COMP_WINMODE_CMPMD_MSK                      (COMP_WINMODE_COMP12MD|COMP_WINMODE_COMP34MD)
#define COMP_WINMODE_CMP34MD                        (COMP_WINMODE_COMP34MD)/* Comparators 3 and 4 can be used in window mode.*/
#define COMP_WINMODE_CMP12MD                        (COMP_WINMODE_COMP12MD)/* Comparators 1 and 2 can be used in window mode.*/

/** COMP_LOCK  **/
#define COMP_LOCK_MSK                               (COMP_LOCK)
#define COMP1_LOCK                                  (COMP_LOCK_CMP1LK)
#define COMP2_LOCK                                  (COMP_LOCK_CMP2LK)
#define COMP3_LOCK                                  (COMP_LOCK_CMP3LK)
#define COMP4_LOCK                                  (COMP_LOCK_CMP4LK)

/** COMP_INTEN  **/
#define COMP_INTIEN_MSK                             (COMP_INTEN)
#define COMP1_INTEN                                 (COMP_INTEN_CMP1IEN) 
#define COMP2_INTEN                                 (COMP_INTEN_CMP2IEN)
#define COMP3_INTEN                                 (COMP_INTEN_CMP3IEN)
#define COMP4_INTEN                                 (COMP_INTEN_CMP4IEN)

/** COMP_INTSTS   **/
#define COMP_INTSTS_MSK                             (COMP_INTSTS)
#define COMP1_INTSTS                                (COMP_INTSTS_COMP1IS) 
#define COMP2_INTSTS                                (COMP_INTSTS_COMP2IS)
#define COMP3_INTSTS                                (COMP_INTSTS_COMP3IS)
#define COMP4_INTSTS                                (COMP_INTSTS_COMP4IS)

/** COMP_VREFSCL   **/
#define COMP_VREFSCL_VVEN_MSK                      (COMP1_CTRL_VV1EN)
#define COMP_VREFSCL_VVTRM_MSK                     (COMP1_CTRL_VV1TRM) /** Vref Voltage scaler triming value. **/ 

/** COMP_OTIMEN   **/
#define COMP_TIM_EN_MSK                             (COMP_OTIMEN_MASK)
#define COMP1_TIM_EN                                (COMP_OTIMEN_CMP1OEN) 
#define COMP2_TIM_EN                                (COMP_OTIMEN_CMP2OEN)
#define COMP3_TIM_EN                                (COMP_OTIMEN_CMP3OEN)
#define COMP4_TIM_EN                                (COMP_OTIMEN_CMP4OEN)

/** COMP Init structure definition **/
typedef struct
{
    COMP_CTRL_BLKING Blking; 

    COMP_CTRL_HYST Hyst;

    FunctionalState PolRev; /* out polarity reverse */ 

    COMP_CTRL_INPSEL InpSel;
    COMP_CTRL_INMSEL InmSel;

    FunctionalState En;    /* COMP enable */ 

    /* filter config */
    uint8_t SampWindow;  /* 5bit */
    uint8_t Threshold;     /* 5bit need > SampWindow/2 */
    FunctionalState FilterEn;

    /* filter psc config */
    uint16_t ClkPsc;
} COMP_InitType;


/** COMP_Exported_Functions **/
void COMP_DeInit(void);
void COMP_StructInit(COMP_InitType* COMP_InitStruct);
void COMP_Init(COMPX COMPx, COMP_InitType* COMP_InitStruct);

void COMP_Enable(COMPX COMPx, FunctionalState Cmd);
void COMP_SetInpSel(COMPX COMPx, COMP_CTRL_INPSEL VpSel);
void COMP_SetInmSel(COMPX COMPx, COMP_CTRL_INMSEL VmSel);
void COMP_SetHyst(COMPX COMPx , COMP_CTRL_HYST HYST);
void COMP_SetBlanking(COMPX COMPx , COMP_CTRL_BLKING BLK);

void COMP_SetFilterPrescaler(COMPX COMPx , uint16_t FilPreVal);
void COMP_SetFilterControl(COMPX COMPx , uint8_t FilEn, uint8_t TheresNum , uint8_t SampPW);
void COMP_EnableVflag(COMPX COMPx, uint32_t InputMode, FunctionalState Cmd);

FlagStatus COMP_GetOutStatus(COMPX COMPx);
FlagStatus COMP_GetFilterOutStatus(COMPX COMPx);

void COMP_SetLowPowerMode(FunctionalState Cmd);
void COMP_WindowModeEnable(uint32_t WinModeEn, FunctionalState Cmd);
void COMP_SetLock(uint32_t Lock);
void COMP_SetIntEn(uint32_t IntEn, FunctionalState Cmd);

FlagStatus COMP_GetIntStsOneComp(COMPX COMPx);
void COMP_ClearIntStsOneComp(COMPX COMPx);

void COMP_SetRefScl( uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En); 
void COMP_OutToTimEnable(uint32_t TimEn, FunctionalState Cmd);

#ifdef __cplusplus
}
#endif

#endif /*__N32H7XX_COMP_H__ */


