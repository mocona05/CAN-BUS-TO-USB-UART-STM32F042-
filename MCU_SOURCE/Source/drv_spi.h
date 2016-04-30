#pragma once

#define SPI_TIMEOUT 1000
//#define SPI_BUFFER_SIZE 8162

//#define LCD_DMA_CONTROL

//#define DMA_Channel_SPI2_RX    DMA1_Channel1  
//#define DMA_Channel_SPI2_TX    DMA1_Channel2  
//#define DMA_FLAG_SPI2_TC_RX    DMA1_FLAG_TC4
//#define DMA_FLAG_SPI2_TC_TX    DMA1_FLAG_TC5


/* Communication boards SPIx Interface */
#define SPIx_DR_ADDRESS                  0x4001300C
#define SPIx_TX_DMA_CHANNEL              DMA1_Channel3
#define SPIx_TX_DMA_FLAG_TC              DMA1_FLAG_TC3
#define SPIx_TX_DMA_FLAG_GL              DMA1_FLAG_GL3
#define SPIx_RX_DMA_CHANNEL              DMA1_Channel2
#define SPIx_RX_DMA_FLAG_TC              DMA1_FLAG_TC2
#define SPIx_RX_DMA_FLAG_GL              DMA1_FLAG_GL2

//typedef struct
//{     uint8_t	buffer[SPI_BUFFER_SIZE];
//			 uint32_t count;
//} SPI_buffer_t;

void spiInit(SPI_TypeDef *SPIx);
uint16_t spiGetErrorCounter(SPI_TypeDef *SPIx);
uint16_t spiReceive(SPI_TypeDef *SPIx);
uint16_t spiTransfer(SPI_TypeDef *SPIx, uint16_t data);
uint16_t spiTransferAndRead(SPI_TypeDef *SPIx, uint16_t data);

uint8_t SPI_SendByte(SPI_TypeDef *SPIx, uint8_t byte);

//extern volatile SPI_buffer_t SPI2_tx_buffer, SPI2_rx_buffer;

//extern volatile uint8_t sp2_rx_buffer[SPI_BUFFER_SIZE];
//extern volatile uint8_t sp2_tx_buffer[SPI_BUFFER_SIZE];


//void spiDMAsend(SPI_TypeDef *SPIx, uint16_t data);



//void DMA1_Channel5_IRQHandler(void); //Rxd
//void LCD_Write_Data_OnlyDMA( uint8_t data);

//void spi2_dma_tx(void);
//void txd_DAM_empty_check(void);

//void spi2_dma_set(void);

//void spi2_DMA_BlockSend (void);

