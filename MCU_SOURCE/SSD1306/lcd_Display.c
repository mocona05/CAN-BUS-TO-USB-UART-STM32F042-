#include "board.h"

Font_set_t font_set;
disp_page_t disp_page;

#define NAME_STRING_BUFFER_SIZE  30
#define SYSTEM_LOOP_TIME_DISPLAY
#ifdef SYSTEM_LOOP_TIME_DISPLAY
void cycleTimmerClear(void) {
	sys.cycleTime=0;
	
}
#endif



title_disp_t  lcd_lay_out_display[]={
	{0,0, "VR&ST GENERATOR ", SYSTEM_SMALL, FILL, },
	{0, 1.4, "V", VERY_SMALL, FILL, },
	{0, 2.4, "R", VERY_SMALL, FILL, },
	
	{0, 3.65, "S", VERY_SMALL, FILL, },
	{0, 4.65, "T", VERY_SMALL, FILL, },
	};
#define LAYOUT_COUNT (sizeof(lcd_lay_out_display) / sizeof(lcd_lay_out_display[0]))


//name_disp_t  measuring_name_set[]={
//	{0, 1.2, "Lambda  :", VERY_SMALL, NOT_FILL,21 },
//	{0, 2.2, "Air/Fuel:", VERY_SMALL, NOT_FILL,21, },
//	{0, 3.2, "Oxygen  :", VERY_SMALL, NOT_FILL,21, },
//	{0, 4.2, "Pumping :", VERY_SMALL, NOT_FILL,21, },
//	
//};

value_disp_t 	lcd_Disp_set[] = {
		{0, 0,50,&rxd_data.imu1_roll , 1000,3,3,VAR_INT32, 	VERY_SMALL, NOT_FILL, -360, 360,  NULL,NULL, "[R]", NOT_FILL,VERY_SMALL},
		{0, 1,50,&rxd_data.imu1_pitch , 1000,3,3,VAR_INT32, 	VERY_SMALL, NOT_FILL, -360, 360,  NULL,NULL, "[P]", NOT_FILL,VERY_SMALL},
		{0, 2,50,&rxd_data.imu1_yaw , 1000,3,3,VAR_INT32, 	VERY_SMALL, NOT_FILL, -360, 360,  NULL,NULL, "[Y]", NOT_FILL,VERY_SMALL},

		{11, 0,50,&rxd_data.imu2_roll , 1000,3,3,VAR_INT32, 	VERY_SMALL, NOT_FILL, -360, 360,  NULL,NULL, "", NOT_FILL,VERY_SMALL},
		{11, 1,50,&rxd_data.imu2_pitch , 1000,3,3,VAR_INT32, 	VERY_SMALL, NOT_FILL, -360, 360,  NULL,NULL, "", NOT_FILL,VERY_SMALL},
		{11, 2,50,&rxd_data.imu2_yaw , 1000,3,3,VAR_INT32, 	VERY_SMALL, NOT_FILL, -360, 360,  NULL,NULL, "", NOT_FILL,VERY_SMALL},

		
		{0, 3,50,&rxd_data.light_adc , 1,5,0,VAR_UINT16, 	VERY_SMALL, NOT_FILL, 0, 0xFFF,  NULL,NULL, "L", NOT_FILL,VERY_SMALL},
		{5, 3,50,&rxd_data.light_differen , 1,5,0,VAR_INT16, 	VERY_SMALL, NOT_FILL, -32767, 32767,  NULL,NULL, "D", NOT_FILL,VERY_SMALL},

		{0, 4,50,&rxd_data.shutter_status , 1,1,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 1,  NULL,NULL, "S", NOT_FILL,VERY_SMALL},
		{3, 4,50,&rxd_data.focus_status , 1,1,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 1,  NULL,NULL, "F", NOT_FILL,VERY_SMALL},
		{6, 4,50,&rxd_data.capture_complit_falg , 1,1,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 1,  NULL,NULL, "C", NOT_FILL,VERY_SMALL},
		{9, 4,50,&rxd_data.capture_time_out_falg , 1,1,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 1,  NULL,NULL, "T", NOT_FILL,VERY_SMALL},
		
		{11, 3,50,&rxd_data.trig_count , 1,4,0,VAR_UINT16, 	VERY_SMALL, NOT_FILL, 0, 0xFFFF,  NULL,NULL, "t", NOT_FILL,VERY_SMALL},
		{16, 3,50,&rxd_data.photo_count , 1,4,0,VAR_UINT16, 	VERY_SMALL, NOT_FILL, 0, 0xFFFF,  NULL,NULL, "o", NOT_FILL,VERY_SMALL},
		
		{15, 4.5,100,&rxd_data.sensor_board_loop_time_us , 1,1,0,VAR_UINT16, 	VERY_SMALL, NOT_FILL, 0, 9999,  NULL,NULL, "ms", NOT_FILL,VERY_SMALL},
		
//		{12, 1.3,50,&sys.offset_voltage_mv, 1000,2,2,VAR_INT16, 	VERY_SMALL, NOT_FILL, -20, 20,  NULL,NULL, "[V]", NOT_FILL,VERY_SMALL},
//		{2, 2.3,50,&sys.vr_gen_rpm, 1,4,0,VAR_UINT16, 	VERY_SMALL, NOT_FILL, 0, 8000,  NULL,NULL, "[rpm]", NOT_FILL,VERY_SMALL},
////		{12, 2.3,50,&sys.DAC_gain ,1, 1,3,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, -1, 1, NULL,NULL,"[X]", NOT_FILL,VERY_SMALL},
//		{13, 2.3,50,&sys.DAC_p_p_volt ,1000, 2,2,VAR_INT32, 	VERY_SMALL, NOT_FILL, 0, 40, NULL,NULL,"[V]", NOT_FILL,VERY_SMALL},
//		{2, 3.5,50,&sys.st_duty_100x,100, 3,1,VAR_UINT16, VERY_SMALL, NOT_FILL, 0, 100, NULL,NULL,"[%]", NOT_FILL,VERY_SMALL},
//		{13, 3.5,50,&sys.st_freq_100x ,100, 2,1,VAR_UINT16, 	VERY_SMALL, NOT_FILL, 0, 99, NULL,NULL,"[Hz]", NOT_FILL,VERY_SMALL},
//		{2, 4.5,100,&sys.st_mVrms,1000, 2,2,VAR_UINT16, VERY_SMALL, NOT_FILL, 0, 45, NULL,NULL,"[V]", NOT_FILL,VERY_SMALL},
//		
//	{11, 4.5,100,&sys.cycleTime, 1000, 3,1,VAR_UINT32, VERY_SMALL, NOT_FILL, 0, 999, NULL,NULL,"ms", NOT_FILL,VERY_SMALL, cycleTimmerClear},
//		{19, 4.5,100,&sys.adj_mode,1, 1,0,VAR_UINT8, VERY_SMALL, FILL, 0, 45, NULL,NULL,"M", FILL,VERY_SMALL},
	};		
#define DISPLAY_COUNT (sizeof(lcd_Disp_set) / sizeof(lcd_Disp_set[0]))
	

void layout_display_string(void) {
	uint8_t i =0;
		for(i=0 ; i < LAYOUT_COUNT ; i++) {
			title_display_string(&lcd_lay_out_display[i]);
	}

}

void title_display_string(title_disp_t * title_t) {
			font_set.bgColor = title_t->title_BT;
			font_set.fontType = title_t->title_FT;
			font_set.fontPosionX = title_t->posion_x;
			font_set.fontPosionY = title_t->posion_y;
			TFT_string(title_t->title, font_set.fontPosionX,font_set.fontPosionY); //스크롤 위치부터 최대 item size 까지만 표시
}




