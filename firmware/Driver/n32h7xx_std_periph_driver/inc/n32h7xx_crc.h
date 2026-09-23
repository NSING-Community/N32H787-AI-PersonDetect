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
 * @file n32h7xx_crc.h
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H7XX_CRC_H__
#define __N32H7XX_CRC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

#include "n32h7xx.h"

typedef struct
{
    uint32_t GeneratingPolynomial;      /* Set CRC generating polynomial as a 7, 8, 16 or 32-bit long value for a polynomial degree
                                           respectively equal to 7, 8, 16 or 32. This field is written in normal,
                                           representation e.g., for a polynomial of degree 7, X^7 + X^6 + X^5 + X^2 + 1
                                           is written 0x65.  */
    uint32_t CRCLength;                 /* This parameter is a value of ref CRC_Polynomial_Sizes and indicates CRC length.
                                           Value can be either one of
                                           arg ref CRC_POLYLENGTH_32B                  (32-bit CRC),
                                           arg ref CRC_POLYLENGTH_16B                  (16-bit CRC),
                                           arg ref CRC_POLYLENGTH_8B                   (8-bit CRC),
                                           arg ref CRC_POLYLENGTH_7B                   (7-bit CRC). */
    uint32_t InitValue;                 /* Init value to initiate CRC computation. No need to specify it if DefaultInitValueUse
                                           is set to DEFAULT_INIT_VALUE_ENABLE.   */
    uint32_t InputDataByteInversionMode;    /* This parameter is a value of ref CRC Input Data Byte Reverse and specifies input data byte inversion mode.
                                           Can be either one of the following values
                                           arg ref CRC_INDATA_BYTE_REVERSE_NONE       no input data inversion
                                           arg ref CRC_INDATA_BYTE_REVERSE_HALFWORD   halfword-wise inversion,0x1A2B3C4D becomes 0x2B1A4D3C
                                           arg ref CRC_INDATA_BYTE_REVERSE_WORD       word-wise inversion, 0x1A2B3C4D becomes 0x4D3C2B1A */
    uint32_t InputDataBitInversionMode;    /* This parameter is a value of ref CRC Input Data Bit Reverse and specifies input data inversion mode.
                                           Can be either one of the following values
                                           arg ref CRC_INDATA_BIT_REVERSE_NONE       no input data inversion
                                           arg ref CRC_INDATA_BIT_REVERSE_BYTE       byte-wise inversion, 0x1A2B3C4D becomes 0x58D43CB2
                                           arg ref CRC_INDATA_BIT_REVERSE_HALFWORD   halfword-wise inversion,0x1A2B3C4D becomes 0xD458B23C
                                           arg ref CRC_INDATA_BIT_REVERSE_WORD       word-wise inversion, 0x1A2B3C4D becomes 0xB23CD458 */
    uint32_t OutputDataInversionMode;   /* This parameter is a value of ref CRC Output Data Reverse and specifies output data (i.e. CRC) inversion mode.
                                            Can be either
                                            arg ref CRC_OUTPUTDATA_INVERSION_DISABLE   no CRC inversion,
                                            arg ref CRC_OUTPUTDATA_INVERSION_ENABLE    CRC 0x11223344 is converted into 0x22CC4488 */
    uint32_t InputDataXor;              /* This parameter is used to set CRC_DR XOR calculation value before CRC calculation. */

    uint32_t OutputDataXor;             /*  This parameter is used to set CRC_DR XOR calculation value after CRC calculation.  */
} CRC_InitType;

/**  CRC_Default_Polynomial_Value   Default CRC generating polynomial **/
#define DEFAULT_CRC32_POLY      ((uint32_t)0x04C11DB7U) /*  X^32 + X^26 + X^23 + X^22 + X^16 + X^12 + X^11 + X^10 +X^8 + X^7 + X^5 + X^4 + X^2+ X +1 */

/** CRC_Default_InitValue    Default CRC computation initialization value */
#define DEFAULT_CRC_INITVALUE   ((uint32_t)0xFFFFFFFFU) /* Initial CRC default value */

