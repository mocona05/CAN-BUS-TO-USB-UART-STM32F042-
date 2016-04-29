#pragma once

#include "stm32f0xx.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>
//#include <math.h>
//#include <ctype.h>
#include <string.h>


//ESC 테스트를 디펄트 동작  모드로 설정시 활성화 , 비활성화시 표준 서보모드(25ms priod로 800~2200us High puls범위로 동작됨.
//#define ESC_TEST_MODE		//FAST PWM & 800~2200 us PWM mode

//#define SPI_DMA_ENABLE
//#define SPI_DMA_RXD_ENABLE


#define UART1_BAURD		115200


//------------------ LED DISPLAY --------------------

#define LED0_GPIO   GPIOA
#define LED0_PIN    GPIO_Pin_1

#define LED1_GPIO   GPIOA
#define LED1_PIN    GPIO_Pin_0

#define LED0_TOGGLE              digitalToggle(LED0_GPIO, LED0_PIN)
#define LED0_ON                 digitalHi(LED0_GPIO, LED0_PIN)
#define LED0_OFF                  digitalLo(LED0_GPIO, LED0_PIN)


#define LED1_TOGGLE              digitalToggle(LED1_GPIO, LED1_PIN)
#define LED1_ON                 digitalHi(LED1_GPIO, LED1_PIN)
#define LED1_OFF                  digitalLo(LED1_GPIO, LED1_PIN)



//#define LED_MENUAL_ON			LED1_ON;
//#define LED_MENUAL_OFF			LED1_OFF;
//#define LED_NETURAL_ON			LED2_ON;
//#define LED_NETURAL_OFF		LED2_OFF;

//#define LED_AUTO_ON					LED1_ON;
//#define LED_AUTO_OFF					LED1_OFF;

	//------------------LCD  CONTROL ---------------------------
		
#define LCD_SPI_PORT				SPI1
#if 1
	#define SH1106			//1.3 INCHI  LCD
#else
	#define SSD1306			//0.9 INCHI	LCD
#endif
//#define INTERFACE_3WIRE_SPI   //3-wire SPI 
#define INTERFACE_4WIRE_SPI     //4-wire SPI 
//#define INTERFACE_IIC         //I2C

#define LCD_UPDATE_SPEED		30000	//us  단위

#define LCD_CS_PIN          				GPIO_Pin_4
#define LCD_DC_PIN          			GPIO_Pin_6
#define LCD_RST_PIN        			 GPIO_Pin_1

#define LCD_CS_GPIO        				 GPIOA
#define LCD_DC_GPIO         				GPIOA
#define LCD_RST_GPIO     			   GPIOB
#if 1
	#define LCD_RST_SET					LCD_RST_GPIO->BSRR = LCD_RST_PIN
	#define LCD_RST_CLR         LCD_RST_GPIO->BRR = LCD_RST_PIN

	#define LCD_CS_SET					LCD_CS_GPIO->BSRR = LCD_CS_PIN
	#define LCD_CS_CLR         LCD_CS_GPIO->BRR = LCD_CS_PIN

	#define LCD_DC_SET					LCD_DC_GPIO->BSRR = LCD_DC_PIN
	#define LCD_DC_CLR         LCD_DC_GPIO->BRR = LCD_DC_PIN
#else
	#define LCD_RST_SET					 digitalHi(LCD_RST_GPIO, LCD_RST_PIN)
	#define LCD_RST_CLR         digitalLo(LCD_RST_GPIO, LCD_RST_PIN)

	#define LCD_CS_SET					digitalHi(LCD_CS_GPIO, LCD_CS_PIN)
	#define LCD_CS_CLR         digitalLo(LCD_CS_GPIO, LCD_CS_PIN)

	#define LCD_DC_SET					digitalHi(LCD_DC_GPIO, LCD_DC_PIN)
	#define LCD_DC_CLR         digitalLo(LCD_DC_GPIO, LCD_DC_PIN)

#endif
//#define __SSD1306_WRITE_BYTE(DATA)	 spi_read_write_byte(LCD_SPI_PORT, DATA)


#define digitalHi(p, i)     { p->BSRR = i; }
#define digitalLo(p, i)     { p->BRR = i; }
#define digitalToggle(p, i) { p->ODR ^= i; }



typedef enum portMode_t {
    MODE_RX = 1 << 0,
    MODE_TX = 1 << 1,
    MODE_RXTX = MODE_RX | MODE_TX,
    MODE_SBUS = 1 << 2,
} portMode_t;



#include "drv_system.h"
#include "config.h"
#include "drv_spi.h"
//#include "drv_spi_dma.h"

#include "Fonts.h"
#include "SSD1306.h"
#include "lcd_Display.h"
#include "function.h"
//#include "queue.h"
#include "drv_can.h"
#include "can_queue.h"

#ifdef ENABLE_UART
	#include "drv_gpio.h"
	#include "drv_uart.h"
#endif
//#include "drv_timer.h"
////#include "rc_input.h"
////#include "ir_protocol.h"
//#include "queue.h"
//#include "drv_uart.h"
//#include "stm32f0xx_it.h"

//#include "drv_adc.h"
//#include "drv_pwm.h"
//#include "drv_keyInput.h"
//#include "drv_flash.h"
//#include "cli.h"
//#include "config.h"
//#include "cli.h"