void LCD_Value_Display(bool reset_flag) {
		static uint8_t i=0;
//		uint8_t disp_max_row  = (MAX_DISPLAY_ROW_SIZE> disp_page.disp_item_size)? disp_page.disp_item_size:MAX_DISPLAY_ROW_SIZE;
//		if(reset_flag) {		//스크롤 위치가 다를경우 
//						i=disp_page.scroll_posion;
//						LCD_string_Display_set(&disp_page.value_name[disp_page.scroll_posion]);
//						LCD_Value_Display_set(disp_page.disp_item[disp_page.scroll_posion], 0, true);
//						LCD_update();
//			
//		}
//				LCD_Value_Display_set(disp_page.disp_item[i], i, false);		//페이지 번호에 따라 다른 화면을 표시
//				i = (i < disp_max_row + disp_page.scroll_posion -1)? i+1:disp_page.scroll_posion;				//스크롤 위치부터 최대 item size 까지만 표시
				LCD_Value_Display_set(lcd_Disp_set[i], i, false);		//페이지 번호에 따라 다른 화면을 표시
				i = (i < DISPLAY_COUNT-1)?i+1:0;	
			LCD_update();
//	
//			static uint8_t i=0;
//				LCD_Value_Display_set(lcd_Disp_set[i], 0, i);
//				i = (i < DISPLAY_COUNT-1)?i+1:0;	
}

void LCD_update(void) {
	static uint32_t beforTime =0;
	uint32_t timeNow;
	
	timeNow = micros();

//    if ( (uint64_t)beforTime + 100 <   timeNow && timeNow > beforTime) {	//100ms 경과 않됨?
    if ( (int64_t)timeNow - beforTime  -LCD_UPDATE_SPEED  <  0 &&  timeNow >= beforTime) {	//100ms 경과 않됨?
			return ;
		}
		beforTime= timeNow;	
			ssd1306_refresh_gram();		//LCD 표시값을 UPDATE.
}


bool LCD_Value_Display_set(value_disp_t val, uint8_t number, bool reset_flag) {
//	#define MAX_VALUE_STRING			20
//		int8_t trim=0;
		static bool display_area[MAX_DISPLAY_COUNT] = {false, };
		static uint32_t displayTime[MAX_DISPLAY_COUNT]={0,};
		static bool startFlag[MAX_DISPLAY_COUNT]={0,};
		static uint8_t beforStrLens[MAX_DISPLAY_COUNT]={0,};
		static char beforValueString[MAX_DISPLAY_COUNT][MAXIMUM_VALUE_STRING_BUFFER]={NULL,};
		
		double value=0;
		uint8_t max_string_lengs ;
		int8_t clear_string_lengs;
		float driftPosion=0;
		uint8_t value_string_lengs=0;
		uint32_t timeNow=0;
		void (*Func) (void);
		static char  value_str_buff[MAXIMUM_VALUE_STRING_BUFFER];
		static char  clear_str_buff[MAXIMUM_VALUE_STRING_BUFFER];
		uint8_t i=0;
		float unit_str_x_posion=0;
		timeNow = millis();
		
		if(reset_flag) {
				memset(display_area, false, MAX_DISPLAY_COUNT );
				memset(displayTime, 0, sizeof(displayTime[0])* MAX_DISPLAY_COUNT);
				memset(startFlag, 0, MAX_DISPLAY_COUNT);
				memset(beforStrLens, 0, MAX_DISPLAY_COUNT);
				memset(beforValueString, NULL, MAX_DISPLAY_COUNT * MAXIMUM_VALUE_STRING_BUFFER);
				memset(value_str_buff,NULL, MAXIMUM_VALUE_STRING_BUFFER);
				memset(clear_str_buff, NULL, MAXIMUM_VALUE_STRING_BUFFER);		//공란으로 클리어
			
		}
		
		
    if ( (int64_t)timeNow -displayTime[number] -val.reflashTime <  0 && timeNow >= displayTime[number]) {
				return false;
		}
		displayTime[number]= timeNow;
		//최대 표시 문자열 길이를 계산
		max_string_lengs = (val.pointDownValue >0)?val.pointUpValue+ val.pointDownValue+1 :val.pointUpValue+ val.pointDownValue;		//최대 표시문장 길이를 계산
		max_string_lengs = (val.dispMin <0)?max_string_lengs+1:max_string_lengs;		//값이 음수일경우 부호자릿수를 +1 해줌.  <<--2015년 6월3일 추가
		
		unit_str_x_posion = max_string_lengs+val.posion_x;
		if(!startFlag[number]){

				startFlag[number]=1;
				font_set.bgColor =val.uintBgType;
				font_set.fontType  =val.unitFontType;
				if(val.unitChar1 != NULL) {		//처음 호출될경우 Unit 기호를  표시 한다.
						TFT_PutCahr(val.unitChar1, unit_str_x_posion , val.posion_y- disp_page.scroll_posion);
						unit_str_x_posion++;
				}
				if(val.unitChar2 != NULL) {		//처음 호출될경우 Unit 기호를  표시 한다.
						TFT_PutCahr(val.unitChar2, unit_str_x_posion , val.posion_y- disp_page.scroll_posion);
						unit_str_x_posion++;
				}
				if(val.unitString != NULL) {		//처음 호출될경우 Unit string을 표시 한다.
						TFT_string(val.unitString, unit_str_x_posion, val.posion_y - disp_page.scroll_posion);		//문자열 크기에 따라서 표시위치를 능동적으로 조절						
				}
		}
		
		switch(val.type) {
				case VAR_UINT8:
							value = (double)(*(uint8_t *)val.value)/val.div;
							break;
				case VAR_INT8:
							value = (double)(*(char *)val.value)/val.div;
							break;
				case VAR_UINT16:
							value = (double)(*(uint16_t *)val.value)/val.div;
							break;
				case VAR_INT16:
							value = (double)(*(short *)val.value)/val.div;
							break;
				case VAR_UINT32:
							value = (double)(*(uint32_t *)val.value)/val.div;
							break;
				case VAR_INT32:
							value = (double)(*(int32_t *)val.value)/val.div;
							break;
				 case VAR_FLOAT:
							value = (double)(*(float *)val.value)/val.div;
							break;
		}
		if(val.function != NULL ) {
				Func = val.function;		
				Func();//관련된 함수 호출
		}
		memset(value_str_buff,NULL, MAXIMUM_VALUE_STRING_BUFFER);
		memset(clear_str_buff, NULL, MAXIMUM_VALUE_STRING_BUFFER);		//공란으로 클리어
		if(val.dispMax>= value && val.dispMin <= value) {		//범위 내일경우
				floatToString(value_str_buff, value,val.pointDownValue,max_string_lengs);
				value_string_lengs = strlen(value_str_buff);		//표시할 값에 대한 문자열 길이를 계산
				driftPosion =max_string_lengs -value_string_lengs;		// 오른쪽 정렬시 드리프트 되는 값
					if(max_string_lengs >= value_string_lengs) {//최대 문자열보다 작거나 같을 경우만 표시
							font_set.bgColor = val.bgType;
							font_set.fontType  =val.valueFontType;
						
							clear_string_lengs = beforStrLens[number]-value_string_lengs;		//이전에 표시한 스트링 크기와 비교하여 지울 문자열  길이를 계산
							clear_string_lengs =(clear_string_lengs>0)?clear_string_lengs:0;		//지울 문자열 길이가 음수일경우  0으로 처리
								
							if(clear_string_lengs >0){		//문자열 길이가 변경되어 공란으로 표시할 자릿수가 있을경우
									memset(clear_str_buff, ' ', clear_string_lengs);	//차이나는 자릿수 만큼 공란을 버퍼에 복사함.
									TFT_string(clear_str_buff, driftPosion-clear_string_lengs+val.posion_x, val.posion_y - disp_page.scroll_posion);	//줄어든 문자열 만큼 공백문자를 표시하여 지움
							}
		#if 1		//변경되눈 문자열만 검사해 update 하는 방식 LCD를 POLLING 방식으로 제어시 유리	
						

								if( display_area[number] == false) {
											TFT_string(value_str_buff, driftPosion+ val.posion_x, val.posion_y - disp_page.scroll_posion);	//문자열 길이에 따라서 오른쪽 정렬하여 표시
											display_area[number] =true;
								}
								else {
											 for(i=0; i<value_string_lengs;i++) {		//이전문장과 현재 생성된 문장을 비교하여 다른 부분만 업데이트
												 
													 if( value_str_buff[i] != beforValueString[number][i+clear_string_lengs]) {		//이전문장과 길이가 다를경우 들여쓰기된것을 감안하여 비교함  
																TFT_PutCahr(value_str_buff[i], clear_string_lengs+i+val.posion_x + driftPosion , val.posion_y - disp_page.scroll_posion);
													 }
											 }
								}
		#else		//모든 문자열을 새로 업데이트 (LCD를 SPI DMA를 사용시는 모두 업데이트 하는것이 빠를수도 있음.)
							TFT_string(value_str_buff, driftPosion+ val.posion_x, val.posion_y - disp_page.scroll_posion);	//문자열 길이에 따라서 오른쪽 정렬하여 표시
		#endif						 
							beforStrLens[number] = value_string_lengs;
				}
				strncpy((char *)&beforValueString[number], value_str_buff, value_string_lengs);	//비교를 위해 표시 문자열을 버퍼로 복사
		}
		else {		//표시 범위내가 아닐경우
				display_area[number] =false;
				font_set.bgColor = val.bgType;
				font_set.fontType  =val.valueFontType;
				memset(value_str_buff,OVER_RANGE_SYMBOL,val.pointUpValue);
				if(val.pointDownValue>0) {
						strcat(value_str_buff,".");
						memset(value_str_buff+strlen(value_str_buff) ,OVER_RANGE_SYMBOL,val.pointDownValue);
				}
				strncpy((char *)&beforValueString[number], value_str_buff, value_string_lengs);	//비교를 위해 표시 문자열을 버퍼로 복사
				value_string_lengs = strlen(value_str_buff);		//표시할 값에 대한 문자열 길이를 계산
				beforStrLens[number] = value_string_lengs;
				driftPosion =max_string_lengs -value_string_lengs;		// 오른쪽 정렬시 드리프트 되는 값
				TFT_string(value_str_buff,  driftPosion + val.posion_x, val.posion_y - disp_page.scroll_posion);	//표시 범위내가 아니므로 공백문자 표시
			
		}
		return true;
}


