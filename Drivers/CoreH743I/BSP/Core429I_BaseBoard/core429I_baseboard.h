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
#ifndef __CORE429I_BASEBOARD_H
#define __CORE429I_BASEBOARD_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Exported types ------------------------------------------------------------*/
typedef enum 
{  
  BTN0 = 0,
  BTN1 = 1,
  BTN2 = 2
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

/* Exported constants --------------------------------------------------------*/
/**
 * @brief User push-buttons
 */
#define BTNn										3

#define USER_BTN0_PIN                				GPIO_PIN_0
#define USER_BTN0_GPIO_PORT          				GPIOA
#define USER_BTN0_GPIO_CLK_ENABLE()  				__HAL_RCC_GPIOA_CLK_ENABLE()
#define USER_BTN0_GPIO_CLK_DISABLE() 				__HAL_RCC_GPIOA_CLK_DISABLE()
#define USER_BTN0_EXTI_IRQn          				EXTI0_IRQn

#define USER_BTN1_PIN                				GPIO_PIN_4
#define USER_BTN1_GPIO_PORT          				GPIOA
#define USER_BTN1_GPIO_CLK_ENABLE()  				__HAL_RCC_GPIOA_CLK_ENABLE()
#define USER_BTN1_GPIO_CLK_DISABLE() 				__HAL_RCC_GPIOA_CLK_DISABLE()
#define USER_BTN1_EXTI_IRQn          				EXTI4_IRQn

#define USER_BTN2_PIN                				GPIO_PIN_5
#define USER_BTN2_GPIO_PORT          				GPIOA
#define USER_BTN2_GPIO_CLK_ENABLE()  				__HAL_RCC_GPIOA_CLK_ENABLE()
#define USER_BTN2_GPIO_CLK_DISABLE() 				__HAL_RCC_GPIOA_CLK_DISABLE()
#define USER_BTN2_EXTI_IRQn          				EXTI9_5_IRQn

/**
 * @brief SPI5
 */
#define DISCOVERY_SPIx                      		SPI5
#define DISCOVERY_SPIx_CLK_ENABLE()         		__HAL_RCC_SPI5_CLK_ENABLE()
#define DISCOVERY_SPIx_GPIO_PORT            		GPIOF
#define DISCOVERY_SPIx_AF                   		GPIO_AF5_SPI1
#define DISCOVERY_SPIx_GPIO_CLK_ENABLE()    		__HAL_RCC_GPIOF_CLK_ENABLE()
#define DISCOVERY_SPIx_GPIO_CLK_DISABLE()   		__HAL_RCC_GPIOF_CLK_DISABLE()
#define DISCOVERY_SPIx_SCK_PIN              		GPIO_PIN_7
#define DISCOVERY_SPIx_MISO_PIN             		GPIO_PIN_8
#define DISCOVERY_SPIx_MOSI_PIN             		GPIO_PIN_9

#define SPIx_TIMEOUT_MAX                    		0x1000 
 
/**
 * @brief I2C1
 */
#define BSP_I2C_TIMING 								0x10B0DCFB

#define DISCOVERY_I2Cx                            	I2C1
#define DISCOVERY_I2Cx_CLK_ENABLE()               	__HAL_RCC_I2C1_CLK_ENABLE()
#define DISCOVERY_I2Cx_SCL_SDA_GPIO_CLK_ENABLE()  	__HAL_RCC_GPIOB_CLK_ENABLE()
#define DISCOVERY_I2Cx_SCL_SDA_AF                 	GPIO_AF4_I2C1
#define DISCOVERY_I2Cx_SCL_SDA_GPIO_PORT          	GPIOB
#define DISCOVERY_I2Cx_SCL_PIN                    	GPIO_PIN_6
#define DISCOVERY_I2Cx_SDA_PIN                    	GPIO_PIN_7

#define DISCOVERY_I2Cx_FORCE_RESET()              	__HAL_RCC_I2C1_FORCE_RESET()
#define DISCOVERY_I2Cx_RELEASE_RESET()            	__HAL_RCC_I2C1_RELEASE_RESET()

#define DISCOVERY_I2Cx_EV_IRQn                    	I2C1_EV_IRQn
#define DISCOVERY_I2Cx_ER_IRQn                    	I2C1_ER_IRQn

#define I2Cx_TIMEOUT_MAX    						0x1000

/**
  * @brief AUDIO
  */
#define AUDIO_I2C_ADDRESS                     		0x94

#define AUDIO_RESET_GPIO_CLK_ENABLE()         		__HAL_RCC_GPIOC_CLK_ENABLE()
#define AUDIO_RESET_PIN                       		GPIO_PIN_6
#define AUDIO_RESET_GPIO                      		GPIOC

/**
  * @brief SD-detect signal
  */
#define SD_DETECT_PIN                        		((uint32_t)GPIO_PIN_3)
#define SD_DETECT_GPIO_PORT                  		((GPIO_TypeDef*)GPIOD)
#define SD_DETECT_GPIO_CLK_ENABLE()          		__HAL_RCC_GPIOD_CLK_ENABLE()
#define SD_DETECT_GPIO_CLK_DISABLE()         		__HAL_RCC_GPIOD_CLK_DISABLE()
#define SD_DETECT_EXTI_IRQn                  		EXTI3_IRQn

/**
  * @brief TS
  */
#define TS_ADDRESS                   				((uint16_t)0x00)
  
/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                        			((uint8_t)0x00)

/* Definition for TIMx clock resources */
#define TIMx                           				TIM3
#define TIMx_CLK_ENABLE                				__HAL_RCC_TIM3_CLK_ENABLE

/* Definition for TIMx's NVIC */
#define TIMx_IRQn                      				TIM3_IRQn
#define TIMx_IRQHandler                				TIM3_IRQHandler

#define TS_USDELAY									1000000U

/**
  * @brief TS Interface pins
  */
#define TS_CS_PIN                        			GPIO_PIN_6
#define TS_CS_GPIO_PORT                  			GPIOF
#define TS_CS_GPIO_CLK_ENABLE()          			__HAL_RCC_GPIOF_CLK_ENABLE()
#define TS_CS_GPIO_CLK_DISABLE()         			__HAL_RCC_GPIOF_CLK_DISABLE()

#define TS_INT_PIN                      			GPIO_PIN_3
#define TS_INT_GPIO_PORT                 			GPIOG
#define TS_INT_GPIO_CLK_ENABLE()         			__HAL_RCC_GPIOG_CLK_ENABLE()
#define TS_INT_GPIO_CLK_DISABLE()        			__HAL_RCC_GPIOG_CLK_DISABLE()

/**
  * @brief OTG_FS1 OVER_CURRENT and POWER_SWITCH Pins definition
  */
#define OTG_FS1_POWER_SWITCH_PIN                  	GPIO_PIN_12
#define OTG_FS1_POWER_SWITCH_PORT                 	GPIOD
#define OTG_FS1_POWER_SWITCH_PORT_CLK_ENABLE()     	__HAL_RCC_GPIOD_CLK_ENABLE() 
  
#define OTG_FS1_OVER_CURRENT_PIN                  	GPIO_PIN_13
#define OTG_FS1_OVER_CURRENT_PORT                 	GPIOD
#define OTG_FS1_OVER_CURRENT_PORT_CLK_ENABLE()     	__HAL_RCC_GPIOD_CLK_ENABLE()

/**
  * @brief OTG_FS2 OVER_CURRENT and POWER_SWITCH Pins definition
  */
#define OTG_FS2_POWER_SWITCH_PIN                  	GPIO_PIN_0
#define OTG_FS2_POWER_SWITCH_PORT                 	GPIOB
#define OTG_FS2_POWER_SWITCH_PORT_CLK_ENABLE()     	__HAL_RCC_GPIOB_CLK_ENABLE() 
  
#define OTG_FS2_OVER_CURRENT_PIN                  	GPIO_PIN_1
#define OTG_FS2_OVER_CURRENT_PORT                 	GPIOB
#define OTG_FS2_OVER_CURRENT_PORT_CLK_ENABLE()     	__HAL_RCC_GPIOB_CLK_ENABLE() 

/**
  * @brief ACCELERO Interrupt pins
  */
#define ACCELERO_INT_GPIO_PORT                  	GPIOE
#define ACCELERO_INT_GPIO_CLK_ENABLE()          	__HAL_RCC_GPIOE_CLK_ENABLE()
#define ACCELERO_INT_GPIO_CLK_DISABLE()         	__HAL_RCC_GPIOE_CLK_DISABLE()

#define ACCELERO_INT1_PIN                       	GPIO_PIN_2
#define ACCELERO_INT1_EXTI_IRQn                 	EXTI2_IRQn
 
#define ACCELERO_INT2_PIN                       	GPIO_PIN_3
#define ACCELERO_INT2_EXTI_IRQn                 	EXTI3_IRQn

/* Exported macro ------------------------------------------------------------*/
/**
 * @brief User push-buttons
 */
#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__) 			do{	if((__INDEX__) == 0) USER_BTN0_GPIO_CLK_ENABLE(); else \
														if((__INDEX__) == 1) USER_BTN1_GPIO_CLK_ENABLE(); else \
														if((__INDEX__) == 2) USER_BTN2_GPIO_CLK_ENABLE(); \
														}while(0)

#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__) 		do{	if((__INDEX__) == 0) USER_BTN0_GPIO_CLK_DISABLE(); else \
														if((__INDEX__) == 1) USER_BTN1_GPIO_CLK_DISABLE(); else \
														if((__INDEX__) == 2) USER_BTN2_GPIO_CLK_DISABLE(); \
														}while(0)

/**
  * @brief TS Interface pins
  */															
#define TS_CS_LOW()       							HAL_GPIO_WritePin(TS_CS_GPIO_PORT, TS_CS_PIN, GPIO_PIN_RESET)
#define TS_CS_HIGH()      							HAL_GPIO_WritePin(TS_CS_GPIO_PORT, TS_CS_PIN, GPIO_PIN_SET)

#define TS_INT_READ()								HAL_GPIO_ReadPin(TS_INT_GPIO_PORT, TS_INT_PIN)
	
/* Exported variables --------------------------------------------------------*/
extern SPI_HandleTypeDef    SpiHandle;
extern I2C_HandleTypeDef    I2cHandle;

/* Exported functions ------------------------------------------------------- */
void     BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Mode);
uint32_t BSP_PB_GetState(Button_TypeDef Button);

#ifdef __cplusplus
}
#endif

#endif /* __CORE429I_BASEBOARD_H */
