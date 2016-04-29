/**
  ******************************************************************************
  * @file    SSD1306.c 
  * @author  Waveshare Team
  * @version 
  * @date    13-October-2014
  * @brief   This file includes the OLED driver for SSD1306 display moudle
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
//#include "LIB_Config.h"
#include "board.h"
#include "SSD1306.h"
#include "Fonts.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SSD1306_CMD    0
#define SSD1306_DAT    1

#define SSD1306_WIDTH    128
#define SSD1306_HEIGHT   64


/* Private macro -------------------------------------------------------------*/

#if !defined(SH1106) && !defined(SSD1306)
	#warning Please select first the target OLED device(SH1106 or SSD1306) in your application!
	#define SSD1306  //define SSD1306 by default	
#endif

#if defined(SSD1306)
#define __SET_COL_START_ADDR() 	do { \
									ssd1306_write_byte(0x00, SSD1306_CMD); \
									ssd1306_write_byte(0x10, SSD1306_CMD); \
								} while(false)
#elif defined(SH1106)
#define __SET_COL_START_ADDR() 	do { \
									ssd1306_write_byte(0x02, SSD1306_CMD); \
									ssd1306_write_byte(0x10, SSD1306_CMD); \
								} while(false)
#endif								
/* Private variables ---------------------------------------------------------*/
static uint8_t s_chDispalyBuffer[128][8];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Writes an byte to the display data ram or the command register
  *         
  * @param  chData: Data to be writen to the display data ram or the command register
  * @param chCmd:  
  *                           0: Writes to the command register
  *                           1: Writes to the display data ram
  * @retval None
**/
								
								
								
void draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, bool fill_point) {
    short dx,dy;      /* The definition of the X Y axis increase the value of the variable */
    short temp;       

    if( x0 > x1 ){
			temp = x1;
			x1 = x0;
			x0 = temp;   
    }
    if( y0 > y1 ){
				temp = y1;
				y1 = y0;
				y0 = temp;   
    }
  
		dx = x1-x0;       
		dy = y1-y0;       
    if( dx == 0 ){
        do{ 
						ssd1306_draw_point(x0, y0,fill_point);
            y0++;
        }
        while( y1 >= y0 ); 
		return; 
    }
    if( dy == 0 ){
        do{
						ssd1306_draw_point(x0, y0,fill_point);
            x0++;
        }
        while( x1 >= x0 ); 
		return;
    }
	
    if( dx > dy ){
	    temp = 2 * dy - dx;                
        while( x0 != x1 ){
					ssd1306_draw_point(x0, y0,fill_point);
	        x0++;                        
	        if( temp > 0 ){
	            y0++;                    
	            temp += 2 * dy - 2 * dx; 
					}
           else{
							temp += 2 * dy;          
					}       
        }
				ssd1306_draw_point(x0, y0,fill_point);
    }  
    else {
				temp = 2 * dx - dy;                     
				while( y0 != y1 ){
						ssd1306_draw_point(x0, y0,fill_point);
						y0++;                 
						if( temp > 0 ){
									x0++;               
									temp+=2*dy-2*dx; 
							}
						else{
									temp += 2 * dy;
						}
				} 
				ssd1306_draw_point(x0, y0,fill_point);
		}

}