void LCD_string_Display_set(name_disp_t  * str) {
	uint8_t i =0;
	name_disp_t * pStr_set = str;
	char str_buffer[NAME_STRING_BUFFER_SIZE];
	uint8_t disp_max_row  = (MAX_DISPLAY_ROW_SIZE> disp_page.disp_item_size)? disp_page.disp_item_size:MAX_DISPLAY_ROW_SIZE;
	for(i=0; i < disp_max_row; i++) {
				uint8_t string_lenth=strlen(pStr_set->string);		//문자열 길이 계산
				memset(str_buffer,NULL, NAME_STRING_BUFFER_SIZE);		//버퍼를 지움
				strcat(str_buffer, pStr_set->string);
				memset(str_buffer + string_lenth, ' ', pStr_set->colum_size - string_lenth);		//표시 행의 스트링 이후의 컬럼의  공란을 지움.
				font_set.bgColor  = pStr_set->bgType;
				font_set.fontType = pStr_set->valueFontType;
//				TFT_string(pStr_set->string,pStr_set->posion_x,pStr_set->posion_y- disp_page.scroll_posion); //스크롤 위치부터 최대 item size 까지만 표시
				TFT_string(str_buffer,pStr_set->posion_x,pStr_set->posion_y- disp_page.scroll_posion); //스크롤 위치부터 최대 item size 까지만 표시
				if(pStr_set->function != NULL) {
					void (*Func) (void);
					Func = pStr_set->function;		
					Func();//관련된 함수 호출
				}
				pStr_set++;
	}
}


void display_value_zeor_process(bool on_off) {
	static float vr_freq, vr_gain;
	static uint16_t vr_offset, st_duty, st_freq, st_mVrms, vr_rpm;
	
	if(on_off) {
				vr_freq = sys.waveform_freq;
				vr_offset = sys.offset_voltage_mv;
				vr_rpm = sys.vr_gen_rpm;
				vr_gain = sys.DAC_gain;
				st_duty = sys.st_duty_100x;
				st_freq = sys.st_freq_100x;
				st_mVrms = sys.st_mVrms;
		
				sys.waveform_freq =0;
				sys.offset_voltage_mv=0;
				sys.vr_gen_rpm=0;
				sys.DAC_gain=0;
				sys.st_duty_100x=0;
				sys.st_freq_100x=0;
				sys.st_mVrms=0;
				sys.DAC_p_p_volt = 0;
		
	}
	else {
				sys.waveform_freq= vr_freq;
				sys.offset_voltage_mv = vr_offset;
				sys.vr_gen_rpm = vr_rpm;
				sys.DAC_gain = vr_gain;
				sys.st_duty_100x = st_duty;
				sys.st_freq_100x = st_freq;
				sys.st_mVrms = st_mVrms;
		
//				sys.DAC_p_p_volt = 	 sys.DAC_gain * MAX_P_P_VOLTAGE_MV;
	}
}



//name_disp_t  sensor_name_set[]={
//	{0, 1.2, "Pressure:", VERY_SMALL, NOT_FILL,21, },
//	{0, 2.2, "Air Temp:", VERY_SMALL, NOT_FILL,21, },
//	{0, 3.2, "Humidity:", VERY_SMALL, NOT_FILL,21, },
//	{0, 4.2, "Air Oxy :", VERY_SMALL, NOT_FILL,21, },
//	{0, 5.2, "Air Temp2 :", VERY_SMALL, NOT_FILL,21, },
//};

//value_disp_t 	sensor_Disp_set[] = {
//		{9, 1.2,100,&Oxy.pressure, 1000,3,3,VAR_UINT32, 	VERY_SMALL, NOT_FILL, 0, 2000,  NULL,NULL,"[kPa]", NOT_FILL,VERY_SMALL},
//		{9, 2.2,100,&Oxy.baro_temp, 100,3,2,VAR_UINT32, 	VERY_SMALL, NOT_FILL, -40, 100, '[', 127,"]  ", NOT_FILL,VERY_SMALL},
//		{9, 3.2,100,&Oxy.humidity, 100,4,2,VAR_UINT32, 	VERY_SMALL, NOT_FILL, 0, 100,  NULL,NULL,"[%]  ", NOT_FILL,  VERY_SMALL},
//		{9, 4.2 ,100,	&Oxy.Po, 100,4,2,VAR_UINT32, VERY_SMALL, NOT_FILL, 15, 30,  NULL,NULL,"[%]  ", NOT_FILL,VERY_SMALL},
//		{9, 5.2,100,&Oxy.hih_temp, 100,3,2,VAR_UINT32, 	VERY_SMALL, NOT_FILL, -40, 100, '[', 127,"]  ", NOT_FILL,VERY_SMALL},
//};

//#define SENSOR_DISP_COUNT (sizeof(sensor_Disp_set) / sizeof(sensor_Disp_set[0]))


//name_disp_t  af_system_name_set[]={
//	{0, 1.2, "F/W Version:", VERY_SMALL, NOT_FILL,21, },
//	{0, 2.2, "ASIC Time:", VERY_SMALL, NOT_FILL,21, },
//	{0, 3.2, "Sys Time:", VERY_SMALL, NOT_FILL,21, },
//	{0, 4.2, "CAN-Tx err cnt:", VERY_SMALL, NOT_FILL,21, },
//	{0, 5.2, "CAN-Rx err cnt:", VERY_SMALL, NOT_FILL,21, },
//	{0, 6.2, "CAN-Last err No:", VERY_SMALL, NOT_FILL,21, },
//	{0, 7.2, "i2C1 Error :", VERY_SMALL, NOT_FILL,21, },
//	{0, 8.2, "i2C2 Error :", VERY_SMALL, NOT_FILL,21, },
//};

//value_disp_t 	af_system_value_set[] = {

