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
 * @file n32h7xx_dsi.h
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */ 
#ifndef __N32H7XX_DSI_H__
#define __N32H7XX_DSI_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes */
#include "n32h7xx.h"

#define DSI_TIME_OUT_VALUE              ((uint32_t)0x00001000U)

#define DSI_REGISTER_MASK               ((uint32_t)0x00000000U)

#define DSI_NO_ERRORS                   ((uint32_t)0x00000000U)    

#define DSI_MAX_RETURN_PKT_SIZE         ((uint32_t)0x00000037U) /* Maximum return packet configuration */

/** DSI_Video_Mode_Type DSI Video Mode Type **/
#define DSI_VID_MODE_NB_PULSES          DSI_REGISTER_MASK
#define DSI_VID_MODE_NB_EVENTS          VID_VIDEOMOD_VIDEOMOD_0
#define DSI_VID_MODE_BURST              VID_VIDEOMOD_VIDEOMOD_1

/** DSI_Video_Pixel_Format **/
#define DSI_RGB_565_16BIT               ((uint32_t)0x0EU)
#define DSI_RGB_666_18BIT               ((uint32_t)0x1EU)
#define DSI_RGB_666_18BIT_LP            ((uint32_t)0x2EU)
#define DSI_RGB_888_24BIT               ((uint32_t)0x3EU)

/** DSI ACTIVE LANES **/
#define DSI_ACTIVE_DATALANE0            ((uint32_t)0U)
#define DSI_ACTIVE_DATALANE1            ((uint32_t)1U)
#define DSI_ACTIVE_DATALANE2            ((uint32_t)2U)
#define DSI_ACTIVE_DATALANE3            ((uint32_t)3U)

/**  DSI_Number_Of_Lanes **/
#define DSI_NO_DATA_LENE          (DSI_REGISTER_MASK)
#define DSI_ONE_DATA_LANE         (DSI_DATLANEN_DATLANEN_0)
#define DSI_TWO_DATA_LANES        (DSI_DATLANEN_DATLANEN_1 | DSI_DATLANEN_DATLANEN_0)
#define DSI_THREE_DATA_LANES      (DSI_DATLANEN_DATLANEN_2 | DSI_DATLANEN_DATLANEN_1 | DSI_DATLANEN_DATLANEN_0)
#define DSI_FOUR_DATA_LANES       (DSI_DATLANEN_DATLANEN_3 | DSI_DATLANEN_DATLANEN_2 | DSI_DATLANEN_DATLANEN_1 | DSI_DATLANEN_DATLANEN_0)


#define DSI_DATALANE0                   (DSI_REGISTER_MASK)
#define DSI_DATALANE1                   (VID_VC_VC_0)
#define DSI_DATALANE2                   (VID_VC_VC_1)
#define DSI_DATALANE3                   (VID_VC_VC_0 | VID_VC_VC_1)

#define DSI_ULPS_NO_DATA_LANE           (DSI_REGISTER_MASK)
#define DSI_ULPS_ONE_DATA_LANE          (DSI_WRPCTRL_ULPSDLEN_0)
#define DSI_ULPS_TWO_DATA_LANE          (DSI_WRPCTRL_ULPSDLEN_0 | DSI_WRPCTRL_ULPSDLEN_1)
#define DSI_ULPS_THREE_DATA_LANE        (DSI_WRPCTRL_ULPSDLEN_0 | DSI_WRPCTRL_ULPSDLEN_1 | DSI_WRPCTRL_ULPSDLEN_2)
#define DSI_ULPS_FOUR_DATA_LANE         (DSI_WRPCTRL_ULPSDLEN_0 | DSI_WRPCTRL_ULPSDLEN_1 | DSI_WRPCTRL_ULPSDLEN_2 | DSI_WRPCTRL_ULPSDLEN_3)

/** DSI Multiple packets per video line **/
#define DSI_1_PACKETS_PER_LINE          (VID_PKTPERLINE_PKTPERLINE_0)
#define DSI_2_PACKETS_PER_LINE          (VID_PKTPERLINE_PKTPERLINE_1)
#define DSI_4_PACKETS_PER_LINE          (VID_PKTPERLINE_PKTPERLINE_2)