static void ssd1306_write_byte(uint8_t chData, uint8_t chCmd) 
{
#ifdef INTERFACE_4WIRE_SPI
#ifndef SPI_DMA_ENABLE	
	LCD_CS_CLR;
	
	if (chCmd) {
		LCD_DC_SET;
	} else {
		LCD_DC_CLR;
	}	
	SPI_SendByte(LCD_SPI_PORT, chData);

	LCD_DC_SET;
	LCD_CS_SET;
#else
		if (chCmd) {
				SPI_MemoryBuffer_WriteStart(LCD_CS_Control,LCD_RS_Control, LOW_CS, HIGH_RS, NULL, NULL);
		} 
		else {
				SPI_MemoryBuffer_WriteStart(LCD_CS_Control,LCD_RS_Control, LOW_CS, LOW_RS, NULL, NULL);
		}
		SPI_MemoryBuffer_WriteData((uint8_t)chData); 
		SPI_MemoryBuffer_WriteEnd(HIGH_CS, HIGH_RS);
#endif	
	
	
#elif defined(INTERFACE_3WIRE_SPI)
	
	uint8_t i;
	uint16_t hwData = 0;
	
	if (chCmd) {
		hwData = (uint16_t)chData | 0x0100;
	} else {
		hwData = (uint16_t)chData & ~0x0100;
	}
	
//	__SSD1306_CS_CLR();
	LCD_CS_CLR;
	for(i = 0; i < 9; i ++) {
//		__SSD1306_CLK_CLR();
			LCD_CLK_CLR;
		if(hwData & 0x0100) {
//			__SSD1306_DIN_SET();
				LCD_DIN_SET;
		} else {
//			__SSD1306_DIN_CLR();
				LCD_DIN_CLR;
		}
//		__SSD1306_CLK_SET();
			LCD_CLK_SET;
		hwData <<= 1;
	}
//	__SSD1306_CS_SET();
		LCD_CS_SET;
	
#elif defined(INTERFACE_IIC)
	
	iic_start();
	iic_write_byte(0x78);
	iic_wait_for_ack();
	if (chCmd) {
		iic_write_byte(0x40);
		iic_wait_for_ack();
	} else {
		iic_write_byte(0x00);
		iic_wait_for_ack();
	}
	iic_write_byte(chData);
	iic_wait_for_ack();
	
	iic_stop();
	
#endif
}   	  

/**
  * @brief  OLED turns on 
  *         
  * @param  None
  *         
  * @retval None
**/ 
void ssd1306_display_on(void)
{
#ifndef SPI_DMA_ENABLE
	ssd1306_write_byte(0x8D, SSD1306_CMD);  
	ssd1306_write_byte(0x14, SSD1306_CMD);  
	ssd1306_write_byte(0xAF, SSD1306_CMD);  
	#else
			SPI_MemoryBuffer_WriteStart(LCD_CS_Control,LCD_RS_Control, LOW_CS, LOW_RS, NULL, NULL);		//CMD
			SPI_MemoryBuffer_WriteData(0x8D); 
			SPI_MemoryBuffer_WriteData(0x14); 	
			SPI_MemoryBuffer_WriteData(0xAF); 	
			SPI_MemoryBuffer_WriteEnd(HIGH_CS, HIGH_RS);
	
	#endif
}
   
/**
  * @brief  OLED turns off
  *         
  * @param  None
  *         
  * @retval  None
**/
void ssd1306_display_off(void)
{
#ifndef SPI_DMA_ENABLE
	ssd1306_write_byte(0x8D, SSD1306_CMD);  
	ssd1306_write_byte(0x10, SSD1306_CMD); 
	ssd1306_write_byte(0xAE, SSD1306_CMD);  
#else
			SPI_MemoryBuffer_WriteStart(LCD_CS_Control,LCD_RS_Control, LOW_CS, LOW_RS, NULL, NULL);		//CMD
			SPI_MemoryBuffer_WriteData(0x8D); 
			SPI_MemoryBuffer_WriteData(0x10); 	
			SPI_MemoryBuffer_WriteData(0xAE); 	
			SPI_MemoryBuffer_WriteEnd(HIGH_CS, HIGH_RS);
#endif	
}

/**
  * @brief  Refreshs the graphic ram
  *         
  * @param  None
  *         
  * @retval  None
**/

