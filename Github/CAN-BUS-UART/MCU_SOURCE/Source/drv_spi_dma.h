#pragma once


#ifndef DRV_SPI_DMA_H
#define DRV_SPI_DMA_H

/* Defines -------------------------------------------------------------------*/
#define MAX_DMA_BUFFER_SIZE      150
#define MAX_DMA_QUEUE_SIZE      2

/* Type declarations ---------------------------------------------------------*/
typedef struct
{
    volatile uint8_t StartCS;
    volatile uint8_t EndCS;
    volatile uint8_t StartRS;
    volatile uint8_t EndRS;
    volatile uint8_t status;
    volatile uint16_t TxCount;
    volatile uint8_t	TxBuffer[MAX_DMA_BUFFER_SIZE];
	
#ifdef SPI_DMA_RXD_ENABLE	
    volatile uint16_t RxCount;
    volatile uint8_t	RxBuffer[MAX_DMA_BUFFER_SIZE];
#endif
	
	 void (* CSFUN) (volatile uint8_t *);
	 void (* RSFUN) (volatile uint8_t *);
//		volatile uint8_t  RxdSize;
	volatile uint8_t * pRxdData;
//	volatile bool RxdComplit;
} SPI_DMA_bufferType;


//typedef struct
//{
//	volatile uint8_t  MemoryNo;
//	volatile uint8_t  DMA_No;

//} SPI_DMA_QueueType;


typedef struct
{
	volatile uint8_t  * rxdData;
	volatile bool receive  ;

} SPI_DMA_RxdType;


//typedef enum {DMA_BUFFER_SUCCESS = 0, DMA_BUFFER_ERROR = !DMA_BUFFER_SUCCESS} DMA_BufferStatus;


typedef enum {
	EMPTY_BUFFER,
	WRITE_BUFFER,
	READY_BUFFER,
	DMA_ACCESS_BUFFER,
	RECEIVE_BUFFER,
	CS_WAIT_BUFFER,
} Buffer_Status;

typedef enum {
	START_DATA,
	CONTINUS_DATA,
	END_DATA,
} data_Status;

typedef enum {
	NONE_CS,
	HIGH_CS,
	LOW_CS,
} cs_Type;


typedef enum {
	NONE_RS,
	HIGH_RS,
	LOW_RS,
} rs_Type;


extern SPI_DMA_bufferType SPI1_Buffer[MAX_DMA_QUEUE_SIZE];
extern volatile bool RxdDMA_Flag;
extern volatile uint8_t SPI1_MemoryNo; 
extern volatile uint8_t SPI1_DMA_No; 

void SPI_DMA_Init(void);
void LCD_WriteI_regDMA(uint16_t index);
void LCD_Write_command_DMA( uint16_t index, uint16_t data);

void LCD_Write_Data_StartDMA(void);

void SPI_MemoryBuffer_WriteStart (void (* cs_func)(volatile uint8_t *),void (* rs_func)(volatile uint8_t *),  uint8_t start_CS, uint8_t start_RS,volatile uint8_t  rxdSize, volatile uint8_t * rxdData);
void SPI_MemoryBuffer_WriteEnd (uint8_t end_CS, uint8_t end_RS);

void LCD_Write_Data_DMA( uint16_t data) ;
static void Memory_To_DMA_Write (void) ;
//static void SPI2_DMA_EndCS_Check(void);
bool SPI_DMA_Write(void);
//void SPI2_MemoryBuffer_WriteStart (uint8_t start_CS);
//void SPI2_MemoryBuffer_WriteStart (void (* function)(volatile uint8_t *), uint8_t start_CS);

void SPI_MemoryBuffer_WriteData (uint8_t data);	//dma data를 연속적으로 저장
void LCD_Write_Data_EndDMA(void);


void DMA1_Channel5_IRQHandler(void);		//txd
void DMA1_Channel4_IRQHandler(void);		//rxd

void TP_CS_Control(volatile uint8_t * status);
void LCD_CS_Control(volatile uint8_t  *status);
void LCD_RS_Control(volatile uint8_t *status);
//bool SPI2_DMA_Receive(uint8_t * setBuffer_No, uint8_t * rxdBuffer);

//void TFT_Char3DMA (uint8_t ch_asc, uint8_t postion_x, uint8_t postion_y);

#endif