/** DSI_HOST NON-CONTINUOUS HS CLOCK/CONTINUOUS HS CLOCK **/
#define DSI_NON_CONTINUOUS_HS_CLOCK     (DSI_REGISTER_MASK)
#define DSI_CONTINUOUS_HS_CLOCK         (DSI_CONTHSCLK_CONTHSCLK)

/** DSI_HOST ENABLE INSERT AN EOTP **/
#define DSI_INSERT_EOTP_DISABLE         (DSI_REGISTER_MASK)
#define DSI_INSERT_EOTP_ENABLE          (DSI_AUTOINSERT_EOTP_AUTOINSEOTP)

/** DSI_HOST ENABLE CHECK CRC **/
#define DSI_CHECK_CRC_ENABLE            (DSI_REGISTER_MASK)
#define DSI_CHECK_CRC_DISABLE           (DSI_DISRXCRCCHK_DISRXCRCCHK)

/** DSI_HOST DISABLE BURST **/
#define DSI_BURST_ENABLE                (DSI_REGISTER_MASK)
#define DSI_BURST_DISABLE               (DSI_DISBST_DISBST)

/** DSI_HOST VID SKEW CAL ENABLE **/
#define DSI_SKEWCALLINE_DISABLE         (DSI_REGISTER_MASK)
#define DSI_SKEWCALLINE_ENABLE          (DSI_SKEWCALINE_SKEWCALINE)

/** DSI_HOST VID ENABLE **/
#define DSI_VID_DISABLE                 (DSI_REGISTER_MASK)
#define DSI_VID_ENABLE                  (VID_EN_EN)

/** DSI_HOST VID Polarity of VSYNC **/
#define DSI_VSYNC_ACTIVE_LOW            (DSI_REGISTER_MASK)
#define DSI_VSYNC_ACTIVE_HIGH           (VID_VSYNCPOL_VSYNCPOL)

/** DSI_HOST VID Polarity of HSYNC **/
#define DSI_HSYNC_ACTIVE_LOW            (DSI_REGISTER_MASK)
#define DSI_HSYNC_ACTIVE_HIGH           (VID_HSYNCPOL_HSYNCPOL)

/** DSI_HOST VID OVERRIDE MODE **/
#define DSI_OVERRIDE_MODE_DISABLE       (DSI_REGISTER_MASK)
#define DSI_OVERRIDE_MODE_ENABLE        (VID_OVERIDE_OVERIDE)

/** DSI_HOST VID BLLP MODE **/
#define DSI_BLANKING_PACKETS_INBLLP     (DSI_REGISTER_MASK)
#define DSI_LP_MODE_INBLLP              (VID_BLLPMOD_BLLPMOD)

/** DSI_HOST VID NULL PACKET IN BLLP MODE **/
#define DSI_NULL_PACKET_INBLLP_DISABLE  (DSI_REGISTER_MASK)
#define DSI_NULL_PACKET_INBLLP_ENABLE   (VID_NULLPKTBLLP_NULLPKTBLLP)

/** DSI_HOST VID EXTERNAL VIDEO INTERFACE PACKET REQUESTS ARE ALLOWED **/
#define DSI_EXT_PACKETS_DISABLE         (DSI_REGISTER_MASK)
#define DSI_EXT_PACKETS_VSYNC_ENABLE    (VID_EXTPKTEN_EXTPKTEN_0)
#define DSI_EXT_PACKETS_VBP_ENABLE      (VID_EXTPKTEN_EXTPKTEN_1)
#define DSI_EXT_PACKETS_AVL_ENABLE      (VID_EXTPKTEN_EXTPKTEN_2)
#define DSI_EXT_PACKETS_VFP_ENABLE      (VID_EXTPKTEN_EXTPKTEN_3)