//		{12, 1.2,150,&AF.AF_FW_ver, 10,3,1,VAR_INT8, 	VERY_SMALL, NOT_FILL, 0, 99, NULL,NULL, NULL, NOT_FILL,VERY_SMALL},
//		{11, 2.2,150,&AF.ASIC_loop_time_us, 1000,2,3,VAR_INT16, 	VERY_SMALL, NOT_FILL, 0, 99, NULL,NULL, "[ms]", NOT_FILL,VERY_SMALL},
//		{12, 3.2,150,&AF.AF_loop_time_us, 1000,1,3,VAR_INT16, 	VERY_SMALL, NOT_FILL, 0, 9.9, NULL,NULL, "[ms]", NOT_FILL,VERY_SMALL},
//		{16, 4.2,150,&sys.can_tx_err_cnt, 1,3,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 255, NULL,NULL, "", NOT_FILL,VERY_SMALL},
//		{16, 5.2,150,&sys.can_rx_err_cnt, 1,3,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 255, NULL,NULL, "", NOT_FILL,VERY_SMALL},
//		{16, 6.2,150,&sys.can_last_err, 1,3,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 255, NULL,NULL, "", NOT_FILL,VERY_SMALL},
//		{11, 7.2,150,&AF.ADC_i2c_error_countt_adc, 1,6,0,VAR_UINT16, 	VERY_SMALL, NOT_FILL, 0, 9999, NULL,NULL, "", NOT_FILL,VERY_SMALL},
//		{11, 8.2,150,&AF.ADC_i2c_error_countt_dac, 1,6,0,VAR_UINT16, 	VERY_SMALL, NOT_FILL, 0, 9999, NULL,NULL, "", NOT_FILL,VERY_SMALL},
//};
//#define AF_CTRL_STATUS_DISP_COUNT (sizeof(af_system_value_set) / sizeof(af_system_value_set[0]))

//name_disp_t  oxy_sensor_status_name_set[]={
//	{0, 1.2, "Ref-Vs  :", VERY_SMALL, NOT_FILL,21, },
//	{0, 2.2, "Rpvs    :", VERY_SMALL, NOT_FILL,21, },
//	{0, 3.2, "HTR curr:", VERY_SMALL, NOT_FILL,21, },
//	{0, 4.2, "STATUS  :", VERY_SMALL, NOT_FILL,21, },
//	{0, 5.2, "Ip-Vout :", VERY_SMALL, NOT_FILL,21, },
//	{0, 6.2, "Input-V :", VERY_SMALL, NOT_FILL,21, },
//	{0, 7.2, "FV Gain :", VERY_SMALL, NOT_FILL,21, },
//	{0, 8.2, "Ref Gain:", VERY_SMALL, NOT_FILL,21, },
//	{0, 9.2, "Icp Curr:", VERY_SMALL, NOT_FILL,21, },
//	{0, 10.2, "OBD Sum :", VERY_SMALL, NOT_FILL,21, },
//	{0, 11.2, "BUS Fail:", VERY_SMALL, NOT_FILL,21, },
//	{0, 12.2, "BUS Cnt :", VERY_SMALL, NOT_FILL,21, },
//	{0, 13.2, "ASIC Ver:", VERY_SMALL, NOT_FILL,21, },
//};
//	
//value_disp_t 	oxy_sensor_value_set[] = {
//		{10, 1.2,50,&AF.Vs, 1,7,0,VAR_UINT16, 	VERY_SMALL, NOT_FILL, 0, 20000,  NULL ,NULL, "[mV]", NOT_FILL,VERY_SMALL},
//		{10, 2.2,50,&AF.Rvps ,10, 6,1,VAR_UINT16, 	VERY_SMALL, NOT_FILL, 0, 65535, NULL,NULL,"[O]", NOT_FILL,VERY_SMALL},
//		{12, 3.2,50,&AF.Heater_current_avg ,1000, 2,2,VAR_UINT16, 	VERY_SMALL, NOT_FILL, -0.5, 9, NULL,NULL,"[A]", NOT_FILL,VERY_SMALL},
//		{11, 4.2,50,&AF.ASIC_status, 1,7,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 20000,  NULL ,NULL, "", NOT_FILL,VERY_SMALL},
//		{13, 5.2,50,&AF.IP_vout,1000, 1,3,VAR_UINT16, VERY_SMALL, NOT_FILL, 0, 30, NULL,NULL,"[V]", NOT_FILL,VERY_SMALL},
//		{13, 6.2,50,&AF.Supply_voltage,1000, 2,2,VAR_UINT16, VERY_SMALL, NOT_FILL, 0, 30, NULL,NULL,"[V]", NOT_FILL,VERY_SMALL},

//		{14, 7.2,50,&AF.fv_gain ,10, 2,1,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 12, NULL,NULL,"[X]", NOT_FILL,VERY_SMALL},
//		{15, 8.2,50,&AF.ref_gain ,10, 1,1,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 8, NULL,NULL,"[X]", NOT_FILL,VERY_SMALL},
//		{14, 9.2,50,&AF.icp_curr,1, 3,0,VAR_UINT8, VERY_SMALL, NOT_FILL, 0, 60, NULL,NULL,"[uA]", NOT_FILL,VERY_SMALL},
//		
//		{15, 10.2,50,&AF.obd1, 1,3,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 20000,  NULL ,NULL, "", NOT_FILL,VERY_SMALL},
//		{15, 11.2,50,&AF.busFail_count ,1, 3,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 7, NULL,NULL,"", NOT_FILL,VERY_SMALL},
//		{15, 12.2,50,&AF.busBus_count,1, 3,0,VAR_UINT8, VERY_SMALL, NOT_FILL, 0, 50, NULL,NULL,"", NOT_FILL,VERY_SMALL},		
//		{16, 13.2,50,&AF.ASIC_version ,1, 2,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 7, NULL,NULL,"", NOT_FILL,VERY_SMALL},
////		{11, 13.2,50,&AF.Heater_current,1000, 2,2,VAR_UINT16, VERY_SMALL, NOT_FILL, 0, 30, NULL,NULL,"[V]", NOT_FILL,VERY_SMALL},
//	};		
//#define OXY_SENSOR_DISP_COUNT (sizeof(oxy_sensor_value_set) / sizeof(oxy_sensor_value_set[0]))

//name_disp_t  config_name_set[]={
//	{0, 1.2, "H/C       :", VERY_SMALL, NOT_FILL,21, },
//	{0, 2.2, "O2 16%  Ip:", VERY_SMALL, NOT_FILL,21, },
//	{0, 3.2, "Cal Air%  :", VERY_SMALL, NOT_FILL, 21, },
//	
//	{0, 4.2, "DAC Min   :", VERY_SMALL, NOT_FILL, 21,},
//	{0, 5.2, "DAC Max   :", VERY_SMALL, NOT_FILL,21,  },
//	{0, 6.2, "DAC Offset:", VERY_SMALL, NOT_FILL,21,  },

//	{0, 7.2, "Sen Type :", VERY_SMALL, NOT_FILL,21,  },
//	{0, 8.2, "Fuel Type :", VERY_SMALL, NOT_FILL,21,  },
//	{0, 9.2, "Dewpint T :", VERY_SMALL, NOT_FILL,21,  },
//	
//	{0, 10.2, "Zero Offset:", VERY_SMALL, NOT_FILL,21,  },
//	{0, 11.2, "Gain Lean :", VERY_SMALL, NOT_FILL,21,  },
//	{0, 12.2, "Gain Rich :", VERY_SMALL, NOT_FILL,21,  },

//	{0, 13.2, "Shunt Offset:", VERY_SMALL, NOT_FILL,21,  },
//	{0, 14.2, "Shunt Gain:", VERY_SMALL, NOT_FILL,21,  },
//	{0, 15.2, "5V Offset :", VERY_SMALL, NOT_FILL,21,  },
//	{0, 16.2, "3.3V Offset:", VERY_SMALL, NOT_FILL,21,  },

//	{0, 17.2, "Ip Zero x4:", VERY_SMALL, NOT_FILL,21,  },
//	{0, 18.2, "Ip Lean x4:", VERY_SMALL, NOT_FILL,21,  },
//	{0, 19.2, "Ip Rich x4 :", VERY_SMALL, NOT_FILL,21,  },

//};

//value_disp_t 	config_value_set[] = {
//		{12, 1.2,50,&controler_cfg.HC , 1,2,3,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 0, 20,  NULL ,NULL, "", NOT_FILL,VERY_SMALL},
//		{12, 2.2,50,&controler_cfg.Cali_Air_Ip ,1000, 1,3,VAR_INT32, 	VERY_SMALL, NOT_FILL, 0, 5000, NULL,NULL,"[mA]", NOT_FILL,VERY_SMALL},
//		{13, 3.2,50,&controler_cfg.Cali_Air_Po ,1, 2,2,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 0, 100, NULL,NULL,"[%] ", NOT_FILL,VERY_SMALL},