void ssd1306_refresh_gram(void)
{
	uint8_t i, j;
#ifndef SPI_DMA_ENABLE

	for (i = 0; i < 8; i ++) {  
		ssd1306_write_byte(0xB0 + i, SSD1306_CMD);    
		__SET_COL_START_ADDR();      
		for (j = 0; j < 128; j ++) {
			ssd1306_write_byte(s_chDispalyBuffer[j][i], SSD1306_DAT); 
		}
	}   
#else
	for (i = 0; i < 8; i ++) {  
			SPI_MemoryBuffer_WriteStart(LCD_CS_Control,LCD_RS_Control, LOW_CS, LOW_RS, NULL, NULL);		//CMD
			SPI_MemoryBuffer_WriteData((uint8_t)0xB0 + i); 
			//set col start address
			SPI_MemoryBuffer_WriteData(0x02); 
			SPI_MemoryBuffer_WriteData(0x10); 
			SPI_MemoryBuffer_WriteEnd(HIGH_CS, HIGH_RS);
		
			SPI_MemoryBuffer_WriteStart(LCD_CS_Control,LCD_RS_Control, LOW_CS, HIGH_RS, NULL, NULL);		//DATA
			for (j = 0; j < 128; j ++) {
					SPI_MemoryBuffer_WriteData(s_chDispalyBuffer[j][i]); 
			}
			SPI_MemoryBuffer_WriteEnd(HIGH_CS, HIGH_RS);
	}   
	
#endif
}


/**
  * @brief   Clears the screen
  *         
  * @param  None
  *         
  * @retval  None
**/

void ssd1306_clear_screen(uint8_t chFill)  
{ 
	uint8_t i, j;
	
	for (i = 0; i < 8; i ++) {
		ssd1306_write_byte(0xB0 + i, SSD1306_CMD);
		__SET_COL_START_ADDR();
		for (j = 0; j < 128; j ++) {
			s_chDispalyBuffer[j][i] = chFill;
		}
	}
	
	ssd1306_refresh_gram();
}

/**
  * @brief  Draws a piont on the screen
  *         
  * @param  chXpos: Specifies the X position
  * @param  chYpos: Specifies the Y position
  * @param  chPoint: 0: the point turns off    1: the piont turns on 
  *         
  * @retval None
**/

void ssd1306_draw_point(uint8_t chXpos, uint8_t chYpos, bool chPoint)
{
	uint8_t chPos, chBx, chTemp = 0;
	
	if (chXpos > 127 || chYpos > 63) {
		return;
	}
	chPos = 7 - chYpos / 8; // 
	chBx = chYpos % 8;
	chTemp = 1 << (7 - chBx);
	
	if (chPoint) {
		s_chDispalyBuffer[chXpos][chPos] |= chTemp;
		
	} else {
		s_chDispalyBuffer[chXpos][chPos] &= ~chTemp;
	}
}
	  
/**
  * @brief  Fills a rectangle
  *         
  * @param  chXpos1: Specifies the X position 1 (X top left position)
  * @param  chYpos1: Specifies the Y position 1 (Y top left position)
  * @param  chXpos2: Specifies the X position 2 (X bottom right position)
  * @param  chYpos3: Specifies the Y position 2 (Y bottom right position)
  *         
  * @retval 
**/

void ssd1306_fill_screen(uint8_t chXpos1, uint8_t chYpos1, uint8_t chXpos2, uint8_t chYpos2, bool chDot)  
{  
	uint8_t chXpos, chYpos; 
	
	for (chXpos = chXpos1; chXpos <= chXpos2; chXpos ++) {
		for (chYpos = chYpos1; chYpos <= chYpos2; chYpos ++) {
			ssd1306_draw_point(chXpos, chYpos, chDot);
		}
	}	
	
	ssd1306_refresh_gram();
}



void TFT_PutCahr( uint8_t ch_asc, float postion_x, float postion_y)  {	// display a put Char TFT LCD 

		switch(font_set.fontType) {
			case VERY_SMALL:
						TFT_CharVerySmall_System(ch_asc, postion_x++, postion_y);
						break;
			case SYSTEM_SMALL:
						TFT_CharSmall_System(ch_asc, postion_x++, postion_y);
						break;
#ifdef FULL_FONT_USED			
			case GODIC_SMALL:
						TFT_CharSmall_Godic(ch_asc, postion_x++, postion_y);
						break;
			case GODIC_MIDDLE:
						TFT_CharMiddle_Godic(ch_asc, postion_x++, postion_y);
						break;
			case GODIC_BIG:
						TFT_CharBig_Godic(ch_asc, postion_x++, postion_y);
						break;
			case FONT_1608:
						TFT_Char_1208(ch_asc, postion_x++, postion_y);
						break;
#endif		
		}
}

