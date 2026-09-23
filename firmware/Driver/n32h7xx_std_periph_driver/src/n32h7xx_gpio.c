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
 * @file n32h7xx_gpio.c
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
/* Includes ------------------------------------------------------------------*/
#include "n32h7xx_gpio.h"
#include "n32h7xx_rcc.h"


#define GPIO_MODE             			((uint32_t)0x00000003)
//#define EXTI_MODE             			((uint32_t)0x10000000)
//#define GPIO_MODE_IT          			((uint32_t)0x00010000)
//#define GPIO_MODE_EVT         			((uint32_t)0x00020000)
//#define RISING_EDGE           			((uint32_t)0x00100000)
//#define FALLING_EDGE          			((uint32_t)0x00200000)
#define GPIO_OUTPUT_TYPE      			((uint32_t)0x00000010)
//#define GPIO_NUMBER           			((uint32_t)16)
#define GPIO_FILT_STEGE_MASK ((uint32_t)0x0000001F)


/**
*\*\name   GPIO_DeInit.
*\*\fun    Reset the GPIOx peripheral registers to their default reset values.
*\*\param  GPIOx :
*\*\          - GPIOA
*\*\          - GPIOB
*\*\          - GPIOC
*\*\          - GPIOD
*\*\          - GPIOE
*\*\          - GPIOF
*\*\          - GPIOG
*\*\          - GPIOH
*\*\          - GPIOI
*\*\          - GPIOJ
*\*\          - GPIOK
*\*\return none
*/
void GPIO_DeInit(GPIO_Module* GPIOx)
{
    /* Configure the port pins */
    /*------------------------- GPIO Mode Configuration --------------------*/
    if (GPIOx == GPIOA)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOA);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOB);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOC);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOD);
    }
    else if (GPIOx == GPIOE)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOE);
    }
    else if (GPIOx == GPIOF)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOF);
    }
    else if (GPIOx == GPIOG)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOG);
    }
    else if (GPIOx == GPIOH)
    {
        RCC_EnableAHB5PeriphReset1(RCC_AHB5_PERIPHRST_GPIOH);
    }
    else if (GPIOx == GPIOI)
    {
        RCC_EnableAHB5PeriphReset2(RCC_AHB5_PERIPHRST_GPIOI);
    }
    else if (GPIOx == GPIOJ)
    {
        RCC_EnableAHB5PeriphReset2(RCC_AHB5_PERIPHRST_GPIOJ);
    }
    else if (GPIOx == GPIOK)
    {
        RCC_EnableAHB5PeriphReset2(RCC_AHB5_PERIPHRST_GPIOK);
    }
    else
    {
        return;
    }
}


