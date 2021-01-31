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

/* Includes -----------------------------------------------------------------*/
#include "core429I_baseboard.h"

/* Private types ------------------------------------------------------------*/
/* Private constants --------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
GPIO_TypeDef* BUTTON_PORT[BTNn] = {	USER_BTN0_GPIO_PORT,
									USER_BTN1_GPIO_PORT,
									USER_BTN2_GPIO_PORT}; 
const uint16_t BUTTON_PIN[BTNn] = {	USER_BTN0_PIN,
									USER_BTN1_PIN,
									USER_BTN2_PIN}; 
const uint8_t BUTTON_IRQn[BTNn] = {	USER_BTN0_EXTI_IRQn,
									USER_BTN1_EXTI_IRQn,
									USER_BTN2_EXTI_IRQn};
									
uint32_t I2cxTimeout = I2Cx_TIMEOUT_MAX;    /*<! Value of Timeout when I2C communication fails */ 
uint32_t SpixTimeout = SPIx_TIMEOUT_MAX;    /*<! Value of Timeout when SPI communication fails */

SPI_HandleTypeDef    	SpiHandle;
I2C_HandleTypeDef    	I2cHandle;
TIM_HandleTypeDef  		htim;

__IO uint32_t 			TimingDelay = 0;

/* Private function prototypes ----------------------------------------------*/
static void 	TIMx_Init(uint32_t nPeriod);

static void     I2Cx_Init(void);
static void     I2Cx_WriteData(uint8_t Addr, uint8_t Reg, uint8_t Value);
static uint8_t  I2Cx_ReadData(uint8_t Addr, uint8_t Reg);
static void     I2Cx_Error(uint8_t Addr);
static void     I2Cx_MspInit(void);

static void     SPIx_Init(void);
static void 	SPIx_WriteData(uint8_t Byte);
static uint8_t 	SPIx_ReadData(void);
static void     SPIx_Error(void);
static void     SPIx_MspInit(void);

void            AUDIO_IO_Init(void);
void            AUDIO_IO_DeInit(void);
void            AUDIO_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t         AUDIO_IO_Read(uint8_t Addr, uint8_t Reg);

void            TS_IO_Init(void);
uint16_t 		TS_IO_WriteRead(uint8_t Addr);
uint8_t 		TS_IO_ITRead(void);
void 			TS_IO_Delay(uint32_t Delay);

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter should be: BUTTON_KEY
  * @param  Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                            generation capability  
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Mode)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);
  
  if (Mode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
  }
  
  if (Mode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
    
    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter should be: BUTTON_KEY  
  * @retval The Button GPIO pin value.
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void TIMx_IRQHandler(void)
{
  if(__HAL_TIM_GET_FLAG(&htim, TIM_FLAG_UPDATE) != RESET)
  {
	if(__HAL_TIM_GET_IT_SOURCE(&htim, TIM_IT_UPDATE) !=RESET)
	{
	  __HAL_TIM_CLEAR_IT(&htim, TIM_IT_UPDATE);

	  if (TimingDelay != 0x00)
	  {
	    TimingDelay--;
	  }
	}
  }
}

/**
  * @brief
  * @param
  * @retval
  */
static void TIMx_Init(uint32_t nPeriod)
{
	/* Enable TIMx Clock */
	TIMx_CLK_ENABLE();

	/* Time base configuration */
	htim.Instance = TIMx;
	htim.Init.Period = HAL_RCC_GetSysClockFreq() / nPeriod;
  	htim.Init.Prescaler = 0;
  	htim.Init.ClockDivision = 0;
  	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
  	HAL_TIM_Base_Init(&htim);

  	/* Configure the NVIC for TIM */
  	HAL_NVIC_SetPriority(TIMx_IRQn, 0, 0);
  	HAL_NVIC_EnableIRQ(TIMx_IRQn);

	/* Enable TIM peripheral counter */
  	HAL_TIM_Base_Start_IT(&htim);
}

/**
  * @brief  Configures I2C interface.
  */
static void I2Cx_Init(void)
{
  if(HAL_I2C_GetState(&I2cHandle) == HAL_I2C_STATE_RESET)
  {
    /* DISCOVERY_I2Cx peripheral configuration */
    I2cHandle.Init.Timing = BSP_I2C_TIMING;
    I2cHandle.Init.OwnAddress1 = 0x33;
    I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Instance = DISCOVERY_I2Cx;
      
    /* Init the I2C */
    I2Cx_MspInit();
    HAL_I2C_Init(&I2cHandle);
  }
}

/**
  * @brief  Write a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  Value: The target register value to be written 
  * @retval HAL status
  */
static void I2Cx_WriteData(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2cxTimeout); 

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }
}