void TFT_string( char *string, float postion_x, float postion_y)  {	// display a string on TFT LCD 

	while(*string != '\0') {			// display string
		
		switch(font_set.fontType) {
			case VERY_SMALL:
						TFT_CharVerySmall_System(*string, postion_x++, postion_y);
						break;
			case SYSTEM_SMALL:
						TFT_CharSmall_System(*string, postion_x++, postion_y);
						break;
#ifdef FULL_FONT_USED						
			case GODIC_SMALL:
						TFT_CharSmall_Godic(*string, postion_x++, postion_y);
						break;
			
			case GODIC_MIDDLE:
						TFT_CharMiddle_Godic(*string, postion_x++, postion_y);
						break;
			case GODIC_BIG:
						TFT_CharBig_Godic(*string, postion_x++, postion_y);
						break;
			case FONT_1608:
						TFT_Char_1208(*string, postion_x++, postion_y);
						break;
#endif				
		}
		
		string++;
	}
}

void TFT_CharVerySmall_System (uint8_t ch_asc, float postion_x, float postion_y) {
	uint16_t i;//, b;
	uint8_t j;//, b;
	uint8_t const Y_offset = font_set.yOffset;	
	uint8_t const X_offset = font_set.xOffset;	
//	uint8_t byteCount=0, size=0;

//	const uint8_t (*pFont)[14] =	MS_Godic_Small;
	const uint8_t (*pFont)[12] =	c_chFont1206;
	uint8_t const font_hight =	pFont[0][1];
	uint8_t const font_wide =	pFont[0][0];
	uint8_t const font_StartNo =pFont[0][2]-1;		//Çì´õ°ªÀ» -1 ÇØÁÜ
	
	
	uint8_t chXpos = postion_x*(font_wide-X_offset);
	uint8_t chYpos = postion_y*(font_hight-Y_offset);
	
	uint8_t chTemp = 0, chYpos0 = chYpos, chMode = 0;

	for (i = 0; i < 12; i ++) {
		chTemp = pFont[ch_asc - font_StartNo][i];
		for (j = 0; j < 8; j ++) {
			chMode = chTemp & 0x80? 1 : 0; 
			chMode ^=font_set.bgColor;
			ssd1306_draw_point(chXpos, chYpos, chMode);
			chTemp <<= 1;
			
			chYpos ++;
			if ((chYpos - chYpos0) == font_hight) {
				chYpos = chYpos0;
				chXpos ++;
				break;
			}
		}
	}
}