/**
*\*\name   GPIO_InitPeripheral.
*\*\fun    Initialize the GPIOx peripheral with the value of the GPIO_InitStruct structure.
*\*\param   GPIOx :
*\*\          - GPIOA
*\*\          - GPIOB
*\*\          - GPIOC
*\*\          - GPIOD
*\*\          - GPIOE
*\*\          - GPIOF
*\*\          - GPIOG
*\*\          - GPIOH
*\*\          - GPIOI
*\*\          - GPIOJ
*\*\          - GPIOK
*\*\param  GPIO_InitStructure :
*\*\          - Pin
*\*\             - GPIO_PIN_0
*\*\             - GPIO_PIN_1
*\*\             - GPIO_PIN_2
*\*\             - GPIO_PIN_3
*\*\             - GPIO_PIN_4
*\*\             - GPIO_PIN_5
*\*\             - GPIO_PIN_6
*\*\             - GPIO_PIN_7
*\*\             - GPIO_PIN_8
*\*\             - GPIO_PIN_9
*\*\             - GPIO_PIN_10
*\*\             - GPIO_PIN_11
*\*\             - GPIO_PIN_12
*\*\             - GPIO_PIN_13
*\*\             - GPIO_PIN_14
*\*\             - GPIO_PIN_15
*\*\             - GPIO_PIN_ALL
*\*\          - GPIO_Mode
*\*\             - GPIO_MODE_INPUT
*\*\             - GPIO_MODE_OUTPUT_PP
*\*\             - GPIO_MODE_OUTPUT_OD
*\*\             - GPIO_MODE_AF_PP
*\*\             - GPIO_MODE_AF_OD
*\*\             - GPIO_MODE_ANALOG
*\*\          - GPIO_Pull
*\*\             - GPIO_NO_PULL
*\*\             - GPIO_PULL_UP
*\*\             - GPIO_PULL_DOWN
*\*\          - GPIO_Slew_Rate
*\*\             - GPIO_SLEW_RATE_FAST
*\*\             - GPIO_SLEW_RATE_SLOW
*\*\          - GPIO_Current
*\*\             3.3V Tolerant IO Driver Strength:
*\*\             - GPIO_DC_2mA
*\*\             - GPIO_DC_4mA
*\*\             - GPIO_DC_8mA
*\*\             - GPIO_DC_12mA
*\*\               3.3V Tolerant IO:
*\*\                  GPIOA: PA0, PA1, PA2, PA3, PA6, PA9
*\*\                  GPIOB: PB0, PB1, PB2, PB7, PB8, PB10, PB11, PB12, PB13
*\*\                  GPIOC: PC1, PC9, PC10, PC11
*\*\                  GPIOD: PD4, PD5, PD6, PD7, PD11, PD12, PD13
*\*\                  GPIOE: PE2, PE3, PE5
*\*\                  GPIOF: PF6, PF7, PF8, PF9, PF10
*\*\                  GPIOG: PG6, PG7, PG9, PG10, PG11, PG12, PG13, PG14
*\*\                  GPIOI: PI11, PI12, PI13, PI14
*\*\                  GPIOJ: PJ1, PJ2
*\*\                  GPIOK: PK3, PK4, PK5, PK6, PK7
*\*\
*\*\             5V Tolerant IO Driver Strength:
*\*\             - GPIO_5VTOL_DC_1mA
*\*\             - GPIO_5VTOL_DC_2mA
*\*\             - GPIO_5VTOL_DC_4mA
*\*\             - GPIO_5VTOL_DC_6mA
*\*\               5V Tolerant IO:
*\*\                  GPIOA: BOOT0, PA8, PA10, PA11, PA12, PA13, PA14, PA15
*\*\                  GPIOB: PB3, PB4, PB9
*\*\                  GPIOC: PC6, PC7, PC8, PC13, PC14, PC15
*\*\                  GPIOD: PD3
*\*\                  GPIOE: PE4, PE6
*\*\                  GPIOG: PG3
*\*\                  GPIOH: PH0, PH1, PH4
*\*\                  GPIOI: PI8, PI15
*\*\                  GPIOJ: PJ0, PJ3, PJJ4, PJ5, PJ6, PJ7, PJ8, PJ9, PJ10, PJ11, PJ12, PJ13, PJ14, PJ15
*\*\                  GPIOK: PK0, PK1, PK2
*\*\
*\*\             High Speed IO Driver Strength:
*\*\             - GPIO_HS_IO_DC_1mA
*\*\             - GPIO_HS_IO_DC_2mA
*\*\             - GPIO_HS_IO_DC_4mA
*\*\             - GPIO_HS_IO_DC_5mA
*\*\             - GPIO_HS_IO_DC_8mA
*\*\             - GPIO_HS_IO_DC_12mA
*\*\               High Speed IO:
*\*\                  GPIOA: PA7, PA5, PA4
*\*\                  GPIOB: PB15, PB14, PB6, PB5
*\*\                  GPIOC: PC12, PC5, PC4, PC3, PC2, PC0
*\*\                  GPIOD: PD15, PD14, PD10, PD9, PD8, PD2, PD1, PD0
*\*\                  GPIOE: PE15, PE14, PE13, PE12, PE11, PE10, PE9, PE8, PE7, PE1, PE0
*\*\                  GPIOF: PF15, PF14, PF13, PF12, PF11, PF5, PF4, PF3, PF2, PF1, PF0
*\*\                  GPIOG: PG15, PG8, PG5, PG4, PG2, PG1, PG0
*\*\                  GPIOH: PH15, PH14, PH13, PH12, PH11, PH10, PH9, PH8, PH7, PH6, PH5, PH3, PH2
*\*\                  GPIOI: PI10, PI9, PI7, PI6, PI5, PI4, PI3, PI2, PI1, PI0
*\*\       
*\*\          - GPIO_Alternate
*\*\             - GPIO_AF0
*\*\             - GPIO_AF1
*\*\             - GPIO_AF2
*\*\             - GPIO_AF3
*\*\             - GPIO_AF4
*\*\             - GPIO_AF5
*\*\             - GPIO_AF6
*\*\             - GPIO_AF7
*\*\             - GPIO_AF8
*\*\             - GPIO_AF9
*\*\             - GPIO_AF10
*\*\             - GPIO_AF11
*\*\             - GPIO_AF12
*\*\             - GPIO_AF13
*\*\             - GPIO_AF14
*\*\             - GPIO_AF15
*\*\             - GPIO_NO_AF
*\*\return none
**/
void GPIO_InitPeripheral( GPIO_Module* GPIOx, GPIO_InitType* GPIO_InitStruct )
{
    uint32_t position = 0x00U;
    uint32_t iocurrent = 0x00U;
    uint32_t temp = 0x00U;
    uint32_t temp2 = 0x00U;
    uint32_t GPIO_Index = 0x00U;
    uint32_t tempReg1 = 0x00U;
    uint32_t tempReg2 = 0x00U;
    uint32_t BitMask = 0x00U;
    uint32_t hsio_position = 0x00U;

    uint8_t start[] = {0, 3, 7, 13, 21, 32, 43, 50, 64};
    uint16_t HS_IO[9] = {0x00B0, 0xC060, 0x103D, 0xC707, 0xFF83, 0xF83F, 0x8137, 0xFFEC, 0x06FF};

    GPIO_Index = GPIO_GET_INDEX((uint32_t)GPIOx);

    /* Configure the port pins */

    while ((( GPIO_InitStruct->Pin ) >> position ) != 0 )
    {
        /* Get the IO position */
        iocurrent = ( GPIO_InitStruct->Pin ) & ( 1U << position );

        /* Get High Speed IO position */
        temp = (0x0001U << position);
        if ((GPIO_Index < 9U) && (((uint16_t)temp) & HS_IO[GPIO_Index]))
        {
            if (temp & GPIO_InitStruct->Pin)
            {
                temp2 = (0x00000001U << hsio_position);
                
            }
            else
            {
                /* No Process */
            }
            
            hsio_position++;
        }
        else
        {
            /* No Process */
        }

        /* Clear */
        temp = 0U;

        if ( iocurrent )
        {
            /*--------------------- GPIO Mode Configuration ------------------------*/
            /* In case of Alternate function mode selection */
            if (( GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_PP) || (GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_OD ) ||
                    (GPIO_InitStruct->GPIO_Mode == GPIO_MODE_INPUT)  || (GPIO_InitStruct->GPIO_Mode == GPIO_MODE_ANALOG))
            {
                /* Configure Alternate function mapped with the current IO */
                if(position & 0x08)
                {
                    temp = GPIOx->AFH;
                    temp &= ~(( uint32_t )0xFU << (( uint32_t )( position & ( uint32_t )0x07U ) * 4U ) ) ;
                    temp |= (( uint32_t )( GPIO_InitStruct->GPIO_Alternate ) << ((( uint32_t )position & ( uint32_t )0x07U ) * 4U ) ) ;
                    GPIOx->AFH = temp;
                }
                else
                {
                    temp = GPIOx->AFL;
                    temp &= ~(( uint32_t )0xFU << (( uint32_t )( position & ( uint32_t )0x07U ) * 4U ) ) ;
                    temp |= (( uint32_t )( GPIO_InitStruct->GPIO_Alternate ) << ((( uint32_t )position & ( uint32_t )0x07U ) * 4U ) ) ;
                    GPIOx->AFL = temp;
                }
            }

            /* In case of Output or Alternate function mode selection */
            if (( GPIO_InitStruct->GPIO_Mode == GPIO_MODE_OUTPUT_PP ) || ( GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_PP ) ||
                    ( GPIO_InitStruct->GPIO_Mode == GPIO_MODE_OUTPUT_OD ) || ( GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_OD ) )
            {
                /* Configure the IO Output Type */
                temp = GPIOx->POTYPE;
                temp &= ~( GPIO_POTYPE_POT0 << position ) ;
                temp |= ((( GPIO_InitStruct->GPIO_Mode & GPIO_OUTPUT_TYPE ) >> 4U ) << position );
                GPIOx->POTYPE = temp;
            }

            /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
            temp = GPIOx->PMODE;

            temp &= ~( GPIO_PMODE_PMODE0 << ( position * 2U ) );

            temp |= (( GPIO_InitStruct->GPIO_Mode & GPIO_MODE ) << ( position * 2U ) );

            GPIOx->PMODE = temp;

            /* Activate the Pull-up or Pull down resistor for the current IO */
            temp = GPIOx->PUPD;

            temp &= ~( GPIO_PUPD_PUPD0 << ( position * 2U ) );

            temp |= (( GPIO_InitStruct->GPIO_Pull ) << ( position * 2U ) );

            GPIOx->PUPD = temp;

            /* Configure slew rate */
            temp = GPIOx->SR;

            temp &= ~(GPIO_SR_BIT_MASK << position);

            temp |= (GPIO_InitStruct->GPIO_Slew_Rate << position);

            GPIOx->SR = temp;

            /* Configure driver current */
            temp = GPIOx->DS;

            temp &= ~(GPIO_DS_BIT_MASK << ( position * 2U ));

            if ((GPIO_Index < 9U) && (((uint16_t)iocurrent) & HS_IO[GPIO_Index]))
            {
                if ((GPIOx == GPIOI) && (iocurrent == GPIO_PIN_0))
                {
                    tempReg1 = AFIO->HS_DSN_CFG[1];
                    tempReg2 = AFIO->HS_DSP_CFG[1];
                    BitMask = 0x80000000U;
                }
                else
                {
                    tempReg1 = AFIO->HS_DSN_CFG[start[GPIO_Index] / 32UL];
                    tempReg2 = AFIO->HS_DSP_CFG[start[GPIO_Index] / 32UL];
                    BitMask = (GPIOx == GPIOI ? (temp2 >> 1U) : temp2) << 
                              (start[GPIO_Index] < 32 ? start[GPIO_Index] : start[GPIO_Index] < 64 ? 
                              (start[GPIO_Index] - 32) : (start[GPIO_Index] - 64));
                }

                if ((GPIO_InitStruct->GPIO_Current & 0xFFFF0000U) == 0xFFFF0000U)
                {
                    /* High Speed IO Driver Strength */
                    tempReg1 |= BitMask;
                    tempReg2 |= BitMask;
                    
                    temp |= (((uint32_t)(GPIO_InitStruct->GPIO_Current & 0x0000000FU)) << ( position * 2U ));
                }
                else if ((GPIO_InitStruct->GPIO_Current & 0xFF000000U) == 0xFF000000U)
                {
                    /* High Speed IO Driver Strength */
                    tempReg1 &= ~(BitMask);
                    tempReg2 &= ~(BitMask);
                    
                    temp |= (((uint32_t)(GPIO_InitStruct->GPIO_Current & 0x0000000FU)) << ( position * 2U ));
                }
                else
                {
                    tempReg1 &= ~(BitMask);
                    tempReg2 &= ~(BitMask);
                    
                    // TDIO: Parameter error, Ignore SDN/DSP configuration
                    temp |= (GPIO_InitStruct->GPIO_Current << ( position * 2U ));
                }
                
                if ((GPIOx == GPIOI) && (iocurrent == GPIO_PIN_0))
                {
                    AFIO->HS_DSN_CFG[1] = tempReg1;
                    AFIO->HS_DSP_CFG[1] = tempReg2;
                }
                else
                {
                    AFIO->HS_DSN_CFG[start[GPIO_Index] / 32UL] = tempReg1;
                    AFIO->HS_DSP_CFG[start[GPIO_Index] / 32UL] = tempReg2;
                }
            }
            else
            {
                if ((GPIO_InitStruct->GPIO_Current & 0xFF000000U) == 0xFF000000U)
                {
                    // TDIO: Parameter error, Ignore SDN/DSP configuration
                    temp |= (((uint32_t)(GPIO_InitStruct->GPIO_Current & 0x0000000FU)) << ( position * 2U ));
                }
                else
                {
                    /* Non-High Speed IO Driver Strength */
                    temp |= (GPIO_InitStruct->GPIO_Current << ( position * 2U ));
                }
            }

            

            GPIOx->DS = temp;
        }

        position++;
    }
}
/**
 *\*\name   GPIO_AFIOInitDefault.
 *\*\fun    Reset the AFIO peripheral registers to their default reset values.
 *\*\param  none
 *\*\return none
 */
void GPIO_AFIOInitDefault(void)
{
    RCC_EnableAHB5PeriphReset2(RCC_AHB5_PERIPHRST_AFIO);
}
/**
 *\*\name   GPIO_InitStruct.
 *\*\fun    Assign default values to each InitStruct member.
 *\*\param  InitStruct :
 *\*\           pointer to GPIO_InitType structure.
 *\*\return none
 */
void GPIO_InitStruct(GPIO_InitType* InitStruct)
{
    /* Reset GPIO structure member */
    InitStruct->Pin            = GPIO_PIN_NONE;
    InitStruct->GPIO_Mode      = GPIO_MODE_INPUT;
    InitStruct->GPIO_Pull      = GPIO_NO_PULL;
    InitStruct->GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    InitStruct->GPIO_Current   = GPIO_DC_2mA;
    InitStruct->GPIO_Alternate = GPIO_NO_AF;
}

/**
 *\*\name   GPIO_ReadInputDataBit.
 *\*\fun    Get the pin status on the specified input pin.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the state on the input pin
  */
uint8_t GPIO_ReadInputDataBit( GPIO_Module* GPIOx, uint16_t GPIO_Pin )
{
    uint8_t bitstatus = 0x00;

    if (( GPIOx->PID & GPIO_Pin ) != ( uint32_t )Bit_RESET )
    {
        bitstatus = ( uint8_t )Bit_SET;
    }
    else
    {
        bitstatus = ( uint8_t )Bit_RESET;
    }

    return bitstatus;
}

/**
 *\*\name   GPIO_ReadInputData.
 *\*\fun    Get the input data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\return the data value on the GPIO input port.
 */
uint16_t GPIO_ReadInputData( GPIO_Module* GPIOx )
{
    return (( uint16_t )GPIOx->PID );
}

/**
 *\*\name   GPIO_ReadOutputDataBit.
 *\*\fun    Get the pin status on the specified input pin.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the state on the input pin
  */