/** CRC_Polynomial_Sizes Polynomial sizes to configure the peripheral */
#define CRC_POLYLENGTH_32B                  ((uint32_t)0x00000000U) /* Resort to a 32-bit long generating polynomial */
#define CRC_POLYLENGTH_16B                  (CRC_CTRL_POLYSIZE_0)   /* Resort to a 16-bit long generating polynomial */
#define CRC_POLYLENGTH_8B                   (CRC_CTRL_POLYSIZE_1)   /* Resort to a 8-bit long generating polynomial  */
#define CRC_POLYLENGTH_7B                   (CRC_CTRL_POLYSIZE)     /* Resort to a 7-bit long generating polynomial  */

/** CRC Input Data Byte Reverse */
#define CRC_INDATA_BYTE_REVERSE_NONE        ((uint32_t)0x00000000U) /* Input Data Byte order not affected */
#define CRC_INDATA_BYTE_REVERSE_HALFWORD    (CRC_CTRL_BYTEENDIAN_1) /* Input Data Byte reversal done by half-word */
#define CRC_INDATA_BYTE_REVERSE_WORD        (CRC_CTRL_BYTEENDIAN)   /* Input Data Byte reversal done by word */

/** CRC Input Data Bit Reverse */
#define CRC_INDATA_BIT_REVERSE_NONE         ((uint32_t)0x00000000U) /* Input Data bit order not affected */
#define CRC_INDATA_BIT_REVERSE_BYTE         (CRC_CTRL_REVIN_0)      /* Input Data bit reversal done by byte */
#define CRC_INDATA_BIT_REVERSE_HALFWORD     (CRC_CTRL_REVIN_1)      /* Input Data bit reversal done by half-word */
#define CRC_INDATA_BIT_REVERSE_WORD         (CRC_CTRL_REVIN_1 \
                                            |CRC_CTRL_REVIN_0)      /* Input Data bit reversal done by word */

/** CRC Output Data Reverse */
#define CRC_OUTDATA_REVERSE_NONE            ((uint32_t)0x00000000U) /* Output Data bit order not affected */
#define CRC_OUTDATA_REVERSE_BIT             (CRC_CTRL_REVOUT)       /* Output Data bit reversal done by bit */

/** CRC_Input_Buffer_Format Input Buffer Format */
#define CRC_INPUTDATA_FORMAT_BYTES          ((uint32_t)0x00000001U) /* Input data in byte format      */
#define CRC_INPUTDATA_FORMAT_HALFWORDS      ((uint32_t)0x00000002U) /* Input data in half-word format */
#define CRC_INPUTDATA_FORMAT_WORDS          ((uint32_t)0x00000003U) /* Input data in word format      */


void CRC_ResetCalculation(void);
void CRC_DeInit(void);
void CRC_SetInputByteOrder(uint32_t ReverseMode);
void CRC_SetInputBitOrder(uint32_t ReverseMode);
void CRC_SetOutputBitOrder(uint32_t ReverseMode);
void CRC_SetInputDataXor(uint32_t xor_value);
void CRC_SetOutputDataXor(uint32_t xor_value);
void CRC_SetInitialData(uint32_t InitCrc);
void CRC_SetPolynomialCoef(uint32_t PolynomCoef);
void CRC_SetPolynomialSize(uint32_t PolySize);

void CRC_StructInit(CRC_InitType *CRC_InitStruct);
void CRC_Init(CRC_InitType *CRC_InitStruct);
uint32_t CRC_Calculate(uint32_t InputDataFormat, void *pBuffer, uint32_t BufferLength);
uint32_t CRC_Accumulate(uint32_t InputDataFormat, void *pBuffer, uint32_t BufferLength);
uint32_t CRC_GetLRC(void);
uint32_t CRC_GetIDAT(void);
void CRC_WriteIDAT(uint32_t Idat);


#ifdef __cplusplus
}
#endif

#endif /* __N32H7XX_CRC_H__ */


