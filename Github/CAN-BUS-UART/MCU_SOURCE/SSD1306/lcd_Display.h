#pragma once

#define MAXIMUM_VALUE_STRING_BUFFER 20		//LCD에 표시되는 VLAUE값을 문자열로 변환할때 사용하는 버퍼 크기
#define OVER_RANGE_SYMBOL  '*'

#define DEFAULT_LCD_DISPLAY_PAGE	AF_MEASURING
//#define DISPLAY_START_ROW	1.2
#define MAX_DISPLAY_ROW_SIZE		4
#define MAX_DISPLAY_COUNT			30//CONFIG_COUNT

//typedef enum {
//    VAR_UINT8,
//    VAR_INT8,
//    VAR_UINT16,
//    VAR_INT16,
//    VAR_UINT32,
//    VAR_INT32,
//    VAR_FLOAT
//} vartype_e;




typedef enum {
		VERY_SMALL,
		SYSTEM_SMALL,
		GODIC_SMALL,
		GODIC_MIDDLE,
		GODIC_BIG,
		FONT_1608,
} FontType;

typedef enum {
    NOT_FILL,
    FILL,
} FillType;


typedef enum {
    AF_MEASURING,
		OXY_SENSOR_STAT,
    AF_STATUS,
    ROOM_SENSOR,
		CONFIG,
} DISPype;
#define MMAXIMUM_LCD_DISPLAY_PAGE 	(CONFIG+1) //5  	//표시할 page 최대 갯수를 기입한다.



typedef struct value_disp_t {
		float  posion_x;
		float	posion_y;
		uint8_t reflashTime;
		void * value;
		uint32_t div;
		uint8_t pointUpValue;
		uint8_t pointDownValue;
		uint8_t type;
		uint8_t 	valueFontType;
		bool bgType;
//		uint16_t  valueFontColor;
//		uint16_t  valueFontBColor;
		float dispMin;
		float dispMax;
		char unitChar1;
		char unitChar2;
		char * unitString;
//		uint16_t  unitFontColor;
//		uint16_t  unitFontBColor;
		bool uintBgType;
		uint8_t 	unitFontType;
		void (* function) (void);
} value_disp_t;

typedef struct name_disp_t {
		float  posion_x;
		float	posion_y;
//		uint8_t reflashTime;
		char * string;
		uint8_t 	valueFontType;
		bool bgType;
	
	uint8_t colum_size;
		void (* function) (void);
	
}name_disp_t;



typedef struct title_disp_t {
		float  posion_x;
		float	posion_y;
		char * title;
		uint8_t 	title_FT;
		bool title_BT;
		uint8_t colum_size;
	
		uint8_t range_FT;
		uint8_t range_BG;
		char * unit;
	
//		char * name;
		uint8_t 	value_FT;
		bool value_BT;
		
		uint8_t add_no;
//		void (* function) (void);
			value_disp_t  * config;
}title_disp_t;





typedef struct disp_page_t {
		int8_t disp_page_no;
		uint8_t disp_item_size;
//		bool page_init_flag;
		value_disp_t * disp_item;
		name_disp_t  * value_name;
//		void (* init_func)(void);
		uint8_t scroll_posion;
		uint8_t indicater_max_page_size;
	
		uint8_t cursor_x_posion;
		uint8_t cursor_y_posion;
	
		int8_t config_page_no;
	
		uint8_t config_max_page_size;
		bool value_change_mode;	
	
	
}disp_page_t;


typedef struct Font_set_t
{
	bool bgColor;
	float fontPosionX;
	float fontPosionY;
	uint8_t fontType;
	uint8_t xOffset;
	uint8_t yOffset;
		

} Font_set_t;

extern Font_set_t font_set;
extern value_disp_t 	config_value_set[];
extern disp_page_t disp_page;
extern title_disp_t  lcd_lay_out_display[];
	

bool LCD_Value_Display_set(value_disp_t val, uint8_t number, bool reset_flag);
void LCD_Value_Display(bool reset_flag);
void LCD_update(void);
//void sensor_lay_out_display (void);
//void LCD_disp_page_init(void);
//void LCD_disp_page_control(bool reset);
void LCD_string_Display_set(name_disp_t  * str);

//void LCD_Config_Value_Display_set(value_disp_t * in_val);
//void LCD_Config_Display(bool reset_flag) ;

//void display_page_control (void);
//void config_page_control (void);

//void display_config_set_display(bool );
//void config_value_change(title_disp_t * title_t, bool reset);

void title_display_string(title_disp_t * title_t);
void display_value_zeor_process(bool on_off);
void layout_display_string(void) ;
