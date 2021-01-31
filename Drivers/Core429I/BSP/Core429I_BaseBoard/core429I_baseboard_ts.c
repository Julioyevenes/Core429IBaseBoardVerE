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
#include "core429I_baseboard_ts.h"

/* Private types ------------------------------------------------------------*/
/* Private constants --------------------------------------------------------*/
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
static TS_CoefTypeDef TSCoef;

/* Private function prototypes ----------------------------------------------*/
static void BSP_TS_GetCoef(TS_CoefTypeDef *CoefPtr);

/**
  * @brief  Initializes and configures the touch screen functionalities and 
  *         configures all necessary hardware resources (GPIOs, clocks..).
  * @param  XSize: The maximum X size of the TS area on LCD
  * @param  YSize: The maximum Y size of the TS area on LCD  
  * @retval TS_OK: if all initializations are OK. Other value if error.
  */
uint8_t BSP_TS_Init(void)
{
  /* Initialize x and y positions boundaries */
  BSP_TS_GetCoef(&TSCoef);

  /* Initialize the TS driver structure */
  TsDrv = &xpt2046_ts_drv;

  /* Initialize the LL TS Driver */
  TsDrv->Init(TS_ADDRESS);

  return TS_OK;
}

/**
  * @brief  Configures and enables the touch screen interrupts.
  * @retval TS_OK: if ITconfig is OK. Other value if error.
  */
uint8_t BSP_TS_ITConfig(void)
{
  /* Enable the TS ITs */
  TsDrv->EnableIT(TS_ADDRESS);

  return TS_OK;
}

/**
  * @brief  Gets the TS IT status.
  * @retval Interrupt status.
  */  
uint8_t BSP_TS_ITGetStatus(void)
{
  /* Return the TS IT status */
  return (TsDrv->GetITStatus(TS_ADDRESS));
}

/**
  * @brief  Returns status and positions of the touch screen.
  * @param  TsState: Pointer to touch screen current state structure
  */
void BSP_TS_GetState(TS_StateTypeDef* TsState)
{
	uint8_t 			i, k, sample = 0;
	uint16_t 			x, y, _x, _y;

	int32_t				m;

	int32_t 			buffer[TS_NBR_SAMPLES][2] = {{0},{0}};
	int32_t				temp[TS_NBR_SAMPLES] = {0};
	int32_t				delta[TS_NBR_SAMPLES] = {0};
	int32_t				value[TS_NBR_SAMPLES] = {0};

	do
	{
		TsState->TouchDetected = TsDrv->DetectTouch(TS_ADDRESS);
		TsDrv->GetXY(TS_ADDRESS, &x, &y);
		buffer[sample][0] = x;
		buffer[sample][1] = y;
		sample++;
	}
	while( (TsState->TouchDetected) && (sample < TS_NBR_SAMPLES) );

	if(sample == TS_NBR_SAMPLES)
	{
		/* Average X */
		for(i = 0; i < TS_NBR_SAMPLES - 1; i++)
		{
			temp[i] = (buffer[i][0] + buffer[i + 1][0]) / 2;
		}
		temp[TS_NBR_SAMPLES - 1] = (buffer[TS_NBR_SAMPLES - 1][0] + buffer[0][0]) / 2;

		/* Shift X */
		for(i = 0; i < TS_NBR_SAMPLES - 1; i++)
		{
			delta[i] = temp[i] - temp[i + 1];
			value[i] = (temp[i] + temp[i + 1]) / 2;
		}
		delta[TS_NBR_SAMPLES - 1] = temp[TS_NBR_SAMPLES - 1] - temp[0];
		value[TS_NBR_SAMPLES - 1] = (temp[TS_NBR_SAMPLES - 1] + temp[0]) / 2;

		/* Check X Tolerances */
		m = 0x7FFFFFFF;
		sample = 0;

		for(i = 0; i < TS_NBR_SAMPLES; i++)
		{
			delta[i] = delta[i] > 0 ? delta[i] : (-delta[i]);

			if(delta[i] > TS_THRESHOLD) sample++;
			if(delta[i] < m) {m = delta[i]; k = i;}
		}

		if( sample == TS_NBR_SAMPLES )
		{
			TsState->X = -1;
			TsState->Y = -1;

			return;
		}

		/* Apply X Value */
		_x = value[k];

		/* Average Y */
		for(i = 0; i < TS_NBR_SAMPLES - 1; i++)
		{
			temp[i] = (buffer[i][1] + buffer[i + 1][1]) / 2;
		}
		temp[TS_NBR_SAMPLES - 1] = (buffer[TS_NBR_SAMPLES - 1][1] + buffer[0][1]) / 2;

		/* Shift Y */
		for(i = 0; i < TS_NBR_SAMPLES - 1; i++)
		{
			delta[i] = temp[i] - temp[i + 1];
			value[i] = (temp[i] + temp[i + 1]) / 2;
		}
		delta[TS_NBR_SAMPLES - 1] = temp[TS_NBR_SAMPLES - 1] - temp[0];
		value[TS_NBR_SAMPLES - 1] = (temp[TS_NBR_SAMPLES - 1] + temp[0]) / 2;

		/* Check Y Tolerances */
		m = 0x7FFFFFFF;
		sample = 0;

		for(i = 0; i < TS_NBR_SAMPLES; i++)
		{
			delta[i] = delta[i] > 0 ? delta[i] : (-delta[i]);

			if(delta[i] > TS_THRESHOLD) sample++;
			if(delta[i] < m) {m = delta[i]; k = i;}
		}

		if( sample == TS_NBR_SAMPLES )
		{
			TsState->X = -1;
			TsState->Y = -1;

			return;
		}

		/* Apply Y Value */
		_y = value[k];

		/* XD = AX + BY + C */
		TsState->X = ( (TSCoef.An * _x) + (TSCoef.Bn * _y) + TSCoef.Cn ) / TSCoef.Divider ;
		/* YD = DX + EY + F */
		TsState->Y = ( (TSCoef.Dn * _x) + (TSCoef.En * _y) + TSCoef.Fn ) / TSCoef.Divider ;

		return;
	}

	TsState->X = -1;
	TsState->Y = -1;
}

/**
  * @brief  Clears all touch screen interrupts.
  */  
void BSP_TS_ITClear(void)
{
  /* Clear TS IT pending bits */
  TsDrv->ClearIT(TS_ADDRESS); 
}

/**
  * @brief  Get the calibration constants obtained from lcd touch module.
  * @param  CoefPtr: pointer to the constants structure.
  * @retval None.
  */
static void BSP_TS_GetCoef(TS_CoefTypeDef *CoefPtr)
{
	uint8_t i;
	uint32_t Addr, Data;

	Addr = ADDR_FLASH_SECTOR_11;

	for (i = 0; i < 7; i++) {
		Data = *(__IO uint32_t*)Addr;

		switch (i) {
		case 0:
			CoefPtr->An = Data;
			break;
		case 1:
			CoefPtr->Bn = Data;
			break;
		case 2:
			CoefPtr->Cn = Data;
			break;
		case 3:
			CoefPtr->Dn = Data;
			break;
		case 4:
			CoefPtr->En = Data;
			break;
		case 5:
			CoefPtr->Fn = Data;
			break;
		case 6:
			CoefPtr->Divider = Data;
			break;
		}

		Addr += 4;
	}
}
