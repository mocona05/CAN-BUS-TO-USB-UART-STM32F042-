#include "board.h"


#include "drv_spi_dma.h"



SPI_DMA_bufferType SPI1_Buffer[MAX_DMA_QUEUE_SIZE];

//SPI_DMA_QueueType	SP2_Queue;
volatile uint8_t SPI1_MemoryNo; 
volatile uint8_t SPI1_DMA_No; 
volatile bool RxdDMA_Flag;

void SPI_DMA_Init(void) {
DMA_InitTypeDef  DMA_InitStructure;
//SPI_InitTypeDef  SPI_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
	
	 //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
#ifdef SPI_DMA_RXD_ENABLE		
	 // DMA RX SPI1 channel
  DMA_DeInit(SPIx_RX_DMA_CHANNEL);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI1_Buffer[0].RxBuffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = SPI1_Buffer[0].RxCount;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(SPIx_RX_DMA_CHANNEL, &DMA_InitStructure);
#endif

  // DMA TX SPI1 channel
  DMA_DeInit(SPIx_TX_DMA_CHANNEL);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
//  DMA_InitStructure.DMA_PeripheralBaseAddr = spixbase;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI1_Buffer[0].TxBuffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 1;//SPI1_Buffer[0].TxCount;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(SPIx_TX_DMA_CHANNEL, &DMA_InitStructure);

   /* Enable SPI_MASTER */
  SPI_Cmd(SPI1, ENABLE);
	
    // Interrupt at DMA transfer complete
		
    DMA_ITConfig(SPIx_TX_DMA_CHANNEL, DMA_IT_TC, ENABLE);
#ifdef SPI_DMA_RXD_ENABLE				
    DMA_ITConfig(SPIx_RX_DMA_CHANNEL, DMA_IT_TC, ENABLE);
 #endif
 
// ----------------------------------------------------------------------------

//  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
// 

  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
 
}


void LCD_WriteI_regDMA(uint16_t index)
{
		/* Write 16-bit Index, then Write Reg */  
				SPI_MemoryBuffer_WriteStart(LCD_CS_Control, LCD_RS_Control, LOW_CS, LOW_RS, NULL, NULL);
				SPI_MemoryBuffer_WriteData(index>>8);  
				SPI_MemoryBuffer_WriteData((uint8_t)index); 
				SPI_MemoryBuffer_WriteEnd(HIGH_CS, NONE_RS);
}


void LCD_Write_command_DMA( uint16_t index, uint16_t data)
{
				SPI_MemoryBuffer_WriteStart(LCD_CS_Control,LCD_RS_Control, LOW_CS, LOW_RS, NULL, NULL);
				SPI_MemoryBuffer_WriteData(index>>8);  
				SPI_MemoryBuffer_WriteData((uint8_t)index); 
				SPI_MemoryBuffer_WriteEnd(NONE_CS, HIGH_RS);

				SPI_MemoryBuffer_WriteStart(LCD_CS_Control, LCD_RS_Control, NONE_CS, NONE_RS, NULL, NULL);
				SPI_MemoryBuffer_WriteData(data>>8);  
				SPI_MemoryBuffer_WriteData((uint8_t)data); 
				SPI_MemoryBuffer_WriteEnd(HIGH_CS, NONE_RS);
}

void LCD_Write_Data_StartDMA(void) {
		SPI_MemoryBuffer_WriteStart(LCD_CS_Control, LCD_RS_Control, LOW_CS, HIGH_RS, NULL, NULL);
}

void LCD_Write_Data_EndDMA(void) {
		SPI_MemoryBuffer_WriteEnd( HIGH_CS, NONE_RS);
}


void LCD_Write_Data_DMA( uint16_t data) 
{
		SPI_MemoryBuffer_WriteData( (data >> 8));  			 /* Write D8..D15                */
		SPI_MemoryBuffer_WriteData( (uint8_t) data);   /* Write D0..D7                 */
}



