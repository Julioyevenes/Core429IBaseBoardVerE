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
#ifndef __CORE429I_BASEBOARD_ACCELEROMETER_H
#define __CORE429I_BASEBOARD_ACCELEROMETER_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "core429I_baseboard.h"

/* Include Accelerometer component driver */
#include "../Components/lsm303dlhc/lsm303dlhc.h"

/* Exported types ------------------------------------------------------------*/
typedef enum 
{
  ACCELERO_OK = 0,
  ACCELERO_ERROR = 1,
  ACCELERO_TIMEOUT = 2
}ACCELERO_StatusTypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t BSP_ACCELERO_Init(void);
void    BSP_ACCELERO_Reset(void);
void    BSP_ACCELERO_Click_ITConfig(void);
void    BSP_ACCELERO_GetXYZ(int16_t *pDataXYZ);

#ifdef __cplusplus
}
#endif

#endif /* __CORE429I_BASEBOARD_ACCELEROMETER_H */