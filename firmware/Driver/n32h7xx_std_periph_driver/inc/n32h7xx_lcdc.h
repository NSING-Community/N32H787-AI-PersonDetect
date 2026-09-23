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
 * @file n32h7xx_lcdc.h
 * @author Nations
 * @version From N32H7xx_Library.1.2.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H7XX_LCDC_H
#define __N32H7XX_LCDC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h7xx.h"

/*** LCDC Structure Definition Start ***/

/** LCDC Init structure definition is used with LCDC. **/
typedef struct
{
    uint32_t LCDC_HSPolarity;                /* configures the horizontal synchronization polarity. */

    uint32_t LCDC_VSPolarity;                /* configures the vertical synchronization polarity. */

    uint32_t LCDC_DEPolarity;                /* configures the data enable polarity. */

    uint32_t LCDC_PCPolarity;                /* configures the pixel clock polarity.  */

    uint32_t LCDC_HorizontalSync;            /* configures the number of Horizontal synchronization width. */

    uint32_t LCDC_VerticalSync;              /* configures the number of Vertical synchronization height. */

    uint32_t LCDC_AccumulatedHBP;            /* configures the accumulated horizontal back porch width. */

    uint32_t LCDC_AccumulatedVBP;            /* configures the accumulated vertical back porch height. */

    uint32_t LCDC_AccumulatedActiveW;        /* configures the accumulated active width. */

    uint32_t LCDC_AccumulatedActiveH;        /* configures the accumulated active height. */

    uint32_t LCDC_TotalWidth;                /* configures the total width. */

    uint32_t LCDC_TotalHeight;               /* configures the total height. */

    uint32_t LCDC_BackgroundRedValue;        /* configures the background red value. */

    uint32_t LCDC_BackgroundGreenValue;      /* configures the background green value. */ 

    uint32_t LCDC_BackgroundBlueValue;       /* configures the background blue value. */
} LCDC_InitType;

typedef struct
{
    uint32_t LCDC_HorizontalStart;            /* Configures the window horizontal start Position. */
    
    uint32_t LCDC_HorizontalStop;             /* Configures the window horizontal stop Position. */
    
    uint32_t LCDC_HorizontalScalerStop;       /* Configures the scaler window horizontal stop Position. */    

    uint32_t LCDC_VerticalStart;              /* Configures the window vertical start Position. */

    uint32_t LCDC_VerticalStop;               /* Configures the window vertical stop Position. */
 
    uint32_t LCDC_VerticalScalerStop;         /* Configures the scaler window vertical stop Position. */      
    
    uint32_t LCDC_PixelFormat;                /* Specifies the pixel format. */
    
    uint32_t LCDC_ConstantAlpha;              /* Specifies the constant alpha used for blending. */

    uint32_t LCDC_DefaultAlpha;               /* Configures the default alpha value. */

    uint32_t LCDC_BlendingFactor1;            /* Select the blending factor 1. */

    uint32_t LCDC_BlendingFactor2;            /* Select the blending factor 2. */

    uint32_t LCDC_CFBStartAdress;             /* Configures the color frame buffer address. */

    uint32_t LCDC_AFB0StartAdress;            /* Configures the Auxiliary frame buffer 0 address. */

    uint32_t LCDC_AFB1StartAdress;            /* Configures the Auxiliary frame buffer 1 address. */
    
    uint32_t LCDC_CFBLineLength;              /* Configures the color frame buffer line length. */    
    
    uint32_t LCDC_CFBLineNumber;              /* Configures the number of line in frame buffer. */      

    uint32_t LCDC_CFBPitch;                   /* Configures the color frame buffer pitch in bytes. */ 
    
    uint32_t LCDC_DefaultColorBlue;           /* Configures the default blue value. */     

    uint32_t LCDC_DefaultColorGreen;          /* Configures the default green value. */   
    
    uint32_t LCDC_DefaultColorRed;            /* Configures the default red value. */   
} LCDC_Layer_InitType;

typedef struct
{
    uint32_t Layer_Window_HorizontalStart;     /* Configures the window horizontal start Position. */

    uint32_t Layer_Window_VerticalStart;       /* Configures the window vertical start Position. */
    
    uint32_t Layer_Window_Width;               /* Configure LCDC layer width. */
    
    uint32_t Layer_Window_Height;              /* Configure LCDC layer height. */
    
} LCDC_LayerWindowType;

typedef struct
{
    uint32_t Layer_Pixel_Format;
    
    uint32_t Layer_Scaler_Enable;     
    
    uint32_t Layer_Scaler_InputWidth;     

    uint32_t Layer_Scaler_InputHeight;       
    
    uint32_t Layer_Scaler_OutputWidth;               
    
    uint32_t Layer_Scaler_OutputHeight;              
    
} LCDC_LayerScalerType;