/**
  * @brief  Read a register of the device through BUS
  * @param  Addr: Device address on BUS  
  * @param  Reg: The target register address to read
  * @retval HAL status
  */
static uint8_t  I2Cx_ReadData(uint8_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t value = 0;
  
  status = HAL_I2C_Mem_Read(&I2cHandle, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &value, 1,I2cxTimeout);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }
  return value;
}

/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address 
  */
static void I2Cx_Error(uint8_t Addr)
{
  /* De-initialize the I2C communication bus */
  HAL_I2C_DeInit(&I2cHandle);
  
  /* Re-Initialize the I2C communication bus */
  I2Cx_Init();
}

/**
  * @brief I2C MSP Initialization
  */
static void I2Cx_MspInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /* Enable I2C GPIO clocks */
  DISCOVERY_I2Cx_SCL_SDA_GPIO_CLK_ENABLE();

  /* DISCOVERY_I2Cx SCL and SDA pins configuration ---------------------------*/
  GPIO_InitStruct.Pin = DISCOVERY_I2Cx_SCL_PIN | DISCOVERY_I2Cx_SDA_PIN; 
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Alternate  = DISCOVERY_I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(DISCOVERY_I2Cx_SCL_SDA_GPIO_PORT, &GPIO_InitStruct);     

  /* Enable the DISCOVERY_I2Cx peripheral clock */
  DISCOVERY_I2Cx_CLK_ENABLE();

  /* Force the I2C peripheral clock reset */
  DISCOVERY_I2Cx_FORCE_RESET();

  /* Release the I2C peripheral clock reset */
  DISCOVERY_I2Cx_RELEASE_RESET();

  /* Enable and set I2Cx Interrupt to the highest priority */
  HAL_NVIC_SetPriority(DISCOVERY_I2Cx_EV_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_EV_IRQn);

  /* Enable and set I2Cx Interrupt to the highest priority */
  HAL_NVIC_SetPriority(DISCOVERY_I2Cx_ER_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DISCOVERY_I2Cx_ER_IRQn); 
}

/**
  * @brief  SPIx Bus initialization
  */
static void SPIx_Init(void)
{
  if(HAL_SPI_GetState(&SpiHandle) == HAL_SPI_STATE_RESET)
  {
    /* SPI configuration -----------------------------------------------------*/
    SpiHandle.Instance = DISCOVERY_SPIx;
    SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    SpiHandle.Init.Direction = SPI_DIRECTION_2LINES;
    SpiHandle.Init.CLKPhase = SPI_PHASE_2EDGE;
    SpiHandle.Init.CLKPolarity = SPI_POLARITY_HIGH;
    SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    SpiHandle.Init.CRCPolynomial = 7;
    SpiHandle.Init.DataSize = SPI_DATASIZE_8BIT;
    SpiHandle.Init.FirstBit = SPI_FIRSTBIT_MSB;
    SpiHandle.Init.NSS = SPI_NSS_SOFT;
    SpiHandle.Init.TIMode = SPI_TIMODE_DISABLED;
    SpiHandle.Init.Mode = SPI_MODE_MASTER;
    SpiHandle.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;  /* Recommanded setting to avoid glitches */

    SPIx_MspInit();
    HAL_SPI_Init(&SpiHandle);
  }
}