void TFT_CharSmall_System (uint8_t ch_asc, float postion_x, float postion_y) {
	uint16_t i;//, b;
	uint8_t j;//, b;
	uint8_t const Y_offset = font_set.yOffset;	
	uint8_t const X_offset = font_set.xOffset;	
//	uint8_t byteCount=0, size=0;

//	const uint8_t (*pFont)[14] =	MS_Godic_Small;
	const uint8_t (*pFont)[14] =	MS_Godic_VerySmall;
	uint8_t const font_wide =	pFont[0][0];
	uint8_t const font_hight =	pFont[0][1];
	uint8_t const font_StartNo =pFont[0][2]-1;		//Çì´õ°ªÀ» -1 ÇØÁÜ
	
	
	uint8_t chXpos = postion_x*(font_wide-X_offset);
	uint8_t chYpos = postion_y*(font_hight-Y_offset);
	
	uint8_t chTemp = 0, chXpos0 = chXpos, chMode = 0;

	for (i = 0; i < font_hight; i ++) {
		chTemp = pFont[ch_asc - font_StartNo][i];
		for (j = 0; j < 8; j ++) {
			chMode = chTemp & 0x01? 1 : 0; 
			chMode ^=font_set.bgColor;
			ssd1306_draw_point(chXpos, chYpos, chMode);
			chTemp >>= 1;
			
			chXpos ++;
			if ((chXpos - chXpos0) == font_wide) {
				chXpos = chXpos0;
				chYpos ++;
				break;
			}
		}
	}

}
#ifdef FULL_FONT_USED			
void TFT_CharBig_Godic (uint8_t ch_asc, float postion_x, float postion_y) {
	uint16_t i;//, b;
	uint8_t j;//, b;
	uint8_t const Y_offset = font_set.yOffset;	
	uint8_t const X_offset = font_set.xOffset;	

	const uint8_t (*pFont)[144] =	MS_Godic_Big;
	uint8_t const font_wide =	pFont[0][0];
	uint8_t const font_hight =	pFont[0][1];
	uint8_t const font_StartNo =pFont[0][2]-1;		//Çì´õ°ªÀ» -1 ÇØÁÜ
	
	uint8_t chXpos = postion_x*(font_wide-X_offset);
	uint8_t chYpos = postion_y*(font_hight-Y_offset);
	uint8_t chTemp = 0, chXpos0 = chXpos, chMode = 0;
	
	for (i = 0; i < 144; i ++) {
		chTemp = pFont[ch_asc - font_StartNo][i];
		for (j = 0; j < 8; j ++) {
			chMode = chTemp & 0x01? 1 : 0; 
			chMode ^=font_set.bgColor;
			ssd1306_draw_point(chXpos, chYpos, chMode);
			
			chTemp >>= 1;
			
			chXpos ++;
			if ((chXpos - chXpos0) == font_wide) {
				chXpos = chXpos0;
				chYpos ++;
				break;
			}
		}
	}
}
#endif
#ifdef FULL_FONT_USED			
void TFT_CharMiddle_Godic (uint8_t ch_asc, float postion_x, float postion_y) {
	uint16_t i;//, b;
	uint8_t j;//, b;
	uint8_t const Y_offset = font_set.yOffset;	
	uint8_t const X_offset = font_set.xOffset;	

//	const uint8_t (*pFont)[14] =	MS_Godic_Small;
	const uint8_t (*pFont)[64] =	MS_Godic_Middle;
	uint8_t const font_wide =	pFont[0][0];
	uint8_t const font_hight =	pFont[0][1];
	uint8_t const font_StartNo =pFont[0][2]-1;		//Çì´õ°ªÀ» -1 ÇØÁÜ
	
	
	uint8_t chXpos = postion_x*(font_wide-X_offset);
	uint8_t chYpos = postion_y*(font_hight-Y_offset);
	
	uint8_t chTemp = 0, chXpos0 = chXpos, chMode = 0;

	
	for (i = 0; i < 64; i ++) {
		chTemp = pFont[ch_asc - font_StartNo][i];
		for (j = 0; j < 8; j ++) {
			chMode = chTemp & 0x01? 1 : 0; 
			chMode ^=font_set.bgColor;
			ssd1306_draw_point(chXpos, chYpos, chMode);
			chTemp >>= 1;
			
			chXpos ++;
			if ((chXpos - chXpos0) == font_wide) {
				chXpos = chXpos0;
				chYpos ++;
				break;
			}
		}
	}
}
#endif

