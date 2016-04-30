

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USE_FONTS_H
#define _USE_FONTS_H


/* Includes ------------------------------------------------------------------*/
//#include "LIB_Config.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern const uint8_t c_chFont1608[97][16];		//OLED용 작은 폰트
extern 	const unsigned char MS_Godic_VerySmall[98][14];	//8*14
extern const uint8_t c_chFont1206[97][12];

//extern const uint8_t c_chBmp4016[96];


//extern const uint8_t c_chFont1612[11][32];
//extern const uint8_t c_chFont3216[11][64];
//extern const uint8_t c_chSingal816[16];
//extern const uint8_t c_chMsg816[16];
//extern const uint8_t c_chBluetooth88[8];
//extern const uint8_t c_chBat816[16];
//extern const uint8_t c_chGPRS88[8];
//extern const uint8_t c_chAlarm88[8];
#ifdef FULL_FONT_USED			
	extern const unsigned char Font_MS_Gothic[97][16];		//ASCII_8X16_MS_Gothic
	extern  const unsigned char MS_Godic_Middle[101][64];	// 16*32
	extern 	const unsigned char MS_Godic_Big[99][144];	// 24*48
#endif

#endif

/*-------------------------------END OF FILE-------------------------------*/

