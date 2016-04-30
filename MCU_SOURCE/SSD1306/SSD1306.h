/**
  ******************************************************************************
  * @file    SSD1306.h
  * @author  Waveshare Team
  * @version 
  * @date    13-October-2014
  * @brief   This file contains all the functions prototypes for the SSD1306 OLED firmware driver.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SSD1306_H_
#define _SSD1306_H_

/* Includes ------------------------------------------------------------------*/
#include "MacroAndConst.h"

//#define FULL_FONT_USED			//폰트파일을 일부만 사용할 경우 비활성화

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

extern void ssd1306_clear_screen(uint8_t chFill);
extern void ssd1306_refresh_gram(void);
extern void ssd1306_draw_point(uint8_t chXpos, uint8_t chYpos, bool chPoint);
extern void ssd1306_fill_screen(uint8_t chXpos1, uint8_t chYpos1, uint8_t chXpos2, uint8_t chYpos2, bool chDot);
//extern void ssd1306_display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr, uint8_t chSize, bool FillMode);
//extern void ssd1306_display_num(uint8_t chXpos, uint8_t chYpos, uint32_t chNum, uint8_t chLen,uint8_t chSize);
//extern void ssd1306_display_string(uint8_t chXpos, uint8_t chYpos, const char *pchString, uint8_t chSize, bool FillMode);
//extern void ssd1306_draw_1206char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar);
//extern void ssd1306_draw_1608char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar);

extern void ssd1306_draw_bitmap(uint8_t chXpos, uint8_t chYpos, const uint8_t *pchBmp, uint8_t chWidth, uint8_t chHeight);

extern void ssd1306_init(void);

//extern void MS_Godic_VerySmall_Char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar);
//extern void MS_Godic_Middle_Char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar);
extern void TFT_PutCahr( uint8_t ch_asc, float postion_x, float postion_y);	// display a put Char TFT LCD 

extern void TFT_string( char *string, float postion_x, float postion_y);	// display a string on TFT LCD 

extern void TFT_CharVerySmall_System (uint8_t ch_asc, float postion_x, float postion_y);
extern void TFT_CharSmall_System (uint8_t ch_asc, float postion_x, float postion_y);
#ifdef FULL_FONT_USED			
	extern void TFT_CharMiddle_Godic (uint8_t ch_asc, float postion_x, float postion_y);
	extern void TFT_CharSmall_Godic (uint8_t ch_asc, float postion_x, float postion_y);
	extern void TFT_CharBig_Godic (uint8_t ch_asc, float postion_x, float postion_y);
	extern void TFT_Char_1208 (uint8_t ch_asc, float postion_x, float postion_y);
#endif
#endif

void draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, bool fill_point);
/*-------------------------------END OF FILE-------------------------------*/