//		{12, 4.2,50,&controler_cfg.dac_out_lambda_min, 1,2,3,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 0, 30,  NULL ,NULL, "[L]", NOT_FILL,VERY_SMALL},
//		{12, 5.2,50,&controler_cfg.dac_out_lambda_max, 1,2,3,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 0, 30,  NULL ,NULL, "[L]", NOT_FILL,VERY_SMALL},
//		{12, 6.2,50,&controler_cfg.dac_offset_mV, 1,3,0,VAR_INT16, 	VERY_SMALL, NOT_FILL, -100, 100,  NULL ,NULL, "[mV]", NOT_FILL,VERY_SMALL},

//		{17, 7.2,50,&controler_cfg.sensor_model, 1,1,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 1,  NULL ,NULL, "", NOT_FILL,VERY_SMALL},
//		{17, 8.2,50,&controler_cfg.fuel_type, 1,1,0,VAR_UINT8, 	VERY_SMALL, NOT_FILL, 0, 5,  NULL ,NULL, "", NOT_FILL,VERY_SMALL},
//		{11, 9.2,50,&controler_cfg.dew_point_time_s, 1,4,1,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 0, 1000,  NULL ,NULL, "[S]", NOT_FILL,VERY_SMALL},
//		
//		{13, 10.2,50,&controler_cfg.ip_Offset_uA, 1,3,0,VAR_INT16, 	VERY_SMALL, NOT_FILL, -9500, 1000,  NULL ,NULL, "[uA]", NOT_FILL,VERY_SMALL},
//		{13,11.2,50,&controler_cfg.gain_lean, 1,1,3,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 0, 2,  NULL ,NULL, "[X]", NOT_FILL,VERY_SMALL},
//		{13,12.2,50,&controler_cfg.gain_rich, 1,1,3,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 0, 2,  NULL ,NULL, "[X]", NOT_FILL,VERY_SMALL},
//		
//		{13, 13.2,50,&Factory_cfg.current_zero_offset, 1,3,0,VAR_INT16, 	VERY_SMALL, NOT_FILL, -999, 999,  NULL ,NULL, "[mA]", NOT_FILL,VERY_SMALL},
//		{13,14.2,50,&Factory_cfg.current_gain, 1,3,1,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 1, 1000,  NULL ,NULL, "[X]", NOT_FILL,VERY_SMALL},
//		{13,15.2,50,&Factory_cfg.ref_5V, 1,1,3,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 4, 6,  NULL ,NULL, "[V]", NOT_FILL,VERY_SMALL},
//		{13,16.2,50,&Factory_cfg.ref_3_3V, 1,1,3,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 2, 4,  NULL ,NULL, "[V]", NOT_FILL,VERY_SMALL},
//		
//		{12, 17.2,50,&Factory_cfg.ref_ip_OffsetV[GAIN_4X], 1,4,0,VAR_INT16, 	VERY_SMALL, NOT_FILL, -3000, 3000,  NULL ,NULL, "[mA]", NOT_FILL,VERY_SMALL},
//		{13,18.2,50,&Factory_cfg.gain_lean[GAIN_4X], 1,1,3,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 0, 2,  NULL ,NULL, "[X]", NOT_FILL,VERY_SMALL},
//		{13,19.2,50,&Factory_cfg.gain_rich[GAIN_4X], 1,1,3,VAR_FLOAT, 	VERY_SMALL, NOT_FILL, 0, 2,  NULL ,NULL, "[X]", NOT_FILL,VERY_SMALL},
//	};		
//#define CONFIG_DISP_COUNT (sizeof(config_value_set) / sizeof(config_value_set[0]))



//title_disp_t  config_title_set[]={
//	{"H/C", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "",  GODIC_MIDDLE, NOT_FILL, HC, config_value_set,},
//	{"V-OUT Minimum", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "V", GODIC_MIDDLE, NOT_FILL, DA_MIN_VOLT, config_value_set,},
//	{"V-OUT Maximum", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "V", GODIC_MIDDLE, NOT_FILL, DA_MAX_VOLT, config_value_set,},
//	{"V-OUT Offset", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "mV", GODIC_MIDDLE, NOT_FILL, DA_OFFSET, config_value_set,},
//	{"Duew Point Time", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "S", GODIC_MIDDLE, NOT_FILL, DUEW_POINT_TIME, config_value_set,},
//	{"Lamd Zero Offset", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "", GODIC_MIDDLE, NOT_FILL, ZERO_OFFSET, config_value_set,},
//	{"Lean Gain", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "X", GODIC_MIDDLE, NOT_FILL, LEAN_GIAN, config_value_set,},
//	{"Rich Gain", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "X", GODIC_MIDDLE, NOT_FILL, RICH_GAIN, config_value_set,},
//	
//	{"Gain 4X Offset", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "", GODIC_MIDDLE, NOT_FILL, IP_ZERO_OFFSET_GAIN4, config_value_set,},
//	{"Gain 4X Lean", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "X", GODIC_MIDDLE, NOT_FILL, IP_LEAN_OFFSET_GAIN4, config_value_set,},
//	{"Gain 4X Rich", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "X", GODIC_MIDDLE, NOT_FILL, IP_RICH_OFFSET_GAIN4, config_value_set,},

//	//	{"Sensor Model", SYSTEM_SMALL, FILL,16, VERY_SMALL, NOT_FILL, "", GODIC_MIDDLE, NOT_FILL, SENSOR_MODEL, config_value_set,},
//	
////	{"Air calibration of the sensor", SYSTEM_SMALL, FILL,16, },
////	{"V-OUT Maximum Lambda", SYSTEM_SMALL, FILL,16, },
////	{"V-OUT Miniimum Lambda", SYSTEM_SMALL, FILL,16, },
////	{"Lambda 1.0 offset", SYSTEM_SMALL, FILL,16, },
////	{"Oxygen Sensor Type", SYSTEM_SMALL, FILL,16, },
//	};
//#define CONFIG_TITLE_COUNT (sizeof(config_title_set) / sizeof(config_title_set[0]))


//static double  value_to_double (value_disp_t * val){
//		double value;
//	
//					switch(val->type) {
//						case VAR_UINT8:
//									value = (double)(*(uint8_t *)val->value)/val->div;
//									break;
//						case VAR_INT8:
//									value = (double)(*(char *)val->value)/val->div;
//									break;
//						case VAR_UINT16:
//									value = (double)(*(uint16_t *)val->value)/val->div;
//									break;
//						case VAR_INT16:
//									value = (double)(*(short *)val->value)/val->div;
//									break;
//						case VAR_UINT32:
//									value = (double)(*(uint32_t *)val->value)/val->div;
//									break;
//						case VAR_INT32:
//									value = (double)(*(int32_t *)val->value)/val->div;
//									break;
//						 case VAR_FLOAT:
//									value = (double)(*(float *)val->value)/val->div;
//									break;
//					}
//		return value;
//}




//static void config_setting_display(title_disp_t * title_t) {
//	#define TITLE_COLUM 	16
//	#define RANGE_COLUM 	21
//	#define VALUE_COLUM 	8

//			char  sub_buffer[22];
//			char string_buffer[22];
//			double value;
//			uint8_t max_string_length;
//			uint8_t front_space;
//			uint8_t dot_up_length = title_t->config[title_t->add_no].pointUpValue;
//			uint8_t dot_down_length =title_t->config[title_t->add_no].pointDownValue;
//	
//			font_set.bgColor = title_t->title_BT;
//			font_set.fontType = title_t->title_FT;
//			font_set.fontPosionX = 0;
//			font_set.fontPosionY = 0;
//			  front_space = (TITLE_COLUM- strlen(title_t->title))/2;
//				memset(sub_buffer,NULL, sizeof(sub_buffer)/sizeof(sub_buffer[0]));
//				memset(sub_buffer,' ',front_space);
//				strcat(sub_buffer,title_t->title);
//				//타이틀의 뒷쪽 빈공간을 채움.
//				memset(string_buffer,' ', TITLE_COLUM- strlen(sub_buffer));		
//				strcat(sub_buffer, string_buffer);
//			TFT_string(sub_buffer, font_set.fontPosionX,0);