/** DSI Packets Data type **/
#define DSI_SHORT_VSYNC_START               (0x01U)
#define DSI_SHORT_VSYNC_END                 (0x11U)
#define DSI_SHORT_HSYNC_START               (0x21U)
#define DSI_SHORT_HSYNC_END                 (0x31U)
#define DSI_SHORT_EOTP                      (0x08U)
#define DSI_SHORT_CMOFF                     (0x02U)
#define DSI_SHORT_CMON                      (0x12U)
#define DSI_SHORT_SHUTDOWN_PH               (0x22U)
#define DSI_SHORT_TURNON_PH                 (0x3FU)
#define DSI_SHORT_GWRITE_NOPARA             (0x03U)
#define DSI_SHORT_GWRITE_1PARA              (0x13U)
#define DSI_SHORT_GWRITE_2PARA              (0x23U)
#define DSI_SHORT_GREAD_NOPARA              (0x04U)
#define DSI_SHORT_GREAD_1PARA               (0x14U)
#define DSI_SHORT_GREAD_2PARA               (0x24U)
#define DSI_SHORT_DCSWRITE_NOPARA           (0x05U)
#define DSI_SHORT_DCSWRITE_1PARA            (0x15U)
#define DSI_SHORT_DCSREAD_NOPARA            (0x06U)
#define DSI_SHORT_MAX_PKTSIZE               (0x37U)
#define DSI_LONG_NULL_PKT                   (0x09U)
#define DSI_LONG_BLANK_PKT                  (0x19U)
#define DSI_LONG_GWRITE                     (0x29U)
#define DSI_LONG_DCSWRITE                   (0x39U)
#define DSI_LONG_YUV422_20BIT               (0x0CU)
#define DSI_LONG_YUV422_24BIT               (0x1CU)
#define DSI_LONG_YUV422_16BIT               (0x2CU)
#define DSI_LONG_RGB101010_30BIT            (0x0DU)
#define DSI_LONG_RGB121212_36BIT            (0x1DU)
#define DSI_LONG_YUV420_12BIT               (0x3DU)
#define DSI_LONG_RGB565                     (0x0EU)
#define DSI_LONG_RGB666                     (0x1EU)
#define DSI_LONG_RGB666_LP                  (0x2EU)
#define DSI_LONG_RGB888                     (0x3EU)

/** DSI_DCS_Command DSI DCS Command **/
#define DSI_ENTER_IDLE_MODE                 (0x39U)
#define DSI_ENTER_INVERT_MODE               (0x21U)
#define DSI_ENTER_NORMAL_MODE               (0x13U)
#define DSI_ENTER_PARTIAL_MODE              (0x12U)
#define DSI_ENTER_SLEEP_MODE                (0x10U)
#define DSI_EXIT_IDLE_MODE                  (0x38U)
#define DSI_EXIT_INVERT_MODE                (0x20U)
#define DSI_EXIT_SLEEP_MODE                 (0x11U)
#define DSI_GET_3D_CONTROL                  (0x3FU)
#define DSI_GET_ADDRESS_MODE                (0x0BU)
#define DSI_GET_BLUE_CHANNEL                (0x08U)
#define DSI_GET_DIAGNOSTIC_RESULT           (0x0FU)
#define DSI_GET_DISPLAY_MODE                (0x0DU)
#define DSI_GET_GREEN_CHANNEL               (0x07U)
#define DSI_GET_PIXEL_FORMAT                (0x0CU)
#define DSI_GET_POWER_MODE                  (0x0AU)
#define DSI_GET_RED_CHANNEL                 (0x06U)
#define DSI_GET_SCANLINE                    (0x45U)
#define DSI_GET_SIGNAL_MODE                 (0x0EU)
#define DSI_NOP                             (0x00U)
#define DSI_READ_DDB_CONTINUE               (0xA8U)
#define DSI_READ_DDB_START                  (0xA1U)
#define DSI_READ_MEMORY_CONTINUE            (0x3EU)
#define DSI_READ_MEMORY_START               (0x2EU)
#define DSI_SET_3D_CONTROL                  (0x3DU)
#define DSI_SET_ADDRESS_MODE                (0x36U)
#define DSI_SET_COLUMN_ADDRESS              (0x2AU)
#define DSI_SET_DISPLAY_OFF                 (0x28U)
#define DSI_SET_DISPLAY_ON                  (0x29U)
#define DSI_SET_GAMMA_CURVE                 (0x26U)
#define DSI_SET_PAGE_ADDRESS                (0x2BU)
#define DSI_SET_PARTIAL_COLUMNS             (0x31U)
#define DSI_SET_PARTIAL_ROWS                (0x30U)
#define DSI_SET_PIXEL_FORMAT                (0x3AU)
#define DSI_SET_SCROLL_AREA                 (0x33U)
#define DSI_SET_SCROLL_START                (0x37U)
#define DSI_SET_TEAR_OFF                    (0x34U)
#define DSI_SET_TEAR_ON                     (0x35U)
#define DSI_SET_TEAR_SCANLINE               (0x44U)
#define DSI_SET_VSYNC_TIMING                (0x40U)
#define DSI_SOFT_RESET                      (0x01U)
#define DSI_WRITE_LUT                       (0x2DU)
#define DSI_WRITE_MEMORY_CONTINUE           (0x3CU)
#define DSI_WRITE_MEMORY_START              (0x2CU)

