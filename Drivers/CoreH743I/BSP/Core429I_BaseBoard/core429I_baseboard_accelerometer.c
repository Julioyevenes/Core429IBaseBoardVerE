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
#include "core429I_baseboard_accelerometer.h"

/* Private types ------------------------------------------------------------*/
/* Private constants --------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
static ACCELERO_DrvTypeDef *AccelerometerDrv;

/* Private function prototypes ----------------------------------------------*/

/**
  * @brief  Set Accelerometer Initialization.
  * @retval ACCELERO_OK if no problem during initialization
  */
uint8_t BSP_ACCELERO_Init(void)
{
  uint8_t ret = ACCELERO_ERROR;
  uint16_t ctrl = 0x0000;
  ACCELERO_InitTypeDef         LSM303DLHC_InitStructure;
  ACCELERO_FilterConfigTypeDef LSM303DLHC_FilterStructure = {0,0,0,0};
  
  if(Lsm303dlhcDrv.ReadID() == I_AM_LMS303DLHC)
  {
    /* Initialize the Accelerometer driver structure */
    AccelerometerDrv = &Lsm303dlhcDrv;

    /* MEMS configuration ----------------------------------------------------*/
    /* Fill the Accelerometer structure */
    LSM303DLHC_InitStructure.Power_Mode = LSM303DLHC_NORMAL_MODE;
    LSM303DLHC_InitStructure.AccOutput_DataRate = LSM303DLHC_ODR_50_HZ;
    LSM303DLHC_InitStructure.Axes_Enable = LSM303DLHC_AXES_ENABLE;
    LSM303DLHC_InitStructure.AccFull_Scale = LSM303DLHC_FULLSCALE_2G;
    LSM303DLHC_InitStructure.BlockData_Update = LSM303DLHC_BlockUpdate_Continous;
    LSM303DLHC_InitStructure.Endianness = LSM303DLHC_BLE_LSB;
    LSM303DLHC_InitStructure.High_Resolution = LSM303DLHC_HR_ENABLE;
    
    /* Configure MEMS: data rate, power mode, full scale and axes */
    ctrl |= (LSM303DLHC_InitStructure.Power_Mode | LSM303DLHC_InitStructure.AccOutput_DataRate | \
                       LSM303DLHC_InitStructure.Axes_Enable);
    
    ctrl |= ((LSM303DLHC_InitStructure.BlockData_Update | LSM303DLHC_InitStructure.Endianness | \
                      LSM303DLHC_InitStructure.AccFull_Scale | LSM303DLHC_InitStructure.High_Resolution) << 8);
    
    /* Configure the Accelerometer main parameters */
    AccelerometerDrv->Init(ctrl);
    
    /* Fill the Accelerometer LPF structure */
    LSM303DLHC_FilterStructure.HighPassFilter_Mode_Selection =LSM303DLHC_HPM_NORMAL_MODE;
    LSM303DLHC_FilterStructure.HighPassFilter_CutOff_Frequency = LSM303DLHC_HPFCF_16;
    LSM303DLHC_FilterStructure.HighPassFilter_AOI1 = LSM303DLHC_HPF_AOI1_DISABLE;
    LSM303DLHC_FilterStructure.HighPassFilter_AOI2 = LSM303DLHC_HPF_AOI2_DISABLE;
    
    /* Configure MEMS: mode, cutoff frquency, Filter status, Click, AOI1 and AOI2 */
    ctrl = (uint8_t) (LSM303DLHC_FilterStructure.HighPassFilter_Mode_Selection |\
                      LSM303DLHC_FilterStructure.HighPassFilter_CutOff_Frequency|\
                      LSM303DLHC_FilterStructure.HighPassFilter_AOI1|\
                      LSM303DLHC_FilterStructure.HighPassFilter_AOI2);

    /* Configure the Accelerometer LPF main parameters */
    AccelerometerDrv->FilterConfig(ctrl);

    ret = ACCELERO_OK;
  }
  else
  {
    ret = ACCELERO_ERROR;
  }

  return ret;
}

/**
  * @brief  Reboot memory content of Accelerometer.
  */
void BSP_ACCELERO_Reset(void)
{
  if(AccelerometerDrv->Reset != NULL)
  {
    AccelerometerDrv->Reset();
  }  
}

/**
  * @brief  Configure Accelerometer click IT. 
  */
void BSP_ACCELERO_Click_ITConfig(void)
{
  if(AccelerometerDrv->ConfigIT!= NULL)
  {
    AccelerometerDrv->ConfigIT();
  }
}

/**
  * @brief  Get XYZ axes acceleration.
  * @param  pDataXYZ: Pointer to 3 angular acceleration axes.  
  *                   pDataXYZ[0] = X axis, pDataXYZ[1] = Y axis, pDataXYZ[2] = Z axis
  */
void BSP_ACCELERO_GetXYZ(int16_t *pDataXYZ)
{
  int16_t SwitchXY = 0;
  
  if(AccelerometerDrv->GetXYZ!= NULL)
  {
    AccelerometerDrv->GetXYZ(pDataXYZ);
    
    /* Switch X and Y Axes in case of LSM303DLHC MEMS */
    if(AccelerometerDrv == &Lsm303dlhcDrv)
    { 
      SwitchXY  = pDataXYZ[0];
      pDataXYZ[0] = pDataXYZ[1];
      
      /* Invert Y Axis to be conpliant with LIS3DSH */
      pDataXYZ[1] = -SwitchXY;
    } 
  }
}