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
 * @file n32h7xx_xspi_v2.h
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __n32h7xx_XSPI_V2_H__
#define __n32h7xx_XSPI_V2_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h7xx.h"


typedef struct 
{
    uint32_t SCPH;             /* Serial Clock Phase */
    uint32_t SCPOL;            /* Serial Clock Polarity */

    uint32_t FrameFormat;      /* Standard SPI Master/Slave: Single wire 
                                  Enhanced SPI Slave: Dual-wire/Quad-wire/Octal-wire */
    uint32_t DataFrameSize;    /* Data Frame Size: 4-bit ~ 32-bit */
    uint32_t TransferMode;     /* Transfer Mode: Transmit & Receive / Transmit only mode / Receive only mode /  EEPROM Read mode */

    uint32_t Role;             /* working in Master or Slave mode*/  
    uint32_t Baudr;            /* Clock Divider: Any even number between 2 and 65534 */

    uint32_t RxdSamplingEdge;  /* Receive Data (rxd) Sampling Edge. Note: no need to worry about it in DDR mode */
    uint32_t RxdSampleDelay;   /* Receive Data (rxd) Sample Delay: Valid values 0 ~ 255, measured in HCLK. Note: no need to worry about it in DDR mode */

    uint32_t NssToggle;        /* Slave Select Toggle: Used in standard SPI mode when SCPH=0; enhanced mode is not effective */ 

    uint32_t EnhSlave_ClockStrech; /* Clock stretching: only effective on enhanced slaves */
} XSPI_InitType;


typedef struct 
{
    uint32_t SCPH;            /* Serial Clock Phase */
    uint32_t SCPOL;           /* Serial Clock Polarity */
    uint32_t FrameFormat;     /* SPI Frame Format: Dual-wire/Quad-wire/Octal-wire */
    uint32_t DataFrameSize;   /* Data Frame Size: 4-bit ~ 32-bit */
    uint32_t TransferMode;    /* Transfer Mode: Transmit only mode / Receive only mode */

    uint32_t Baudr;           /* Clock Divider: Any even number between 2 and 65534 */

    uint32_t RxdSamplingEdge; /* Receive Data (rxd) Sampling Edge. Note: no need to worry about it in DDR mode */
    uint32_t RxdSampleDelay;  /* Receive Data (rxd) Sample Delay: Valid values 0 ~ 255, measured in HCLK. Note: no need to worry about it in DDR mode */

    uint32_t TransferType;    /* Address and instruction transfer format */
    uint32_t AddrLen;         /* Defines Length of Address to be transmitted. Note: DDR mode cannot be programmed as 0 */
    uint32_t InstructLen;     /* Dual/Quad/Octal mode instruction length. Note: DDR mode cannot be programmed as 0 */

    uint32_t WaitCycles;      /* Wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception.
                                 Note: do not set to 0 when reading DDR, measure with XSPI_SCK */ 

    uint32_t ClockStrech;     /* Clock stretching capability.
                                 In case of write, if the FIFO becomes empty XSPI will stretch the clock until FIFO has enough data to continue the transfer
                                 In case of read, if the receive FIFO becomes full XSPI will stop the clock until data has been read from the FIFO */

    uint32_t DDREable;        /* SPI DDR enable Dual-data rate transfers in Dual/Quad/Octal frame formats of SPI.
                                 Note: DDR mode only supports mode 0 (SCPH = 0/SCPOL = 0) and mode 3 (SCPH = 1/SCPOL = 1) */

    struct 
    {
        uint32_t InstrucDDR;    /* Instruction DDR: enable Dual-data rate transfer for Instruction phase.
                                   Note: DDR mode only supports mode 0 (SCPH = 0/SCPOL = 0) and mode 3 (SCPH = 1/SCPOL = 1) */
        uint32_t RxdsSignal;    /* Read data strobe enable XSPI will use Read data strobe (rxds) to capture read data in DDR mode */
        uint32_t TxdDataMask;   /* SPI data mask control the txd_dm signal is used to mask the data on the txd data line */
        uint32_t TxdDriverEdge; /* Decided the driving edge of transmit data (0 ~ 255, Max value = (BAUD/2) - 1, BAUDR = CLKDIV[14:0] * 2) */
    } DDR_InitType;
}XSPI_EnhancedInitType;


