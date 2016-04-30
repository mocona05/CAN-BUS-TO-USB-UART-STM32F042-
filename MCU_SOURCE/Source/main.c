

/* Includes ------------------------------------------------------------------*/
#include "board.h"

/** @addtogroup STM32F0308_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define BSRR_VAL        0x0300

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//GPIO_InitTypeDef        GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

 void RCC_init(void){
   ErrorStatus HSEStartUpStatus;
   RCC_DeInit(); //RCC system reset(for debug purpose)


   RCC_HSEConfig(RCC_HSE_ON); //Enable HSE
   HSEStartUpStatus = RCC_WaitForHSEStartUp(); //Wait till HSE is ready

 

   if(HSEStartUpStatus == SUCCESS) {
      FLASH_PrefetchBufferCmd(ENABLE); //Enable Prefetch Buffer
      FLASH_SetLatency(FLASH_Latency_1); //Flash 1 wait state
      RCC_HCLKConfig(RCC_SYSCLK_Div1); //HCLK = SYSCLK
	   RCC_PCLKConfig(RCC_HCLK_Div1);
//      RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_6); //PLLCLK = 8MHz * 6 = 48 MHz
      RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_6); //PLLCLK = 8MHz * 6 = 48 MHz
      RCC_PLLCmd(ENABLE); //Enable PLL

 

      while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); //Wait till PLL is ready
      RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //Select PLL as system clock source
      while (RCC_GetSYSCLKSource() != 0x08); //Wait till PLL is used as system clock source
   }

}	



//void print_value (void) {	//I 일정주기마다 측정된 BAT전압을 전송 
//    uint32_t msNow;
//    static uint32_t  actionTime, elapsedTime, oldTime;

//    msNow = millis();
//			elapsedTime = elapsedTime + (msNow - oldTime);
//			oldTime = msNow;   
//	
//		if( actionTime + 250  < elapsedTime) {
//				actionTime = elapsedTime;
////				adcCallcul(ADC_Value[0], &sys.bat_V);		//공급전압을 스케일링
//			
//					printf("MODE=%d\r\n",sys.runningMode);
//		}
//}



int main(void) {


		RCC_init();			//Clock Setting
		systemInit();			//GPIO Init

	
//		init_queue(&Uart1RxQueue);
//		init_queue(&Uart1TxQueue);
//		USART1_Init();
		spiInit(SPI1);
//		SPI_DMA_Init();
		ssd1306_init();
		ssd1306_clear_screen(0x00);
//		draw_line(0, 41, 128, 41, true);
	//	ssd1306_refresh_gram();		//LCD 표시값을 UPDATE.
//		layout_display_string();
	
	LED0_ON;
	LED1_ON;	
	
can_bus_init();
	
	
   	while (1) {
//			uint32_t msNow;
//			static uint32_t  actionTime, elapsedTime, oldTime;
//			uint8_t i=0;
//			msNow = millis();
//			elapsedTime = elapsedTime + (msNow - oldTime);
//			oldTime = msNow;  

			LCD_Value_Display(false);
			//CAN_TXD_Time_Handller_en_queue();
		CAN_RXD_Queue_Handller();
			
			
//			if(actionTime + 20 <= elapsedTime) {		//5ms loop running
//						actionTime = elapsedTime;
//	//				CAN_Transmit(CANx, &TxMessage);
//			}		
//		print_value();
//		read_uart_string();
//		loop_time_measuring(&sys.cycleTime);					
					
	}//while(1)
}//main

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