/**
  * @brief
  * @param
  * @retval
  */
static void SPIx_WriteData(uint8_t Byte)
{
  /* Send a Byte through the SPI peripheral */
  if(HAL_SPI_Transmit(&SpiHandle, (uint8_t*) &Byte, 1, SpixTimeout) != HAL_OK)
  {
    SPIx_Error();
  }
}

/**
  * @brief
  * @param
  * @retval
  */
static uint8_t SPIx_ReadData(void)
{
  uint8_t Byte = 0;

  /* Read byte from the SPI bus */
  if(HAL_SPI_Receive(&SpiHandle, (uint8_t*) &Byte, 1, SpixTimeout) != HAL_OK)
  {
    SPIx_Error();
  }
  
  return Byte;
}

/**
  * @brief  SPIx error treatment function.
  */
static void SPIx_Error(void)
{
  /* De-initialize the SPI communication bus */
  HAL_SPI_DeInit(&SpiHandle);
  
  /* Re-Initialize the SPI communication bus */
  SPIx_Init();
}

/**
  * @brief  SPI MSP Init.
  */
static void SPIx_MspInit(void)
{
  GPIO_InitTypeDef   GPIO_InitStruct;

  /* Enable the SPI peripheral */
  DISCOVERY_SPIx_CLK_ENABLE();
  
  /* Enable SCK, MOSI and MISO GPIO clocks */
  DISCOVERY_SPIx_GPIO_CLK_ENABLE();
  
  /* SPI SCK, MOSI, MISO pin configuration */
  GPIO_InitStruct.Pin = (DISCOVERY_SPIx_SCK_PIN | DISCOVERY_SPIx_MISO_PIN | DISCOVERY_SPIx_MOSI_PIN);
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = DISCOVERY_SPIx_AF;
  HAL_GPIO_Init(DISCOVERY_SPIx_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief  Initializes Audio low level.
  */
void AUDIO_IO_Init(void) 
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /* Enable Reset GPIO Clock */
  AUDIO_RESET_GPIO_CLK_ENABLE();
  
  /* Audio reset pin configuration */
  GPIO_InitStruct.Pin = AUDIO_RESET_PIN; 
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  HAL_GPIO_Init(AUDIO_RESET_GPIO, &GPIO_InitStruct);    
  
  I2Cx_Init();
  
  /* Power Down the codec */
  HAL_GPIO_WritePin(AUDIO_RESET_GPIO, AUDIO_RESET_PIN, GPIO_PIN_RESET);
  
  /* Wait for a delay to insure registers erasing */
  HAL_Delay(5); 
  
  /* Power on the codec */
  HAL_GPIO_WritePin(AUDIO_RESET_GPIO, AUDIO_RESET_PIN, GPIO_PIN_SET);
  
  /* Wait for a delay to insure registers erasing */
  HAL_Delay(5); 
}

/**
  * @brief  DeInitializes Audio low level.
  */
void AUDIO_IO_DeInit(void)
{
  
}

/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @param  Value: Data to be written
  */
void AUDIO_IO_Write (uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_WriteData(Addr, Reg, Value);
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @retval Data to be read
  */
uint8_t AUDIO_IO_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_ReadData(Addr, Reg);
}

/**
  * @brief  Configures the Accelerometer SPI interface.
  */
void TS_IO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Enable GPIO Clock */  
  TS_CS_GPIO_CLK_ENABLE();
  TS_INT_GPIO_CLK_ENABLE();
	
  /* Configure CS Pin */
  GPIO_InitStruct.Pin = TS_CS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(TS_CS_GPIO_PORT, &GPIO_InitStruct);

  /* Configure INT Pin */
  GPIO_InitStruct.Pin = TS_INT_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(TS_INT_GPIO_PORT, &GPIO_InitStruct);

  /* Deselect: Chip Select high */
  TS_CS_HIGH();
  
  TIMx_Init(TS_USDELAY);
  SPIx_Init();  
}

