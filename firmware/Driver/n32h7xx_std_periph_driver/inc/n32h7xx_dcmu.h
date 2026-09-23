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
 * @file n32h7xx_dcmu.h
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H7XX_DCMU_H__
#define __N32H7XX_DCMU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h7xx.h"

/** n32h7xx_StdPeriph_Driver **/

/** DCMU_Exported_Constants **/

/** DCMU Min and Max Define **/
#define DCMU_TXMSGID_MIN      (0U)       /* DCMU Transmit Messaging Register ID Min */
#define DCMU_TXMSGID_MAX      (3U)       /* DCMU Transmit Messaging Register ID Max */
#define DCMU_RXMSGID_MIN      (0U)       /* DCMU Receive Messaging Register ID Min */
#define DCMU_RXMSGID_MAX      (3U)       /* DCMU Receive Messaging Register ID Max */
#define DCMU_GPIRID_MIN       (0U)       /* DCMU General Purpose Interrupt Request ID Min */
#define DCMU_GPIRID_MAX       (3U)       /* DCMU General Purpose Interrupt Request ID Max */
#define DCMU_FLAGID_MIN       (0U)       /* DCMU Flag ID Min */
#define DCMU_FLAGID_MAX       (2U)       /* DCMU Flag ID Max */

#define DCMU_CTRL_GPIE0_MASK      (DCMU_CTRL_GPIE0)
#define DCMU_CTRL_GPIE1_MASK      (DCMU_CTRL_GPIE1)
#define DCMU_CTRL_GPIE2_MASK      (DCMU_CTRL_GPIE2)
#define DCMU_CTRL_GPIE3_MASK      (DCMU_CTRL_GPIE3)
#define DCMU_CTRL_TEIE0_MASK      (DCMU_CTRL_TEIE0)
#define DCMU_CTRL_TEIE1_MASK      (DCMU_CTRL_TEIE1)
#define DCMU_CTRL_TEIE2_MASK      (DCMU_CTRL_TEIE2)
#define DCMU_CTRL_TEIE3_MASK      (DCMU_CTRL_TEIE3)

#define DCMU_CTRL_RFIE0_MASK      (DCMU_CTRL_RFIE0)
#define DCMU_CTRL_RFIE1_MASK      (DCMU_CTRL_RFIE1)
#define DCMU_CTRL_RFIE2_MASK      (DCMU_CTRL_RFIE2)
#define DCMU_CTRL_RFIE3_MASK      (DCMU_CTRL_RFIE3)

#define DCMU_CTRL_GPIE_ALL_MASK   (DCMU_CTRL_GPIE0 | DCMU_CTRL_GPIE1 | DCMU_CTRL_GPIE2 | DCMU_CTRL_GPIE3) 
#define DCMU_CTRL_TEIE_ALL_MASK   (DCMU_CTRL_TEIE0 | DCMU_CTRL_TEIE1 | DCMU_CTRL_TEIE2 | DCMU_CTRL_TEIE3) 
#define DCMU_CTRL_RFIE_ALL_MASK   (DCMU_CTRL_RFIE0 | DCMU_CTRL_RFIE1 | DCMU_CTRL_RFIE2 | DCMU_CTRL_RFIE3) 
#define DCMU_CTRL_ALL_IE_MASK     (DCMU_CTRL_GPIE_ALL_MASK|DCMU_CTRL_TEIE_ALL_MASK|DCMU_CTRL_RFIE_ALL_MASK)

#define DCMU_CTRL_GPIR0_MASK      (DCMU_CTRL_GPIR0)
#define DCMU_CTRL_GPIR1_MASK      (DCMU_CTRL_GPIR1)
#define DCMU_CTRL_GPIR2_MASK      (DCMU_CTRL_GPIR2)
#define DCMU_CTRL_GPIR3_MASK      (DCMU_CTRL_GPIR3)
#define DCMU_CTRL_GPIR_ALL_MASK   (DCMU_CTRL_GPIR0_MASK | DCMU_CTRL_GPIR1_MASK | DCMU_CTRL_GPIR2_MASK | DCMU_CTRL_GPIR3_MASK)

#define DCMU_CTRL_RST_MASK        (DCMU_CTRL_RST)

#define DCMU_CTRL_TXFN0_MASK      (DCMU_CTRL_TXFN0)
#define DCMU_CTRL_TXFN1_MASK      (DCMU_CTRL_TXFN1)
#define DCMU_CTRL_TXFN2_MASK      (DCMU_CTRL_TXFN2)
#define DCMU_CTRL_TXFN_ALL_MASK   (DCMU_CTRL_TXFN0_MASK | DCMU_CTRL_TXFN1_MASK | DCMU_CTRL_TXFN2_MASK)

