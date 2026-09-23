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
 * @file system_n32h7xx.c
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h7xx.h"

#if !defined  (HSE_VALUE)
#define HSE_VALUE    ((uint32_t)8000000UL) /* Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (CSI_VALUE)
  #define CSI_VALUE           ((uint32_t)4000000UL) /* Value of the Internal oscillator in Hz*/
#endif /* CSI_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE           ((uint32_t)64000000UL) /* Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#ifndef VECT_TAB_OFFSET
#define VECT_TAB_OFFSET       ((uint32_t)0x00000000UL) /* Vector Table base offset field.   */
#endif

#define FLASH_BANK1_BASE      (0x15000000U)

#define FLASH_BANK2_BASE      (0x15080000U)

#ifndef VECT_TAB_BASE
#define VECT_TAB_BASE         FLASH_BANK1_BASE
#endif

uint32_t SystemCoreClock = 600000000;

#define TCM_SIZE_VALUE        (0x15) /*256 KiB ITCM,512 KiB DTCM,256 KiB AXI SRAM2,128 KiB AXI SRAM1*/

volatile uint32_t g_tcm_boot_config;

/** Private_Functions  */

/* defaule power supply is extern LDO. User can change the way of power supply*/
//#define PWR_SUPPLY_SELECTION       (PWR_LDO_SUPPLY)  /* External LDO Supply  */
#define PWR_SUPPLY_SELECTION       (PWR_DIRECT_SMPS_SUPPLY)  /* DCDC Supply  */
//#define PWR_SUPPLY_SELECTION       (PWR_EXTERNAL_SOURCE_SUPPLY)  /* VCAP Supply  */

/**
 *\*\name   ConfigTcmSize.
 *\*\fun    Config TCM_SIZE
 *\*\param  tcmSizeValue 
 *\*\    for N32H76x and N32H78x (The input parameters must be the following values):
 *\*\           0x00 :1024KB ITCM,  0   KB DTCM,  0   KB AXI_SRAM2/3,  128KB AXI SRMA1 
 *\*\           0x01 :896 KB ITCM,  128 KB DTCM,  0   KB AXI_SRAM2/3,  128KB AXI SRMA1 
 *\*\           0x02 :768 KB ITCM,  256 KB DTCM,  0   KB AXI_SRAM2/3,  128KB AXI SRMA1 
 *\*\           0x03 :640 KB ITCM,  384 KB DTCM,  0   KB AXI_SRAM2/3,  128KB AXI SRMA1 
 *\*\           0x04 :512 KB ITCM,  512 KB DTCM,  0   KB AXI_SRAM2/3,  128KB AXI SRMA1 
 *\*\           0x05 :384 KB ITCM,  640 KB DTCM,  0   KB AXI_SRAM2/3,  128KB AXI SRMA1 
 *\*\           0x06 :256 KB ITCM,  768 KB DTCM,  0   KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x07 :128 KB ITCM,  896 KB DTCM,  0   KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x08 :0   KB ITCM,  1024KB DTCM,  0   KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x09 :896 KB ITCM,  0   KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x0A :768 KB ITCM,  128 KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x0B :640 KB ITCM,  256 KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x0C :512 KB ITCM,  384 KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x0D :384 KB ITCM,  512 KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x0E :256 KB ITCM,  640 KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x0F :128 KB ITCM,  768 KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x10 :0   KB ITCM,  896 KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x11 :768 KB ITCM,  0   KB DTCM,  256 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x12 :640 KB ITCM,  128 KB DTCM,  256 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x13 :512 KB ITCM,  256 KB DTCM,  256 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x14 :384 KB ITCM,  384 KB DTCM,  256 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x15 :256 KB ITCM,  512 KB DTCM,  256 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x16 :128 KB ITCM,  640 KB DTCM,  256 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x17 :0   KB ITCM,  768 KB DTCM,  256 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x18 :640 KB ITCM,  0   KB DTCM,  384 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x19 :512 KB ITCM,  128 KB DTCM,  384 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x1A :384 KB ITCM,  256 KB DTCM,  384 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x1B :256 KB ITCM,  384 KB DTCM,  384 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x1C :128 KB ITCM,  512 KB DTCM,  384 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x1D :0   KB ITCM,  640 KB DTCM,  384 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x1E :512 KB ITCM,  0   KB DTCM,  512 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x1F :384 KB ITCM,  128 KB DTCM,  512 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x20 :256 KB ITCM,  256 KB DTCM,  512 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x21 :128 KB ITCM,  384 KB DTCM,  512 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x22 :0   KB ITCM,  512 KB DTCM,  512 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x23 :384 KB ITCM,  0   KB DTCM,  640 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x24 :256 KB ITCM,  128 KB DTCM,  640 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x25 :128 KB ITCM,  256 KB DTCM,  640 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x26 :0   KB ITCM,  384 KB DTCM,  640 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x27 :256 KB ITCM,  0   KB DTCM,  768 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x28 :128 KB ITCM,  128 KB DTCM,  768 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x29 :0   KB ITCM,  256 KB DTCM,  768 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x2A :128 KB ITCM,  0   KB DTCM,  896 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x2B :0   KB ITCM,  128 KB DTCM,  896 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x2C~2F :0KB ITCM,  0   KB DTCM,  1024KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\    for N32H73x (The input parameters must be the following values):
 *\*\           0x1E :512 KB ITCM,  0   KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x1F :384 KB ITCM,  128 KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x20 :256 KB ITCM,  256 KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x21 :128 KB ITCM,  384 KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x22 :0   KB ITCM,  512 KB DTCM,  128 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x23 :384 KB ITCM,  0   KB DTCM,  256 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x24 :256 KB ITCM,  128 KB DTCM,  256 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x25 :128 KB ITCM,  256 KB DTCM,  256 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x26 :0   KB ITCM,  384 KB DTCM,  256 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x27 :256 KB ITCM,  0   KB DTCM,  384 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x28 :128 KB ITCM,  128 KB DTCM,  384 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x29 :0   KB ITCM,  256 KB DTCM,  384 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x2A :128 KB ITCM,  0   KB DTCM,  512 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x2B :0   KB ITCM,  128 KB DTCM,  512 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\           0x2C~2F :0KB ITCM,  0   KB DTCM,  640 KB AXI_SRAM2/3,  128KB AXI SRMA1
 *\*\return none  
 */               