/** DSI_Color_Coding DSI Color Coding **/
#define DSI_RGB565                  ((uint32_t)0x00000000U) /* The values 0x00000001 and 0x00000002 can also be used for the RGB565 color mode configuration */
#define DSI_RGB666                  ((uint32_t)0x00000003U) /* The value 0x00000004 can also be used for the RGB666 color mode configuration                 */
#define DSI_RGB888                  ((uint32_t)0x00000005U)

/** DSI_SHORT_WRITE_PKT_Data_Type DSI SHORT WRITE PKT Data Type **/
#define DSI_DCS_SHORT_PKT_WRITE_P0  ((uint32_t)0x00000005U) /* DCS short write, no parameters      */
#define DSI_DCS_SHORT_PKT_WRITE_P1  ((uint32_t)0x00000015U) /* DCS short write, one parameter      */
#define DSI_GEN_SHORT_PKT_WRITE_P0  ((uint32_t)0x00000003U) /* Generic short write, no parameters  */
#define DSI_GEN_SHORT_PKT_WRITE_P1  ((uint32_t)0x00000013U) /* Generic short write, one parameter  */
#define DSI_GEN_SHORT_PKT_WRITE_P2  ((uint32_t)0x00000023U) /* Generic short write, two parameters */

/** DSI_LONG_WRITE_PKT_Data_Type DSI LONG WRITE PKT Data Type **/
#define DSI_DCS_LONG_PKT_WRITE      ((uint32_t)0x00000039U) /* DCS long write     */
#define DSI_GEN_LONG_PKT_WRITE      ((uint32_t)0x00000029U) /* Generic long write */

/** DSI_SHORT_READ_PKT_Data_Type DSI SHORT READ PKT Data Type **/
#define DSI_DCS_SHORT_PKT_READ      ((uint32_t)0x00000006U) /* DCS short read                     */
#define DSI_GEN_SHORT_PKT_READ_P0   ((uint32_t)0x00000004U) /* Generic short read, no parameters  */
#define DSI_GEN_SHORT_PKT_READ_P1   ((uint32_t)0x00000014U) /* Generic short read, one parameter  */
#define DSI_GEN_SHORT_PKT_READ_P2   ((uint32_t)0x00000024U) /* Generic short read, two parameters */

#define DSI_EOTP                    ((uint32_t)0x00000008U)

/* DSI APB Packet Send Mode */
#define DSI_MODE_LPDT               (DSI_REGISTER_MASK)
#define DSI_MODE_HSDT               (DSI_PKTCTRL_MOD)

