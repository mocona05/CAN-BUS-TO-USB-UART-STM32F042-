#pragma once

#define CYCLE_TIME_TAB_SIZE_MAX 128

typedef enum {
    VAR_UINT8,
    VAR_INT8,
    VAR_UINT16,
    VAR_INT16,
    VAR_UINT32,
    VAR_INT32,
    VAR_FLOAT,
		VAR_NO_VALUE
} vartype_e;


void loop_time_clear(void);
void loop_time_measuring(uint32_t  * const cycleTime);
void Loop_time_Common(uint32_t);		//메인루프의 이동평균 계산
void LED0_failureDisplay(int16_t mode);		//LED0의 상태표시
void LED1_failureDisplay(int16_t mode);		//LED1의 상태표시
void number_to_2hex(uint8_t number, char * hex_string) ;           //  2-digit hex number 
void check_Sum_to_str(char * data_string, char * result_string, uint8_t lens);
char *itoa(int i, char *a, int r);
char * floatToString(char * outstr, double val, uint8_t precision, uint8_t widthp);       // folat to String Converter
uint8_t data_checkSum(uint8_t * str, uint16_t lens);