#define DCMU_STS_GPIF0_MASK       (DCMU_STS_GPIF0)
#define DCMU_STS_GPIF1_MASK       (DCMU_STS_GPIF1)
#define DCMU_STS_GPIF2_MASK       (DCMU_STS_GPIF2)
#define DCMU_STS_GPIF3_MASK       (DCMU_STS_GPIF3)
#define DCMU_STS_TEF0_MASK        (DCMU_STS_TEF0)
#define DCMU_STS_TEF1_MASK        (DCMU_STS_TEF1)
#define DCMU_STS_TEF2_MASK        (DCMU_STS_TEF2)
#define DCMU_STS_TEF3_MASK        (DCMU_STS_TEF3)
#define DCMU_STS_RFF0_MASK        (DCMU_STS_RFF0)
#define DCMU_STS_RFF1_MASK        (DCMU_STS_RFF1)
#define DCMU_STS_RFF2_MASK        (DCMU_STS_RFF2)
#define DCMU_STS_RFF3_MASK        (DCMU_STS_RFF3)

#define DCMU_STS_GPIF_ALL_MASK    (DCMU_STS_GPIF0_MASK|DCMU_STS_GPIF1_MASK|DCMU_STS_GPIF2_MASK|DCMU_STS_GPIF3_MASK)
#define DCMU_STS_TEF_ALL_MASK     (DCMU_STS_TEF0_MASK|DCMU_STS_TEF1_MASK|DCMU_STS_TEF2_MASK|DCMU_STS_TEF3_MASK)
#define DCMU_STS_RFF_ALL_MASK     (DCMU_STS_RFF0_MASK|DCMU_STS_RFF1_MASK|DCMU_STS_RFF2_MASK|DCMU_STS_RFF3_MASK)

#define DCMU_STS_EPF_MASK         (DCMU_STS_EPF) 
#define DCMU_STS_FUPF_MASK        (DCMU_STS_FUPF) 
#define DCMU_STS_RSTF_MASK        (DCMU_STS_RSTF) 

#define DCMU_STS_RCVFN0_MASK      (DCMU_STS_RCVFN0)
#define DCMU_STS_RCVFN1_MASK      (DCMU_STS_RCVFN1)
#define DCMU_STS_RCVFN2_MASK      (DCMU_STS_RCVFN2)
#define DCMU_STS_RCVFN_ALL_MASK   (DCMU_STS_RCVFN0_MASK|DCMU_STS_RCVFN1_MASK|DCMU_STS_RCVFN2_MASK)


/** DCMU_Exported_Typedef_t **/
typedef enum dcmu_wait_mode
{
	NON_BLOCKING =0,
	BLOCKING

}dcmu_wait_mode_t;

typedef enum dcmu_txmsg_idx
{
	TXMSG_IDX0 = 0,
	TXMSG_IDX1    ,
	TXMSG_IDX2    ,
	TXMSG_IDX3

}dcmu_txmsg_idx_t;

typedef enum dcmu_rcvmsg_idx
{
	RCVMSG_IDX0 = 0,
	RCVMSG_IDX1    ,
	RCVMSG_IDX2    ,
	RCVMSG_IDX3

}dcmu_rcvmsg_idx_t;

typedef enum dcmu_gpi_idx
{
	GPI_IDX0 = 0,
	GPI_IDX1    ,
	GPI_IDX2    ,
	GPI_IDX3

}dcmu_gpi_idx_t;




/** DCMU_Exported_Functions **/

void DCMU_DeInit( void );

#if defined(CORE_CM7)
void DCMU_SelfReset( void );
#endif

void DCMU_TransmitMsg( uint8_t TxIdx, uint32_t TxMsgData, dcmu_wait_mode_t Mode);
uint32_t DCMU_ReceiveMsg( uint8_t RcvIdx, dcmu_wait_mode_t Mode);
void DCMU_Set3BitFlagNumbers( uint8_t FlagData, dcmu_wait_mode_t Mode);
uint8_t DCMU_Get3BitFlagNumbers( void );
uint32_t DCMU_GetStatusFlags( uint32_t StatusMask);
uint32_t DCMU_GetIntPendingFlags( uint32_t IntPendingMask);
void DCMU_ClearIntPendingFlags( uint32_t GPIntPendingMask);
void DCMU_ConfigInt( uint32_t IntMask, FunctionalState Cmd);
void DCMU_RequestGPInt( uint32_t ReqGPIntMask);

#ifdef __cplusplus
}
#endif

#endif /*__N32H7XX_DCMU_H__ */