typedef struct
{
    uint32_t LCDC_Blue;                        /* Blue width */
    
    uint32_t LCDC_Green;                       /* Green width */
    
    uint32_t LCDC_Red;                         /* Red width */
}LCDC_RGBType;

typedef struct
{
  uint32_t LCDC_POSX;                           /*  Current X Position */
  uint32_t LCDC_POSY;                           /*  Current Y Position */
} LCDC_PosType;

typedef struct
{
  uint32_t LCDC_ColorKeyBlue;                   /* Configures the color key blue value. 
                                                    This parameter must range from 0x00 to 0xFF. */

  uint32_t LCDC_ColorKeyGreen;                  /* Configures the color key green value. 
                                                    This parameter must range from 0x00 to 0xFF. */
            
  uint32_t LCDC_ColorKeyRed;                    /* Configures the color key red value. 
                                                    This parameter must range from 0x00 to 0xFF. */
} LCDC_ColorKeying_InitType;


typedef struct
{
  uint32_t LCDC_CLUTAdress;                     /* Configures the CLUT address.
                                                    This parameter must range from 0x00 to 0xFF. */

  uint32_t LCDC_RedValue;                            /* Configures the red value.
                                                    This parameter must range from 0x00 to 0xFF. */
    
  uint32_t LCDC_GreenValue;                     /* Configures the green value. 
                                                    This parameter must range from 0x00 to 0xFF. */

  uint32_t LCDC_BlueValue;                      /* Configures the blue value. 
                                                    This parameter must range from 0x00 to 0xFF. */
} LCDC_CLUT_InitType;

/*** LCDC Structure Definition End ***/

/*** LCDC Macro Definition Start ***/

/** LCDC register bit mask definition **/
#define LCDC_REG_BIT_MASK                     ((uint32_t)0x00000000)

/** Whether it is RGB pixel format **/
#define IS_RGB_PIXEL(FORMAT)                   (((FORMAT) == LCDC_PIXEL_FORMAT_ARGB8888)  || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_ABGR8888)  || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_RGBA8888)  || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_BGRA8888)  || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_RGB565)    || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_BGR565)    || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_RGB888))

/** Whether it is YUV pixel format **/
#define IS_YUV_PIXEL(FORMAT)                   (((FORMAT) == LCDC_PIXEL_FORMAT_YUV422I)   || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_YUV420S)   || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_YUV420P)   || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_YUV444))

/** Whether it is L format **/
#define IS_CUSTOM_PIXEL(FORMAT)                (((FORMAT) == LCDC_PIXEL_FORMAT_L8)    || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_AL44)   || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_AL88)   || \
                                                ((FORMAT) == LCDC_PIXEL_FORMAT_CUSTOM))
                                                
/** Horizontal Synchronization POLARITY **/
#define LCDC_HSPOLARITY_LOW                   (LCDC_REG_BIT_MASK)              
#define LCDC_HSPOLARITY_HIGH                  (LCDC_GCTRL_HSPOL)

/** Vertical Synchronization POLARITY **/
#define LCDC_VSPOLARITY_LOW                   (LCDC_REG_BIT_MASK)              
#define LCDC_VSPOLARITY_HIGH                  (LCDC_GCTRL_VSPOL)

/** Data enable POLARITY **/
#define LCDC_DEPOLARITY_LOW                   (LCDC_GCTRL_DEPOL)              
#define LCDC_DEPOLARITY_HIGH                  (LCDC_REG_BIT_MASK)

/** Pixel clock POLARITY **/
#define LCDC_PCPOLARITY_IPC                   (LCDC_REG_BIT_MASK)              
#define LCDC_PCPOLARITY_IIPC                  (LCDC_GCTRL_PCLKPOL)

/** LCDC reload **/
#define LCDC_IMRELOAD                         (LCDC_SRCTRL_IMR)
#define LCDC_VBRELOAD                         (LCDC_SRCTRL_VBR)

/** LCDC reload **/
#define LCDC_LAYER_IMRELOAD                   (LCDC_LSRCTRL_IMR)
#define LCDC_LAYER_VBRELOAD                   (LCDC_LSRCTRL_VBR)
#define LCDC_LAYER_MGRELOAD                   (LCDC_LSRCTRL_MGR)

