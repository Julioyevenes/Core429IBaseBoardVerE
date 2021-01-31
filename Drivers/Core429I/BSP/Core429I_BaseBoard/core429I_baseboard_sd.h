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
#ifndef __CORE429I_BASEBOARD_SD_H
#define __CORE429I_BASEBOARD_SD_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "core429I_baseboard.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define BSP_SD_CardInfo 					HAL_SD_CardInfoTypeDef

#define MSD_OK                        		((uint8_t)0x00)
#define MSD_ERROR                     		((uint8_t)0x01)
#define MSD_ERROR_SD_NOT_PRESENT      		((uint8_t)0x02)

#define SD_TRANSFER_OK                		((uint8_t)0x00)
#define SD_TRANSFER_BUSY              		((uint8_t)0x01)

#define SD_PRESENT               			((uint8_t)0x01)
#define SD_NOT_PRESENT           			((uint8_t)0x00)

#define SD_TRANSFER_CLK_DIV					((uint8_t)0x02)

#define SD_DATATIMEOUT           			((uint32_t)100000000)

/* DMA definitions for SD DMA transfer */
#define __DMAx_TxRx_CLK_ENABLE            	__HAL_RCC_DMA2_CLK_ENABLE
#define SD_DMAx_Tx_CHANNEL                	DMA_CHANNEL_4
#define SD_DMAx_Rx_CHANNEL                	DMA_CHANNEL_4
#define SD_DMAx_Tx_STREAM                 	DMA2_Stream6
#define SD_DMAx_Rx_STREAM                 	DMA2_Stream3
#define SD_DMAx_Tx_IRQn                   	DMA2_Stream6_IRQn
#define SD_DMAx_Rx_IRQn                   	DMA2_Stream3_IRQn
#define BSP_SD_IRQHandler                 	SDIO_IRQHandler
#define BSP_SD_DMA_Tx_IRQHandler          	DMA2_Stream6_IRQHandler
#define BSP_SD_DMA_Rx_IRQHandler          	DMA2_Stream3_IRQHandler
#define SD_DetectIRQHandler()             	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3)

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t BSP_SD_Init(void);
uint8_t BSP_SD_DeInit(void);
uint8_t BSP_SD_ITConfig(void);
uint8_t BSP_SD_ReadBlocks(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks, uint32_t Timeout);
uint8_t BSP_SD_WriteBlocks(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks, uint32_t Timeout);
uint8_t BSP_SD_ReadBlocks_DMA(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks);
uint8_t BSP_SD_WriteBlocks_DMA(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks);
uint8_t BSP_SD_Erase(uint32_t StartAddr, uint32_t EndAddr);
uint8_t BSP_SD_GetCardState(void);
void    BSP_SD_GetCardInfo(HAL_SD_CardInfoTypeDef *CardInfo);
uint8_t BSP_SD_IsDetected(void);

void    BSP_SD_MspInit(SD_HandleTypeDef *hsd, void *Params);
void    BSP_SD_Detect_MspInit(SD_HandleTypeDef *hsd, void *Params);
void    BSP_SD_MspDeInit(SD_HandleTypeDef *hsd, void *Params);
void    BSP_SD_AbortCallback(void);
void    BSP_SD_WriteCpltCallback(void);
void    BSP_SD_ReadCpltCallback(void);

#ifdef __cplusplus
}
#endif

#endif /* __CORE429I_BASEBOARD_SD_H */
