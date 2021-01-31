/**
  ******************************************************************************
  * @file    ${file_name} 
  * @author  ${user}
  * @version 
  * @date    ${date}
  * @brief   
  ******************************************************************************
  * @attention
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CORE429I_BASEBOARD_LCD_H
#define __CORE429I_BASEBOARD_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
/* Include LCD component Driver */
#include "../Components/rk043fn48h/rk043fn48h.h"

/* Include SDRAM Driver */
#include "core429I_baseboard_sdram.h"
 
#include "core429I_baseboard.h"
#include "../../../Utilities/Fonts/fonts.h"

/* Exported types ------------------------------------------------------------*/
typedef struct 
{ 
  uint32_t TextColor; 
  uint32_t BackColor;  
  sFONT    *pFont;
}LCD_DrawPropTypeDef;   
   
typedef struct 
{
  int16_t X;
  int16_t Y;
}Point, * pPoint; 
   
/** 
  * @brief  Line mode structures definition  
  */ 
typedef enum
{
  CENTER_MODE             = 0x01,    /* Center mode */
  RIGHT_MODE              = 0x02,    /* Right mode  */
  LEFT_MODE               = 0x03     /* Left mode   */
}Text_AlignModeTypdef;

/* Exported constants --------------------------------------------------------*/
#define MAX_LAYER_NUMBER       				((uint32_t)2)

#define LCD_LayerCfgTypeDef    				LTDC_LayerCfgTypeDef

#define LTDC_ACTIVE_LAYER	     			((uint32_t)1) /* Layer 1 */
/** 
  * @brief  LCD status structure definition  
  */     
#define LCD_OK                 				((uint8_t)0x00)
#define LCD_ERROR              				((uint8_t)0x01)
#define LCD_TIMEOUT            				((uint8_t)0x02)

/** 
  * @brief  LCD FB_StartAddress  
  */
#define LCD_FB_START_ADDRESS       			((uint32_t)0xD0000000)

/** 
  * @brief  LCD color  
  */ 
#define LCD_COLOR_BLUE          			((uint32_t)0xFF0000FF)
#define LCD_COLOR_GREEN         			((uint32_t)0xFF00FF00)
#define LCD_COLOR_RED           			((uint32_t)0xFFFF0000)
#define LCD_COLOR_CYAN          			((uint32_t)0xFF00FFFF)
#define LCD_COLOR_MAGENTA       			((uint32_t)0xFFFF00FF)
#define LCD_COLOR_YELLOW        			((uint32_t)0xFFFFFF00)
#define LCD_COLOR_LIGHTBLUE     			((uint32_t)0xFF8080FF)
#define LCD_COLOR_LIGHTGREEN    			((uint32_t)0xFF80FF80)
#define LCD_COLOR_LIGHTRED      			((uint32_t)0xFFFF8080)
#define LCD_COLOR_LIGHTCYAN     			((uint32_t)0xFF80FFFF)
#define LCD_COLOR_LIGHTMAGENTA  			((uint32_t)0xFFFF80FF)
#define LCD_COLOR_LIGHTYELLOW   			((uint32_t)0xFFFFFF80)
#define LCD_COLOR_DARKBLUE      			((uint32_t)0xFF000080)
#define LCD_COLOR_DARKGREEN     			((uint32_t)0xFF008000)
#define LCD_COLOR_DARKRED       			((uint32_t)0xFF800000)
#define LCD_COLOR_DARKCYAN      			((uint32_t)0xFF008080)
#define LCD_COLOR_DARKMAGENTA   			((uint32_t)0xFF800080)
#define LCD_COLOR_DARKYELLOW    			((uint32_t)0xFF808000)
#define LCD_COLOR_WHITE         			((uint32_t)0xFFFFFFFF)
#define LCD_COLOR_LIGHTGRAY     			((uint32_t)0xFFD3D3D3)
#define LCD_COLOR_GRAY          			((uint32_t)0xFF808080)
#define LCD_COLOR_DARKGRAY      			((uint32_t)0xFF404040)
#define LCD_COLOR_BLACK         			((uint32_t)0xFF000000)
#define LCD_COLOR_BROWN         			((uint32_t)0xFFA52A2A)
#define LCD_COLOR_ORANGE        			((uint32_t)0xFFFFA500)
#define LCD_COLOR_TRANSPARENT   			((uint32_t)0xFF000000)

/** 
  * @brief LCD default font 
  */ 
#define LCD_DEFAULT_FONT        			Font24     

/** 
  * @brief  LCD Reload Types  
  */