/** LCDC Pixel format **/
#define LCDC_PIXEL_FORMAT_ARGB8888            (LCDC_REG_BIT_MASK)
#define LCDC_PIXEL_FORMAT_ABGR8888            (LCDC_PFCTRL_PF_0)
#define LCDC_PIXEL_FORMAT_RGBA8888            (LCDC_PFCTRL_PF_1)
#define LCDC_PIXEL_FORMAT_BGRA8888            (LCDC_PFCTRL_PF_0 | LCDC_PFCTRL_PF_1)
#define LCDC_PIXEL_FORMAT_RGB565              (LCDC_PFCTRL_PF_2)
#define LCDC_PIXEL_FORMAT_BGR565              (LCDC_PFCTRL_PF_0 | LCDC_PFCTRL_PF_2)
#define LCDC_PIXEL_FORMAT_RGB888              (LCDC_PFCTRL_PF_1 | LCDC_PFCTRL_PF_2)
#define LCDC_PIXEL_FORMAT_CUSTOM              (LCDC_PFCTRL_PF_0 | LCDC_PFCTRL_PF_1 | LCDC_PFCTRL_PF_2)
#define LCDC_PIXEL_FORMAT_YUVMODE_FLAG        (0x80000000U)
#define LCDC_PIXEL_FORMAT_YUV422I             (LCDC_PIXEL_FORMAT_YUVMODE_FLAG | LCDC_REG_BIT_MASK)
#define LCDC_PIXEL_FORMAT_YUV420S             (LCDC_PIXEL_FORMAT_YUVMODE_FLAG | LCDC_AFBCTRL_YUVMD_0)
#define LCDC_PIXEL_FORMAT_YUV420P             (LCDC_PIXEL_FORMAT_YUVMODE_FLAG | LCDC_AFBCTRL_YUVMD_1)
#define LCDC_PIXEL_FORMAT_YUV444              (LCDC_PIXEL_FORMAT_YUVMODE_FLAG | LCDC_AFBCTRL_YUVMD_0 | LCDC_AFBCTRL_YUVMD_1)
#define LCDC_PIXEL_FORMAT_L8                  (0x00001000U)
#define LCDC_PIXEL_FORMAT_AL44                (0x00002000U)
#define LCDC_PIXEL_FORMAT_AL88                (0x00004000U)

/* YUV order */
#define YUV444_ORDER                          (LCDC_AFBCTRL_YUVIMDO_0 | LCDC_AFBCTRL_YUVIMDO_1)
#define YUV422_ORDER                          (LCDC_AFBCTRL_YUVIMDO)
#define YUV420_ORDER                          (LCDC_AFBCTRL_YUVIMDO_1)

/** LCDC blending factor1 **/
#define LCDC_BLENDING_FACTOR1_CA              (LCDC_BFCTRL_BF1_2)
#define LCDC_BLENDING_FACTOR1_PAxCA           (LCDC_BFCTRL_BF1_1 | LCDC_BFCTRL_BF1_2)

/** LCDC blending factor2 **/
#define LCDC_BLENDING_FACTOR2_CA              (LCDC_BFCTRL_BF2_0 | LCDC_BFCTRL_BF2_2)
#define LCDC_BLENDING_FACTOR2_PAxCA           (LCDC_BFCTRL_BF2_0 | LCDC_BFCTRL_BF2_1 | LCDC_BFCTRL_BF2_2)

/** LCDC interrupt sources **/
#define LCDC_INT_LIEN                         (LCDC_INTEN_LIEN)
#define LCDC_INT_FUIEN                        (LCDC_INTEN_FUIEN)
#define LCDC_INT_BEIEN                        (LCDC_INTEN_BEIEN)
#define LCDC_INT_RRIEN                        (LCDC_INTEN_RRIEN)
#define LCDC_INT_STNSIGIEN                    (LCDC_INTEN_STNSIGIEN)
#define LCDC_INT_STNSYNCIEN                   (LCDC_INTEN_STNSYNCIEN)
#define LCDC_INT_FUKIEN                       (LCDC_INTEN_FUKIEN)
#define LCDC_INT_CRCIEN                       (LCDC_INTEN_CRCIEN)
#define LCDC_INT_RFEIEN                       (LCDC_INTEN_RFEIEN)

/** LCDC Flags **/
#define LCDC_FLAG_L                           (LCDC_INTEN_LIEN)
#define LCDC_FLAG_FU                          (LCDC_INTEN_FUIEN)
#define LCDC_FLAG_BE                          (LCDC_INTEN_BEIEN)
#define LCDC_FLAG_RR                          (LCDC_INTEN_RRIEN)
#define LCDC_FLAG_STNSIG                      (LCDC_INTEN_STNSIGIEN)
#define LCDC_FLAG_STNSYNC                     (LCDC_INTEN_STNSYNCIEN)
#define LCDC_FLAG_FUK                         (LCDC_INTEN_FUKIEN)
#define LCDC_FLAG_CRC                         (LCDC_INTEN_CRCIEN)
#define LCDC_FLAG_RFE                         (LCDC_INTEN_RFEIEN)