/** DSI Host periph status flag **/
#define DSI_FLAG_SOT_ERROR          (DSI_STS_SOTERR)
#define DSI_FLAG_SOTSYNC_ERROR      (DSI_STS_SOTSYNCERR)
#define DSI_FLAG_EOTSYNC_ERROR      (DSI_STS_EOTSYNCERR)
#define DSI_FLAG_ESCMOD_ERROR       (DSI_STS_ESCMODERR)
#define DSI_FLAG_LPTXSYNC_ERROR     (DSI_STS_LPTXSYNCERR)
#define DSI_FLAG_TO_ERROR           (DSI_STS_TOERR)
#define DSI_FLAG_FCTRL_ERROR        (DSI_STS_FCTRLERR)
#define DSI_FLAG_COTDET_ERROR       (DSI_STS_COTDET)
#define DSI_FLAG_ECCSB_ERROR        (DSI_STS_ECCSERR)
#define DSI_FLAG_ECCML_ERROR        (DSI_STS_ECCMERR)
#define DSI_FLAG_CRC_ERROR          (DSI_STS_CRCERR)
#define DSI_FLAG_DATATYPE_ERROR     (DSI_STS_DATYPERR)
#define DSI_FLAG_VCIDINVLID_ERROR   (DSI_STS_VCIDINVLD)
#define DSI_FLAG_INVLID_TXLEN_ERROR (DSI_STS_INVLDTXL)
#define DSI_FLAG_PROVILT_ERROR      (DSI_STS_PROVILT)
#define DSI_FLAG_BIT0_ERROR         (DSI_STS_BIT0)
#define DSI_FLAG_BIT1_ERROR         (DSI_STS_BIT1)
#define DSI_FLAG_BIT2_ERROR         (DSI_STS_BIT2)
#define DSI_FLAG_BIT3_ERROR         (DSI_STS_BIT3)

/** DSI Host RX error status flag **/
#define DSI_ERROR_FLAG_ECCSB        (DSI_ERRSTS_ECCSERR)
#define DSI_ERROR_FLAG_ECCML        (DSI_ERRSTS_ECCMERR)
#define DSI_ERROR_FLAG_CRC          (DSI_ERRSTS_CRCERR)
#define DSI_ERROR_FLAG_HTXTO        (DSI_ERRSTS_HTXTOERR)
#define DSI_ERROR_FLAG_LRXTO        (DSI_ERRSTS_LRXTOERR)
#define DSI_ERROR_FLAG_BATTO        (DSI_ERRSTS_BATTOERR)

/** DSI Host packet status flag **/
#define DSI_PKT_FLAG_NIDLE          (DSI_PKTSTS_NIDLE)
#define DSI_PKT_FLAG_TXD            (DSI_PKTSTS_TXD)
#define DSI_PKT_FLAG_DPHYDIR        (DSI_PKTSTS_DPHYDIR)
#define DSI_PKT_FLAG_TXFOVER        (DSI_PKTSTS_TXFOVER)
#define DSI_PKT_FLAG_TXFUNDER       (DSI_PKTSTS_TXFUNDER)
#define DSI_PKT_FLAG_RXFOVER        (DSI_PKTSTS_RXFOVER)
#define DSI_PKT_FLAG_RXFUNDER       (DSI_PKTSTS_RXFUNDER)
#define DSI_PKT_FLAG_RXPKTD         (DSI_PKTSTS_RXPKTD)
#define DSI_PKT_FLAG_ALLRXPKTD      (DSI_PKTSTS_ALLRXPKTD)

/** DSI Wrapper interrupt sources **/
#define DSI_WRAPPER_INT_BLKERRIEN   (DSI_WRPCTRL_BLKEERIEN)
#define DSI_WRAPPER_INT_SPERRIEN    (DSI_WRPCTRL_SPERRIEN)
#define DSI_WRAPPER_INT_OVERRIEN    (DSI_WRPCTRL_OVERRIEN)
#define DSI_WRAPPER_INT_UNDERRIEN   (DSI_WRPCTRL_UNDERRIEN)

/** DSI Wrapper Flag **/
#define DSI_WRAPPER_FLAG_ISKEWCALDN (DSI_WRPSTS_ISKEWCALDN)
#define DSI_WRAPPER_FLAG_PSKEWCALDN (DSI_WRPSTS_PSKEWCALDN)
#define DSI_WRAPPER_FLAG_TRIGACK    (DSI_WRPSTS_TRIGACK)
#define DSI_WRAPPER_FLAG_BLKERRIEN  (DSI_WRPSTS_BLKERRF)
#define DSI_WRAPPER_FLAG_SPERRIEN   (DSI_WRPSTS_SPERRIEN)
#define DSI_WRAPPER_FLAG_OVERRIEN   (DSI_WRPSTS_OVERRIEN)
#define DSI_WRAPPER_FLAG_UNDERRIEN  (DSI_WRPSTS_UNDERRIEN)