#define LCD_RELOAD_IMMEDIATE               	((uint32_t)LTDC_SRCR_IMR)
#define LCD_RELOAD_VERTICAL_BLANKING       	((uint32_t)LTDC_SRCR_VBR) 

/**
  * @brief LCD special pins
  */
/* Display enable pin */
#define LCD_DISP_PIN                    	GPIO_PIN_10
#define LCD_DISP_GPIO_PORT              	GPIOF
#define LCD_DISP_GPIO_CLK_ENABLE()      	__HAL_RCC_GPIOF_CLK_ENABLE()
#define LCD_DISP_GPIO_CLK_DISABLE()     	__HAL_RCC_GPIOF_CLK_DISABLE()

/* Backlight control pin */
#define LCD_BL_CTRL_PIN                  	GPIO_PIN_8
#define LCD_BL_CTRL_GPIO_PORT            	GPIOI
#define LCD_BL_CTRL_GPIO_CLK_ENABLE()    	__HAL_RCC_GPIOI_CLK_ENABLE()
#define LCD_BL_CTRL_GPIO_CLK_DISABLE()   	__HAL_RCC_GPIOI_CLK_DISABLE()

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t  BSP_LCD_Init(void);
uint8_t  BSP_LCD_DeInit(void);
uint32_t BSP_LCD_GetXSize(void);
uint32_t BSP_LCD_GetYSize(void);
void     BSP_LCD_SetXSize(uint32_t imageWidthPixels);
void     BSP_LCD_SetYSize(uint32_t imageHeightPixels);

void     BSP_LCD_LayerDefaultInit(uint16_t LayerIndex, uint32_t FrameBuffer);
void     BSP_LCD_LayerRgb565Init(uint16_t LayerIndex, uint32_t FB_Address);
void     BSP_LCD_SetTransparency(uint32_t LayerIndex, uint8_t Transparency);
void     BSP_LCD_SetTransparency_NoReload(uint32_t LayerIndex, uint8_t Transparency);
void     BSP_LCD_SetLayerAddress(uint32_t LayerIndex, uint32_t Address);
void     BSP_LCD_SetLayerAddress_NoReload(uint32_t LayerIndex, uint32_t Address);
void     BSP_LCD_SetColorKeying(uint32_t LayerIndex, uint32_t RGBValue);
void     BSP_LCD_SetColorKeying_NoReload(uint32_t LayerIndex, uint32_t RGBValue);
void     BSP_LCD_ResetColorKeying(uint32_t LayerIndex);
void     BSP_LCD_ResetColorKeying_NoReload(uint32_t LayerIndex);
void     BSP_LCD_SetLayerWindow(uint16_t LayerIndex, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_SetLayerWindow_NoReload(uint16_t LayerIndex, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_SelectLayer(uint32_t LayerIndex);
void     BSP_LCD_SetLayerVisible(uint32_t LayerIndex, FunctionalState State);
void     BSP_LCD_SetLayerVisible_NoReload(uint32_t LayerIndex, FunctionalState State);
void     BSP_LCD_Reload(uint32_t ReloadType);

void     BSP_LCD_SetTextColor(uint32_t Color);
uint32_t BSP_LCD_GetTextColor(void);
void     BSP_LCD_SetBackColor(uint32_t Color);
uint32_t BSP_LCD_GetBackColor(void);
void     BSP_LCD_SetFont(sFONT *fonts);
sFONT    *BSP_LCD_GetFont(void);

uint32_t BSP_LCD_ReadPixel(uint16_t Xpos, uint16_t Ypos);
void     BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t pixel);
void     BSP_LCD_Clear(uint32_t Color);
void     BSP_LCD_ClearStringLine(uint32_t Line);
void     BSP_LCD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr);
void     BSP_LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode);
void     BSP_LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);

void     BSP_LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void     BSP_LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     BSP_LCD_DrawPolygon(pPoint Points, uint16_t PointCount);
void     BSP_LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius);
void     BSP_LCD_DrawBitmap(uint32_t Xpos, uint32_t Ypos, uint8_t *pbmp);

void     BSP_LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     BSP_LCD_FillPolygon(pPoint Points, uint16_t PointCount);
void     BSP_LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius);

void     BSP_LCD_DisplayOff(void);
void     BSP_LCD_DisplayOn(void);

void     BSP_LCD_MspInit(LTDC_HandleTypeDef *hltdc, void *Params);
void     BSP_LCD_MspDeInit(LTDC_HandleTypeDef *hltdc, void *Params);
void     BSP_LCD_ClockConfig(LTDC_HandleTypeDef *hltdc, void *Params);

#ifdef __cplusplus
}
#endif

#endif /* __CORE429I_BASEBOARD_LCD_H */