//			font_set.bgColor = title_t->range_BG;
//			font_set.fontType = title_t->range_FT;
//			memset(string_buffer,NULL,sizeof(string_buffer) / sizeof(string_buffer[0]));
//			//minimum value display
//			
//			max_string_length = (dot_down_length >0)?dot_up_length+ dot_down_length+1 :dot_up_length+ dot_down_length;		//최대 표시문장 길이를 계산
//			floatToString(string_buffer+strlen(string_buffer), title_t->config[title_t->add_no].dispMin ,dot_down_length,max_string_length);
//			strcat(string_buffer," ~ ");
//			//maximum value display
//			max_string_length = (dot_down_length >0)?dot_up_length+ dot_down_length+1 :dot_up_length+ dot_down_length;		//최대 표시문장 길이를 계산

//			floatToString(string_buffer+strlen(string_buffer), title_t->config[title_t->add_no].dispMax ,dot_down_length,max_string_length);
//				strcat(string_buffer, title_t->unit);
//			  front_space = (RANGE_COLUM- strlen(string_buffer))/2;
//				memset(sub_buffer,NULL, sizeof(sub_buffer)/sizeof(sub_buffer[0]));
//				memset(sub_buffer,' ',front_space);
//				strcat(sub_buffer,string_buffer);
//			TFT_string(sub_buffer, 0 ,1.3); //min~max 범위를 표시

//			//setting value display
//			font_set.bgColor = title_t->value_BT;
//			font_set.fontType = title_t->value_FT;
//			memset(string_buffer,NULL,sizeof(string_buffer) / sizeof(string_buffer[0]));
//			value = value_to_double(&title_t->config[title_t->add_no]);
//			max_string_length = (dot_down_length >0)?dot_up_length+ dot_down_length+1 :dot_up_length+ dot_down_length;		//최대 표시문장 길이를 계산
//			max_string_length = (value<0)?max_string_length+1:max_string_length;		//값이 음수일경우 부호자릿수를 +1 해줌.  <<--2015년 6월3일 추가


//			floatToString(string_buffer, value ,dot_down_length,max_string_length);
//			front_space = (VALUE_COLUM- strlen(string_buffer))/2;
//			memset(sub_buffer,NULL, sizeof(sub_buffer)/sizeof(sub_buffer[0]));
//			memset(sub_buffer,' ',front_space);
//			strcat(sub_buffer,string_buffer);
//			TFT_string(sub_buffer, 0 ,1); 
//			
//	//		sys.value_staring_start_posion = string_buffer -  sub_buffer;		//값의 시작위치 기록

//	
//}



//enum { 
//			INIT_CONFIG,
//			UPDATE_ALL_REQUEST,
//			RECEIVE_WAIT,
//			PAGE_DISPLAY,
//			IDLE_DISPLAY,
//			SEND_COFIG_DATA,
//			UPDATE_ONE_REQUEST,
//			RECEIVE_TIME_OUT,
//}_config_set_status;

//#define CAN_RECEIVE_TIME_OUT_MS		1000
//void display_config_set_display(bool reset) {
//	static uint8_t status = INIT_CONFIG; 
//	static int8_t befor_page=-1;
//	static uint32_t beforTime=0;
//	uint32_t timeNow;
//		//config data update flag pointing
//	bool * config_data_receive_flag = &sys.config_value_receive_flag[(config_title_set[disp_page.config_page_no].add_no)];
//	
//	timeNow = millis();
//	if(reset) {
//			status = INIT_CONFIG; 
//	}
//	
//		switch(status) {
//						 case INIT_CONFIG:
//									status = UPDATE_ALL_REQUEST;
//									beforTime =timeNow;
//									break;
//						 
//						 case UPDATE_ALL_REQUEST:
//									config_all_request();		//CAN 통신으로 컨트롤러에 설정값 전송을 요청함.
//									if ( (int64_t)timeNow - beforTime-100 > 0 ||   beforTime > timeNow) { //수신 받을때까지 잠시 기다림
//												status = PAGE_DISPLAY;
//												beforTime =timeNow;
//									}								 
//									break;
//		
//						 case RECEIVE_WAIT:
//								 if(* config_data_receive_flag== true) {		//config data의  변경값이 can통신으로  update 된경우
//											* config_data_receive_flag = false;
//											status = PAGE_DISPLAY;
//								 }
//								if ( (int64_t)timeNow - beforTime-CAN_RECEIVE_TIME_OUT_MS > 0 ||   beforTime > timeNow) { //500ms 이내에 응답이 없으면 에러 처리
//											status = RECEIVE_TIME_OUT;
//											beforTime =timeNow;
//								}								 
//									config_value_change(&config_title_set[disp_page.config_page_no], false);		//설정값을 표시
//							 break;
//								 
//						 case PAGE_DISPLAY:
//									ssd1306_clear_screen(0x00);
//									config_setting_display(&config_title_set[disp_page.config_page_no]);		//페이지 형식을 표시
//									config_value_change(&config_title_set[disp_page.config_page_no], true);		//설정값을 표시
//									status = IDLE_DISPLAY;
//									break;
//						 
//						 case IDLE_DISPLAY:
//									if(disp_page.config_page_no != befor_page ) {// 컨피그 모드 진입 또는 컨피그 페이지가 변경될경우 
//											befor_page= disp_page.config_page_no;
//											if(send_config_data.update_flag == true) {		//사용자에 의해 컨피그 값이 변경된경우
//														send_config_data.update_flag =false;
//														status = SEND_COFIG_DATA;
//														break;
//											}
//											status = PAGE_DISPLAY;
//											break;
//									}
//									config_value_change(&config_title_set[disp_page.config_page_no], false);		//설정값을 표시
//									break;
//						
//						 case UPDATE_ONE_REQUEST:
//									config_One_item_request(send_config_data);
//									beforTime =timeNow;
//									status = RECEIVE_WAIT;
//									config_value_change(&config_title_set[disp_page.config_page_no], false);		//설정값을 표시
//									break;
//									
//						 case SEND_COFIG_DATA:
//								sending_config_data(send_config_data);
//								send_config_data.update_flag =false;
//								
//								//응답확인 타임 아웃 코드 추가
//									status = UPDATE_ONE_REQUEST;
//									config_value_change(&config_title_set[disp_page.config_page_no], false);		//설정값을 표시
//									break;

//						 case RECEIVE_TIME_OUT:
//									font_set.fontType =GODIC_SMALL;		
//									font_set.bgColor = NOT_FILL;
//									ssd1306_clear_screen(0x00);
//									TFT_string("CAN-BUS ERROR",0 ,1); 
//									ssd1306_refresh_gram();
//									if ( (int64_t)timeNow - beforTime-1000 > 0 ||   beforTime > timeNow) { //1000ms 기다림
//												status = UPDATE_ALL_REQUEST;
//									}								 
//									break;

//						 default:
//									break;
//	}
//}
//enum {
//						INIT_CONFIG_SET,
//						CONFIG_VALUE_UPDATE,
//						CURSOR_MOVE,
//						CONFIG_DISPLAY,
//						CURSOR_DISABLE,
//						CONFIG_IDLE,
////						CONFIG_PAGE_VIEW_MODE,
////						CONFIG_CHANGE_MODE,
////						CURSOR_MOVE,

//}_config_page_update_control;

// void config_value_change(title_disp_t * title_t, bool reset) {			//컨피그 값을 사용자 조작으로 변경
//		static double value=0, befor_value=0;
//		static double min_value, max_value;
//		static int8_t befor_cursor;
//		static int8_t exponent[10];
//		static int8_t cursor_posion;
//		static uint8_t max_string_length;
//		static int8_t value_start_posion;
//		static int8_t value_end_posion;
//		static uint8_t dot_posion=0;
//		static uint8_t dot_value=0;
//		static uint8_t negative_sign=0;
//		int8_t i;

//		char  sub_buffer[22];
//		static char string_buffer[22];
////		uint8_t front_space;
//		static uint8_t status = INIT_CONFIG_SET;

//		static uint8_t dot_up_length;
//		static uint8_t dot_down_length;
////		static uint8_t displa_start_posion;
//	 
//	 dot_up_length = title_t->config[title_t->add_no].pointUpValue;
//	 dot_down_length =title_t->config[title_t->add_no].pointDownValue;
////		bool * config_value_change_flag = &sys.config_value_change_flag[(config_title_set[disp_page.config_page_no].add_no)];