void ConfigTcmSize(uint32_t tcmSizeValue)
{
    uint32_t currValue = (*(uint32_t(*)(void))0x1ff00f01)();
    g_tcm_boot_config = currValue;
    /* The SDK mailbox survives a software reset. A firmware upgrade can
       therefore start with the preceding image's non-default partition. */
    if (currValue != tcmSizeValue && currValue <= 0x2cU &&
        *(volatile uint32_t*)0x51105280 != tcmSizeValue)
    {
        *(volatile uint32_t*)0x51105280 = tcmSizeValue;
        NVIC_SystemReset();
    }
    /* An already-requested but rejected partition must not cause a reset loop
       or let startup copy data beyond the physical TCM boundary. */
    if (currValue != tcmSizeValue) {
        g_tcm_boot_config = 0x80000000U | currValue;
        for (;;) __NOP();
    }
}
#ifdef CORE_CM7
/**
*\*\name    PWR_ConfigSupply.
*\*\fun     Configure the PWR supply.
*\*\param   SupplySource (The input parameters must be the following values):
*\*\          - PWR_LDO_SUPPLY               :External LDO  SUPPLY 
*\*\          - PWR_DIRECT_SMPS_SUPPLY       :DCDC SUPPLY 
*\*\          - PWR_EXTERNAL_SOURCE_SUPPLY   :External VCAP SUPPLY 
*\*\return  none
**/
static void PWR_ConfigSupply(uint32_t SupplySource)
{
    __IO uint32_t tempreg;
    /* Get the old register value */
    tempreg = PWR->SYSCTRL4;
    /* Clear the old  value */
    tempreg &= (~PWR_SUPPLY_MODE_MASK);
    /* Set the new values */
    tempreg |= SupplySource;
    /* Set the power supply configuration */
    PWR->SYSCTRL4 = tempreg;
    
    /* Config NRST Filter Function */
    tempreg = PWR->SYSCTRL1;
    tempreg &= ~(PWR_RST_AGFBPEN_MAST | PWR_RST_DGF_CNT_MAST | PWR_RST_DGFBPEN_MAST);
    tempreg |= PWR_RST_DGF_CNT_DEFAULT;
    PWR->SYSCTRL1 = tempreg;
}
#endif
/**
 *\*\name   SystemInit.
 *\*\fun    Setup the microcontroller system.Initialize the FPU setting, vector table location and External memory configuration.
 *\*\param  none
 *\*\return none
 */
void SystemInit (void)
{    
  /* FPU settings ------------------------------------------------------------*/
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << (10*2))|(3UL << (11*2)));  /* set CP10 and CP11 Full Access */
  #endif

    /*SEVONPEND enabled so that an interrupt coming from the CPU(n) interrupt signal is
     detectable by the CPU after a WFI/WFE instruction.*/ 
 SCB->SCR |= SCB_SCR_SEVONPEND_Msk;

#ifdef CORE_CM7 
  
#endif /* CORE_CM7*/

#ifdef CORE_CM4

  /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
  SCB->VTOR = 0x30000000; /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = FLASH_BANK2_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
#endif  

#else
#ifdef CORE_CM7

  /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
  SCB->VTOR = 0x24000000;       /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = VECT_TAB_BASE | VECT_TAB_OFFSET;          /* Vector Table Relocation in Internal FLASH */
#endif

   /*defaule TCM_SIZE=0x2F,All TCMSRAM are AXI_SRAM,if you want to use ITCM/DTCM, define INIT_TCM_SIZE*/
#ifdef USING_TCM
    ConfigTcmSize(TCM_SIZE_VALUE);
#endif
    /* PWR_ConfigSupply lives in .QuickCodes. It is called by SystemPostInit()
       after Reset_Handler has copied .QuickCodes into ITCM. */

#else
#error Please #define CORE_CM4 or CORE_CM7
#endif                       
#endif

}

/* Called by Reset_Handler after .QuickCodes has become executable. */
void SystemPostInit(void)
{
    PWR_ConfigSupply(PWR_SUPPLY_SELECTION);
}


/**
 *\*\name   N32SysTick_Handler.
 *\*\fun    This function handles N32SysTick Handler.
 *\*\param  none
 *\*\return none
 */
void N32SysTick_Handler(void)
{

}