typedef struct 
{
    uint32_t SCPH;            /* Serial Clock Phase */
    uint32_t SCPOL;           /* Serial Clock Polarity */
    uint32_t DataFrameSize;   /* Data Frame Size: 4-bit ~ 32-bit */
    uint32_t TransferMode;    /* Transfer Mode: Transmit only mode / Receive only mode */

    uint32_t Baudr;           /* Clock Divider: Any even number between 2 and 65534 */

    uint32_t XipFrameFormat;  /* SPI Frame Format: Dual-wire/Quad-wire/Octal-wire */
    uint32_t XipTransferType; /* Address and instruction transfer format */
    uint32_t XipAddrLen;      /* Defines Length of Address to be transmitted. Note: DDR mode cannot be programmed as 0 */

    uint32_t XipWaitCycles;   /* Wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception.
                                 Note: do not set to 0 when reading DDR, measure with XSPI_SCK */
    uint32_t XipDDREable;     /* SPI DDR enable Dual-data rate transfers in Dual/Quad/Octal frame formats of SPI.
                                 Note: DDR mode only supports mode 0 (SCPH = 0/SCPOL = 0) and mode 3 (SCPH = 1/SCPOL = 1) */

    union {
        struct 
        {
            uint32_t XipInstructLen;   /* Dual/Quad/Octal mode instruction length. Note: DDR mode cannot be programmed as 0 */
            uint32_t XipInstrctEnable; /* XIP instruction control. If enable then XIP transfers will also have instruction phase */

            union {
                struct 
                {
                    uint32_t TxdDriverEdge; /* Decided the driving edge of transmit data (0 ~ 255, Max value = (BAUD/2) - 1, BAUDR = CLKDIV[14:0] * 2) */
                    uint32_t XipInstrucDDR; /* Instruction DDR: enable Dual-data rate transfer for Instruction phase.
                                               Note: DDR mode only supports mode 0 (SCPH = 0/SCPOL = 0) and mode 3 (SCPH = 1/SCPOL = 1) */
                    uint32_t XipRxdsSignal; /* Read data strobe enable XSPI will use Read data strobe (rxds) to capture read data in DDR mode */
                } DDR_InitType;
                
                struct 
                {
                    uint32_t RxdSamplingEdge; /* Receive Data (rxd) Sampling Edge. Note: no need to worry about it in DDR mode */
                    uint32_t RxdSampleDelay;  /* Receive Data (rxd) Sample Delay: Valid values 0 ~ 255, measured in HCLK. Note: no need to worry about it in DDR mode */
                } Rxds_InitType;
            } Info;

            uint32_t XipDFSHC;         /* Fix DFS for XIP transfers. 
                                          If enable then data frame size for XIP transfers will be fixed to the programmed value in XSPI_CTRL0.DFS[4:0]. 
                                          The number of data frames to fetch will be determined by HSIZE and HBURST signals. 
                                          If disable then data frame size and number of data frames to fetch will be determined by HSIZE and HBURST signals */
            uint32_t XipPrefetch;      /* XIP pre-fetch functionality: if enable XSPI will pre-fetch data frames from next contigous location, to reduce the 
                                          latency for the upcoming contiguous transfer. 
                                          Note: If the next XIP request is not contigous then pre-fetched bits will be discarded */
            
            uint32_t XipModeBit;       /* Mode bits enable in XIP mode, if enable then in XIP mode of operation XSPI will insert mode bits after the address phase */
            uint32_t XipModeBitLen;    /* XIP Mode bits length. Sets the length of mode bits in XIP mode of operation */

            struct 
            {
                uint32_t XipContinueTransfer; /* Continuous transfer in XIP mode. If enable then continuous transfer mode in XIP will be enabled, in this mode XSPI will 
                                                 keep slave selected until a non-XIP transfer is detected on the AHB interface */
                uint32_t XipWatchDogTimeout;  /* XIP time out value (0 ~ 255) in terms of HCLK. Once slave is selected in continuous XIP mode this counter will be used to de-select the
                                                 slave if there is no request for the time specified in the counter */
            } ContinueTransfer;
        } Read_XIPInitType;
        
        struct 
        {
            uint32_t XipInstructLen;    /* Dual/Quad/Octal mode instruction length. 
                                           Note: Configuring the instruction length has an instruction phase and does not require instruction enable like reading does. */
            uint32_t Reserved;

            struct 
            {
                uint32_t TxdDriverEdge; /* Decided the driving edge of transmit data (0 ~ 255, Max value = (BAUD/2) - 1, BAUDR = CLKDIV[14:0] * 2) */
                uint32_t XipInstrucDDR; /* Instruction DDR: enable Dual-data rate transfer for Instruction phase.
                                           Note: DDR mode only supports mode 0 (SCPH = 0/SCPOL = 0) and mode 3 (SCPH = 1/SCPOL = 1) */
            } DDR_InitType;

        } Write_XIPInitType;
    } XIP_Info;
} XSPI_XIPInitType;


typedef struct 
{
    uint32_t Baudr;         /* Clock Divider: Any even number between 2 and 65534 */

    uint32_t TransferMode;  /* Transfer Mode: Transmit only mode / Receive only mode */
    uint32_t DataFrameSize; /* Data Frame Size: 4-bit ~ 32-bit */

    uint32_t WaitCycles;    /* Wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception.
                               Note: do not set to 0 when reading DDR, measure with XSPI_SCK */ 
    uint32_t CAPhaseRxds;   /* Enable rxds signaling during address and command phase of Hyperbus transfer */
    uint32_t ClockStrech;   /* Clock stretching capability.
                               In case of write, if the FIFO becomes empty XSPI will stretch the clock until FIFO has enough data to continue the transfer
                               In case of read, if the receive FIFO becomes full XSPI will stop the clock until data has been read from the FIFO */
    uint32_t TxdDriverEdge; /* Decided the driving edge of transmit data (0 ~ 255, Max value = (BAUD/2) - 1, BAUDR = CLKDIV[14:0] * 2) */

    uint32_t XIPHyperbus;   /* XIP Hyperbus or non-XIP Hyperbus mode */

    struct
    {
        uint32_t XipFixDFS;     /* Fix DFS for XIP transfers. 
                                   If enable then data frame size for XIP transfers will be fixed to the programmed value in XSPI_CTRL0.DFS[4:0]. 
                                   The number of data frames to fetch will be determined by HSIZE and HBURST signals. 
                                   If disable then data frame size and number of data frames to fetch will be determined by HSIZE and HBURST signals */
        uint32_t XipPrefetch;   /* XIP pre-fetch functionality: if enable XSPI will pre-fetch data frames from next contigous location, to reduce the 
                                   latency for the upcoming contiguous transfer. 
                                   Note: If the next XIP request is not contigous then pre-fetched bits will be discarded */
    } XIP_ReadHyperbusInitType;
}XSPI_HyperbusInitType;