static void Memory_To_DMA_Write (void) {
#if 0	
	switch(SPI1_Buffer[SPI1_DMA_No].StartCS) {
		case NONE_CS:
			break;
		case HIGH_CS:
			LCD_CS_HIGH;
			break;
		case LOW_CS:
			LCD_CS_LOW;
			break;
	}	
#else
		void (*Func) (volatile uint8_t  *); 
		Func =	SPI1_Buffer[SPI1_DMA_No].CSFUN;
		Func(&SPI1_Buffer[SPI1_DMA_No].StartCS);
		Func =	SPI1_Buffer[SPI1_DMA_No].RSFUN;
		Func(&SPI1_Buffer[SPI1_DMA_No].StartRS);

		
#endif		
		
	SPI1_Buffer[SPI1_DMA_No].status = DMA_ACCESS_BUFFER;
	SPI_I2S_DMACmd(SPI1,  SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx, DISABLE);
	SPIx_TX_DMA_CHANNEL->CMAR = (uint32_t)SPI1_Buffer[SPI1_DMA_No].TxBuffer;		//버퍼를 포인팅
	DMA_SetCurrDataCounter(SPIx_TX_DMA_CHANNEL, SPI1_Buffer[SPI1_DMA_No].TxCount);
	DMA_Cmd(SPIx_TX_DMA_CHANNEL, ENABLE);
#ifdef SPI_DMA_RXD_ENABLE		
	SPIx_RX_DMA_CHANNEL->CMAR = (uint32_t)SPI1_Buffer[SPI1_DMA_No].RxBuffer;		//버퍼를 포인팅
	DMA_SetCurrDataCounter(SPIx_RX_DMA_CHANNEL, SPI1_Buffer[SPI1_DMA_No].RxCount);
	DMA_Cmd(SPIx_RX_DMA_CHANNEL, ENABLE);
	SPI_I2S_DMACmd(SPI1,  SPI_I2S_DMAReq_Rx , ENABLE);
#endif	
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
}



bool SPI_DMA_Write(void) {
	uint8_t nextBufferNo=((SPI1_DMA_No+1)%MAX_DMA_QUEUE_SIZE);
//	SPI1_DMA_EndCS_Check();			//현재 DMA버퍼의 END CS 확인 및 처리
	//현재의 DMA버퍼가 준비되어 있을 경우
if((SPI1->SR & SPI_SR_TXE)){ // Wait for bus free
	if(SPI1_Buffer[SPI1_DMA_No].status == READY_BUFFER) {	//선택된 버퍼가 쓸준비가 되어있는경우
		Memory_To_DMA_Write();
		return true;
	}
		//현재의 DMA버퍼가 비어있고 다음 버퍼가 준비 된경우 
		if(SPI1_Buffer[SPI1_DMA_No].status == EMPTY_BUFFER && SPI1_Buffer[nextBufferNo].status ==READY_BUFFER) {
			SPI1_DMA_No=nextBufferNo;
			//DMA 전송이 완료되었을경우
			Memory_To_DMA_Write();
			return true;
		}
	}
	return false;
}



//비어있는 DMA Memory Queue를 검색 하여 쓰기 시작 설정 
//비어있는 메모리가 없다면 false를 반환 

//void SPI1_MemoryBuffer_WriteStart (void (* function)(volatile uint8_t *),uint8_t start_CS) {
void SPI_MemoryBuffer_WriteStart (void (* cs_func)(volatile uint8_t *),void (* rs_func)(volatile uint8_t *),uint8_t start_CS,uint8_t start_RS, volatile uint8_t rxdSize, volatile uint8_t * rxdData) {
	uint32_t timeNow=0;		
	uint32_t readTime =0;
	uint8_t 	nextBufferNo=((SPI1_MemoryNo+1)%MAX_DMA_QUEUE_SIZE);
	
	//현재의 메모리 버퍼가 비어있는지 확인
	if(SPI1_Buffer[SPI1_MemoryNo].status==EMPTY_BUFFER ) {
		SPI1_Buffer[SPI1_MemoryNo].StartCS = start_CS;
		SPI1_Buffer[SPI1_MemoryNo].StartRS = start_RS;
		SPI1_Buffer[SPI1_MemoryNo].CSFUN = cs_func;
		SPI1_Buffer[SPI1_MemoryNo].RSFUN = rs_func;
		
		SPI1_Buffer[SPI1_MemoryNo].status = WRITE_BUFFER;
#ifdef SPI_DMA_RXD_ENABLE			
			SPI1_Buffer[SPI1_MemoryNo].RxCount = rxdSize;
		if(rxdSize >0) {
			SPI1_Buffer[SPI1_DMA_No].pRxdData =rxdData;
		}
		else {
			SPI1_Buffer[SPI1_DMA_No].pRxdData =NULL;
		}
#endif
		
		SPI_DMA_Write();
		return;
	}
	//다음버퍼가 비워질때까지 대기
	readTime = timeNow;
	while(SPI1_Buffer[nextBufferNo].status != EMPTY_BUFFER){
		timeNow = millis();
		if((int64_t)timeNow-readTime-50>0 && timeNow >= readTime) {		//50ms time out 처리
			SPI1_DMA_No =nextBufferNo;
			SPI1_Buffer[SPI1_DMA_No].status=EMPTY_BUFFER;			
			break;
		}
		SPI_DMA_Write();
	}		
//	else if(SPI1_Buffer[nextBufferNo].status==EMPTY_BUFFER) {
		SPI1_MemoryNo=nextBufferNo;
		SPI1_Buffer[SPI1_MemoryNo].StartCS = start_CS;
		SPI1_Buffer[SPI1_MemoryNo].StartRS = start_RS;
		SPI1_Buffer[SPI1_MemoryNo].CSFUN = cs_func;
		SPI1_Buffer[SPI1_MemoryNo].RSFUN = rs_func;
		SPI1_Buffer[SPI1_MemoryNo].status = WRITE_BUFFER;
#ifdef SPI_DMA_RXD_ENABLE		
		SPI1_Buffer[SPI1_MemoryNo].RxCount = rxdSize;
		if(rxdSize >0) {
			SPI1_Buffer[SPI1_DMA_No].pRxdData =rxdData;
		}
		else {
			SPI1_Buffer[SPI1_DMA_No].pRxdData =NULL;
		}
#endif		
		SPI_DMA_Write();
}