//if(reset ) {		//페이지가 변경되거나 컨피그 모드로 진입시 실행
//			status = INIT_CONFIG_SET;
//}
//if(sys.page_change_hold) {
//				if(sys.cursor_move >0 && value_end_posion-1> cursor_posion ) {		//커서값이 +로 변경될경우
//					cursor_posion++;
//						if(dot_posion == cursor_posion &&  dot_value) {// //도트위치에 오면 이동방향으로 한칸 더 이동
//							cursor_posion++;
//						}
//				}
//				else if(sys.cursor_move <0 && value_start_posion + ((min_value<0)?+1:0) <  cursor_posion) {	//커서값이 -로 변경될경우
//					cursor_posion--;
//						if(dot_posion == cursor_posion && dot_value) {	//실수이고  도트위치에 오면 이동방향으로 한칸 더 이동
//							cursor_posion--;
//						}
//				}
//				sys.cursor_move=0;
//				if(sys.change_value > 0 ) {		//값을 변경시 자리위치에 따라서 값을 변경함
//						value = value + (double)pow(10.0f, (double)exponent[cursor_posion]);	//자리위치에 따라서 값을 +해줌
//						if(value >max_value) {
//								value = max_value;
//						}
//				}
//				else if(sys.change_value < 0 ) {
//						value = value - (double)pow(10.0f, (double)exponent[cursor_posion]);	//자리위치에 따라서 값을 -해줌
//						if(value <min_value) {
//								value = min_value;
//						}
//				}
//				sys.change_value=0;
//				
//		if(befor_value != value ) {	//값이 변경될 경우
////				if(befor_value >0 && value <0) {	//값이 +에서 -로 변할경우
////	//					cursor_posion--;
////				}
////				else if(befor_value <0 && value >0) {	//값이 -에서 +로 변할경우
////	//					cursor_posion++;
////				}
//				befor_value = value ;
//				status = CONFIG_VALUE_UPDATE;
//		}		
//		if(befor_cursor != cursor_posion ) {	//커서 위치가 바뀔경우
//				status = CURSOR_MOVE;
//		}
//		if(!sys.page_change_hold) {
//				status = CURSOR_DISABLE;
//		}

//}

//	switch(status) {
//		case INIT_CONFIG_SET:
//				max_value  = title_t->config[title_t->add_no].dispMax;
//				min_value  = title_t->config[title_t->add_no].dispMin;
////				negative_sign = (min_value<0)?1:0;
//		
//				max_string_length = (dot_down_length >0)?dot_up_length+dot_down_length+1 :dot_up_length+ dot_down_length;		//최대 표시문장 길이를 계산
//				max_string_length = (min_value<0)?max_string_length+1:max_string_length;		//값이 음수일경우 부호자릿수를 +1 해줌.  
//				value =  value_to_double(&title_t->config[title_t->add_no]);		//void형 값을 숫자로
//				dot_value = (dot_down_length>0)?1:0;		//소숫점 아랫자리가 있을경우 1로 입력
//				value_start_posion = (VALUE_COLUM- max_string_length)/2 ;
//				value_end_posion = value_start_posion + max_string_length;
//				dot_posion = value_start_posion + dot_up_length  ;		// 도트위치  계산

//			//자릿수에 따른 지수가 입력된 마스크 배열을  만듬
//				memset(exponent,NULL, sizeof(exponent)/sizeof(exponent[0]));
//					//3,2,1,0,-1,-2,-3,
//					//0 0 0 0 . 0  0  0
//				for(i=0; i<dot_up_length; i++){
//						exponent[i+value_start_posion+ ((min_value<0)?+1:0) ] = dot_up_length-i-1;			//소숫점 윗자리부터 위치에 따른 +지수값을 입력
//				}
//				if(dot_value) {		//소숫점 아래 자리가 있을경우
//						for(i=0; i<dot_down_length; i++) {
//								exponent[i+dot_posion+dot_value + negative_sign+ ((min_value<0)?+1:0)] = -i-1;			//소숫점 아랫자리부터 위치에 따른 -지수값을 입력
//						}
//				}
////				cursor_posion = value_start_posion;		//커서의 위치를 숫자의 표시 위치로 설정한다.
//				cursor_posion = dot_posion-1+((min_value<0)?+1:0);		//커서의 위치를 1의 자리에 표시 위치로 설정한다.
//				befor_cursor = cursor_posion ;
//				status = CONFIG_VALUE_UPDATE;
//				break;
//				
//		case CONFIG_VALUE_UPDATE:
////				max_string_length = (dot_down_length >0)?dot_up_length+dot_down_length+1 :dot_up_length+ dot_down_length;		//최대 표시문장 길이를 계산
////				max_string_length = (value<0)?max_string_length+1:max_string_length;		//값이 음수일경우 부호자릿수를 +1 해줌.  
//				memset(sub_buffer,NULL, sizeof(sub_buffer)/sizeof(sub_buffer[0]));
//				floatToString(sub_buffer, value ,dot_down_length,max_string_length);
//	//			front_space = (float)(VALUE_COLUM- strlen(sub_buffer))/2;

//				memset(string_buffer,NULL,sizeof(string_buffer) / sizeof(string_buffer[0]));
////				displa_start_posion = ((min_value<0)?-1:0) + value_start_posion;
//				memset(string_buffer,' ', value_start_posion);		
//				strcat(string_buffer,sub_buffer);
//				font_set.bgColor = title_t->value_BT;
//				font_set.fontType = title_t->value_FT;		
//				TFT_string(string_buffer, 0 ,1);
//				ssd1306_refresh_gram();
//				if(sys.page_change_hold) {
//						status = CURSOR_MOVE;
//				}
//				else {
//						status = CONFIG_IDLE;
//				}
//				if(	value !=  value_to_double(&title_t->config[title_t->add_no])){	
//					//수신받은 설정값과 설정한 값이 다를경우  전송할 데이터를 변수에 기록					
//					send_config_data.value = value * title_t->config[title_t->add_no].div;
//					send_config_data.data_type = title_t->config[title_t->add_no].type;
//					send_config_data.address = title_t->add_no;
//					send_config_data.update_flag= true;
//				}
//				break;
//		
//		case CURSOR_DISABLE:
//				memset(sub_buffer,NULL, sizeof(sub_buffer)/sizeof(sub_buffer[0]));
//				strncpy(sub_buffer, string_buffer+cursor_posion, 1);
//				font_set.fontType = title_t->value_FT;		
//				font_set.bgColor = NOT_FILL;
//				TFT_string(sub_buffer,cursor_posion ,1); 			
//				ssd1306_refresh_gram();
//				status = CONFIG_IDLE;
//				break;
//		
//		case CURSOR_MOVE:
//				memset(sub_buffer,NULL, sizeof(sub_buffer)/sizeof(sub_buffer[0]));
//				strncpy(sub_buffer, string_buffer+befor_cursor, 1);
//				font_set.bgColor = NOT_FILL;
//				font_set.fontType = title_t->value_FT;		
//				TFT_string(sub_buffer,befor_cursor ,1); 
//				font_set.bgColor = FILL;
//				memset(sub_buffer,NULL, sizeof(sub_buffer)/sizeof(sub_buffer[0]));
//				strncpy(sub_buffer, string_buffer+cursor_posion, 1);
//				TFT_string(sub_buffer,cursor_posion ,1); 
//				befor_cursor = cursor_posion;
//				font_set.bgColor = NOT_FILL;
//				ssd1306_refresh_gram();
//				status = CONFIG_IDLE;
//				break;
//				
//		case CONFIG_IDLE:
//							if(sys.page_change_hold) {
//									status = CURSOR_MOVE;
//							}
//							else {
//									status = CURSOR_DISABLE;
//							}
//				break;
//				
////		case CONFIG_CHANGE_MODE:
////	
////				break;
//	}

//}
// 




//void LCD_disp_page_init(void) {
////	disp_page.page_init_flag =false;
//	disp_page.indicater_max_page_size =MMAXIMUM_LCD_DISPLAY_PAGE;		
//	disp_page.config_max_page_size =CONFIG_TITLE_COUNT;		
//	disp_page.disp_page_no = DEFAULT_LCD_DISPLAY_PAGE;
//	disp_page.scroll_posion=0;
//	
//	LCD_disp_page_control(true);
//}