/** Serial Clock Phase **/
#define XSPI_SCPH_FIRST_EDGE                     ((uint32_t)0x00000000U)      
#define XSPI_SCPH_SECOND_EDGE                    ((uint32_t)XSPI_V2_CTRL0_SCPH)  

/** Serial Clock Polarity **/
#define XSPI_SCPOL_LOW_LEVEL                     ((uint32_t)0x00000000U)       
#define XSPI_SCPOL_HIGH_LEVEL                    ((uint32_t)XSPI_V2_CTRL0_SCPOL) 

/** Transfer Mode **/
#define XSPI_TX_AND_RX_MODE                      ((uint32_t)0x00000000U)                                   /* Transmit & Receive */
#define XSPI_TX_ONLY_MODE                        ((uint32_t)XSPI_V2_CTRL0_TMOD_0)                          /* Transmit only mode */
#define XSPI_RX_ONLY_MODE                        ((uint32_t)XSPI_V2_CTRL0_TMOD_1)                          /* Receive only mode*/
#define XSPI_EEPROM_READ_MODE                    ((uint32_t)(XSPI_V2_CTRL0_TMOD_0 | XSPI_V2_CTRL0_TMOD_1)) /* EEPROM Read mode */

/** Slave Select Toggle **/
#define XSPI_NSS_TOGGLE_DISABLE                  ((uint32_t)0x00000000U)        /* XSPI_NSS line will toggle between consecutive data frames, with the serial clock (sclk) being held to its default value */
#define XSPI_NSS_TOGGLE_ENABLE                   ((uint32_t)XSPI_V2_CTRL0_SSTE) /* XSPI_NSS will stay low and sclk will run continuously for the duration of the transfer */

/** XSPI Work Role */
#define XSPI_SLAVE_ROLE                          ((uint32_t)0x00000000U)        /* Slave mode */
#define XSPI_MASTER_ROLE                         ((uint32_t)XSPI_V2_CTRL0_MST)  /* Master mode */

/** Data Frame Size **/
#define XSPI_FRAME_SIZE_4_BIT                    ((uint32_t)(XSPI_V2_CTRL0_DFS_1 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_5_BIT                    ((uint32_t)XSPI_V2_CTRL0_DFS_2)
#define XSPI_FRAME_SIZE_6_BIT                    ((uint32_t)(XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_7_BIT                    ((uint32_t)(XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_1))
#define XSPI_FRAME_SIZE_8_BIT                    ((uint32_t)(XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_1 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_9_BIT                    ((uint32_t)XSPI_V2_CTRL0_DFS_3)
#define XSPI_FRAME_SIZE_10_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_11_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_1))
#define XSPI_FRAME_SIZE_12_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_1 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_13_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_2))
#define XSPI_FRAME_SIZE_14_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_15_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_1))
#define XSPI_FRAME_SIZE_16_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_1 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_17_BIT                   ((uint32_t)XSPI_V2_CTRL0_DFS_4)
#define XSPI_FRAME_SIZE_18_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_19_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_1))
#define XSPI_FRAME_SIZE_20_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_1 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_21_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_2))
#define XSPI_FRAME_SIZE_22_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_23_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_1))
#define XSPI_FRAME_SIZE_24_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_1 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_25_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_3))
#define XSPI_FRAME_SIZE_26_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_27_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_1))
#define XSPI_FRAME_SIZE_28_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_1 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_29_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_2))
#define XSPI_FRAME_SIZE_30_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_0))
#define XSPI_FRAME_SIZE_31_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_1))
#define XSPI_FRAME_SIZE_32_BIT                   ((uint32_t)(XSPI_V2_CTRL0_DFS_4 | XSPI_V2_CTRL0_DFS_3 | XSPI_V2_CTRL0_DFS_2 | XSPI_V2_CTRL0_DFS_1 | XSPI_V2_CTRL0_DFS_0))

/** Receive Data (rxd) Sampling Edge with hclk **/
#define XSPI_RXD_HCLK_RISING_SAMPLING            ((uint32_t)0x00000000U)           /* Positive edge of hclk will be used to sample the incoming data */
#define XSPI_RXD_HCLK_FALLING_SAMPLING           ((uint32_t)XSPI_V2_RX_DELAY_SES)  /* Negative edge of hclk will be used to sample the incoming data */

