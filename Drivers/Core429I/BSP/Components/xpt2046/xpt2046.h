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
#ifndef __XPT2046_H
#define __XPT2046_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "../Common/ts.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Chip IDs */   
#define XPT2046_ID				0x2046

/* Control Byte Mask */
#define XPT2046_START_BIT		0x80
#define XPT2046_ADD2_BIT		0x40
#define XPT2046_ADD1_BIT		0x20
#define XPT2046_ADD0_BIT		0x10
#define XPT2046_MODE_BIT		0x08
#define XPT2046_S/D_BIT			0x04
#define XPT2046_PD1_BIT			0x02
#define XPT2046_PD0_BIT			0x01

/* Input Configuration Single-Ended Mask */
#define XPT2046_SER_TEMP0		0x04
#define XPT2046_SER_Y			0x14
#define XPT2046_SER_BAT			0x24
#define XPT2046_SER_Z1			0x34
#define XPT2046_SER_Z2			0x44
#define XPT2046_SER_X			0x54
#define XPT2046_SER_AUX			0x64
#define XPT2046_SER_TEMP1		0x74

/* Input Configuration Differential Mask */
#define XPT2046_DFR_Y			0x10
#define XPT2046_DFR_Z1			0x30
#define XPT2046_DFR_Z2			0x40
#define XPT2046_DFR_X			0x50

/* Power-Down Configuration Mask */
#define XPT2046_PD0				0x00	/* Power-Down Between Conversions */
#define XPT2046_PD1				0x01	/* Reference is off and ADC is on */
#define XPT2046_PD2				0x02	/* Reference is on and ADC is off */
#define XPT2046_PD3				0x03	/* Device is always powered       */

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void     xpt2046_Init(uint16_t DeviceAddr);
uint16_t xpt2046_ReadID(uint16_t DeviceAddr);
void     xpt2046_Reset(uint16_t DeviceAddr);

void     xpt2046_TS_Start(uint16_t DeviceAddr);
uint8_t  xpt2046_TS_DetectTouch(uint16_t DeviceAddr);
void     xpt2046_TS_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y);
void     xpt2046_TS_EnableIT(uint16_t DeviceAddr);
void     xpt2046_TS_ClearIT (uint16_t DeviceAddr);
uint8_t  xpt2046_TS_ITStatus (uint16_t DeviceAddr);
void     xpt2046_TS_DisableIT(uint16_t DeviceAddr);

/* TS IO functions */
void 		TS_IO_Init(void);
uint16_t 	TS_IO_WriteRead(uint8_t Addr);
uint8_t 	TS_IO_ITRead(void);
void 		TS_IO_Delay(uint32_t Delay);

/* Touch screen driver structure */
extern TS_DrvTypeDef xpt2046_ts_drv;

#ifdef __cplusplus
}
#endif

#endif /* __XPT2046_H */