#ifdef FULL_FONT_USED			
void TFT_CharSmall_Godic (uint8_t ch_asc, float postion_x, float postion_y) {
	uint16_t i;//, b;
	uint8_t j;//, b;
	uint8_t const Y_offset = font_set.yOffset;	
	uint8_t const X_offset = font_set.xOffset;	
//	uint8_t byteCount=0, size=0;

//	const uint8_t (*pFont)[14] =	MS_Godic_Small;
	const uint8_t (*pFont)[16] =	Font_MS_Gothic;
	uint8_t const font_wide =	pFont[0][0];
	uint8_t const font_hight =	pFont[0][1];
	uint8_t const font_StartNo =pFont[0][2]-1;		//Çì´õ°ªÀ» -1 ÇØÁÜ
	
	
	uint8_t chXpos = postion_x*(font_wide-X_offset);
	uint8_t chYpos = postion_y*(font_hight-Y_offset);
	
	uint8_t chTemp = 0, chXpos0 = chXpos, chMode = 0;

	for (i = 0; i < font_hight; i ++) {
		chTemp = pFont[ch_asc - font_StartNo][i];
		for (j = 0; j < 8; j ++) {
			chMode = chTemp & 0x80? 1 : 0; 
			chMode ^=font_set.bgColor;
			ssd1306_draw_point(chXpos, chYpos, chMode);
			chTemp <<= 1;
			
			chXpos ++;
			if ((chXpos - chXpos0) == font_wide) {
				chXpos = chXpos0;
				chYpos ++;
				break;
			}
		}
	}

}
#endif

#ifdef FULL_FONT_USED			

void TFT_Char_1208 (uint8_t ch_asc, float postion_x, float postion_y) {
	uint16_t i;//, b;
	uint8_t j;//, b;
	uint8_t const Y_offset = font_set.yOffset;	
	uint8_t const X_offset = font_set.xOffset;	
//	uint8_t byteCount=0, size=0;

//	const uint8_t (*pFont)[14] =	MS_Godic_Small;
	const uint8_t (*pFont)[16] =	c_chFont1608;
	uint8_t const font_hight =	pFont[0][1];
	uint8_t const font_wide =	pFont[0][0];
	uint8_t const font_StartNo =pFont[0][2]-1;		//Çì´õ°ªÀ» -1 ÇØÁÜ
	
	
	uint8_t chXpos = postion_x*(font_wide-X_offset);
	uint8_t chYpos = postion_y*(font_hight-Y_offset);
	
	uint8_t chTemp = 0, chYpos0 = chYpos, chMode = 0;

	for (i = 0; i < 16; i ++) {
		chTemp = pFont[ch_asc - font_StartNo][i];
		for (j = 0; j < 8; j ++) {
			chMode = chTemp & 0x80? 1 : 0; 
			chMode ^=font_set.bgColor;
			ssd1306_draw_point(chXpos, chYpos, chMode);
			chTemp <<= 1;
			
			chYpos ++;
			if ((chYpos - chYpos0) == font_hight) {
				chYpos = chYpos0;
				chXpos ++;
				break;
			}
		}
	}
}
#endif





void ssd1306_draw_bitmap(uint8_t chXpos, uint8_t chYpos, const uint8_t *pchBmp, uint8_t chWidth, uint8_t chHeight)
{
	uint16_t i, j, byteWidth = (chWidth + 7) / 8;
	
    for(j = 0; j < chHeight; j ++){
        for(i = 0; i < chWidth; i ++ ) {
            if(*(pchBmp + j * byteWidth + i / 8) & (128 >> (i & 7))) {
                ssd1306_draw_point(chXpos + i, chYpos + j, 1);
            }
        }
    }
}