/** XSPI Data Channel Number with Multi-Channel **/
#define XSPI_STANDARD_MODE                       ((uint32_t)0x00000000U)                                       /* Standard SPI Format */
#define XSPI_DUAL_LINE_MODE                      ((uint32_t)XSPI_V2_CTRL0_SPIFRF_0)                            /* Dual SPI Format */
#define XSPI_QUAD_LINE_MODE                      ((uint32_t)XSPI_V2_CTRL0_SPIFRF_1)                            /* Quad SPI Format */
#define XSPI_OCTAL_LINE_MODE                     ((uint32_t)(XSPI_V2_CTRL0_SPIFRF_0 | XSPI_V2_CTRL0_SPIFRF_1)) /* Octal SPI Format */

/** Address and instruction transfer format **/
#define XSPI_INST_ADDR_SINGLE_LINE               ((uint32_t)0x00000000U)                    /* Instruction and Address will be sent in Standard SPI Mode*/
#define XSPI_INST_SINGLE_LINE_ADDR_MULTI_LINE    ((uint32_t)XSPI_V2_ENH_CTRL0_TRANSTYPE_0)  /* Instruction will be sent in Standard SPI Mode and Address will be sent in the mode specified by XSPI_CTRLR0.SPI_FRF*/
#define XSPI_INST_ADDR_MULTI_LINE                ((uint32_t)XSPI_V2_ENH_CTRL0_TRANSTYPE_1)  /* Both Instruction and Address will be sent in the mode specified by XSPI_CTRLR0.SPI_FRF */

/** defines Length of Address to be transmitted **/
#define XSPI_NO_ADDR_PHASE                       ((uint32_t)0x00000000U)
#define XSPI_ADDR_LEN_4BIT                       ((uint32_t)XSPI_V2_ENH_CTRL0_ADDRLEN_0)
#define XSPI_ADDR_LEN_8BIT                       ((uint32_t)XSPI_V2_ENH_CTRL0_ADDRLEN_1)
#define XSPI_ADDR_LEN_12BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_ADDRLEN_1 | XSPI_V2_ENH_CTRL0_ADDRLEN_0))
#define XSPI_ADDR_LEN_16BIT                      ((uint32_t)XSPI_V2_ENH_CTRL0_ADDRLEN_2)
#define XSPI_ADDR_LEN_20BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_ADDRLEN_2 | XSPI_V2_ENH_CTRL0_ADDRLEN_0))
#define XSPI_ADDR_LEN_24BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_ADDRLEN_2 | XSPI_V2_ENH_CTRL0_ADDRLEN_1))
#define XSPI_ADDR_LEN_28BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_ADDRLEN_2 | XSPI_V2_ENH_CTRL0_ADDRLEN_1 | XSPI_V2_ENH_CTRL0_ADDRLEN_0))
#define XSPI_ADDR_LEN_32BIT                      ((uint32_t)XSPI_V2_ENH_CTRL0_ADDRLEN_3)
#define XSPI_ADDR_LEN_36BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_ADDRLEN_3 | XSPI_V2_ENH_CTRL0_ADDRLEN_0))
#define XSPI_ADDR_LEN_40BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_ADDRLEN_3 | XSPI_V2_ENH_CTRL0_ADDRLEN_1))
#define XSPI_ADDR_LEN_44BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_ADDRLEN_3 | XSPI_V2_ENH_CTRL0_ADDRLEN_1 | XSPI_V2_ENH_CTRL0_ADDRLEN_0))
#define XSPI_ADDR_LEN_48BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_ADDRLEN_3 | XSPI_V2_ENH_CTRL0_ADDRLEN_2))
#define XSPI_ADDR_LEN_52BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_ADDRLEN_3 | XSPI_V2_ENH_CTRL0_ADDRLEN_2 | XSPI_V2_ENH_CTRL0_ADDRLEN_0))
#define XSPI_ADDR_LEN_56BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_ADDRLEN_3 | XSPI_V2_ENH_CTRL0_ADDRLEN_2 | XSPI_V2_ENH_CTRL0_ADDRLEN_1))
#define XSPI_ADDR_LEN_60BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_ADDRLEN_3 | XSPI_V2_ENH_CTRL0_ADDRLEN_2 | XSPI_V2_ENH_CTRL0_ADDRLEN_1 | XSPI_V2_ENH_CTRL0_ADDRLEN_0))

/** Dual/Quad/Octal mode instruction length in bits **/
#define XSPI_NO_INST_PHASE                       ((uint32_t)0x00000000U)
#define XSPI_INST_LEN_4BIT                       ((uint32_t)XSPI_V2_ENH_CTRL0_INSTL_0)
#define XSPI_INST_LEN_8BIT                       ((uint32_t)XSPI_V2_ENH_CTRL0_INSTL_1)
#define XSPI_INST_LEN_16BIT                      ((uint32_t)(XSPI_V2_ENH_CTRL0_INSTL_1 | XSPI_V2_ENH_CTRL0_INSTL_0))

/** Wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception **/
#define XSPI_WAIT_0_CYCLES                       ((uint32_t)0x00U)
#define XSPI_WAIT_1_CYCLES                       ((uint32_t)0x01U)
#define XSPI_WAIT_2_CYCLES                       ((uint32_t)0x02U)
#define XSPI_WAIT_3_CYCLES                       ((uint32_t)0x03U)
#define XSPI_WAIT_4_CYCLES                       ((uint32_t)0x04U)
#define XSPI_WAIT_5_CYCLES                       ((uint32_t)0x05U)
#define XSPI_WAIT_6_CYCLES                       ((uint32_t)0x06U)
#define XSPI_WAIT_7_CYCLES                       ((uint32_t)0x07U)
#define XSPI_WAIT_8_CYCLES                       ((uint32_t)0x08U)
#define XSPI_WAIT_9_CYCLES                       ((uint32_t)0x09U)
#define XSPI_WAIT_10_CYCLES                      ((uint32_t)0x0AU)
#define XSPI_WAIT_11_CYCLES                      ((uint32_t)0x0BU)
#define XSPI_WAIT_12_CYCLES                      ((uint32_t)0x0CU)
#define XSPI_WAIT_13_CYCLES                      ((uint32_t)0x0DU)
#define XSPI_WAIT_14_CYCLES                      ((uint32_t)0x0EU)
#define XSPI_WAIT_15_CYCLES                      ((uint32_t)0x0FU)
#define XSPI_WAIT_16_CYCLES                      ((uint32_t)0x10U)
#define XSPI_WAIT_17_CYCLES                      ((uint32_t)0x11U)
#define XSPI_WAIT_18_CYCLES                      ((uint32_t)0x12U)
#define XSPI_WAIT_19_CYCLES                      ((uint32_t)0x13U)
#define XSPI_WAIT_20_CYCLES                      ((uint32_t)0x14U)
#define XSPI_WAIT_21_CYCLES                      ((uint32_t)0x15U)
#define XSPI_WAIT_22_CYCLES                      ((uint32_t)0x16U)
#define XSPI_WAIT_23_CYCLES                      ((uint32_t)0x17U)
#define XSPI_WAIT_24_CYCLES                      ((uint32_t)0x18U)
#define XSPI_WAIT_25_CYCLES                      ((uint32_t)0x19U)
#define XSPI_WAIT_26_CYCLES                      ((uint32_t)0x1AU)
#define XSPI_WAIT_27_CYCLES                      ((uint32_t)0x1BU)
#define XSPI_WAIT_28_CYCLES                      ((uint32_t)0x1CU)
#define XSPI_WAIT_29_CYCLES                      ((uint32_t)0x1DU)
#define XSPI_WAIT_30_CYCLES                      ((uint32_t)0x1EU)
#define XSPI_WAIT_31_CYCLES                      ((uint32_t)0x1FU)

/** XSPI DDR Enable **/
#define XSPI_DDR_DISABLE                         ((uint32_t)0x00000000U)
#define XSPI_DDR_ENABLE                          ((uint32_t)XSPI_V2_ENH_CTRL0_WRSPIDDREN)

/** Instruction DDR Enable **/
#define XSPI_INST_DDR_DISABLE                    ((uint32_t)0x00000000U)
#define XSPI_INST_DDR_ENABLE                     ((uint32_t)XSPI_V2_ENH_CTRL0_WRINDDREN)

/** Read data strobe enable **/
#define XSPI_RXDS_SIGNAL_DISABLE                 ((uint32_t)0x00000000U)
#define XSPI_RXDS_SIGNAL_ENABLE                  ((uint32_t)XSPI_V2_ENH_CTRL0_SPIRXDSEN)

/** XSPI data mask enable **/
#define XSPI_DATA_MASK_DISABLE                   ((uint32_t)0x00000000U)
#define XSPI_DATA_MASK_ENABLE                    ((uint32_t)XSPI_V2_ENH_CTRL0_SPIDMEN)

/** clock stretching capability in SPI transfers **/
#define XSPI_CLOCK_STRETCH_DISABLE               ((uint32_t)0x00000000U)
#define XSPI_CLOCK_STRETCH_ENABLE                ((uint32_t)XSPI_V2_ENH_CTRL0_CLKSTREN)

/** Defined XIP Read/Write Mode **/
#define XSPI_XIP_READ_MODE                       ((uint32_t)0x00000000U)
#define XSPI_XIP_WRITE_MODE                      ((uint32_t)0x00000001U)

/** Mode bits enable in XIP mode **/
#define XSPI_XIP_MODE_BIT_DISABLE                ((uint32_t)0x00000000U)
#define XSPI_XIP_MODE_BIT_ENABLE                 ((uint32_t)XSPI_V2_XIP_CTRL_MDBITSEN)

/** XIP Mode bits length **/
#define XSPI_XIP_MODE_BIT_LEN_2_BIT              ((uint32_t)0x00000000U)
#define XSPI_XIP_MODE_BIT_LEN_4_BIT              ((uint32_t)XSPI_V2_XIP_CTRL_XIPMBL_0)
#define XSPI_XIP_MODE_BIT_LEN_8_BIT              ((uint32_t)XSPI_V2_XIP_CTRL_XIPMBL_1)
#define XSPI_XIP_MODE_BIT_LEN_16_BIT             ((uint32_t)(XSPI_V2_XIP_CTRL_XIPMBL_1 | XSPI_V2_XIP_CTRL_XIPMBL_0))

/** Fix DFS for XIP transfers **/
#define XSPI_XIP_DFSHC_DISABLE                   ((uint32_t)0x00000000U)
#define XSPI_XIP_DFSHC_ENABLE                    ((uint32_t)XSPI_V2_XIP_CTRL_DFSHC)

/** XIP instruction enable **/
#define XSPI_XIP_INSTRUCT_DISABLE                ((uint32_t)0x00000000U)
#define XSPI_XIP_INSTRUCT_ENABLE                 ((uint32_t)XSPI_V2_XIP_CTRL_XIPINSTEN)

