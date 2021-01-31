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
#ifndef __CORE429I_BASEBOARD_TS_H
#define __CORE429I_BASEBOARD_TS_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "core429I_baseboard.h"
/* Include TouchScreen component driver */
#include "../Components/xpt2046/xpt2046.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint16_t TouchDetected;
  uint16_t X;
  uint16_t Y;
  uint16_t Z;
}TS_StateTypeDef;

typedef enum 
{
  TS_OK       = 0x00,
  TS_ERROR    = 0x01,
  TS_TIMEOUT  = 0x02
}TS_StatusTypeDef;

typedef struct
{						
  int32_t An;
  int32_t Bn;
  int32_t Cn;
  int32_t Dn;
  int32_t En;
  int32_t Fn;
  int32_t Divider;
}TS_CoefTypeDef;

/* Exported constants --------------------------------------------------------*/
#define TS_NBR_SAMPLES		20
#define TS_THRESHOLD 		100

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
TS_DrvTypeDef     			*TsDrv;
/* Exported functions ------------------------------------------------------- */
uint8_t BSP_TS_Init(void);
void    BSP_TS_GetState(TS_StateTypeDef *TsState);
uint8_t BSP_TS_ITConfig(void);
uint8_t BSP_TS_ITGetStatus(void);
void    BSP_TS_ITClear(void);

#ifdef __cplusplus
}
#endif

#endif /* __CORE429I_BASEBOARD_TS_H */