/** DSI Status structures definition **/
typedef enum
{
    DSI_OK       = 0x00,
    DSI_RESET    = 0x01,
    DSI_READY    = 0x02,
    DSI_ERROR    = 0x03,
    DSI_BUSY     = 0x04,
    DSI_TIMEOUT  = 0x05
} DSI_StateTypeDef;

/** DSI Host Init Structure definition **/
typedef struct
{
    uint32_t NumOfLanes;                /* Number of lanes */
    uint32_t BurstSel;                  /* Select combined burst or not */
    uint32_t AutoInsertEOTP;            /* Select auto insert EOTP  or not */
    uint32_t DisRXCRC;                  /* Select check CRC or not */
} DSI_HostInitTypeDef;

/** DSI Clock structure definition **/
typedef struct
{
    uint32_t ClockBeforeHS;                /* Set the number of byte clock periods before HS */
    uint32_t ClockHS2LP;                   /* Set the number of byte clock periods before clock lane into LP after detected in stop state */
    uint32_t ClockLP2HS;                   /* Set the number of byte clock periods LP mode to HS mode */
    uint32_t ClockExitULPS;                /* Set the number of byte clock periods in MARK_1 state after exiting ULPS */
    uint32_t ContinuousHSCLK;              /* Select the continuous HS clock or non-continuous HS clock */
} DSI_ClockInitTypeDef;

/** DSI Skew Calibration Clock structure definition **/
typedef struct
{
    uint32_t ClockInitialSkewcal;          /* Set the number of byte clock consumed by an initial skewcal */
    uint32_t ClockPeriodicSkewcal;         /* Set the number of byte clock consumed by a periodic skewcal */
    uint32_t LinePeriodicSkewcal;          /* Set the lane to issue periodic  */
} DSI_SkewcalInitTypeDef;


/** DSI PHY Clock structure definition **/
typedef struct
{
    uint32_t RefCLK_In_Sel;
    uint32_t PLL_PRE_DIV;
    uint32_t PLL_FBK_INT;
    uint32_t EXTD_CYCLE_SEL; 
    uint32_t PLL_FBK_FRA23_16; 
    uint32_t PLL_FBK_FRA15_8; 
    uint32_t PLL_FBK_FRA7_0;
    
    uint32_t DLANE_HS_PER_TIME;
    uint32_t DLANE_HS_ZERO_TIME;
    uint32_t DLANE_HS_TRAIL_TIME;
    uint32_t CLANE_HS_PER_TIME;
    uint32_t CLANE_HS_ZERO_TIME;
    uint32_t CLANE_HS_TRAIL_TIME;
    uint32_t CLANE_HS_CLK_PRE_TIME;
    uint32_t CLANE_HS_CLK_POST_TIME;
    uint32_t L0_Swap_Sel_Value;     // data/clock lane value config to PAD_CDTX_L0X 
    uint32_t L1_Swap_Sel_Value;     // data/clock lane value config to PAD_CDTX_L1X 
    uint32_t L2_Swap_Sel_Value;     // data/clock lane value config to PAD_CDTX_L2X 
    uint32_t L3_Swap_Sel_Value;     // data/clock lane value config to PAD_CDTX_L3X 
    uint32_t L4_Swap_Sel_Value;     // data/clock lane value config to PAD_CDTX_L4X 
    
    uint32_t SSC_Enable;
    uint32_t PLL_SSC_PRD9_8;  
    uint32_t PLL_SSC_PRD7_0; 
    uint32_t PLL_SSC_DELTA_INIT17_16;  
    uint32_t PLL_SSC_DELTA_INIT15_8; 
    uint32_t PLL_SSC_DELTA_INIT7_0;
    uint32_t PLL_SSC_DELTA17_16;
    uint32_t PLL_SSC_DELTA15_8;
    uint32_t PLL_SSC_DELTA7_0;
} DSI_PHY_InitTypeDef;