/** Enable continuous transfer in XIP mode **/
#define XSPI_XIP_CONTINUE_TRANSFER_DISABLE       ((uint32_t)0x00000000U)
#define XSPI_XIP_CONTINUE_TRANSFER_ENABLE        ((uint32_t)XSPI_V2_XIP_CTRL_XIPCTEN)

/** Enables XIP pre-fetch functionality **/
#define XSPI_XIP_PREFETCH_DISABLE                ((uint32_t)0x00000000U)
#define XSPI_XIP_PREFETCH_ENABLE                 ((uint32_t)XSPI_V2_XIP_CTRL_XIPPREEN)

/** Enable rxds signaling during address and command phase of Hyperbus transfer **/
#define XSPI_HYPERBUS_CA_RXDS_DISABLE            ((uint32_t)0x00000000U)
#define XSPI_HYPERBUS_CA_RXDS_ENABLE             ((uint32_t)XSPI_V2_ENH_CTRL0_RXDSSIGEN)

/** Defined XIP-Hyperbus and NON-XIP-Hyperbus */
#define XSPI_XIP_HYPERBUS_MODE                   ((uint32_t)0x00000001U)
#define XSPI_NON_XIP_HYPERBUS_MODE               ((uint32_t)0x00000000U)


/** Defined Non-XIP Slave Number */
#define XSPI_NO_SELECT_SLAVE                     ((uint32_t)0x00000000U)
#define XSPI_SELECT_SLAVE_1                      ((uint32_t)XSPI_V2_SLAVE_EN_SEN_0)
#define XSPI_SELECT_SLAVE_2                      ((uint32_t)XSPI_V2_SLAVE_EN_SEN_1)

/** Defined XIP Slave Number */
#define XSPI_NO_XUP_SELECT_SLAVE                 ((uint32_t)0x00000000U)
#define XSPI_XIP_SELECT_SLAVE_1                  ((uint32_t)XSPI_V2_XIP_SLAVE_EN_SEN_0)
#define XSPI_XIP_SELECT_SLAVE_2                  ((uint32_t)XSPI_V2_XIP_SLAVE_EN_SEN_1)

/** Defined FIFO Level */
#define XSPI_FIFO_THRESHOLD_LEVEL0               ((uint32_t)0U)
#define XSPI_FIFO_THRESHOLD_LEVEL1               ((uint32_t)1U)
#define XSPI_FIFO_THRESHOLD_LEVEL2               ((uint32_t)2U)
#define XSPI_FIFO_THRESHOLD_LEVEL3               ((uint32_t)3U)
#define XSPI_FIFO_THRESHOLD_LEVEL4               ((uint32_t)4U)
#define XSPI_FIFO_THRESHOLD_LEVEL5               ((uint32_t)5U)
#define XSPI_FIFO_THRESHOLD_LEVEL6               ((uint32_t)6U)
#define XSPI_FIFO_THRESHOLD_LEVEL7               ((uint32_t)7U)
#define XSPI_FIFO_THRESHOLD_LEVEL8               ((uint32_t)8U)
#define XSPI_FIFO_THRESHOLD_LEVEL9               ((uint32_t)9U)
#define XSPI_FIFO_THRESHOLD_LEVEL10              ((uint32_t)10U)
#define XSPI_FIFO_THRESHOLD_LEVEL11              ((uint32_t)11U)
#define XSPI_FIFO_THRESHOLD_LEVEL12              ((uint32_t)12U)
#define XSPI_FIFO_THRESHOLD_LEVEL13              ((uint32_t)13U)
#define XSPI_FIFO_THRESHOLD_LEVEL14              ((uint32_t)14U)
#define XSPI_FIFO_THRESHOLD_LEVEL15              ((uint32_t)15U)

/** TX-DMA or RX-DMA Enable  **/
#define XSPI_DMA_TX                              ((uint32_t)XSPI_V2_DMA_CTRL_TXDMAEN)
#define XSPI_DMA_RX                              ((uint32_t)XSPI_V2_DMA_CTRL_RXDMAEN)


#define XSPI_BUSY_FLAG                           ((uint32_t)XSPI_V2_STS_BUSY)  /* When set, indicates that a serial transfer is in progress; when cleared indicates that the XSPI is idle or disabled */
#define XSPI_TXFNF_FLAG                          ((uint32_t)XSPI_V2_STS_TXFNF) /* Set when the TX FIFO contains one or more empty locations, and is cleared when the TX FIFO is full */
#define XSPI_TXFE_FLAG                           ((uint32_t)XSPI_V2_STS_TXFE)  /* When the TX FIFO is completely empty is set. 
                                                                             * When the TX FIFO contains one or more valid entries is cleared. This flag does not request an interrupt */
#define XSPI_RXFNE_FLAG                          ((uint32_t)XSPI_V2_STS_RXFNE) /* Set when the receive FIFO contains one or more entries
                                                                             * Cleared when the receive FIFO is empty
                                                                             * This flag can be polled by software to completely empty the receive FIFO */
#define XSPI_RXFF_FLAG                           ((uint32_t)XSPI_V2_STS_RXFF)  /* When the receive FIFO is completely full is set. 
                                                                             * Whenthe receive FIFO contains one or more empty location is cleared */