/**
  * @brief  Writes one byte to the Accelerometer.
  * @param  pBuffer: pointer to the buffer containing the data to be written to the Accelerometer.
  * @param  WriteAddr: Accelerometer's internal address to write to.
  * @param  NumByteToWrite: Number of bytes to write.
  */
uint16_t TS_IO_WriteRead(uint8_t Addr)
{
  uint16_t ReadByte, ReturnByte;
	
  /* Set chip select Low at the start of the transmission */
  TS_CS_LOW();
  
  /* Wait for a delay */
  TS_IO_Delay(1);
  
  /* Send the Address of the indexed register */
  SPIx_WriteData(Addr);

  /* Wait for a delay */
  TS_IO_Delay(1);

  /* Send dummy byte (0x00) to generate the SPI clock to Slave device */
  ReadByte = SPIx_ReadData();
  ReturnByte =  ReadByte << 8;

  /* Wait for a delay */
  TS_IO_Delay(1);

  /* Send dummy byte (0x00) to generate the SPI clock to Slave device */
  ReadByte = SPIx_ReadData();
  ReturnByte |= ReadByte;
  ReturnByte >>= 3;
  ReturnByte &= 0xFFF;

  /* Set chip select High at the end of the transmission */ 
  TS_CS_HIGH();

  return ReturnByte;  
}

/**
  * @brief  Read IT Pin
  * @param  None
  * @retval IT Pin State
  */
uint8_t TS_IO_ITRead(void)
{
  return TS_INT_READ();
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length.
  * @retval None
  */
void TS_IO_Delay(uint32_t Delay)
{
  TimingDelay = Delay;

  while(TimingDelay != 0);
}

/**
  * @brief  Configures COMPASS / ACCELERO I2C interface.
  */
void COMPASSACCELERO_IO_Init(void)
{ 
  I2Cx_Init();
}

/**
  * @brief  Configures COMPASS / ACCELERO click IT.
  */
void COMPASSACCELERO_IO_ITConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable INT1 and INT2 GPIO clock */
  ACCELERO_INT_GPIO_CLK_ENABLE();
  
  /* Configure GPIO PINs to detect Interrupts */
  GPIO_InitStructure.Pin = ACCELERO_INT1_PIN | ACCELERO_INT2_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull  = GPIO_NOPULL;
  HAL_GPIO_Init(ACCELERO_INT_GPIO_PORT, &GPIO_InitStructure);
  
  /* Enable and set COMPASS / ACCELERO Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(ACCELERO_INT1_EXTI_IRQn, 0x0F, 0x00);
  HAL_NVIC_EnableIRQ(ACCELERO_INT1_EXTI_IRQn);
}

/**
  * @brief  Writes one byte to the COMPASS / ACCELERO.
  * @param  DeviceAddr: the slave address to be programmed
  * @param  RegisterAddr: the COMPASS / ACCELERO register to be written
  * @param  Value: Data to be written
 */
void COMPASSACCELERO_IO_Write(uint16_t DeviceAddr, uint8_t RegisterAddr, uint8_t Value)
{
  /* Call I2Cx Read data bus function */
  I2Cx_WriteData(DeviceAddr, RegisterAddr, Value);
}

/**
  * @brief  Reads a block of data from the COMPASS / ACCELERO.
  * @param  DeviceAddr: the slave address to be programmed(ACC_I2C_ADDRESS or MAG_I2C_ADDRESS).
  * @param  RegisterAddr: the COMPASS / ACCELERO internal address register to read from
  * @retval COMPASS / ACCELERO register value
  */
uint8_t COMPASSACCELERO_IO_Read(uint16_t DeviceAddr, uint8_t RegisterAddr)
{
  /* Call I2Cx Read data bus function */   
  return I2Cx_ReadData(DeviceAddr, RegisterAddr);
}
