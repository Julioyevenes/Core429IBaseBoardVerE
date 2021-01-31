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

/* Includes ------------------------------------------------------------------*/
#include "xpt2046.h"

/* Private types ------------------------------------------------------------*/
/* Private constants --------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Touch screen driver structure initialization */  
TS_DrvTypeDef xpt2046_ts_drv = 
{
  xpt2046_Init,
  xpt2046_ReadID,
  xpt2046_Reset,
  xpt2046_TS_Start,
  xpt2046_TS_DetectTouch,
  xpt2046_TS_GetXY,
  xpt2046_TS_EnableIT,
  xpt2046_TS_ClearIT,
  xpt2046_TS_ITStatus,
  xpt2046_TS_DisableIT,
};

/* Private function prototypes ----------------------------------------------*/

/**
  * @brief  Initialize the xpt2046 and configure the needed hardware resources
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */
void xpt2046_Init(uint16_t DeviceAddr)
{
	/* Initialize IO layer */
	TS_IO_Init();
}

/**
  * @brief  Read the xpt2046 IO Expander device ID.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval The Device ID (two bytes).
  */
uint16_t xpt2046_ReadID(uint16_t DeviceAddr)
{
	return 0x00;
}

/**
  * @brief  Reset the xpt2046 by Software.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void xpt2046_Reset(uint16_t DeviceAddr)
{
}

/**
  * @brief  Configures the touch Screen Controller (Single point detection)
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None.
  */
void xpt2046_TS_Start(uint16_t DeviceAddr)
{
}

/**
  * @brief  Return if there is touch detected or not.
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval Touch detected state.
  */
uint8_t xpt2046_TS_DetectTouch(uint16_t DeviceAddr)
{
	return !TS_IO_ITRead();
}

/**
  * @brief  Get the touch screen X and Y positions values
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  X: Pointer to X position value
  * @param  Y: Pointer to Y position value   
  * @retval None.
  */
void xpt2046_TS_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y)
{
	/* Read X Channel in Differential Reference Mode */
	*X = TS_IO_WriteRead(XPT2046_START_BIT | XPT2046_DFR_Y | XPT2046_PD0);
	
	/* Wait for a delay */
	TS_IO_Delay(1);
	
	/* Read Y Channel in Differential Reference Mode */
	*Y = TS_IO_WriteRead(XPT2046_START_BIT | XPT2046_DFR_X | XPT2046_PD0);
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void xpt2046_TS_EnableIT(uint16_t DeviceAddr)
{
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void xpt2046_TS_ClearIT(uint16_t DeviceAddr)
{
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.    
  * @retval TS interrupts status
  */
uint8_t xpt2046_TS_ITStatus(uint16_t DeviceAddr)
{
	return 0x00;
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.    
  * @retval None
  */
void xpt2046_TS_DisableIT(uint16_t DeviceAddr)
{
}