#define XSPI_TXE_FLAG                            ((uint32_t)XSPI_V2_STS_TXE)   /* Set if the tx FIFO is empty when a transfer is started
                                                                             * This flag can be set only when the XSPI is configured as a slave device
                                                                             * Data from the previous transmission is resent on the txd line. This flag is cleared when read */
#define XSPI_DCERR_FLAG                          ((uint32_t)XSPI_V2_STS_DCERR) /* Relevant only when the XSPI is configured as a master device
                                                                             * This flag will be set if ss_in_n input is asserted by other master when the XSPI master is in the middle of the transfer
                                                                             * This informs the processor that the last data transfer was halted before completion. This flag is cleared when read */



#define XSPI_TXEICR_CLR_OFFSET                   ((uint32_t)0x00000038U)
#define XSPI_RXFUI_CLR_OFFSET                    ((uint32_t)0x00000040U)
#define XSPI_RXFOI_CLR_OFFSET                    ((uint32_t)0x0000003CU)
#define XSPI_MMC_CLR_OFFSET                      ((uint32_t)0x00000044U)
#define XSPI_XIP_RXFOI_CLR_OFFSET                ((uint32_t)0x00000110U)


/* The TX FIFO empty interrupt is triggered when the TX FIFO is equal to or below XSPI_TXFT.TXFTTEI[4:0]. 
   When data is written to the TX FIFO buffer and exceeds the XSPI_TXFT.TXFTTEI[4:0] threshold, the hardware clears this interrupt.
   Note: hardware clearing interrupt flag */
#define XSPI_INT_TXFEMPTY                        ((uint32_t)XSPI_V2_IMASK_TXFEIM) 

/* When data is written to the TX FIFO after it is full, the TX FIFO overflow interrupt is triggered. 
   The written data will be discarded, and reading XSPI_TXEICR_CLR clears the flag. 
   Note: read XSPI_TXEICR_CLR to clear the interrupt flag */
#define XSPI_INT_TXFOVER                         ((uint32_t)(((uint32_t)(XSPI_TXEICR_CLR_OFFSET << 16)) | XSPI_V2_IMASK_TXFOIM)) 

/* The RX FIFO underflow interrupt occurs when trying to read data from an empty RX FIFO. Read XSPI_RXFUI_CLR to clear the flag.
   Note: read XSPI_RXFUI_CLR to clear the interrupt flag */
#define XSPI_INT_RXFUNDER                        ((uint32_t)(((uint32_t)(XSPI_RXFUI_CLR_OFFSET << 16)) | XSPI_V2_IMASK_RXFUIM))

/* The RX FIFO overflow interrupt is triggered when data is still attempted to be written into the RX FIFO after it is completely full. 
   The newly received data will be discarded. Read XSPI_RXFOI_CLR to clear the flag. 
   Note: read XSPI_RXFOI_CLR to clear the interrupt flag */
#define XSPI_INT_RXFOVER                         ((uint32_t)(((uint32_t)(XSPI_RXFOI_CLR_OFFSET << 16)) | XSPI_V2_IMASK_RXFOIM))

/* The RX FIFO full interrupt is triggered when the RX FIFO is equal to or above XSPI_RXFT.RXFTTFI[4:0]. 
   When data is read from the RX FIFO buffer, causing it to fall below the XSPI_RXFT.RXFTTFI[4:0] threshold, the hardware clears this interrupt. 
   Note: hardware clearing interrupt flag */
#define XSPI_INT_RXFFULL                         ((uint32_t)XSPI_V2_IMASK_RXFFIM) 

/* This interrupt is only effective when XSPI is the serial master. When another serial master device on the serial bus selects the XSPI master 
   device as a serial slave device  and is transmitting data, this interrupt will be set. It can be cleared by reading XSPI_MMC_CLR. 
   Note: read XSPI_MMC_CLR to clear the interrupt flag */
#define XSPI_INT_MMCONTENTION                    ((uint32_t)(((uint32_t)(XSPI_MMC_CLR_OFFSET << 16)) | XSPI_V2_IMASK_MMCIM)) 

/* It may be caused by the master device inserting a long WAIT state during transmission, or due to choosing a lower FIFO depth than required for 
   the given frequency ratio between hclk and XSPI_SCK,  cleared by reading XSPI_XIP_RXFOI_CLR. 
   Note: read XSPI_XIP_RXFOI_CLR to clear the interrupt flag */
#define XSPI_INT_XIP_RXFOVER                     ((uint32_t)(((uint32_t)(XSPI_XIP_RXFOI_CLR_OFFSET << 16)) | XSPI_V2_IMASK_XRXOIM))

/* When XIP write transfers are enabled, an interrupt will be triggered if the serial FSM attempts to pop from the transmit FIFO while it is empty. 
   The flag can be cleared by reading XSPI_TXEICR_CLR.
   Note: read XSPI_TXEICR_CLR to clear the interrupt flag */
#define XSPI_INT_TXFUNDER                        ((uint32_t)(((uint32_t)(XSPI_TXEICR_CLR_OFFSET << 16)) | XSPI_V2_IMASK_TXUIM)) 


void XSPI_DeInit(void);