//dma buffer memory에 연속 쓰기를 실행 하며, 버퍼가 꽉찰경우 false를 반환
//--------------------------------------------------------------
void SPI_MemoryBuffer_WriteData (uint8_t data) {
	uint8_t nextBufferNo=((SPI1_MemoryNo+1)%MAX_DMA_QUEUE_SIZE);
//	if(MAX_DMA_BUFFER_SIZE  > SPI1_Buffer[SPI1_MemoryNo].TxCount) {
	if(MAX_DMA_BUFFER_SIZE  > SPI1_Buffer[SPI1_MemoryNo].TxCount) {
		SPI1_Buffer[SPI1_MemoryNo].TxBuffer[SPI1_Buffer[SPI1_MemoryNo].TxCount] = data;
		SPI1_Buffer[SPI1_MemoryNo].TxCount++;
	}
	else {
		SPI1_Buffer[SPI1_MemoryNo].EndCS = NONE_CS;		//가득찬 버퍼의 end cs를  none로 처리
		SPI1_Buffer[SPI1_MemoryNo].EndRS = NONE_RS;		//가득찬 버퍼의 end rs를  none로 처리
		SPI1_Buffer[SPI1_MemoryNo].status = READY_BUFFER;		//가득찬 버퍼를 전송준비 됨으로 변경.
		SPI_DMA_Write();
		SPI1_MemoryNo =nextBufferNo;//메모리 큐를 다음 큐로 선택
		//CS 변화가 없이 연속적으로 전송될수 있도록 다음 큐를 설정
		SPI1_Buffer[SPI1_MemoryNo].StartCS = NONE_CS;
		SPI1_Buffer[SPI1_MemoryNo].EndCS = NONE_CS;
		SPI1_Buffer[SPI1_MemoryNo].StartRS = NONE_RS;
		SPI1_Buffer[SPI1_MemoryNo].EndRS = NONE_RS;
		SPI1_Buffer[SPI1_MemoryNo].status = WRITE_BUFFER;
		SPI1_Buffer[SPI1_MemoryNo].TxBuffer[SPI1_Buffer[SPI1_MemoryNo].TxCount] = data;
		SPI1_Buffer[SPI1_MemoryNo].TxCount++;
	}
	SPI_DMA_Write();
}


//DMA 메모리 쓰기 완료 
void SPI_MemoryBuffer_WriteEnd (uint8_t end_CS, uint8_t end_RS) {		//메모리 쓰기 완료 
	uint8_t nextBufferNo=((SPI1_MemoryNo+1)%MAX_DMA_QUEUE_SIZE);
	SPI1_Buffer[SPI1_MemoryNo].EndCS = end_CS;
	SPI1_Buffer[SPI1_MemoryNo].EndRS = end_RS;
	SPI1_Buffer[SPI1_MemoryNo].status = READY_BUFFER;
	SPI1_MemoryNo =nextBufferNo;		//다음 메모리로 선택 **********
	SPI_DMA_Write();
}