uint8_t GPIO_ReadOutputDataBit( GPIO_Module* GPIOx, uint16_t GPIO_Pin )
{
    uint8_t bitstatus = 0x00;

    if (( GPIOx->POD & GPIO_Pin ) != ( uint32_t )Bit_RESET )
    {
        bitstatus = ( uint8_t )Bit_SET;
    }
    else
    {
        bitstatus = ( uint8_t )Bit_RESET;
    }

    return bitstatus;
}


/**
 *\*\name   GPIO_ReadOutputData.
 *\*\fun    Get the output data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\return the data value on the GPIO output port.
 */
uint16_t GPIO_ReadOutputData( GPIO_Module* GPIOx )
{
    return (( uint16_t )GPIOx->POD );
}

/**
 *\*\name   GPIO_SetBits.
 *\*\fun    Get the pin status on the specified input pin.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the state on the input pin
  */
void GPIO_SetBits( GPIO_Module* GPIOx, uint16_t GPIO_Pin )
{
    GPIOx->PBSC = GPIO_Pin;
}

/**
 *\*\name   GPIO_ResetBits.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_ResetBits( GPIO_Module* GPIOx, uint16_t GPIO_Pin )
{
    GPIOx->PBC = GPIO_Pin;
}


/**
 *\*\name   GPIO_WriteBit.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
  *\*\param  BitVal :
 *\*\          - Bit_RESET
 *\*\          - Bit_SET
 *\*\return none
 */
void GPIO_WriteBit( GPIO_Module* GPIOx, uint16_t GPIO_Pin, Bit_OperateType BitVal )
{
    if ( BitVal != Bit_RESET )
    {
        GPIOx->PBSC = GPIO_Pin;
    }
    else
    {
        GPIOx->PBC = GPIO_Pin;
    }
}

/**
 *\*\name   GPIO_Write.
 *\*\fun    Write data on the designated GPIO data port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  data_value :
 *\*\          the value to be written to the port output data register.
 *\*\          - 0~0xFFFF
 *\*\return none
 */
void GPIO_Write( GPIO_Module* GPIOx, uint16_t data_value)
{
    GPIOx->POD = data_value;
}

/**
 *\*\name   GPIO_Pin_Toggle.
 *\*\fun    Toggle the specified port pin level.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_TogglePin(GPIO_Module *GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}


/**
 *\*\name   GPIO_ConfigPinLock.
 *\*\fun    Toggle the specified port pin level.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_ConfigPinLock(GPIO_Module* GPIOx, uint16_t Pin)
{
    __IO uint32_t tmp = GPIO_PLOCK_PLOCKK;

    if(GPIOx == GPIOK)
    {
        tmp = GPIO_PLOCK_PLOCKK >> 8;
    }

    tmp |= Pin;
    /* Set PLOCKK bit */
    GPIOx->PLOCK = tmp;
    /* Reset PLOCKK bit */
    GPIOx->PLOCK = Pin;
    /* Set PLOCKK bit */
    GPIOx->PLOCK = tmp;
    /* Read PLOCKK bit*/
    tmp = GPIOx->PLOCK;
    /* Read PLOCKK bit*/
    tmp = GPIOx->PLOCK;
}


/**
*\*\name   GPIO_EXTILineConfig.
*\*\fun    Selects the GPIO pin used as EXTI Line.
*\*\param  EXTI_Line
             - EXTI_LINE0
             - EXTI_LINE1
             - ......
             - EXTI_LINE15
*\*\param  GPIO_PinSource
             - EXTI_GPIOA_Pin_0
             - ......
             - EXTI_GPIOA_Pin_15
             - EXTI_GPIOB_Pin_0
             - ......
             - EXTI_GPIOB_Pin_15
             - ......
             - EXTI_GPIOJ_Pin_0
             - ......
             - EXTI_GPIOJ_Pin_15
*\*\return none
*/
void GPIO_ConfigEXTILine(uint8_t EXTI_Line, uint8_t GPIO_PinSource)
{
    AFIO->EXTI_CFG[EXTI_Line / 4] |= GPIO_PinSource << (8 * (EXTI_Line % 4));
}

/**
 *\*\name   AFIO_ConfigSIPFLASHSEL.
 *\*\fun    Configure the SIP FLASH MODE SEL.
 *\*\param  AFIO_FLASH :
 *\*\          - AFIO_FLASH0
 *\*\          - AFIO_FLASH1
 *\*\          - AFIO_FLASH2
 *\*\          - AFIO_FLASH3
 *\*\          - AFIO_FLASH4
 *\*\          - AFIO_DISFLASH
 *\*\return none
 */
void AFIO_ConfigSIPFLASHSEL(uint32_t AFIO_FLASH)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;
    tempReg &= ~AFIO_RMP_CFG_SIP_FLASHSEL;
    tempReg |= AFIO_FLASH;

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigSPINSSMode.
 *\*\fun    Configure the SPIx NSS mode during idle.
 *\*\param  AFIO_SPIx_NSS :
 *\*\          - AFIO_SPI1_NSS
 *\*\          - AFIO_SPI2_NSS
 *\*\          - AFIO_SPI3_NSS
 *\*\          - AFIO_SPI4_NSS
 *\*\          - AFIO_SPI5_NSS
 *\*\          - AFIO_SPI6_NSS
 *\*\          - AFIO_SPI7_NSS
 *\*\param  NSS_Mode :
 *\*\          - AFIO_SPI_NSS_HIGH_IMPEDANCE
 *\*\          - AFIO_SPI_NSS_HIGH_LEVEL
 *\*\return none
 */