void LCDC_DeInit(void);
void LCDC_Init(LCDC_InitType* LCDC_InitStruct);
void LCDC_StructInit(LCDC_InitType* LCDC_InitStruct);
void LCDC_StructInit(LCDC_InitType* LCDC_InitStruct);
void LCDC_Enable(FunctionalState Cmd);
void LCDC_DitherEnable(FunctionalState Cmd);
LCDC_RGBType LCDC_GetDitherWidth(void);
void LCDC_DitherStructInit(LCDC_RGBType* LCDC_RGB_DitherStruct);
void LCDC_LINTPConfig(uint32_t LCDC_LINTPosition);
void LCDC_LayerInit(LCDC_Layer_Module* LCDC_Layerx , LCDC_Layer_InitType* LCDC_Layer_InitStruct);
void LCDC_LayerStructInit(LCDC_Layer_InitType* LCDC_Layer_InitStruct);
void LCDC_LayerEnable(LCDC_Layer_Module* LCDC_Layerx , FunctionalState Cmd);
LCDC_PosType LCDC_GetPosStatus(void);
void LCDC_PosStructInit(LCDC_PosType* LCDC_Pos_InitStruct);
FlagStatus LCDC_GetCDStatus(uint32_t LCDC_CD);
void LCDC_ReloadConfig(uint32_t LCDC_Reload);
void LCDC_LayerReloadConfig(LCDC_Layer_Module* LCDC_Layerx , uint32_t LCDC_LayerReload);
void LCDC_LayerColorKeyingConfig(LCDC_Layer_Module* LCDC_Layerx, LCDC_ColorKeying_InitType* LCDC_ColorKeying_InitStruct, FunctionalState Cmd);
void LCDC_LayerColorKeyingStructInit(LCDC_ColorKeying_InitType* LCDC_ColorKeying_InitStruct);
void LCDC_LayerCLUTEnable(LCDC_Layer_Module* LCDC_Layerx, FunctionalState Cmd);
void LCDC_LayerCLUTInit(LCDC_Layer_Module* LCDC_Layerx, LCDC_CLUT_InitType* LCDC_CLUT_InitStruct);
void LCDC_LayerCLUTStructInit(LCDC_CLUT_InitType* LCDC_CLUT_InitStruct);
void LCDC_LayerPosition(LCDC_Layer_Module* LCDC_Layerx, uint16_t OffsetX, uint16_t OffsetY);
void LCDC_LayerAlpha(LCDC_Layer_Module* LCDC_Layerx, uint8_t ConstantAlpha);
void LCDC_LayerAddress(LCDC_Layer_Module* LCDC_Layerx, uint32_t Address);
void LCDC_LayerSize(LCDC_Layer_Module* LCDC_Layerx, uint32_t Width, uint32_t Height);
void LCDC_LayerPixelFormat(LCDC_Layer_Module* LCDC_Layerx, uint32_t PixelFormat);
void LCDC_ConfigInt(uint32_t LCDC_IT, FunctionalState Cmd);
FlagStatus LCDC_GetFlagStatus(uint32_t LCDC_FLAG);
void LCDC_ClearFlag(uint32_t LCDC_FLAG);
INTStatus LCDC_GetIntStatus(uint32_t LCDC_IT);
void LCDC_ClrIntPendingBit(uint32_t LCDC_IT);
void LCDC_LayerYUVEnable(LCDC_Layer_Module* LCDC_Layerx ,FunctionalState Cmd);
void LCDC_LayerYHeadroomEnable(LCDC_Layer_Module* LCDC_Layerx ,FunctionalState Cmd);
void LCDC_LayerWindow(LCDC_Layer_Module* LCDC_Layerx,LCDC_LayerWindowType* LCDC_LayerWindowStruct);
void LCDC_LayerWindowStructInit(LCDC_LayerWindowType* LCDC_LayerWindowStruct);
void LCDC_LayerScalerStructInit(LCDC_LayerScalerType* LCDC_LayerScalerStruct);
void LCDC_LayerScaler(LCDC_Layer_Module* LCDC_Layerx ,LCDC_LayerScalerType* LCDC_LayerScalerStruct);
void LCDC_LayerScalerEnable(LCDC_Layer_Module* LCDC_Layerx ,FunctionalState Cmd);
void LCDC_LayerRotate180Enable(LCDC_Layer_Module* LCDC_Layerx ,FunctionalState Cmd);
void LCDC_LayerHorizontalMirrorEnable(LCDC_Layer_Module* LCDC_Layerx ,FunctionalState Cmd);



/** LCDC_Exported_Functions End **/

#ifdef __cplusplus
}

#endif

#endif /*__N32H7XX_LCDC_H */
















