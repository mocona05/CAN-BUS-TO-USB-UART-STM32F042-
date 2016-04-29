#include "board.h"




#ifndef SPI1_PORTB_SET

#define SPI1_GPIO             GPIOA
#define SPI1_SCK_PIN          GPIO_Pin_5
#define SPI1_SCK_PIN_SOURCE   GPIO_PinSource5
#define SPI1_SCK_CLK          RCC_AHBPeriph_GPIOA
#define SPI1_MISO_PIN         GPIO_Pin_6
#define SPI1_MISO_PIN_SOURCE  GPIO_PinSource6
#define SPI1_MISO_CLK         RCC_AHBPeriph_GPIOA
#define SPI1_MOSI_PIN         GPIO_Pin_7
#define SPI1_MOSI_PIN_SOURCE  GPIO_PinSource7
#define SPI1_MOSI_CLK         RCC_AHBPeriph_GPIOA

#else		//SPI1 PORTB 
#define SPI1_GPIO             GPIOB
#define SPI1_SCK_PIN          GPIO_Pin_3
#define SPI1_SCK_PIN_SOURCE   GPIO_PinSource3
#define SPI1_SCK_CLK          RCC_AHBPeriph_GPIOB
#define SPI1_MISO_PIN         GPIO_Pin_4
#define SPI1_MISO_PIN_SOURCE  GPIO_PinSource4
#define SPI1_MISO_CLK         RCC_AHBPeriph_GPIOB
#define SPI1_MOSI_PIN         GPIO_Pin_5
#define SPI1_MOSI_PIN_SOURCE  GPIO_PinSource5
#define SPI1_MOSI_CLK         RCC_AHBPeriph_GPIOB
#endif

#define SPI2_GPIO             GPIOB
#define SPI2_SCK_PIN          GPIO_Pin_13
#define SPI2_SCK_PIN_SOURCE   GPIO_PinSource13
#define SPI2_SCK_CLK          RCC_AHBPeriph_GPIOB
#define SPI2_MISO_PIN         GPIO_Pin_14
#define SPI2_MISO_PIN_SOURCE  GPIO_PinSource14
#define SPI2_MISO_CLK         RCC_AHBPeriph_GPIOB
#define SPI2_MOSI_PIN         GPIO_Pin_15
#define SPI2_MOSI_PIN_SOURCE  GPIO_PinSource15
#define SPI2_MOSI_CLK         RCC_AHBPeriph_GPIOB



 //QueueType SPI2RxQueue, SPI2TxQueue;

static volatile uint16_t spi1ErrorCount = 0;
static volatile uint16_t spi2ErrorCount = 0;
static volatile uint16_t spi3ErrorCount = 0;


//---------------SPI  DMA---------------------//
// DMA related names
//volatile uint8_t sp2_rx_buffer[buffer_size];
//volatile uint8_t sp2_tx_buffer[buffer_size];
//SPI_buffer_t volatile SPI2_tx_buffer, SPI2_rx_buffer;


// DMA related names
//#define DMA_Channel_SPI1_RX    DMA1_Channel2  // SPI1
//#define DMA_Channel_SPI1_TX    DMA1_Channel3  // SPI1
//#define DMA_FLAG_SPI1_TC_RX    DMA1_FLAG_TC2
//#define DMA_FLAG_SPI1_TC_TX    DMA1_FLAG_TC3



///////////////////////////////////////////////////////////////////////////////
// SPI Initialize
///////////////////////////////////////////////////////////////////////////////

void spiInit(SPI_TypeDef *SPIx)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

    ///////////////////////////////////

    if (SPIx == SPI1)
    {
    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
				GPIO_PinAFConfig(SPI1_GPIO, SPI1_SCK_PIN_SOURCE, GPIO_AF_0);
				GPIO_PinAFConfig(SPI1_GPIO, SPI1_MISO_PIN_SOURCE, GPIO_AF_0);
				GPIO_PinAFConfig(SPI1_GPIO, SPI1_MOSI_PIN_SOURCE, GPIO_AF_0);
			
	    // Init pins
        GPIO_InitStructure.GPIO_Pin   = SPI1_SCK_PIN | SPI1_MOSI_PIN;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
        GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);

//        GPIO_InitStructure.GPIO_Pin   = SPI1_MISO_PIN ;
//        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;;
//				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			
//				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
//        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
        GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);
				
				SPI_I2S_DeInit(SPI1);
  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPIx);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;