/** DSI Video mode configuration **/
typedef struct
{
    uint32_t PixelsPerPacket;              /* Number of pixels to be sent on a video line */
    uint32_t PixelPayloadSize;             /* Maximum number of pixels that should be sent as one DSI packet */
    uint32_t PixelFormat;                  /* Set the pixel format  */
    uint32_t VSPolarity;                   /* VSYNC pin polarity */
    uint32_t HSPolarity;                   /* HSYNC pin polarity */
    uint32_t Mode;                         /* Video mode type */
    uint32_t Override;                     /* Select CFG_VID parameters or first video frame is used to calibrate */
    uint32_t DelayFromStart;               /* Set the number of cycles to delay the start of line */
    uint32_t HorizontalFrontPorch;         /* Horizontal front-porch duration, Only Override = 1 need to program */
    uint32_t HorizontalBackPorch;          /* Horizontal back-porch duration (in lane byte clock cycles), Only Override = 1 need to program */
    uint32_t HorizontalSyncActive;         /* Horizontal synchronism active duration (in lane byte clock cycles), Only Override = 1 need to program */
    uint32_t PacketsPerLine;               /* Multiple packets per video line */
    uint32_t VerticalBackPorch;            /* Vertical back-porch duration, Only Override = 1 need to program */
    uint32_t VerticalFrontPorch;           /* Vertical front-porch duration, Only Override = 1 need to program */
    uint32_t BLLPMode;                     /* Select blanking packets or LP mode in BLLP */
    uint32_t NULLPacketInBLLP;             /* Select blanking packet or NULL packet in BLLP */
    uint32_t VerticalActive;               /* Vertical active duration, Only Override = 1 need to program */
    uint32_t VirtualChannel;               /* Virtual channel ID */
    uint32_t ExternalPacket;               /* Select external to the video interface packet requests are allowed */
    uint32_t VerticalSyncStartPayload;     /* Set the payload value for vertical sync start */
    uint32_t PayloadPerPacket;             /* Set the payload in a multipacket per video line */
} DSI_VidCfgTypeDef;

/** DSI HOST Timeouts definition **/
typedef struct
{   
    uint32_t HighSpeedTXTimeout;           /* High-speed tx time-out */
    uint32_t LowPowerRxTimeout;            /* Low-power rx time-out */
    uint32_t BTATimeout;                   /* Bus turn around BTA time-out */
} DSI_TimeoutCfgTypeDef;

/** DSI Packet header type define **/
typedef struct
{
    uint32_t                  WordCount;    /* DSI packet word count  */
    uint32_t                  ChannelID;    /* DSI packet virtual channel  */
    uint32_t                  DataType;     /* DSI Error monitoring mask  */
} DSI_PKTHeaderTypeDef;

/** DSI Packet Control type define **/
typedef struct
{
    DSI_PKTHeaderTypeDef      Header;
    uint32_t                  CmdType;
    uint32_t                  IsBTAEnable;
    uint32_t                  IsBTAOnly;
} DSI_PKTCtrlTypeDef;


/** DSI handle Structure definition **/
typedef struct
{
    DSI_Module               *Instance;           /* DSI Register base address */
    DSI_Wrapper_Module       *InstanceWrap;       /* DSI Wrapper Register base address */
    DSI_HostInitTypeDef       HostInit;           /* DSI required parameters */
    DSI_ClockInitTypeDef      ClockInit;          /* DSI required parameters */
    DSI_SkewcalInitTypeDef    SkewcalInit;        /* DSI optional required parameters */
} DSI_HandleTypeDef;



DSI_StateTypeDef DSI_EnableResetTrigger(DSI_HandleTypeDef *hdsi);

void DSI_EnableWrapper(DSI_HandleTypeDef *hdsi, FunctionalState Cmd);
void DSI_Disable(DSI_HandleTypeDef *hdsi);

void DSI_EnableClockLane(DSI_HandleTypeDef *hdsi, FunctionalState Cmd);
void DSI_ConfigDataLaneNum(DSI_HandleTypeDef *hdsi, uint32_t datalinenum);

