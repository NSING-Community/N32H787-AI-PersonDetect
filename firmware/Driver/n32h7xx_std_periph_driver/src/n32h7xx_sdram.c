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
 * @file n32h7xx_sdram.c
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h7xx_sdram.h"
#include "n32h7xx_rcc.h"

/**
*\*\name    SDRAM_DeInit.
*\*\fun     Deinitializes the SDRAM module to their default reset values.
*\*\param   none
*\*\return  none
**/
void SDRAM_DeInit(void)
{
    /* SDRAM soft reset */
    RCC_EnableAXIPeriphReset4(RCC_AXI_PERIPHRST_SDRAM);
}

/**
*\*\name    SDRAM_TimingInit.
*\*\fun     SDRAM Timing Registers Configuration.
*\*\param   Timing: The parameter range is as follows
*\*\            - RowActiveTime       : from 1 to 64
*\*\            - RowCycleTime        : from 1 to 64
*\*\            - RowActToRowActDelay : from 1 to 64
*\*\            - PrechargeTime       : from 1 to 64
*\*\            - WriteRecoveryTime   : from 1 to 64
*\*\            - RefreshCycleTime    : from 1 to 64
*\*\            - RAStoCASDelay       : from 1 to 16
*\*\return  none
**/
void SDRAM_TimingInit(SDRAM_TimingType *Timing)
{
    SDRAM->RAT    = Timing->RowActiveTime;
    SDRAM->RCT    = Timing->RowCycleTime;
    SDRAM->RRDLY  = Timing->RowActToRowActDelay;
    SDRAM->PT     = Timing->PrechargeTime;
    SDRAM->WRT    = Timing->WriteRecoveryTime;
    SDRAM->RFCT   = Timing->RefreshCycleTime;
    SDRAM->RCDLY  = Timing->RAStoCASDelay;
}

/**
*\*\name    SDRAM_RefreshIntervalInit.
*\*\fun     Configure the refresh interval parameter.
*\*\param   The input parameters must be the following values:
*\*\          - RefreshIntervalTime: from 1 to 16777216
*\*\return  none
**/
void SDRAM_RefreshIntervalInit(uint32_t RefreshIntervalTime)
{
    SDRAM->RI = RefreshIntervalTime;
}

/**
*\*\name    SDRAM_SetAddress.
*\*\fun     SDRAM set Base Address and mask address.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - BaseAddr
*\*\               - 0xC0000000    Default value for SDRAM1
*\*\               - 0xD0000000    Default value for SDRAM2
*\*\          - AddrMask
*\*\               - (0xFFFFFFFF-(SDRAM SIZE-1))
*\*\return  none
**/
void SDRAM_SetDeviceAddress(SDRAM_DeviceType DeviceNo, uint32_t BaseAddr, uint32_t AddrMask)
{
    if(DeviceNo == SDRAM_DEVICE_1)
    {
        SDRAM->BADD1    = BaseAddr;
        SDRAM->ADDMASK1 = AddrMask;
    }
    else
    {
        SDRAM->BADD2    = BaseAddr;
        SDRAM->ADDMASK2 = AddrMask;
    }
}