/**
  * @brief  SSd1306 initialization
  *         
  * @param  None
  *         
  * @retval None
**/
void ssd1306_init(void)
{

#ifdef INTERFACE_4WIRE_SPI	  
//	__SSD1306_CS_SET();   //CS set
//	__SSD1306_DC_CLR();   //D/C reset
//	__SSD1306_RES_SET();  //RES set
		LCD_CS_SET;
		LCD_DC_CLR;
		LCD_RST_SET;

#elif defined(INTERFACE_3WIRE_SPI)	
//	__SSD1306_CS_CLR();   //CS reset
//	__SSD1306_DC_CLR();   //D/C reset
//	__SSD1306_RES_SET();  //RES set
		LCD_CS_CLR;
		LCD_DC_CLR;
		LCD_RST_SET;
	
#elif defined(INTERFACE_IIC)	  
//	__SSD1306_CS_CLR();   //CS reset
//	__SSD1306_DC_CLR();   //D/C reset
//	__SSD1306_RES_SET();  //RES set
		LCD_CS_CLR;
		LCD_DC_CLR;
		LCD_RST_SET;

#endif

	ssd1306_write_byte(0xAE, SSD1306_CMD);//--turn off oled panel
	ssd1306_write_byte(0x00, SSD1306_CMD);//---set low column address
	ssd1306_write_byte(0x10, SSD1306_CMD);//---set high column address
	ssd1306_write_byte(0x40, SSD1306_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	ssd1306_write_byte(0x81, SSD1306_CMD);//--set contrast control register
	ssd1306_write_byte(0xCF, SSD1306_CMD);// Set SEG Output Current Brightness
	ssd1306_write_byte(0xA1, SSD1306_CMD);//--Set SEG/Column Mapping     
	ssd1306_write_byte(0xC0, SSD1306_CMD);//Set COM/Row Scan Direction   
	ssd1306_write_byte(0xA6, SSD1306_CMD);//--set normal display
	ssd1306_write_byte(0xA8, SSD1306_CMD);//--set multiplex ratio(1 to 64)
	ssd1306_write_byte(0x3f, SSD1306_CMD);//--1/64 duty
	ssd1306_write_byte(0xD3, SSD1306_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	ssd1306_write_byte(0x00, SSD1306_CMD);//-not offset
	ssd1306_write_byte(0xd5, SSD1306_CMD);//--set display clock divide ratio/oscillator frequency
	ssd1306_write_byte(0x80, SSD1306_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	ssd1306_write_byte(0xD9, SSD1306_CMD);//--set pre-charge period
	ssd1306_write_byte(0xF1, SSD1306_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	ssd1306_write_byte(0xDA, SSD1306_CMD);//--set com pins hardware configuration
	ssd1306_write_byte(0x12, SSD1306_CMD);
	ssd1306_write_byte(0xDB, SSD1306_CMD);//--set vcomh
	ssd1306_write_byte(0x40, SSD1306_CMD);//Set VCOM Deselect Level
	ssd1306_write_byte(0x20, SSD1306_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	ssd1306_write_byte(0x02, SSD1306_CMD);//
	ssd1306_write_byte(0x8D, SSD1306_CMD);//--set Charge Pump enable/disable
	ssd1306_write_byte(0x14, SSD1306_CMD);//--set(0x10) disable
	ssd1306_write_byte(0xA4, SSD1306_CMD);// Disable Entire Display On (0xa4/0xa5)
	ssd1306_write_byte(0xA6, SSD1306_CMD);// Disable Inverse Display On (0xa6/a7) 
	ssd1306_write_byte(0xAF, SSD1306_CMD);//--turn on oled panel
	
	ssd1306_clear_screen(0x00);
}

/*-------------------------------END OF FILE-------------------------------*/

/*
static uint32_t pow(uint8_t m, uint8_t n)
{
	uint32_t result = 1;	 
	while(n --) result *= m;    
	return result;
}	
*/

//void ssd1306_display_num(uint8_t chXpos, uint8_t chYpos, uint32_t chNum, uint8_t chLen, uint8_t chSize)
//{         	
//	uint8_t i;
//	uint8_t chTemp, chShow = 0;
//	
//	for(i = 0; i < chLen; i ++) {
//		chTemp = (chNum / pow(10, chLen- i -1 )) ;
//		chTemp %=10;
////		chTemp = (chNum / pow(10, chLen - i - 1)) % 10;
//		if(chShow == 0 && i < (chLen - 1)) {
//			if(chTemp == 0) {
//				ssd1306_display_char(chXpos + (chSize / 2) * i, chYpos, ' ', chSize, 1);
//				continue;
//			} else {
//				chShow = 1;
//			}	 
//		}
//	 	ssd1306_display_char(chXpos + (chSize / 2) * i, chYpos, chTemp + '0', chSize, 1); 
//	}
//} 


///**
//  * @brief  Displays a string on the screen
//  *         
//  * @param  chXpos: Specifies the X position
//  * @param  chYpos: Specifies the Y position
//  * @param  pchString: Pointer to a string to display on the screen 
//  *         
//  * @retval  None
//**/
//void ssd1306_display_string(uint8_t chXpos, uint8_t chYpos, const char *pchString, uint8_t chSize, bool chMode)
//{
//    while (*pchString != '\0') {       
//        if (chXpos > (SSD1306_WIDTH - chSize / 2)) {
//			chXpos = 0;
//			chYpos += chSize;
//			if (chYpos > (SSD1306_HEIGHT - chSize)) {
//				chYpos = chXpos = 0;
//				ssd1306_clear_screen(0x00);
//			}
//		}
//		
//        ssd1306_display_char(chXpos, chYpos, *pchString, chSize, chMode);
//        chXpos += chSize / 2;
//        pchString ++;
//    }
//}


///**
//  * @brief Displays one character at the specified position    
//  *         
//  * @param  chXpos: Specifies the X position
//  * @param  chYpos: Specifies the Y position
//  * @param  chSize: 
//  * @param  chMode
//  * @retval 
//**/
//void ssd1306_display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr, uint8_t chSize, bool FillMode)
//{      	
//	uint8_t i, j;
//	uint8_t chTemp, chYpos0 = chYpos;
//	
//	chChr = chChr - ' ';				   
//    for (i = 0; i < chSize; i ++) {   
//		if (chSize == 12) {
//			if (FillMode) {
//				chTemp = c_chFont1206[chChr][i];
//			} else {
//				chTemp = ~c_chFont1206[chChr][i];
//			}
//		} 
//		else {
//			if (FillMode) {
//				chTemp = c_chFont1608[chChr][i];
//			} else {
//				chTemp = ~c_chFont1608[chChr][i];
//			}
//		}
//		
//        for (j = 0; j < 8; j ++) {
//			if (chTemp & 0x80) {
//				ssd1306_draw_point(chXpos, chYpos, 1);
//			} else {
//				ssd1306_draw_point(chXpos, chYpos, 0);
//			}
//			chTemp <<= 1;
//			chYpos ++;
//			
//			if ((chYpos - chYpos0) == chSize) {
//				chYpos = chYpos0;
//				chXpos ++;
//				break;
//			}
//		}  	 
//    } 
//}


//void ssd1306_draw_1206char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar)
//{
//	uint8_t i, j;
//	uint8_t chTemp = 0, chYpos0 = chYpos, chMode = 0;

//	for (i = 0; i < 12; i ++) {
//		chTemp = c_chFont1206[chChar - 0x20][i];
//		for (j = 0; j < 8; j ++) {
//			chMode = chTemp & 0x80? 1 : 0; 
//			ssd1306_draw_point(chXpos, chYpos, chMode);
//			chTemp <<= 1;
//			chYpos ++;
//			if ((chYpos - chYpos0) == 12) {
//				chYpos = chYpos0;
//				chXpos ++;
//				break;
//			}
//		}
//	}
//}


//void ssd1306_draw_1608char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar)
//{
//	uint8_t i, j;
//	uint8_t chTemp = 0, chYpos0 = chYpos, chMode = 0;

//	for (i = 0; i < 16; i ++) {
//		chTemp = c_chFont1608[chChar - 0x20][i];
//		for (j = 0; j < 8; j ++) {
//			chMode = chTemp & 0x80? 1 : 0; 
//			ssd1306_draw_point(chXpos, chYpos, chMode);
//			chTemp <<= 1;
//			chYpos ++;
//			if ((chYpos - chYpos0) == 16) {
//				chYpos = chYpos0;
//				chXpos ++;
//				break;
//			}
//		}
//	}
//}