void XSPI_InitBase(XSPI_Module *xSPIx, XSPI_InitType* XSPI_StandInitStruct);
void XSPI_InitEnhanced(XSPI_Module *xSPIx, XSPI_EnhancedInitType* XSPI_EnhancedInitStruct);
void XSPI_InitXIP(XSPI_Module *xSPIx, XSPI_XIPInitType* XSPI_XIPInitStruct);
void XSPI_InitHyperbus(XSPI_Module *xSPIx, XSPI_HyperbusInitType* XSPI_HyperbusInitStruct);

void XSPI_StructBaseInit(XSPI_InitType* XSPI_StandInitStruct);  
void XSPI_InitEnhancedStruct(XSPI_EnhancedInitType* XSPI_EnhancedInitStruct);
void XSPI_InitXIPStruct(XSPI_XIPInitType* XSPI_XIPInitStruct);
void XSPI_InitHyperbusStruct(XSPI_HyperbusInitType* XSPI_HyperbusInitStruct);

void XSPI_EnableHyperbus(XSPI_Module* xSPIx, FunctionalState cmd);
void XSPI_EnableXIPHyperbusRead(XSPI_Module* xSPIx, FunctionalState cmd);
void XSPI_EnableXIPHyperbusWrite(XSPI_Module* xSPIx, FunctionalState cmd);

void XSPI_SetNumberOfDataFrame(XSPI_Module* xSPIx, uint32_t NumDataFrame);

void XSPI_EnableClockStrech(XSPI_Module* xSPIx, FunctionalState cmd);
void XSPI_EnableDataMask(XSPI_Module* xSPIx, FunctionalState cmd);

void XSPI_Enable(XSPI_Module* xSPIx, FunctionalState cmd);
void XSPI_Slave_Select(XSPI_Module* xSPIx, uint32_t Slave);
void XSPI_XIP_Slave_Select(XSPI_Module* xSPIx, uint32_t Slave);

void XSPI_SetTXStartFIFOThreshold(XSPI_Module* xSPIx, uint32_t fifo_level);
uint16_t XSPI_GetTXStartFIFOThreshold(XSPI_Module* xSPIx);

void XSPI_SetTXFIFOEmptyThreshold(XSPI_Module* xSPIx, uint32_t fifo_level);
uint16_t XSPI_GetTXFIFOEmptyThreshold(XSPI_Module* xSPIx);

void XSPI_SetRXFIFOFullThreshold(XSPI_Module* xSPIx, uint32_t fifo_level);
uint16_t XSPI_GetRXFIFOFullThreshold(XSPI_Module* xSPIx);

uint16_t XSPI_GetTXFIFODataNum(XSPI_Module* xSPIx);
uint16_t XSPI_GetRXFIFODataNum(XSPI_Module* xSPIx);

uint32_t XSPI_GetDataPointer(XSPI_Module* xSPIx);
void XSPI_SendData(XSPI_Module* xSPIx, uint32_t SendData);
uint32_t XSPI_ReceiveData(XSPI_Module* xSPIx);
void XSPI_ClearRxFIFO(XSPI_Module* xSPIx);

void XSPI_EnableDma(XSPI_Module* xSPIx, uint16_t XSPI_DMAReq, FunctionalState Cmd);
void XSPI_SetDMATxFIFOThreshold(XSPI_Module* xSPIx, uint32_t fifo_level);
uint16_t XSPI_GetDMATxFIFOThreshold(XSPI_Module* xSPIx);
void XSPI_SetDMARxFIFOThreshold(XSPI_Module* xSPIx, uint32_t fifo_level);
uint16_t XSPI_GetDMARxFIFOThreshold(XSPI_Module* xSPIx);
uint32_t XSPI_GetDMACompletedDataFrameNum(XSPI_Module* xSPIx);

uint32_t XSPI_GetIdentification(XSPI_Module* xSPIx);
uint32_t XSPI_GetComponentVersion(XSPI_Module* xSPIx);

void XSPI_SetXIPModeBit(XSPI_Module* xSPIx, uint16_t mode_bit);
void XSPI_SetXIPReadIncrOpcode(XSPI_Module* xSPIx, uint16_t opcode);
void XSPI_SetXIPReadWrapOpcode(XSPI_Module* xSPIx, uint16_t opcode);
void XSPI_SetXIPWriteIncrOpcode(XSPI_Module* xSPIx, uint16_t opcode);
void XSPI_SetXIPWriteWrapOpcode(XSPI_Module* xSPIx, uint16_t opcode);

FlagStatus XSPI_GetFlagStatus(XSPI_Module* xSPIx, uint32_t Flag);
void XSPI_DisbaleAllInt(XSPI_Module* xSPIx);
void XSPI_EnableInt(XSPI_Module* xSPIx, uint32_t XSPI_IT, FunctionalState Cmd);
INTStatus XSPI_GetINTStatus(XSPI_Module* xSPIx, uint32_t XSPI_IT);
INTStatus XSPI_GetINTRawStatus(XSPI_Module* xSPIx, uint32_t XSPI_IT);
void XSPI_ClrITPendingBit(XSPI_Module* xSPIx, uint32_t XSPI_IT);
void XSPI_ClrITAllPendingBit(XSPI_Module* xSPIx);



#ifdef __cplusplus
}
#endif

#endif /* __n32h7xx_XSPI_V2_H__ */