/**
*\*\name    SDRAM_EnableDevice.
*\*\fun     SDRAM Device enable.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableDevice(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM Device*/
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Device */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_EnableRefreshCMD.
*\*\fun     SDRAM Refresh enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableRefreshCMD(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM Refresh */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_REFRESH_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_REFRESH_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Refresh */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_REFRESH_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_REFRESH_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_EnableAutoPrecharge.
*\*\fun     SDRAM Auto Precharge enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableAutoPrecharge(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM Auto Precharge */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_AUTOPRECHRG_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_AUTOPRECHRG_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Auto Precharge */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_AUTOPRECHRG_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_AUTOPRECHRG_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_EnablePrefetchRead.
*\*\fun     SDRAM Prefetch Read enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnablePrefetchRead(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM Prefetch Read */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_PREFETCHREAD_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_PREFETCHREAD_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Prefetch Read */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_PREFETCHREADG_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_PREFETCHREADG_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_EnableSOM.
*\*\fun     SDRAM Store On Miss(SOM) enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableSOM(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM Store On Miss(SOM) */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_SOM_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_SOM_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Store On Miss(SOM) */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_SOM_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_SOM_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_EnableBankInterleave.
*\*\fun     SDRAM BankInterleave enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableBankInterleave(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM BankInter leave */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_BANKIL_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_BANKIL_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Bank Interleave */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_BANKIL_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_BANKIL_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_ConfigBusWidth.
*\*\fun     Configures the SDRAM Bus Width of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - BusWidth:
*\*\               - SDRAM_DEVICE_BUSWID_8BITS
*\*\               - SDRAM_DEVICE_BUSWID_16BITS
*\*\               - SDRAM_DEVICE_BUSWID_32BITS
*\*\return  none
**/
void SDRAM_ConfigBusWidth(SDRAM_DeviceType DeviceNo, uint32_t BusWidth)
{
    uint32_t reg_value;

    /* Configures the selected SDRAM Bus Width */
    if(DeviceNo == SDRAM_DEVICE_1)
    {
        reg_value = SDRAM->CFG1;
        reg_value &= SDRAM_DEVICE_BUSWID_MASK;
        reg_value |= BusWidth;
        SDRAM->CFG1 = reg_value;
    }
    else
    {
        reg_value = SDRAM->CFG2;
        reg_value &= SDRAM_DEVICE_BUSWID_MASK;
        reg_value |= BusWidth;
        SDRAM->CFG2 = reg_value;
    }
}

/**
*\*\name    SDRAM_ConfigBurstLength.
*\*\fun     Configures the SDRAM Burst Length of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - BurstLength:
*\*\               - SDRAM_DEVICE_BURSTLEN_1
*\*\               - SDRAM_DEVICE_BURSTLEN_2
*\*\               - SDRAM_DEVICE_BURSTLEN_4
*\*\               - SDRAM_DEVICE_BURSTLEN_8
*\*\return  none
**/
void SDRAM_ConfigBurstLength(SDRAM_DeviceType DeviceNo, uint32_t BurstLength)
{
    uint32_t reg_value;

    /* Configures the selected SDRAM Burst Length */
    if(DeviceNo == SDRAM_DEVICE_1)
    {
        reg_value = SDRAM->CFG1;
        reg_value &= SDRAM_DEVICE_BURSTLEN_MASK;
        reg_value |= BurstLength;
        SDRAM->CFG1 = reg_value;
    }
    else
    {
        reg_value = SDRAM->CFG2;
        reg_value &= SDRAM_DEVICE_BURSTLEN_MASK;
        reg_value |= BurstLength;
        SDRAM->CFG2 = reg_value;
    }
}

/**
*\*\name    SDRAM_ConfigCASLatency.
*\*\fun     Configures the SDRAM CAS Latency of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - CASLatency:
*\*\               - SDRAM_DEVICE_CASLTCY_0
*\*\               - SDRAM_DEVICE_CASLTCY_1
*\*\               - SDRAM_DEVICE_CASLTCY_2
*\*\               - SDRAM_DEVICE_CASLTCY_3
*\*\return  none
**/
void SDRAM_ConfigCASLatency(SDRAM_DeviceType DeviceNo, uint32_t Latency)
{
    uint32_t reg_value;

    /* Configures the selected SDRAM CAS Latency */
    if(DeviceNo == SDRAM_DEVICE_1)
    {
        reg_value = SDRAM->CFG1;
        reg_value &= SDRAM_DEVICE_CASLTCY_MASK;
        reg_value |= Latency;
        SDRAM->CFG1 = reg_value;
    }
    else
    {
        reg_value = SDRAM->CFG2;
        reg_value &= SDRAM_DEVICE_CASLTCY_MASK;
        reg_value |= Latency;
        SDRAM->CFG2 = reg_value;
    }
}

/**
*\*\name    SDRAM_ConfigAddress.
*\*\fun     Configures the SDRAM Address of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Address:
*\*\               - SDRAM_BANK4_ROW4096_COL256
*\*\               - SDRAM_BANK4_ROW4096_COL512
*\*\               - SDRAM_BANK4_ROW4096_COL1024
*\*\               - SDRAM_BANK4_ROW4096_COL2048
*\*\               - SDRAM_BANK4_ROW8192_COL256
*\*\               - SDRAM_BANK4_ROW8192_COL512
*\*\               - SDRAM_BANK4_ROW8192_COL1024
*\*\               - SDRAM_BANK4_ROW8192_COL2048
*\*\               - SDRAM_BANK4_ROW2048_COL256
*\*\               - SDRAM_BANK4_ROW2048_COL512
*\*\               - SDRAM_BANK4_ROW2048_COL1024
*\*\               - SDRAM_BANK4_ROW2048_COL2048
*\*\return  none
**/
void SDRAM_ConfigAddress(SDRAM_DeviceType DeviceNo, uint32_t Address)
{
    uint32_t reg_value;

    /* Configures the selected SDRAM Address */
    if(DeviceNo == SDRAM_DEVICE_1)
    {
        reg_value = SDRAM->CFG1;
        reg_value &= SDRAM_DEVICE_ADDCFG_MASK;
        reg_value |= Address;
        SDRAM->CFG1 = reg_value;
    }
    else
    {
        reg_value = SDRAM->CFG2;
        reg_value &= SDRAM_DEVICE_ADDCFG_MASK;
        reg_value |= Address;
        SDRAM->CFG2 = reg_value;
    }
}

/**
*\*\name    SDRAM_EnableClock.
*\*\fun     SDRAM Clock enable.
*\*\param   The input parameters must be the following values:
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableClock(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the SDRAM Clock */
        SDRAM->OS |= SDRAM_CLOCK_ENABLE;
    }
    else
    {
        /* Disable the SDRAM Clock */
        SDRAM->OS &= SDRAM_CLOCK_DISABLE;
    }
}

/**
*\*\name    SDRAM_SetOperationCode.
*\*\fun     Set the SDRAM Operation Code.
*\*\param   The input parameters must be the following values:
*\*\          - OperationCode:
*\*\               - SDRAM_OPCODE_NONE
*\*\               - SDRAM_OPCODE_PRECHRG
*\*\               - SDRAM_OPCODE_REFRESH
*\*\               - SDRAM_OPCODE_LOADMODE
*\*\return  none
**/
void SDRAM_SetOperationCode(uint32_t OperationCode)
{
    uint32_t reg_value;

    reg_value = SDRAM->OS;
    /* Clear the SDRAM Operation Code */
    reg_value &= SDRAM_OPCODE_MASK;
    /* Set the SDRAM Operation Code */
    reg_value |= OperationCode;
    SDRAM->OS = reg_value;
}

/**
*\*\name    SDRAM_SetDeviceSelect.
*\*\fun     Set the SDRAM Device.
*\*\param   The input parameters must be the following values:
*\*\          - ChipSelect:
*\*\               - SDRAM_CS_ALL
*\*\               - SDRAM_CS_SDRAM2_ONLY
*\*\               - SDRAM_CS_SDRAM1_ONLY
*\*\               - SDRAM_CS_NONE
*\*\return  none
**/
void SDRAM_SetDeviceSelect(uint32_t ChipSelect)
{
    uint32_t reg_value;

    reg_value = SDRAM->OS;
    /* Clear the SDRAM Device */
    reg_value &= SDRAM_CS_MASK;
    /* Set the SDRAM Device */
    reg_value |= ChipSelect;
    SDRAM->OS = reg_value;
}

/**
*\*\name    SDRAM_SetBank.
*\*\fun     Set the SDRAM Bank.
*\*\param   The input parameters must be the following values:
*\*\          - BankNo:
*\*\               - SDRAM_BANKADD_1
*\*\               - SDRAM_BANKADD_2
*\*\               - SDRAM_BANKADD_3
*\*\               - SDRAM_BANKADD_4
*\*\return  none
**/
void SDRAM_SetBank(uint32_t BankNo)
{
    uint32_t reg_value;

    reg_value = SDRAM->OS;
    /* Clear the SDRAM Bank */
    reg_value &= SDRAM_BANKADD_MASK;
    /* Set the SDRAM Bank */
    reg_value |= BankNo;
    SDRAM->OS = reg_value;
}

/**
*\*\name    SDRAM_SetAddress.
*\*\fun     Set the SDRAM Bank.
*\*\param   The input parameters must be the following values:
*\*\          - Address:
*\*\return  none
**/
void SDRAM_SetAddress(uint32_t Address)
{
    uint32_t reg_value;

    reg_value = SDRAM->OS;
    /* Clear the SDRAM Address */
    reg_value &= SDRAM_OS_ADDRESS_MASK;
    /* Set the SDRAM Address */
    reg_value |= (Address & SDRAM_OS_ADD);
    SDRAM->OS = reg_value;
}

/**
*\*\name    SDRAM_EnableWriteProtection.
*\*\fun     Write protection enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableWriteProtection(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the Write protection of selected SDRAM Device*/
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->WP |= SDRAM_WP_SDRAM1_ENABLE;
        }
        else
        {
            SDRAM->WP |= SDRAM_WP_SDRAM2_ENABLE;
        }
    }
    else
    {
        /* Disable the Write protection of selected SDRAM Device */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->WP &= SDRAM_WP_SDRAM1_DISABLE;
        }
        else
        {
            SDRAM->WP &= SDRAM_WP_SDRAM2_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_EnableAddressRemap.
*\*\fun     SDRAM1 address remapped from 0xC0000000 to 0x60000000.
*\*\param   The input parameters must be the following values:
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableAddressRemap(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        FEMC->FEMC_REMAP = SDRAM_REMAP_ENABLE;
    }
    else
    {
        FEMC->FEMC_REMAP = SDRAM_REMAP_DISABLE;
    }
}