void DSI_CofigWrapULPSDL(DSI_HandleTypeDef *hdsi, uint32_t datalinenum, FunctionalState Cmd);
void DSI_EnableWrapULPSCL(DSI_HandleTypeDef *hdsi, FunctionalState Cmd);
DSI_StateTypeDef DSI_EnterULPSData(DSI_HandleTypeDef *hdsi, FunctionalState Cmd);
DSI_StateTypeDef DSI_EnterULPSClock(DSI_HandleTypeDef *hdsi);
DSI_StateTypeDef DSI_ExitULPSClock(DSI_HandleTypeDef *hdsi);
DSI_StateTypeDef DSI_EnterULPS(DSI_HandleTypeDef *hdsi);
DSI_StateTypeDef DSI_ExitULPS(DSI_HandleTypeDef *hdsi);

void DSI_DisableSkewCal(DSI_HandleTypeDef *hdsi);
void DSI_EnableWrapperISkewCal(DSI_HandleTypeDef *hdsi, FunctionalState Cmd);
void DSI_EnableWrapperPSkewCal(DSI_HandleTypeDef *hdsi, FunctionalState Cmd);
DSI_StateTypeDef DSI_EnableInitialSkewCalib(DSI_HandleTypeDef *hdsi);
DSI_StateTypeDef DSI_EnablePeriodSkewCali(DSI_HandleTypeDef *hdsi);

void DSI_SetVCID(DSI_HandleTypeDef *hdsi, uint32_t channel);
void DSI_ConfigTimeout(DSI_HandleTypeDef *hdsi, uint32_t hstxcnt, uint32_t lprxcnt, uint32_t btacnt);
void DSI_Start(DSI_HandleTypeDef *hdsi);


DSI_StateTypeDef DSI_APBPKT_ShortWrite(DSI_HandleTypeDef *hdsi, uint32_t ChannelID, uint32_t Mode, uint32_t Speed, uint32_t Param1, uint32_t Param2);
DSI_StateTypeDef DSI_APBPKT_LongWrite(DSI_HandleTypeDef *hdsi, uint32_t ChannelID, uint32_t Mode, uint32_t Speed, uint8_t *ParametersTable, uint32_t NbParams);
DSI_StateTypeDef DSI_APBPKT_Read(DSI_HandleTypeDef *hdsi, uint32_t ChannelNbr, uint8_t *Array, uint32_t Size, uint32_t Mode, uint32_t DCSCmd, uint8_t *ParametersTable);
DSI_StateTypeDef DSI_APBPKT_Read_BTA(DSI_HandleTypeDef *hdsi, uint32_t ChannelNbr, uint8_t *Array, uint32_t Size, uint32_t Mode);

void DSI_Wrapper_ConfigInt(DSI_HandleTypeDef *hdsi, uint32_t DSI_IT, FunctionalState Cmd);
FlagStatus DSI_Wrapper_GetFlagStatus(DSI_HandleTypeDef *hdsi, uint32_t DSI_FLAG);
void DSI_Wrapper_ClearFlag(DSI_HandleTypeDef *hdsi, uint32_t DSI_FLAG);
INTStatus DSI_Wrapper_GetIntStatus(DSI_HandleTypeDef *hdsi, uint32_t DSI_IT);

FlagStatus DSI_GetPHYStatus(DSI_HandleTypeDef *hdsi);
FlagStatus DSI_GetSTS(DSI_HandleTypeDef *hdsi, uint32_t DSI_FLAG);
FlagStatus DSI_GetERRSTS(DSI_HandleTypeDef *hdsi, uint32_t DSI_FLAG);
FlagStatus DSI_GetPKTSTS(DSI_HandleTypeDef *hdsi, uint32_t DSI_FLAG);

DSI_StateTypeDef DSI_DeInit(DSI_HandleTypeDef *hdsi);
void DSI_InitHostWrap(DSI_HandleTypeDef *hdsi);
void DSI_InitPHY(DSI_HandleTypeDef *hdsi, DSI_PHY_InitTypeDef *PHY_InitParams);
DSI_StateTypeDef DSI_Init(DSI_HandleTypeDef *hdsi);
DSI_StateTypeDef DSI_ConfigVideoMode(DSI_HandleTypeDef *hdsi, DSI_VidCfgTypeDef *VidCfg);

#ifdef __cplusplus
}
#endif

#endif /* __N32H7XX_DSI_H__ */