//	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn ;
//	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x01;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

			SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx | SPI_I2S_DMAReq_Rx, ENABLE);



    }

    if (SPIx == SPI2)
    {
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

				// Init pins
					GPIO_InitStructure.GPIO_Pin   = SPI2_SCK_PIN | SPI2_MOSI_PIN ;
					GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
					GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(SPI2_GPIO, &GPIO_InitStructure);

//					GPIO_InitStructure.GPIO_Pin   =  SPI2_MOSI_PIN;
//					GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
//					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
//					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//					GPIO_Init(SPI2_GPIO, &GPIO_InitStructure);

	        GPIO_InitStructure.GPIO_Pin   = SPI2_MISO_PIN ;
	        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;;
					GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	        GPIO_Init(SPI2_GPIO, &GPIO_InitStructure);


				GPIO_PinAFConfig(SPI2_GPIO, SPI2_SCK_PIN_SOURCE, GPIO_AF_0);
				GPIO_PinAFConfig(SPI2_GPIO, SPI2_MISO_PIN_SOURCE, GPIO_AF_0);
				GPIO_PinAFConfig(SPI2_GPIO, SPI2_MOSI_PIN_SOURCE, GPIO_AF_0);
				
	//        GPIO_InitStructure.GPIO_Pin   = LCD_CS_PIN ;
	//        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;;
	//        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//        GPIO_Init(LCD_CS_GPIO, &GPIO_InitStructure);

	//				LCD_CS_GPIO->BSRR |= LCD_CS_PIN;  // GPIOA Pin 12 (NSS) is HIGH (for hardware SPI support)
 
 
			//  /* 1 bit for pre-emption priority, 3 bits for subpriority */
			//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

			//  /* Configure and enable SPI_MASTER interrupt -------------------------------*/
			//  NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
			//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
			//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
			//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			//  NVIC_Init(&NVIC_InitStructure);

			SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
			SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
			SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
			SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
			SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
			SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		//	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
			SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
			SPI_InitStructure.SPI_CRCPolynomial = 7;
			
			
	//		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;//2.25MHz     //  BD663474  MAX SPI READ SPEED : 2.875MHz	
//			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;//4.5MHz		
			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//8MHz		
//			SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//16MHz		
		//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;//1.125MHz
			SPI_Init(SPI2, &SPI_InitStructure);

			/* Enable SPI_MASTER NSS output for master mode */
		 // SPI_SSOutputCmd(SPI2, ENABLE);

			 //     SPI_RxFIFOThresholdConfig(L3GD20_SPI, SPI_RxFIFOThreshold_QF);
			// tell SPI1 to use DMA
//					SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx | SPI_I2S_DMAReq_Rx, ENABLE);

						
			NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn ;
			NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
						
    }			
		
  /* Initializes the SPI communication */
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPIx, &SPI_InitStructure);
  
  /* Initialize the FIFO threshold */
//  SPI_RxFIFOThresholdConfig(SPIx, SPI_RxFIFOThreshold_QF);
  
//  /* Enable the Rx buffer not empty interrupt */
//  SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_RXNE, ENABLE);
//  /* Enable the SPI Error interrupt */
//  SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_ERR, ENABLE);
//  /* Data transfer is performed in the SPI interrupt routine */
  
  /* Enable the SPI peripheral */
  SPI_Cmd(SPIx, ENABLE);
}

///////////////////////////////////////////////////////////////////////////////
// SPI Timeout Callback
///////////////////////////////////////////////////////////////////////////////

uint32_t spiTimeoutUserCallback(SPI_TypeDef *SPIx)
{
//	RED_S_LED_ON;

	if (SPIx == SPI1)
	{
		spi1ErrorCount++;
		return spi1ErrorCount;
	}
	else if (SPIx == SPI2)
	{
		spi2ErrorCount++;
		return spi2ErrorCount;
	}
	else
	{    spi3ErrorCount++;
	     return spi3ErrorCount;
	}
}

///////////////////////////////////////////////////////////////////////////////
// SPI Transfer
///////////////////////////////////////////////////////////////////////////////

uint16_t  spiTransfer(SPI_TypeDef *SPIx, uint16_t data)
{
    uint16_t spiTimeout;
//		LCD_CS_LOW;
    spiTimeout = 0x1000;
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
      if ((spiTimeout--) == 0) return spiTimeoutUserCallback(SPIx);

    SPI_I2S_SendData16(SPIx, data);

    spiTimeout = 0x1000;
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
      if ((spiTimeout--) == 0) return spiTimeoutUserCallback(SPIx);
	//	LCD_CS_HIGH;

    return SPI_I2S_ReceiveData16(SPIx);
		
}


uint16_t spiTransferAndRead(SPI_TypeDef *SPIx, uint16_t data)
{
    uint16_t spiTimeout;

    spiTimeout = 0x1000;
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
      if ((spiTimeout--) == 0) return spiTimeoutUserCallback(SPIx);

    SPI_I2S_SendData16(SPIx, data);

    spiTimeout = 0x1000;
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
      if ((spiTimeout--) == 0) return spiTimeoutUserCallback(SPIx);

    return SPI_I2S_ReceiveData16(SPIx);
}


///////////////////////////////////////////////////////////////////////////////
// SPI Receive
///////////////////////////////////////////////////////////////////////////////

uint16_t spiReceive(SPI_TypeDef *SPIx)
{
    uint16_t spiTimeout;

//     spiTimeout = 0x1000;
//     while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)
//       if ((spiTimeout--) == 0) return spiTimeoutUserCallback(SPIx);

  //  SPI_I2S_SendData(SPIx, data);

    spiTimeout = 0x1000;
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
      if ((spiTimeout--) == 0) return spiTimeoutUserCallback(SPIx);

    return(SPI_I2S_ReceiveData16(SPIx));
}


///////////////////////////////////////////////////////////////////////////////
// Get SPI Error Count
///////////////////////////////////////////////////////////////////////////////

uint16_t spiGetErrorCounter(SPI_TypeDef *SPIx)
{
    if (SPIx == SPI1)
    	return spi1ErrorCount;
//    else if (SPIx == SPI2)
		else
        return spi2ErrorCount;
	}

uint8_t SPI_SendByte(SPI_TypeDef *SPIx, uint8_t byte){
    uint16_t spiTimeout;
    spiTimeout = SPI_TIMEOUT;

	  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET)      
		if ((spiTimeout--) == 0) return spiTimeoutUserCallback(SPIx);
         
	  SPI_SendData8(SPIx, byte);          
	  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)          
		if ((spiTimeout--) == 0) return spiTimeoutUserCallback(SPIx);

	  return SPI_ReceiveData8(SPIx);
}

