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
#ifndef __CORE429I_BASEBOARD_AUDIO_H
#define __CORE429I_BASEBOARD_AUDIO_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "../Components/cs43l22/cs43l22.h"

#include "core429I_baseboard.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
  * @brief  AUDIO
  */
/* I2S peripheral configuration defines */
#define I2S3                            SPI3
#define I2S3_CLK_ENABLE()               __HAL_RCC_SPI3_CLK_ENABLE()
#define I2S3_CLK_DISABLE()              __HAL_RCC_SPI3_CLK_DISABLE()
#define I2S3_SCK_WS_AF               	GPIO_AF6_SPI3
#define I2S3_SD_AF               		GPIO_AF5_SPI3
#define I2S3_SCK_CLK_ENABLE()        	__HAL_RCC_GPIOB_CLK_ENABLE()
#define I2S3_SD_CLK_ENABLE()        	__HAL_RCC_GPIOD_CLK_ENABLE()
#define I2S3_MCK_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define I2S3_WS_CLK_ENABLE()            __HAL_RCC_GPIOA_CLK_ENABLE()
#define I2S3_WS_PIN                     GPIO_PIN_15
#define I2S3_SCK_PIN                    GPIO_PIN_3
#define I2S3_SD_PIN                     GPIO_PIN_6
#define I2S3_MCK_PIN                    GPIO_PIN_7
#define I2S3_SCK_GPIO_PORT           	GPIOB
#define I2S3_SD_GPIO_PORT           	GPIOD
#define I2S3_WS_GPIO_PORT               GPIOA
#define I2S3_MCK_GPIO_PORT              GPIOC

/* I2S DMA Stream definitions */
#define I2S3_DMAx_CLK_ENABLE()          __HAL_RCC_DMA1_CLK_ENABLE()
#define I2S3_DMAx_CLK_DISABLE()         __HAL_RCC_DMA1_CLK_DISABLE()
#define I2S3_DMAx_STREAM                DMA1_Stream7
#define I2S3_DMAx_CHANNEL               DMA_CHANNEL_0
#define I2S3_DMAx_IRQ                   DMA1_Stream7_IRQn
#define I2S3_DMAx_PERIPH_DATA_SIZE      DMA_PDATAALIGN_HALFWORD
#define I2S3_DMAx_MEM_DATA_SIZE         DMA_MDATAALIGN_HALFWORD
#define DMA_MAX_SZE                     0xFFFF

#define I2S3_IRQHandler                 DMA1_Stream7_IRQHandler

/* Select the interrupt preemption priority and subpriority for the DMA interrupt */
#define AUDIO_OUT_IRQ_PREPRIO           0x0E   /* Select the preemption priority level(0 is the highest) */

#define AUDIODATA_SIZE                  2   /* 16-bits audio data size */

/* Audio status definition */     
#define AUDIO_OK                        0
#define AUDIO_ERROR                     1
#define AUDIO_TIMEOUT                   2

/* Exported macro ------------------------------------------------------------*/
#define DMA_MAX(_X_)                	(((_X_) <= DMA_MAX_SZE)? (_X_):DMA_MAX_SZE)

/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t BSP_AUDIO_OUT_Init(uint16_t OutputDevice, uint8_t Volume, uint32_t AudioFreq);
uint8_t BSP_AUDIO_OUT_Play(uint16_t* pBuffer, uint32_t Size);
void    BSP_AUDIO_OUT_ChangeBuffer(uint16_t *pData, uint16_t Size);
uint8_t BSP_AUDIO_OUT_Pause(void);
uint8_t BSP_AUDIO_OUT_Resume(void);
uint8_t BSP_AUDIO_OUT_Stop(uint32_t Option);
uint8_t BSP_AUDIO_OUT_SetVolume(uint8_t Volume);
void    BSP_AUDIO_OUT_SetFrequency(uint32_t AudioFreq);
uint8_t BSP_AUDIO_OUT_SetMute(uint32_t Cmd);
uint8_t BSP_AUDIO_OUT_SetOutputMode(uint8_t Output);

void    BSP_AUDIO_OUT_TransferComplete_CallBack(void);
void    BSP_AUDIO_OUT_HalfTransfer_CallBack(void);
void    BSP_AUDIO_OUT_Error_CallBack(void);

void  	BSP_AUDIO_OUT_ClockConfig(I2S_HandleTypeDef *hi2s, uint32_t AudioFreq, void *Params);
void  	BSP_AUDIO_OUT_MspInit(I2S_HandleTypeDef *hi2s, void *Params);
void  	BSP_AUDIO_OUT_MspDeInit(I2S_HandleTypeDef *hi2s, void *Params);

#ifdef __cplusplus
}
#endif

#endif /* __CORE429I_BASEBOARD_AUDIO_H */