////LCD DISPLAY PAGE CONTROL 
//void LCD_disp_page_control(bool reset) {
//	static int8_t befor_page_no = -1;
//	static uint8_t beror_scroll_posion=0;
//	
//	
//	if(befor_page_no != disp_page.disp_page_no || reset) {		//페이지 번호가 바뀌거나 초기화 신호 입력시
//		befor_page_no = disp_page.disp_page_no;
//		disp_page.scroll_posion = disp_page.scroll_posion =0;		//스크롤 위치가 바뀔경우
//		ssd1306_clear_screen(0x00);
//		title_display_string(&status_title_set[disp_page.disp_page_no]);		//TITLE을 표시함.

//			switch(disp_page.disp_page_no) {
//	
//				case AF_MEASURING:
//						disp_page.disp_item_size = AF_DISP_COUNT;
//						disp_page.disp_item = &af_measuring_value_set[disp_page.scroll_posion];
//						disp_page.value_name = &measuring_name_set[disp_page.scroll_posion];
//						LCD_Value_Display(true);
//						break;
//				
//				case OXY_SENSOR_STAT:
//						disp_page.disp_item_size = OXY_SENSOR_DISP_COUNT;
//						disp_page.disp_item = &oxy_sensor_value_set[disp_page.scroll_posion];
//						disp_page.value_name = &oxy_sensor_status_name_set[disp_page.scroll_posion];
//					LCD_Value_Display(true);
//						break;				

//				case AF_STATUS:
//						disp_page.disp_item_size = AF_CTRL_STATUS_DISP_COUNT;
//						disp_page.disp_item = &af_system_value_set[disp_page.scroll_posion];
//						disp_page.value_name = &af_system_name_set[disp_page.scroll_posion];
//						LCD_Value_Display(true);
//						break;

//				case ROOM_SENSOR:
//						disp_page.disp_item_size = SENSOR_DISP_COUNT;
//						disp_page.disp_item = &sensor_Disp_set[disp_page.scroll_posion];
//						disp_page.value_name = &sensor_name_set[disp_page.scroll_posion];
//						LCD_Value_Display(true);
//						break;

//				case CONFIG:
//						config_all_request();		//컨트롤러에 설정값 전송을 요청함.
//						disp_page.disp_item_size = CONFIG_DISP_COUNT;
//						disp_page.disp_item = &config_value_set[disp_page.scroll_posion];
//						disp_page.value_name = &config_name_set[disp_page.scroll_posion];
//						LCD_Value_Display(true);
////						disp_page.cursor_y_posion = disp_page.scroll_posion;
////						LCD_Config_Display(true);
//				
//						break;				


//				default:
//						break;
//			}
//	}
//				
//	LCD_Value_Display(beror_scroll_posion != disp_page.scroll_posion);	//이전값과 다를 경우 리
//	if( beror_scroll_posion != disp_page.scroll_posion ) {	//스크롤 위치가 다를경우
//			beror_scroll_posion = disp_page.scroll_posion;
////			LCD_Value_Display(true);
//	}
//	else {
////			LCD_Value_Display(false);
//	}

//}



//void cursor_control(void) {
//	static bool befor_button= 0;
//		if( befor_button != sys.push_btn[CENTER_BUTTON] && disp_page.disp_page_no == CONFIG) {			//버튼이 눌러진경우
//				befor_button= sys.push_btn[CENTER_BUTTON];
//				
//				if (!sys.push_btn[CENTER_BUTTON]) {
//						sys.scroll_hold =true;
//						font_set.bgColor = FILL;
//						font_set.fontType  =VERY_SMALL;
//						TFT_string(" ", 10 , disp_page.cursor_y_posion+1); //스크롤 위치부터 최대 item size 까지만 표시
////							LCD_update();
//							ssd1306_refresh_gram();		//LCD 표시값을 UPDATE.
////							sys.update_config =1;
//				}
//				else {
//						sys.scroll_hold =false;
//						font_set.bgColor = NOT_FILL;
//						font_set.fontType  =VERY_SMALL;
//						TFT_string(" ", 10 , disp_page.cursor_y_posion +1); //스크롤 위치부터 최대 item size 까지만 표시
////						LCD_update();
//						ssd1306_refresh_gram();		//LCD 표시값을 UPDATE.
////							sys.update_config =1;
//				}
//		 }
//}



#define VALUE_STRING_BUFFER_SIZE  30

//void LCD_Config_Display(bool reset_flag) {
//		static uint8_t i=0;
//		uint8_t disp_max_row  = (MAX_DISPLAY_ROW_SIZE> disp_page.disp_item_size)? disp_page.disp_item_size:MAX_DISPLAY_ROW_SIZE;
//		if(reset_flag) {		//스크롤 위치가 다를경우 
//						i=disp_page.scroll_posion;
//						LCD_string_Display_set(&disp_page.value_name[disp_page.scroll_posion]);
//						LCD_Config_Value_Display_set(&disp_page.disp_item[disp_page.scroll_posion]);
//						LCD_update();
//			
//		}
//						LCD_Config_Value_Display_set(&disp_page.disp_item[i]);
//				i = (i < disp_max_row + disp_page.scroll_posion -1)? i+1:disp_page.scroll_posion;				//스크롤 위치부터 최대 item size 까지만 표시
//			LCD_update();
//}


//void LCD_Config_Value_Display_set(value_disp_t * in_val) {
//	uint8_t i =0;
////	name_disp_t * pStr_set = str;
//	value_disp_t  * val = in_val;
//	double value;
//	char value_str_buff[VALUE_STRING_BUFFER_SIZE];
//	uint8_t max_string_lengs;
//	uint8_t disp_max_row  = (MAX_DISPLAY_ROW_SIZE> disp_page.disp_item_size)? disp_page.disp_item_size:MAX_DISPLAY_ROW_SIZE;
//	for(i=0; i < disp_max_row; i++) {
//		
//				switch(val->type) {
//						case VAR_UINT8:
//									value = (double)(*(uint8_t *)val->value)/val->div;
//									break;
//						case VAR_INT8:
//									value = (double)(*(char *)val->value)/val->div;
//									break;
//						case VAR_UINT16:
//									value = (double)(*(uint16_t *)val->value)/val->div;
//									break;
//						case VAR_INT16:
//									value = (double)(*(short *)val->value)/val->div;
//									break;
//						case VAR_UINT32:
//									value = (double)(*(uint32_t *)val->value)/val->div;
//									break;
//						case VAR_INT32:
//									value = (double)(*(int32_t *)val->value)/val->div;
//									break;
//						 case VAR_FLOAT:
//									value = (double)(*(float *)val->value)/val->div;
//									break;
//				}		
//				memset(value_str_buff,NULL, MAXIMUM_VALUE_STRING_BUFFER);
//				font_set.bgColor = val->bgType;
//				font_set.fontType  =val->valueFontType;
//		//최대 표시 문자열 길이를 계산
//				max_string_lengs = (val->pointDownValue >0)?val->pointUpValue+ val->pointDownValue+1 :val->pointUpValue+ val->pointDownValue;		//최대 표시문장 길이를 계산
//				max_string_lengs = (val->dispMin <0)?max_string_lengs+1:max_string_lengs;		//값이 음수일경우 부호자릿수를 +1 해줌.  <<--2015년 6월3일 추가
//				
//				floatToString(value_str_buff, value,val->pointDownValue,max_string_lengs);
//				font_set.bgColor  = val->bgType;
//				font_set.fontType = val->valueFontType;
////				TFT_string(pStr_set->string,pStr_set->posion_x,pStr_set->posion_y- disp_page.scroll_posion); //스크롤 위치부터 최대 item size 까지만 표시
//				TFT_string(value_str_buff,val->posion_x,val->posion_y- disp_page.scroll_posion); //스크롤 위치부터 최대 item size 까지만 표시
//				if(val->function != NULL) {
//					void (*Func) (void);
//					Func = val->function;		
//					Func();//관련된 함수 호출
//				}
//				val++;
//	}
//}


