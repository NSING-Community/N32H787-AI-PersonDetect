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
 * @file n32h7xx_smu.h
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H7XX_SMU_H__
#define __N32H7XX_SMU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h7xx.h"

/** n32h7xx_StdPeriph_Driver **/

/** SMU_Exported_Constants **/

/** Flash Operation Error Code Macro Definition **/
typedef enum{
    FLASH_SUCCESS           = 0U,
    FLASH_BUS_ADDR_ERROR    = 1U,
    FLASH_LOGIC_ADDR_ERROR  = 2U,
    FLASH_RESTRICTED        = 3U,
    FLASH_RDP_PROTECTED     = 4U,
    FLASH_SECURE_AREA       = 5U,
    FLASH_PFOER_AREA        = 6U,
    FLASH_WRP_PROTECTED     = 7U,
    FLASH_FAILED            = 8U
}FLASH_ErrCode;


typedef enum{
    RDP_L0 = 0U,
    RDP_L1 = 1U,
    RDP_L2 = 2U,
}RDPLEVEL;



/*API Status Code*/
#define  SMU_SUCCESS                       ((uint32_t)0x1000U)
#define  SMU_INVAILED                      ((uint32_t)0x1002U)
#define  SMU_RDP_L2_ERR                    ((uint32_t)0x1003U)
#define  SMU_UNCHANGE_ERR                  ((uint32_t)0x1004U)
#define  SMU_PARA_ERR                      ((uint32_t)0x1005U)
#define  SMU_OTHER_ERR                     ((uint32_t)0x101BU)





/*Boot API Address Pointer adresss*/
#define  GET_M4ADDR                         (0x1ff00601)
#define  SET_M4ADDR                         (0x1ff00631)
#define  GET_M7ADDR                         (0x1ff005c1)
#define  SET_M7ADDR                         (0x1ff00501)
#define  GET_RDPLevel                       (0x1ff00011)
#define  SET_RDPLevel                       (0x1ff00081)
#define  SET_AHBSRAMProtection              (0x1ff01701)
#define  SET_ITCMProtection                 (0x1ff01601)
#define  GET_FLASHWRProtection              (0x1ff001a1)
#define  SET_FLASHWRProtection              (0x1ff00201)
#define  WR_FLASH                           (0x1fff7b81)
#define  ER_FLASH                           (0x1fff7c81)






uint32_t SMU_GetM4BootAddr( void );
ErrorStatus SMU_SetM4BootAddr( uint32_t addr );
uint32_t SMU_GetM7BootAddr( void );
ErrorStatus SMU_SetM7BootAddr( uint32_t addr );

/*Set RDP Function*/
RDPLEVEL SMU_GetRDPLevel( void );
ErrorStatus SMU_SetRDPLevel( RDPLEVEL RDPLevel );

/*Set Write Protectio Area*/
ErrorStatus SMU_EnWriteProtection(uint32_t WRPSector);
uint32_t SMU_GetWriteProtection( void );

/*Set Protectio Area*/
ErrorStatus SMU_SetITCMProtection(uint32_t StrAddr, uint32_t EndAddr);
ErrorStatus SMU_SetSRAMProtection(uint32_t StrAddr, uint32_t EndAddr);

/*Flash operation*/
uint32_t SMU_EraseFlash(uint32_t StrAddr);
uint32_t SMU_WriteFlash(uint32_t StrAddr, uint8_t *SrcBuf, uint32_t Len);   
    
#ifdef __cplusplus
}
#endif

#endif /*__N32H7XX_SMU_H__ */