void DMA1_Channel2_3_IRQHandler(void){		// SPI1 RXD
		uint8_t 	bufferNo=( (SPI1_DMA_No+1)%MAX_DMA_QUEUE_SIZE);	
#ifdef SPI_DMA_RXD_ENABLE	
	void (*Func) (volatile uint8_t  *); 
#endif	
    if(DMA_GetITStatus(DMA1_IT_TC3)){		//SPI TXD
		DMA_ClearFlag(DMA1_FLAG_TC3);
		SPI_I2S_DMACmd(SPI1,  SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx, DISABLE);
		DMA_Cmd(SPIx_TX_DMA_CHANNEL, DISABLE);
		DMA_Cmd(SPIx_RX_DMA_CHANNEL, DISABLE);
		SPI1_Buffer[SPI1_DMA_No].TxCount =0;		//전송 카운터 버퍼를 클리어
		
		if(SPI1_Buffer[SPI1_DMA_No].EndCS ==NONE_CS&& SPI1_Buffer[SPI1_DMA_No].EndRS ==NONE_RS) {		//종료 CS변경이 없을경우
			SPI1_Buffer[SPI1_DMA_No].status = EMPTY_BUFFER;		//전송 완료된 버퍼를 빈버퍼로 처리
//			SPI1_Buffer[SPI1_DMA_No].TxCount =0;		//전송 카운터 버퍼를 클리어
			//다음 버퍼가 준비되어 있고 시작 CS변경이 없는경우 
			if(SPI1_Buffer[bufferNo].status == READY_BUFFER && SPI1_Buffer[bufferNo].StartCS == NONE_CS&& SPI1_Buffer[bufferNo].StartRS == NONE_RS){
				SPI1_DMA_No =bufferNo;	//다음버퍼 번호를 설정
				Memory_To_DMA_Write();
			}
		}

		else {	//CS 변경이 있을경우 CS기다림으로 상태를 변경
			void (*Func) (volatile uint8_t  *); 
				if((SPI1->SR & SPI_SR_TXE)){ // Wait for bus free
#ifdef SPI_DMA_RXD_ENABLE	
					 if(SPI1_Buffer[SPI1_DMA_No].RxCount >0) {
							SPI1_Buffer[SPI1_DMA_No].status = RECEIVE_BUFFER;		//수신설정 버퍼의 경우 수신으로 처리
//							memcpy((uint8_t *)SPI1_Buffer[SPI1_DMA_No].pRxdData, (uint8_t *)SPI1_Buffer[SPI1_DMA_No].RxBuffer, SPI1_Buffer[SPI1_DMA_No].RxCount);
//							RxdDMA_Flag=1;
					 }
					 else {
#endif						 
							Func =	SPI1_Buffer[SPI1_DMA_No].CSFUN;
							Func(&SPI1_Buffer[SPI1_DMA_No].EndCS);	//CS처리함수 호출						 
							Func =	SPI1_Buffer[SPI1_DMA_No].RSFUN;
							Func(&SPI1_Buffer[SPI1_DMA_No].EndRS);	//RS처리함수 호출						 
							SPI1_Buffer[SPI1_DMA_No].status = EMPTY_BUFFER;		//전송 완료된 버퍼를 빈버퍼로 처리
							SPI1_DMA_No =bufferNo;	//다음버퍼 번호를 설정
							if(SPI1_Buffer[SPI1_DMA_No].status == READY_BUFFER) {	//선택된 버퍼가 쓸준비가 되어있는경우
								Memory_To_DMA_Write();
							}
#ifdef SPI_DMA_RXD_ENABLE	
					 }
#endif				
				}
				else {		//특별히 필요없는것으로 판단됨 확인후 삭제필요
						SPI1_Buffer[SPI1_DMA_No].status  =CS_WAIT_BUFFER;
				}
		}

	}	
#ifdef SPI_DMA_RXD_ENABLE		
    if(DMA_GetITStatus(DMA1_IT_TC2)) {		//SPI RXD
        DMA_ClearFlag(DMA1_FLAG_TC2);
				Func =	SPI1_Buffer[SPI1_DMA_No].CSFUN;
				Func(&SPI1_Buffer[SPI1_DMA_No].EndCS);	//CS처리함수 호출
				Func =	SPI1_Buffer[SPI1_DMA_No].RSFUN;
				Func(&SPI1_Buffer[SPI1_DMA_No].EndRS);	//RS처리함수 호출
			if(SPI1_Buffer[SPI1_DMA_No].status == RECEIVE_BUFFER ) {
				memcpy((uint8_t *)SPI1_Buffer[SPI1_DMA_No].pRxdData, (uint8_t *)SPI1_Buffer[SPI1_DMA_No].RxBuffer, SPI1_Buffer[SPI1_DMA_No].RxCount);
				RxdDMA_Flag=1;
			}
				SPI1_Buffer[SPI1_DMA_No].RxCount=0;
				SPI1_Buffer[SPI1_DMA_No].pRxdData=NULL;
				SPI1_Buffer[SPI1_DMA_No].status = EMPTY_BUFFER;		//수신처리 완료 후  빈버퍼로 처리
				SPI1_DMA_No =bufferNo;	//다음버퍼 번호를 설정
		if(SPI1_Buffer[SPI1_DMA_No].status == READY_BUFFER) {	//선택된 버퍼가 쓸준비가 되어있는경우
			Memory_To_DMA_Write();
		}
	}	
#endif
	
}

void LCD_CS_Control(volatile uint8_t *status) {
	switch(*status) {
		case NONE_CS:
			break;
		case HIGH_CS:
			LCD_CS_SET;
			break;
		case LOW_CS:
			LCD_CS_CLR;
			break;
	}
}

void LCD_RS_Control(volatile uint8_t *status) {
	switch(*status) {
		case NONE_RS:
			break;
		case HIGH_RS:
			LCD_DC_SET;
			break;
		case LOW_RS:
			LCD_DC_CLR;
			break;
	}
}