void AFIO_ConfigSPINSSMode(uint32_t AFIO_SPIx_NSS, uint32_t NSS_Mode)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    if(NSS_Mode != AFIO_SPI_NSS_HIGH_IMPEDANCE)
    {
        tempReg |= AFIO_SPIx_NSS;
    }
    else
    {
        tempReg &= ~AFIO_SPIx_NSS;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_Config_EXTI_Filter.
 *\*\fun    Enable or disable EXTI analog filter.
 *\*\param  EXTI_Filter :
 *\*\        - AFIO_EXTI_FILTER_ENABLE
 *\*\        - AFIO_EXTI_FILTER_DISABLE
 *\*\return none
 */
void AFIO_ConfigEXTIFilter(uint32_t EXTI_Filter)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG ;

    if(EXTI_Filter != AFIO_EXTI_FILTER_ENABLE)
    {
        tempReg |= AFIO_EXTI_FILTER_DISABLE;
    }
    else
    {
        tempReg &= ~AFIO_EXTI_FILTER_DISABLE;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
*\*\name   AFIO_ConfigSIPSDRAMPrior.
*\*\fun    Configure SIP SDRAM prority.
*\*\param  priority :
*\*\          - AFIO_SIP_SDRAM_PRIORITY_HIGH
*\*\          - AFIO_SIP_SDRAM_PRIORITY_LOW
*\*\return none
**/
void AFIO_ConfigSIPSDRAMPrior(uint32_t priority)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    if(priority != AFIO_SIP_SDRAM_PRIORITY_LOW)
    {
        tempReg |= AFIO_SIP_SDRAM_PRIORITY_HIGH;
    }
    else
    {
        tempReg &= ~AFIO_SIP_SDRAM_PRIORITY_HIGH;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigSPII2SMode.
 *\*\fun    SEL only for pads sharing SPI/I2S.
 *\*\param  AFIO_SPIx_I2Sx :
 *\*\          - AFIO_SELECT_SPI1
 *\*\          - AFIO_SELECT_SPI2
 *\*\          - AFIO_SELECT_SPI3
 *\*\          - AFIO_SELECT_SPI4
 *\*\param  PADS_Mode :
 *\*\          - SPI_MODE
 *\*\          - I2S_MODE
 *\*\return none
 */
void AFIO_ConfigSPII2SMode(uint32_t AFIO_SPIx_I2Sx, uint32_t PADS_Mode)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    if(PADS_Mode != I2S_MODE)
    {
        tempReg |= AFIO_SPIx_I2Sx;
    }
    else
    {
        tempReg &= ~AFIO_SPIx_I2Sx;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_SDMMCClkSel.
 *\*\fun    SDMMC clk external or feedback clk input.
 *\*\param  AFIO_clk_sel :
 *\*\          - SDMMC1_CLKFB
 *\*\          - SDMMC2_CLKFB
 *\*\param  cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return none
 */
void AFIO_SDMMCClkSel(uint32_t AFIO_clk_sel, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    if(cmd != DISABLE)
    {
        tempReg |= AFIO_clk_sel;
    }
    else
    {
        tempReg &= ~AFIO_clk_sel;
    }

    AFIO->RMP_CFG = tempReg;
}


/**
 *\*\name   AFIO_I2SFullpuplexSel.
 *\*\fun    To enable full duplex mode for I2S1-4
 *\*\param  AFIO_I2S_sel :
 *\*\          - I2S1_FULLDUPLEX
 *\*\          - I2S2_FULLDUPLEX
 *\*\          - I2S3_FULLDUPLEX
 *\*\          - I2S4_FULLDUPLEX
 *\*\return none
 */
void AFIO_I2SFullpuplexSel(uint32_t AFIO_clk_sel)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    tempReg &= ~AFIO_RMP_CFG_I2S_FDUP;
    tempReg |= AFIO_clk_sel;

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigXSPIBigEndian.
 *\*\fun    Enable or disable the big endian for XSPI XIP mode.
 *\*\param  AFIO_BigEndian_sel :
 *\*\          - XSPI1_ENDIAN
 *\*\          - XSPI2_ENDIAN
 *\*\param  Endian :
 *\*\          - XSPI_LITTLE_ENDIAN
 *\*\          - XSPI_BIG_ENDIAN
 *\*\return none
 */
void AFIO_ConfigXSPIBigEndian(uint32_t xspi_endian, uint32_t Endian)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG ;

    if(Endian != XSPI_LITTLE_ENDIAN)
    {
        tempReg |= xspi_endian;
    }
    else
    {
        tempReg &= ~xspi_endian;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigFEMCNANDSRAM.
 *\*\fun    To select between Nand and Sram.
 *\*\param  Nand_Sram_sel :
 *\*\        - FEMC_NAND_SEL
 *\*\        - FEMC_SRAM_SEL
 *\*\return none
 */
void AFIO_ConfigFEMCNANDSRAM(uint32_t Nand_Sram_sel)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG ;

    if(Nand_Sram_sel == FEMC_NAND_SEL)
    {
        tempReg |= FEMC_NAND_SEL;
    }
    else
    {
        tempReg &= ~FEMC_NAND_SEL;
    }

    AFIO->RMP_CFG = tempReg;
}


/**
 *\*\name   AFIO_FEMCNOByteStrobe.
 *\*\fun    ANDed of NBLs for Flashes do or not support byte strobes.
 *\*\param  Byte_Strobes_sel :
 *\*\        - NO_BYTE_STROBE
 *\*\        - BYTE_STROBE
 *\*\return none
 */
void AFIO_FEMCNOByteStrobe(uint32_t Byte_Strobes_sel)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG ;

    if(Byte_Strobes_sel == NO_BYTE_STROBE)
    {
        tempReg |= NO_BYTE_STROBE;
    }
    else
    {
        tempReg &= ~NO_BYTE_STROBE;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigETH1Mode.
 *\*\fun    For the ETH1 PHY selection.
 *\*\param  ETH1_PHY_sel :
 *\*\          ETH1_GMII_SEL
 *\*\          ETH1_RGMII_SEL
 *\*\          ETH1_RMII_SEL
 *\*\          ETH1_MII_SEL
 *\*\return none
 */
void AFIO_ConfigETH1Mode(uint32_t ETH1_PHY_sel)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG;

    tempReg &= ~AFIO_RMP_CFG_ETH1_PHY;

    tempReg |= ETH1_PHY_sel;

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigETH2Mode.
 *\*\fun    For the ETH2 PHY selection.
 *\*\param  ETH2_PHY_sel :
 *\*\        - ETH2_RMII_SEL
 *\*\        - ETH2_MII_SEL
 *\*\return none
 */
void AFIO_ConfigETH2Mode(uint32_t ETH2_PHY_sel)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG ;

    if(ETH2_PHY_sel == ETH2_RMII_SEL)
    {
        tempReg |= ETH2_RMII_SEL;
    }
    else
    {
        tempReg &= ~ETH2_RMII_SEL;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
*\*\name   AFIO_ConfigSHRT1FALTPin.
*\*\fun    SHRTIM1 GPIO FAULT PIN Config
*\*\param  channel_pin :
*\*\          - SHRT1_FAULT_CHANNEL_PA15
*\*\          - SHRT1_FAULT_CHANNEL_PB3
*\*\          - SHRT1_FAULT_CHANNEL_PC11
*\*\          - SHRT1_FAULT_CHANNEL_PD4
*\*\          - SHRT1_FAULT_CHANNEL_PE4
*\*\          - SHRT1_FAULT_CHANNEL_PG9
*\*\          - SHRT1_FAULT_CHANNEL_PG10
*\*\          - SHRT1_FAULT_CHANNEL_PI6
*\*\          - SHRT1_FAULT_CHANNEL_PI15
*\*\          - SHRT1_FAULT_CHANNEL_PK2
*\*\param  channel_num :
*\*\          - SHRT_FAULT_CHANNEL_1
*\*\          - SHRT_FAULT_CHANNEL_2
*\*\          - SHRT_FAULT_CHANNEL_3
*\*\          - SHRT_FAULT_CHANNEL_4
*\*\          - SHRT_FAULT_CHANNEL_5
*\*\          - SHRT_FAULT_CHANNEL_6
*\*\return none
**/
void AFIO_ConfigSHRT1FALTPin(SHRT1_FAULT_CHANNEL channel_pin, SHRT_FAULT_CHANNEL_NUM channel_num)
{
    uint32_t tempReg;

    tempReg = AFIO->SHRT1_FALT_CFG;
    tempReg &= ~(AFIO_SHRT1_FALT_CFG_SHRT_FALT1 << ((channel_num) * 4));
    tempReg |= channel_pin << (channel_num * 4);
    AFIO->SHRT1_FALT_CFG = tempReg;
}

/**
*\*\name   AFIO_ConfigSHRT2FALTPin.
*\*\fun    SHRTIM2 GPIO FAULT PIN Config
*\*\param  channel_pin :
*\*\          - SHRT2_FAULT_CHANNEL_PC5
*\*\          - SHRT2_FAULT_CHANNEL_PD1
*\*\          - SHRT2_FAULT_CHANNEL_PD15
*\*\          - SHRT2_FAULT_CHANNEL_PF9
*\*\          - SHRT2_FAULT_CHANNEL_PF13
*\*\          - SHRT2_FAULT_CHANNEL_PG1
*\*\          - SHRT2_FAULT_CHANNEL_PI0
*\*\          - SHRT2_FAULT_CHANNEL_PI9
*\*\          - SHRT2_FAULT_CHANNEL_PI13
*\*\          - SHRT2_FAULT_CHANNEL_PJ0
*\*\          - SHRT2_FAULT_CHANNEL_PK1
*\*\          - SHRT2_FAULT_CHANNEL_PK6
*\*\param  channel_num :
*\*\          - SHRT_FAULT_CHANNEL_1
*\*\          - SHRT_FAULT_CHANNEL_2
*\*\          - SHRT_FAULT_CHANNEL_3
*\*\          - SHRT_FAULT_CHANNEL_4
*\*\          - SHRT_FAULT_CHANNEL_5
*\*\          - SHRT_FAULT_CHANNEL_6
*\*\return none
**/
void AFIO_ConfigSHRT2FALTPin(SHRT2_FAULT_CHANNEL channel_pin, SHRT_FAULT_CHANNEL_NUM channel_num)
{
    uint32_t tempReg;

    tempReg = AFIO->SHRT2_FALT_CFG;
    tempReg &= ~(AFIO_SHRT2_FALT_CFG_SHRT_FALT1 << ((channel_num) * 4));
    tempReg |= channel_pin << (channel_num * 4);
    AFIO->SHRT2_FALT_CFG = tempReg;
}

/**
*\*\name   AFIO_ConfigSHRT1EXEVPin.
*\*\fun    SHRTIM1 external event pin Config
*\*\param  channel_pin :
*\*\          - SHRT1_EXEV_CHANNEL_PB4
*\*\          - SHRT1_EXEV_CHANNEL_PB5
*\*\          - SHRT1_EXEV_CHANNEL_PB6
*\*\          - SHRT1_EXEV_CHANNEL_PB7
*\*\          - SHRT1_EXEV_CHANNEL_PC10
*\*\          - SHRT1_EXEV_CHANNEL_PC12
*\*\          - SHRT1_EXEV_CHANNEL_PD5
*\*\          - SHRT1_EXEV_CHANNEL_PD8
*\*\          - SHRT1_EXEV_CHANNEL_PD9
*\*\          - SHRT1_EXEV_CHANNEL_PE6
*\*\          - SHRT1_EXEV_CHANNEL_PG0
*\*\          - SHRT1_EXEV_CHANNEL_PG11
*\*\          - SHRT1_EXEV_CHANNEL_PG12
*\*\          - SHRT1_EXEV_CHANNEL_PG13
*\*\          - SHRT1_EXEV_CHANNEL_PI14
*\*\          - SHRT1_EXEV_CHANNEL_PJ5
*\*\          - SHRT1_EXEV_CHANNEL_PK3
*\*\          - SHRT1_EXEV_CHANNEL_PK4
*\*\param  channel_num :
*\*\          - SHRT_EXEV_CHANNEL_1
*\*\          - SHRT_EXEV_CHANNEL_2
*\*\          - SHRT_EXEV_CHANNEL_3
*\*\          - SHRT_EXEV_CHANNEL_4
*\*\          - SHRT_EXEV_CHANNEL_5
*\*\          - SHRT_EXEV_CHANNEL_6
*\*\          - SHRT_EXEV_CHANNEL_7
*\*\          - SHRT_EXEV_CHANNEL_8
*\*\          - SHRT_EXEV_CHANNEL_9
*\*\          - SHRT_EXEV_CHANNEL_10
*\*\return none
**/
void AFIO_ConfigSHRT1EXEVPin(SHRT1_EXEV_CHANNEL channel_pin, SHRT_EXEV_CHANNEL_NUM channel_num)
{
    uint32_t tempReg;
    uint32_t temp_index;

    temp_index = channel_num / 5;

    tempReg = AFIO->SHRT1_EXEV_CFG[temp_index];

    tempReg &= ~(AFIO_SHRT1_EXEV_CFG1_SHRT_EXEV1 << ((channel_num % 5) * 5));

    tempReg |= channel_pin << ((channel_num % 5) * 5);

    AFIO->SHRT1_EXEV_CFG[temp_index] = tempReg;
}

/**
*\*\name   AFIO_ConfigSHRT2EXEVPin.
*\*\fun    SHRTIM2 external event pin Config
*\*\param  channel_pin :
*\*\          - SHRT2_EXEV_CHANNEL_PA2
*\*\          - SHRT2_EXEV_CHANNEL_PC4
*\*\          - SHRT2_EXEV_CHANNEL_PD0
*\*\          - SHRT2_EXEV_CHANNEL_PD11
*\*\          - SHRT2_EXEV_CHANNEL_PE3
*\*\          - SHRT2_EXEV_CHANNEL_PE14
*\*\          - SHRT2_EXEV_CHANNEL_PF10
*\*\          - SHRT2_EXEV_CHANNEL_PG8
*\*\          - SHRT2_EXEV_CHANNEL_PG15
*\*\          - SHRT2_EXEV_CHANNEL_PH7
*\*\          - SHRT2_EXEV_CHANNEL_PH8
*\*\          - SHRT2_EXEV_CHANNEL_PH10
*\*\          - SHRT2_EXEV_CHANNEL_PH11
*\*\          - SHRT2_EXEV_CHANNEL_PH12
*\*\          - SHRT2_EXEV_CHANNEL_PI11
*\*\          - SHRT2_EXEV_CHANNEL_PJ2
*\*\          - SHRT2_EXEV_CHANNEL_J14
*\*\          - SHRT2_EXEV_CHANNEL_PK0
*\*\param  channel_num :
*\*\          - SHRT_EXEV_CHANNEL_1
*\*\          - SHRT_EXEV_CHANNEL_2
*\*\          - SHRT_EXEV_CHANNEL_3
*\*\          - SHRT_EXEV_CHANNEL_4
*\*\          - SHRT_EXEV_CHANNEL_5
*\*\          - SHRT_EXEV_CHANNEL_6
*\*\          - SHRT_EXEV_CHANNEL_7
*\*\          - SHRT_EXEV_CHANNEL_8
*\*\          - SHRT_EXEV_CHANNEL_9
*\*\          - SHRT_EXEV_CHANNEL_10
*\*\return none
**/
void AFIO_ConfigSHRT2EXEVPin(SHRT2_EXEV_CHANNEL channel_pin, SHRT_EXEV_CHANNEL_NUM channel_num)
{
    uint32_t tempReg;
    uint32_t temp_index;

    temp_index = channel_num / 5;

    tempReg = AFIO->SHRT2_EXEV_CFG[temp_index];

    tempReg &= ~(AFIO_SHRT2_EXEV_CFG1_SHRT_EXEV1 << ((channel_num % 5) * 5));

    tempReg |= channel_pin << ((channel_num % 5) * 5);

    AFIO->SHRT2_EXEV_CFG[temp_index] = tempReg;
}

/**
*\*\name   AFIO_ConfigPinAnalogSignalChannelGPIOA.
*\*\fun    Enable or disable the analog signal channel for GPIOA pin.
*\*\param  Pin :
*\*\           - AFIO_ANAEN_PA0_C
*\*\           - AFIO_ANAEN_PA0
*\*\           - AFIO_ANAEN_PA1_C
*\*\           - AFIO_ANAEN_PA1
*\*\           - AFIO_ANAEN_PA2
*\*\           - AFIO_ANAEN_PA3
*\*\           - AFIO_ANAEN_PA4
*\*\           - AFIO_ANAEN_PA5
*\*\           - AFIO_ANAEN_PA6
*\*\           - AFIO_ANAEN_PA7
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinAnalogSignalChannelGPIOA(uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->ANAEN_CFG0;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->ANAEN_CFG0 = tempReg;
}

/**
*\*\name   AFIO_ConfigPinAnalogSignalChannelGPIOB.
*\*\fun    Enable or disable the analog signal channel for GPIOB pin.
*\*\param  Pin :
*\*\           - AFIO_ANAEN_PB0
*\*\           - AFIO_ANAEN_PB1
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinAnalogSignalChannelGPIOB(uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->ANAEN_CFG1;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->ANAEN_CFG1 = tempReg;
}
/**
*\*\name   AFIO_ConfigPinAnalogSignalChannelGPIOC.
*\*\fun    Enable or disable the analog signal channel for GPIOC pin.
*\*\param  Pin :
*\*\           - AFIO_ANAEN_PC0
*\*\           - AFIO_ANAEN_PC1
*\*\           - AFIO_ANAEN_PC2
*\*\           - AFIO_ANAEN_PC2_C
*\*\           - AFIO_ANAEN_PC3
*\*\           - AFIO_ANAEN_PC3_C
*\*\           - AFIO_ANAEN_PC4
*\*\           - AFIO_ANAEN_PC5
*\*\           - AFIO_ANAEN_PC6
*\*\           - AFIO_ANAEN_PC8
*\*\           - AFIO_ANAEN_PC13
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinAnalogSignalChannelGPIOC(uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->ANAEN_CFG2;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->ANAEN_CFG2 = tempReg;
}

/**
*\*\name   AFIO_ConfigPinAnalogSignalChannelGPIOF.
*\*\fun    Enable or disable the analog signal channel for GPIOF pin.
*\*\param  Pin :
*\*\           - AFIO_ANAEN_PF3
*\*\           - AFIO_ANAEN_PF4
*\*\           - AFIO_ANAEN_PF5
*\*\           - AFIO_ANAEN_PF6
*\*\           - AFIO_ANAEN_PF7
*\*\           - AFIO_ANAEN_PF8
*\*\           - AFIO_ANAEN_PF9
*\*\           - AFIO_ANAEN_PF10
*\*\           - AFIO_ANAEN_PF11
*\*\           - AFIO_ANAEN_PF12
*\*\           - AFIO_ANAEN_PF13
*\*\           - AFIO_ANAEN_PF14
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinAnalogSignalChannelGPIOF( uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->ANAEN_CFG3;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->ANAEN_CFG3 = tempReg;
}

/**
*\*\name   AFIO_ConfigPinAnalogSignalChannelGPIOH.
*\*\fun    Enable or disable the analog signal channel for GPIOH pin.
*\*\param  Pin :
*\*\           - AFIO_ANAEN_PH2
*\*\           - AFIO_ANAEN_PH3
*\*\           - AFIO_ANAEN_PH4
*\*\           - AFIO_ANAEN_PH5
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinAnalogSignalChannelGPIOH( uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->ANAEN_CFG4;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->ANAEN_CFG4 = tempReg;
}

/**
*\*\name   AFIO_ConfigPinAnalogSignalChannelGPIOI.
*\*\fun    Enable or disable the analog signal channel for GPIOI pin.
*\*\param  Pin :
*\*\           - AFIO_ANAEN_PI8
*\*\           - AFIO_ANAEN_PI15
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinAnalogSignalChannelGPIOI( uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->ANAEN_CFG5;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->ANAEN_CFG5 = tempReg;
}

/**
*\*\name   AFIO_ConfigPinAnalogSignalChannelGPIOJ.
*\*\fun    Enable or disable the analog signal channel for GPIOJ pin.
*\*\param  Pin :
*\*\           - AFIO_ANAEN_PJ0
*\*\           - AFIO_ANAEN_PJ3
*\*\           - AFIO_ANAEN_PJ4
*\*\           - AFIO_ANAEN_PJ5
*\*\           - AFIO_ANAEN_PJ6
*\*\           - AFIO_ANAEN_PJ7
*\*\param  cmd :
*\*\           - DISABLE
*\*\           - ENABLE
*\*\return none
**/
void AFIO_ConfigPinAnalogSignalChannelGPIOJ( uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;

    tempReg = AFIO->ANAEN_CFG6;

    if(cmd != DISABLE)
    {
        tempReg |= Pin;
    }
    else
    {
        tempReg &= ~(Pin);
    }

    AFIO->ANAEN_CFG6 = tempReg;
}

/**
 *\*\name   AFIO_SIPInitPeripheral.
 *\*\fun    Configure the Sip Pin  Pull up or down
 *\*\param  sip_index :
 *\*\           - AFIO_SIP_DAT7
 *\*\           - AFIO_SIP_DAT6
 *\*\           - AFIO_SIP_DAT5
 *\*\           - AFIO_SIP_DAT4
 *\*\           - AFIO_SIP_DAT3
 *\*\           - AFIO_SIP_DAT2
 *\*\           - AFIO_SIP_DAT1
 *\*\           - AFIO_SIP_DAT0
 *\*\param  pupd :
 *\*\           - AFIO_SIP_Mode_NO_PULL
 *\*\           - AFIO_SIP_Mode_PULL_UP
 *\*\           - AFIO_SIP_Mode_PULL_DOWN
 *\*\param  slew_rate :
 *\*\           - SIP_Mode_FAST
 *\*\           - SIP_Mode_SLOW
 *\*\param  driver_stength :
 *\*\           - SIP_DC_2mA
 *\*\           - SIP_DC_4mA
 *\*\           - SIP_DC_8mA
 *\*\           - SIP_DC_12mA
 *\*\return none
 */
void AFIO_SIPInitPeripheral(uint8_t sip_index, uint32_t pupd, uint32_t slew_rate, uint32_t driver_stength)
{
    uint32_t temp = 0x00U;

    temp = AFIO->SIP_PUPD;

    temp &= ~(AFIO_SIP_MASK << (2 * sip_index));

    temp |= (pupd << (2 * sip_index));

    AFIO->SIP_PUPD = temp;


    temp = AFIO->SIPSR;

    temp &= ~(GPIO_SR_BIT_MASK << (sip_index));

    temp |= (slew_rate << ( sip_index));

    AFIO->SIPSR = temp;

    temp = AFIO->SIPDS;

    temp &= ~(GPIO_DS_BIT_MASK << (2 * sip_index));

    temp |= (driver_stength << (2 * sip_index));

    AFIO->SIPDS = temp;
}

/**
 * @brief  Configur ADC external trigger.
 * @param ADCETRType choose whether to configure rule conversion or injection conversion .
 *   This parameter can be AFIO_ADC_ETRI and AFIO_ADC_ETRR.
 * @param ADCTrigRemap specifies the external trigger line be configured.
 *   This parameter can be AFIO_ADC_TRIG_EXTI_x where x can be (0..15) or AFIO_ADC_TRIG_TIM8_CHy where y can be(3..4).
 */

/**
*\*\name   AFIO_ConfigADCExtLineTrigSource.
*\*\fun    Configurate ADC external line trigger.
*\*\param  ADC_num :
*\*\          - AFIO_ADC_1
*\*\          - AFIO_ADC_2
*\*\          - AFIO_ADC_3
*\*\param  ADCETRType :
*\*\          - AFIO_ADC_ETRI
*\*\          - AFIO_ADC_ETRR
*\*\param  ADC_trigger :
*\*\          - AFIO_ADC_TRIG_EXTI_0
*\*\          - AFIO_ADC_TRIG_EXTI_1
*\*\          - AFIO_ADC_TRIG_EXTI_2
*\*\          - AFIO_ADC_TRIG_EXTI_3
*\*\          - AFIO_ADC_TRIG_EXTI_4
*\*\          - AFIO_ADC_TRIG_EXTI_5
*\*\          - AFIO_ADC_TRIG_EXTI_6
*\*\          - AFIO_ADC_TRIG_EXTI_7
*\*\          - AFIO_ADC_TRIG_EXTI_8
*\*\          - AFIO_ADC_TRIG_EXTI_9
*\*\          - AFIO_ADC_TRIG_EXTI_10
*\*\          - AFIO_ADC_TRIG_EXTI_11
*\*\          - AFIO_ADC_TRIG_EXTI_12
*\*\          - AFIO_ADC_TRIG_EXTI_13
*\*\          - AFIO_ADC_TRIG_EXTI_14
*\*\          - AFIO_ADC_TRIG_EXTI_15
*\*\return none
**/
void AFIO_ConfigADCExtLineTrigSource(AFIO_ADC_NUM ADC_num, AFIO_ADC_ETRType ADCETRType, AFIO_ADC_Trig_RemapType ADCTrigRemap)
{
    uint32_t tmpregister = 0x00;

    /* Check the parameters */
    tmpregister = AFIO->ADCRMP_CFG;

    /* clear AFIO_ADCRMP_CFG register bit*/
    tmpregister &= (~(AFIO_ADCRMP_CFG_ADC3_EXTIRRSEL << (ADC_num * 8 + ADCETRType * 4)));

    /* select which external line is connected*/
    tmpregister |= ADCTrigRemap << (ADC_num * 8 + ADCETRType * 4);

    AFIO->ADCRMP_CFG = tmpregister;
}

/**
*\*\name   AFIO_ConfigADCSWPA0_C.
*\*\fun    Config ADC PA0_C channel.
*\*\param  ADCsw
*\*\           - ADC_SW_PA0_C_ADC2_INP0
*\*\           - ADC_SW_PA0_C_ADC2_INN1
*\*\           - ADC_SW_PA0_C_ADC1_INP0
*\*\           - ADC_SW_PA0_C_ADC1_INN1
*\*\           - ADC_SW_PA0_C_CLOSE
*\*\return none
**/
void AFIO_ConfigADCSWPA0_C(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_PA0_C_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWPC2_C.
*\*\fun    Config ADC PC2_C channel
*\*\param  ADCsw
*\*\           - ADC_SW_PC2_C_ADC2_INP0
*\*\           - ADC_SW_PC2_C_ADC2_INN1
*\*\           - ADC_SW_PC2_C_ADC3_INP0
*\*\           - ADC_SW_PC2_C_ADC3_INN1
*\*\           - ADC_SW_PC2_C_CLOSE
*\*\return none
**/
void AFIO_ConfigADCSWPC2_C(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_PC2_C_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWPC3_C.
*\*\fun    Config ADC PC3_C channel
*\*\param  ADCsw
*\*\           - ADC_SW_PC3_C_ADC2_INP1
*\*\           - ADC_SW_PC3_C_ADC3_INP1
*\*\           - ADC_SW_PC3_C_CLOSE
*\*\return none
**/
void AFIO_ConfigADCSWPC3_C(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_PC3_C_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWPA1_C.
*\*\fun    Config ADC PA1_C channel
*\*\param  ADCsw
*\*\           - ADC_SW_PA1_C_ADC2_INP1
*\*\           - ADC_SW_PA1_C_ADC1_INP1
*\*\           - ADC_SW_PA1_C_CLOSE
*\*\return none
**/
void AFIO_ConfigADCSWPA1_C(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_PA1_C_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWPI15.
*\*\fun    Config ADC PI15 channel
*\*\param  ADCsw
*\*\           - ADC_SW_PI15_ADC2_INP17
*\*\           - ADC_SW_PI15_ADC3_INP17
*\*\           - ADC_SW_PI15_CLOSE
*\*\return none
**/
void AFIO_ConfigADCSWPI15(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_PI15_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWVBATEnable.
*\*\fun    Enable or disable ADC VBAT channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWVBATEnable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_VBAT_ADC3_INP17;
    }
    else
    {
        tempReg &= ~ADC_SW_VBAT_ADC3_INP17;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ0Enable.
*\*\fun    Enable or disable ADC PJ0 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ0Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ0_ADC2_INP16;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ0_ADC2_INP16;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ3Enable.
*\*\fun    Enable or disable ADC PJ3 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ3Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ3_ADC3_INP18;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ3_ADC3_INP18;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWTEMPEnable.
*\*\fun    Enable or disable ADC TEMP channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWTEMPEnable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_TEMP_ADC3_INP18;
    }
    else
    {
        tempReg &= ~ADC_SW_TEMP_ADC3_INP18;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ4Enable.
*\*\fun    Enable or disable ADC PJ4 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ4Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ4_ADC3_INP19;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ4_ADC3_INP19;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ5Enable.
*\*\fun    Enable or disable ADC PJ5 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ5Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ5_ADC2_INP16;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ5_ADC2_INP16;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ6Enable.
*\*\fun    Enable or disable ADC PJ6 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ6Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ6_ADC3_INP18;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ6_ADC3_INP18;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWPJ7Enable.
*\*\fun    Enable or disable ADC PJ7 channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWPJ7Enable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_PJ7_ADC3_INP19;
    }
    else
    {
        tempReg &= ~ADC_SW_PJ7_ADC3_INP19;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ADCSWVREFEnable.
*\*\fun    Enable or disable ADC VREF channel
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return none
**/
void AFIO_ADCSWVREFEnable(FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;

    if (Cmd != DISABLE)
    {
        tempReg |= ADC_SW_VREF_ADC3_INP19;
    }
    else
    {
        tempReg &= ~ADC_SW_VREF_ADC3_INP19;
    }

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWDAC246OUT.
*\*\fun    Config ADC DAC2/4/6_OUT channel
*\*\param  ADCsw
*\*\           - ADC_SW_DAC2_OUT_ADC2_INP17
*\*\           - ADC_SW_DAC4_OUT_ADC2_INP17
*\*\           - ADC_SW_DAC6_OUT_ADC2_INP17
*\*\           - ADC_SW_DAC246_OUT_ADC2_DISABLE
*\*\return none
**/
void AFIO_ConfigADCSWDAC246OUT(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_DAC246_OUT_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
*\*\name   AFIO_ConfigADCSWDAC135OUT.
*\*\fun    Config ADC DAC1/3/5_OUT channel
*\*\param  ADCsw
*\*\           - ADC_SW_DAC1_OUT_ADC2_INP16
*\*\           - ADC_SW_DAC3_OUT_ADC2_INP16
*\*\           - ADC_SW_DAC5_OUT_ADC2_INP16
*\*\           - ADC_SW_DAC135_OUT_ADC2_DISABLE
*\*\return none
**/
void AFIO_ConfigADCSWDAC135OUT(uint32_t ADCsw)
{
    uint32_t tempReg;

    tempReg  = AFIO->ADCSW_CFG;
    tempReg &= ~ADC_SW_DAC135_OUT_MSK;
    tempReg |= ADCsw;

    AFIO->ADCSW_CFG  = tempReg;
}

/**
 *\*\name   AFIO_ConfigIOFilter.
 *\*\fun    Configure IO filter cycle which is counted in AHB clock.
 *\*\param  Filter_Cycle :
 *\*\        - 0~127
 *\*\return none
 */
void AFIO_ConfigIOFilter(uint8_t Filter_Cycle)
{
    uint32_t tempReg;

    tempReg  = AFIO->FILTER_CFG;
    tempReg &= ~AFIO_FILTER_CFG_IOFLTCFG;
    tempReg |= Filter_Cycle;
    AFIO->FILTER_CFG  = tempReg;
}

/**
 *\*\name   AFIO_ConfigPinFilter.
 *\*\fun    Enable or disable the analog filter function for GPIOx pin.
 *\*\param   GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\          - GPIOJ
 *\*\          - GPIOK
 *\*\param   Pin :
 *\*\          - GPIO_Pin_0
 *\*\          - GPIO_Pin_1
 *\*\          - GPIO_Pin_2
 *\*\          - GPIO_Pin_3
 *\*\          - GPIO_Pin_4
 *\*\          - GPIO_Pin_5
 *\*\          - GPIO_Pin_6
 *\*\          - GPIO_Pin_7
 *\*\          - GPIO_Pin_8
 *\*\          - GPIO_Pin_9
 *\*\          - GPIO_Pin_10
 *\*\          - GPIO_Pin_11
 *\*\          - GPIO_Pin_12
 *\*\          - GPIO_Pin_13
 *\*\          - GPIO_Pin_14
 *\*\          - GPIO_Pin_15
 *\*\          - GPIO_Pin_ALL
 *\*\param   cmd :
 *\*\          - DISABLE
 *\*\          - ENABLE
 *\*\return none
 */
void AFIO_ConfigPinAnFilter(GPIO_Module* GPIOx, uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;
    uint32_t RegNum;
    uint32_t BitMask;
    uint32_t GPIO_Index;

    GPIO_Index = (uint32_t)GPIOx;
    GPIO_Index = GPIO_GET_INDEX(GPIO_Index);

    RegNum = GPIO_Index / 2UL;

    if(GPIO_Index == 8 || GPIO_Index == 9) //GPIOI, GPIOJ
    {
        BitMask = Pin << (16UL * ((GPIO_Index + 1) & 0x1UL));
    }
    else
    {
        BitMask = Pin << (16UL * (GPIO_Index & 0x1UL));
    }

    tempReg = AFIO->EFT_CFG[RegNum];

    if(cmd != DISABLE)
    {
        tempReg |= BitMask;
    }
    else
    {
        tempReg &= ~(BitMask);
    }

    AFIO->EFT_CFG[RegNum] = tempReg;
}
/**
*\*\name   AFIO_ConfigDigitalPinFilter.
*\*\fun    Enable or disable the digital filter function for GPIOx pin.
*\*\param   GPIOx :
*\*\          - GPIOA
*\*\          - GPIOB
*\*\          - GPIOC
*\*\          - GPIOD
*\*\          - GPIOE
*\*\          - GPIOF
*\*\          - GPIOG
*\*\          - GPIOH
*\*\          - GPIOI
*\*\          - GPIOJ
*\*\          - GPIOK
*\*\param  Pin :
*\*\          - GPIO_Pin_0
*\*\          - GPIO_Pin_1
*\*\          - GPIO_Pin_2
*\*\          - GPIO_Pin_3
*\*\          - GPIO_Pin_4
*\*\          - GPIO_Pin_5
*\*\          - GPIO_Pin_6
*\*\          - GPIO_Pin_7
*\*\          - GPIO_Pin_8
*\*\          - GPIO_Pin_9
*\*\          - GPIO_Pin_10
*\*\          - GPIO_Pin_11
*\*\          - GPIO_Pin_12
*\*\          - GPIO_Pin_13
*\*\          - GPIO_Pin_14
*\*\          - GPIO_Pin_15
*\*\          - GPIO_Pin_ALL
*\*\param  cmd :
*\*\          - DISABLE
*\*\          - ENABLE
*\*\return none
**/
void AFIO_ConfigPinFilter(GPIO_Module* GPIOx, uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;
    uint32_t RegNum;
    uint32_t BitMask;
    uint32_t GPIO_Index;

    GPIO_Index = (uint32_t)GPIOx;
    GPIO_Index = GPIO_GET_INDEX(GPIO_Index);

    RegNum = GPIO_Index / 2UL;

    if(GPIO_Index == 8 || GPIO_Index == 9) //GPIOI, GPIOJ
    {
        BitMask = Pin << (16UL * ((GPIO_Index + 1) & 0x1UL));
    }
    else
    {
        BitMask = Pin << (16UL * (GPIO_Index & 0x1UL));
    }

    tempReg = AFIO->DIGEFT_CFG[RegNum];

    if(cmd != DISABLE)
    {
        tempReg |= BitMask;
    }
    else
    {
        tempReg &= ~(BitMask);
    }

    AFIO->DIGEFT_CFG[RegNum] = tempReg;
}

/**
 *\*\name   AFIO_ConfigHSMODE.
 *\*\fun    Enable or disable high speed pad interface connection for port x Pad Model.
 *\*\param   GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\param   Pin :
 *\*\        GPIOA:
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_7
 *\*\        GPIOB:
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOC:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_12
 *\*\        GPIOD:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOE:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOF:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOG:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_15
 *\*\        GPIOH:
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
  *\*\        GPIOI:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\param   cmd :
 *\*\          - DISABLE
 *\*\          - ENABLE
 *\*\note   Most of pins support ,but some pins don't support.
 *\*\return none
 */
void AFIO_ConfigHSMODE(GPIO_Module* GPIOx, uint32_t Pin, FunctionalState cmd)
{
    uint32_t tempReg;
    uint32_t RegNum;
    uint32_t BitMask;
    uint32_t GPIO_Index;

    GPIO_Index = (uint32_t)GPIOx;
    GPIO_Index = GPIO_GET_INDEX(GPIO_Index);

    RegNum = GPIO_Index / 2UL;
    BitMask = Pin << (16UL * ((GPIO_Index + 1) & 0x1UL));
    tempReg = AFIO->HSMODE_CFG[RegNum];

    if(cmd != DISABLE)
    {
        tempReg |= BitMask;
    }
    else
    {
        tempReg &= ~(BitMask);
    }

    AFIO->HSMODE_CFG[RegNum] = tempReg;
}

/**
*\*\name   AFIO_ConfigXSPIDecNonce.
*\*\fun    Set the XSPI DEC NONCE counter value.
*\*\param  nonce_num
*\*\           - 0
*\*\           - 1
*\*\           - 2
*\*\param  data: 0x00000000~ 0xFFFFFFFF
*\*\return none
**/
void AFIO_ConfigXSPIDecNonce(uint8_t nonce_num, u32 data)
{
    if(nonce_num == 0x00)
    {
        AFIO->XSPI1_NONCE0 = data;
    }
    else if(nonce_num == 0x01)
    {
        AFIO->XSPI1_NONCE1 = data;
    }
    else if(nonce_num == 0x02)
    {
        AFIO->XSPI1_NONCE2 = data;
    }
}

/**
*\*\name   AFIO_ConfigHSMODEVREFRemap.
*\*\fun    Config high speed RX reference pad signal connection for port y Pad.
*\*\param  pin
*\*\          - AFIO_HIGH_SPEED_IO_PA4
*\*\          - AFIO_HIGH_SPEED_IO_PA5
*\*\          - AFIO_HIGH_SPEED_IO_PA7
*\*\          - AFIO_HIGH_SPEED_IO_PB5
*\*\          - AFIO_HIGH_SPEED_IO_PB6
*\*\          - ...
*\*\          - AFIO_HIGH_SPEED_IO_PI7
*\*\          - AFIO_HIGH_SPEED_IO_PI9
*\*\          - AFIO_HIGH_SPEED_IO_PI10
*\*\param  cmd :
*\*\          - DISABLE
*\*\          - ENABLE
*\*\return none
**/
void AFIO_ConfigHSMODEVREFRemap(AFIO_HIGH_SPEED_PIN pin, FunctionalState cmd)
{
    uint8_t temp;
    uint32_t temp_reg;

    temp = pin / 32;
    temp_reg = AFIO->HSMODE_VREF_EN[temp];

    if(cmd != DISABLE)
    {
        temp_reg |= (uint32_t)(0x00000001) << (pin % 32);
    }
    else
    {
        temp_reg &= ~(uint32_t)(0x00000001) << (pin % 32);
    }

    AFIO->HSMODE_VREF_EN[temp] = temp_reg;
}

/**
*\*\name   AFIO_ConfigHSMODEVREFData.
*\*\fun    Config high speed RX reference pad signal connection register value.
*\*\param  reg_index:
*\*\          - 0
*\*\          - 1
*\*\          - 2
*\*\param  data: when reg_index = 0 or 1, data range 0~0xFFFFFFFF, when reg_index = 2, data range 0~0x1FF
*\*\return none
**/
void AFIO_ConfigHSMODEVREFData(uint8_t reg_index, uint32_t data)
{
    AFIO->HSMODE_VREF_EN[reg_index] = data;
}


/**
*\*\name   AFIO_ConfigHSPortDSNRemap.
*\*\fun    Config DSN PAD signal connection for high speed port.
*\*\param  pin
*\*\          - AFIO_HIGH_SPEED_IO_PA4
*\*\          - AFIO_HIGH_SPEED_IO_PA5
*\*\          - AFIO_HIGH_SPEED_IO_PA7
*\*\          - AFIO_HIGH_SPEED_IO_PB5
*\*\          - AFIO_HIGH_SPEED_IO_PB6
*\*\          - ...
*\*\          - AFIO_HIGH_SPEED_IO_PI7
*\*\          - AFIO_HIGH_SPEED_IO_PI9
*\*\          - AFIO_HIGH_SPEED_IO_PI10
*\*\param  cmd :
*\*\          - DISABLE
*\*\          - ENABLE
*\*\return none
**/
void AFIO_ConfigHSPortDSNRemap(AFIO_HIGH_SPEED_PIN pin, FunctionalState cmd)
{
    uint8_t temp;
    uint32_t temp_reg;

    temp = pin / 32;
    temp_reg = AFIO->HS_DSN_CFG[temp];

    if(cmd != DISABLE)
    {
        temp_reg |= (uint32_t)(0x00000001) << (pin % 32);
    }
    else
    {
        temp_reg &= ~(uint32_t)(0x00000001) << (pin % 32);
    }

    AFIO->HS_DSN_CFG[temp] = temp_reg;
}

/**
*\*\name   AFIO_ConfigHSPortDSNData.
*\*\fun    Config DSN PAD signal connection for high speed port register value.
*\*\param  reg_index:
*\*\          - 0
*\*\          - 1
*\*\          - 2
*\*\param  data: when reg_index = 0 or 1, data range 0~0xFFFFFFFF, when reg_index = 2, data range 0~0x1FF
*\*\return none
**/
void AFIO_ConfigHSPortDSNData(uint8_t reg_index, uint32_t data)
{
    AFIO->HS_DSN_CFG[reg_index] = data;
}

/**
*\*\name   AFIO_ConfigHSPortDSPRemap.
*\*\fun    Config DSP PAD signal connection for high speed port.
*\*\param  pin
*\*\          - AFIO_HIGH_SPEED_IO_PA4
*\*\          - AFIO_HIGH_SPEED_IO_PA5
*\*\          - AFIO_HIGH_SPEED_IO_PA7
*\*\          - AFIO_HIGH_SPEED_IO_PB5
*\*\          - AFIO_HIGH_SPEED_IO_PB6
*\*\          - ...
*\*\          - AFIO_HIGH_SPEED_IO_PI7
*\*\          - AFIO_HIGH_SPEED_IO_PI9
*\*\          - AFIO_HIGH_SPEED_IO_PI10
*\*\param  cmd :
*\*\          - DISABLE
*\*\          - ENABLE
*\*\return none
**/
void AFIO_ConfigHSPortDSPRemap(AFIO_HIGH_SPEED_PIN pin, FunctionalState cmd)
{
    uint8_t temp;
    uint32_t temp_reg;

    temp = pin / 32;
    temp_reg = AFIO->HS_DSP_CFG[temp];

    if(cmd != DISABLE)
    {
        temp_reg |= (uint32_t)(0x00000001) << (pin % 32);
    }
    else
    {
        temp_reg &= ~(uint32_t)(0x00000001) << (pin % 32);
    }

    AFIO->HS_DSP_CFG[temp] = temp_reg;
}

/**
*\*\name   AFIO_ConfigHSPortDSPData.
*\*\fun    Config DSP PAD signal connection for high speed port register value.
*\*\param  reg_index:
*\*\          - 0
*\*\          - 1
*\*\          - 2
*\*\param  data: when reg_index = 0 or 1, data range 0~0xFFFFFFFF, when reg_index = 2, data range 0~0x1FF
*\*\return none
**/
void AFIO_ConfigHSPortDSPData(uint8_t reg_index, uint32_t data)
{
    AFIO->HS_DSP_CFG[reg_index] = data;
}

/**
 *\*\name   AFIO_ConfigHSMODE.
 *\*\fun    Enable or disable high speed pad interface for port x Pad Model.
 *\*\param   GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\param   Pin :
 *\*\        GPIOA:
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_7
 *\*\        GPIOB:
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOC:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_12
 *\*\        GPIOD:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOE:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOF:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOG:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_15
 *\*\        GPIOH:
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
  *\*\        GPIOI:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\param   cmd :
 *\*\          - DISABLE
 *\*\          - ENABLE
 *\*\note   Most of pins support ,but some pins don't support.
 *\*\return none
 */
void AFIO_ConfigIOHsMode(GPIO_Module* GPIOx, uint32_t Pin, FunctionalState cmd)
{
    uint16_t position = 0x00U, index = 0x00U, temp1 = 0x00U, temp2 = 0x00U;

    uint8_t start[] = {0, 3, 7, 13, 21, 32, 43, 50, 64};
    uint16_t gpiox_hsmode[] = {0x00B0, 0xC060, 0x103D, 0xC707, 0xFF83, 0xF83F, 0x8137, 0xFFEC, 0x06FF};

    uint32_t tempReg;
    uint32_t RegNum;
    uint32_t BitMask;
    uint32_t GPIO_Index;

    GPIO_Index = (uint32_t)GPIOx;
    GPIO_Index = GPIO_GET_INDEX(GPIO_Index);

    if (GPIO_Index < 9U)
    {
        RegNum = GPIO_Index / 2UL;
        BitMask = Pin << (16UL * ((GPIO_Index + 1) & 0x1UL));
        tempReg = AFIO->HSMODE_CFG[RegNum];

        if(cmd != DISABLE)
        {
            tempReg |= BitMask;
        }
        else
        {
            tempReg &= ~(BitMask);
        }
        AFIO->HSMODE_CFG[RegNum] = tempReg;
        
        while ((Pin >> position) != 0)
        {
            temp1 = (0x0001 << position);
            
            if (temp1 & gpiox_hsmode[GPIO_Index])
            {
                if (temp1 & Pin)
                {
                    temp2 |= (0x0001 << index);
                }
                else
                {
                    /* No Process */
                }
                
                index++;
            }
            else
            {
                /* No Process */
            }

            position++;
        }
        
        tempReg = AFIO->HSMODE_VREF_EN[start[GPIO_Index] / 32UL];
        BitMask = (GPIOx == GPIOI ? temp2 >> 1 : temp2) << (start[GPIO_Index] < 32 ? start[GPIO_Index] : start[GPIO_Index] < 64 ? start[GPIO_Index] - 32 : start[GPIO_Index] - 64);
        if(cmd != DISABLE)
        {
            tempReg |= BitMask;
        }
        else
        {
            tempReg &= ~(BitMask);
        }
        AFIO->HSMODE_VREF_EN[start[GPIO_Index] / 32UL] = tempReg;
        
        if ((GPIOx == GPIOI) && (temp2 & 0x0001))
        {
            BitMask = 0x80000000;
            tempReg = AFIO->HSMODE_VREF_EN[1];
            
            if(cmd != DISABLE)
            {
                tempReg |= BitMask;
            }
            else
            {
                tempReg &= ~(BitMask);
            }
            
            AFIO->HSMODE_VREF_EN[1] = tempReg;
        }
    }
    else
    {
        /* No Process */
    }
}


/**
 *\*\name   AFIO_ConfigHSPortDSNAndDSP.
 *\*\fun    Config high speed pad interface driver strength.
 *\*\param   GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\          - GPIOI
 *\*\param   Pin :
 *\*\        GPIOA:
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_7
 *\*\        GPIOB:
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOC:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_12
 *\*\        GPIOD:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOE:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOF:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\        GPIOG:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_15
 *\*\        GPIOH:
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
  *\*\        GPIOI:
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\param   cmd :
 *\*\          - DISABLE
 *\*\          - ENABLE
 *\*\note   Most of pins support ,but some pins don't support.
 *\*\return none
 */
void AFIO_ConfigHSPortDSNAndDSP(GPIO_Module* GPIOx, uint32_t Pin, FunctionalState cmd)
{
    uint16_t position = 0x00U, index = 0x00U, temp1 = 0x00U, temp2 = 0x00U;

    uint8_t start[] = {0, 3, 7, 13, 21, 32, 43, 50, 64};
    uint16_t gpiox_hsmode[] = {0x00B0, 0xC060, 0x103D, 0xC707, 0xFF83, 0xF83F, 0x8137, 0xFFEC, 0x06FF};

    uint32_t tempReg1;
    uint32_t tempReg2;
    uint32_t BitMask;
    uint32_t GPIO_Index;

    GPIO_Index = (uint32_t)GPIOx;
    GPIO_Index = GPIO_GET_INDEX(GPIO_Index);

    if (GPIO_Index < 9U)
    {
        while ((Pin >> position) != 0)
        {
            temp1 = (0x0001 << position);

            if (temp1 & gpiox_hsmode[GPIO_Index])
            {
                if (temp1 & Pin)
                {
                    temp2 |= (0x0001 << index);
                }
                else
                {
                    /* No Process */
                }
                
                index++;
            }
            else
            {
                /* No Process */
            }

            position++;
        }
        
        tempReg1 = AFIO->HS_DSN_CFG[start[GPIO_Index] / 32UL];
        tempReg2 = AFIO->HS_DSP_CFG[start[GPIO_Index] / 32UL];
        BitMask = (GPIOx == GPIOI ? temp2 >> 1 : temp2) << (start[GPIO_Index] < 32 ? start[GPIO_Index] : start[GPIO_Index] < 64 ? start[GPIO_Index] - 32 : start[GPIO_Index] - 64);
        if(cmd != DISABLE)
        {
            tempReg1 |= BitMask;
            tempReg2 |= BitMask;
        }
        else
        {
            tempReg1 &= ~(BitMask);
            tempReg2 &= ~(BitMask);
        }
        AFIO->HS_DSN_CFG[start[GPIO_Index] / 32UL] = tempReg1;
        AFIO->HS_DSP_CFG[start[GPIO_Index] / 32UL] = tempReg2;
        
        if ((GPIOx == GPIOI) && (temp2 & 0x0001))
        {
            BitMask = 0x80000000;
            tempReg1 = AFIO->HS_DSN_CFG[1];
            tempReg2 = AFIO->HS_DSP_CFG[1];
            
            if(cmd != DISABLE)
            {
                tempReg1 |= BitMask;
                tempReg2 |= BitMask;
            }
            else
            {
                tempReg1 &= ~(BitMask);
                tempReg2 &= ~(BitMask);
            }
            
            AFIO->HS_DSN_CFG[1] = tempReg1;
            AFIO->HS_DSP_CFG[1] = tempReg2;
        }
    }
    else
    {
        /* No Process */
    }
}
