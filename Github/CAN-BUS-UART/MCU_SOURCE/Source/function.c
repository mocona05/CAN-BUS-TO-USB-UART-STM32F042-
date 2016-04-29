#include "board.h"


//uint32_t loop_cycle_time =0;
//uint64_t loop_cycle_time_sum=0;

void loop_time_clear(void) {
	sys.cycleTime =0;
}

void loop_time_measuring(uint32_t  * const cycleTime) {
		static uint32_t	beforTime=0;
		uint32_t timeNow=0;
	
		timeNow = micros();
		if(timeNow >= beforTime) {	//time overf flow가 아닐경우
				if(* cycleTime <timeNow-beforTime) {
						* cycleTime = timeNow-beforTime;
				}
		}
		else {	//time over flow 일경우
					* cycleTime = timeNow + 0xFFFFFFFF - beforTime;
		}
		beforTime = timeNow;
}

// 이동평균 계산
void Loop_time_Common(uint32_t loop_cycle_time) {
	
#if 0
//    static uint32_t cycleTimeoHistTab[ CYCLE_TIME_TAB_SIZE_MAX];
//    static int cycleTimeHistIdx;
//    int indexplus1;

//    indexplus1 = (cycleTimeHistIdx + 1);
//    if (indexplus1 == CYCLE_TIME_TAB_SIZE_MAX){
//        indexplus1 = 0;
//		}
//    cycleTimeoHistTab[cycleTimeHistIdx] = loop_cycle_time;
//    loop_cycle_time_sum += cycleTimeoHistTab[cycleTimeHistIdx];
//    loop_cycle_time_sum -= cycleTimeoHistTab[indexplus1];
//    cycleTimeHistIdx = indexplus1;
#else
	//	System.loop_time = ((uint64_t)System.loop_time*(CYCLE_TIME_TAB_SIZE_MAX-1) + loop_cycle_time)/CYCLE_TIME_TAB_SIZE_MAX;

	
		
#endif
		
}


void number_to_2hex(uint8_t number, char * hex_string)  {           //  2-digit hex number 
		uint8_t i;
		char * pString = hex_string;
		i = (number >> 4) & 0x0F;                     // 16^1
		if(i <= 9) {
				* pString = i + '0';
		}
		else {       
				* pString = i - 10 + 'A';
		}
		i = number & 0x0F;                            // 16^0
		if(i <= 9) {
				* (pString+1) = i + '0';
		}
	else {       
			* (pString+1) = i - 10 + 'A';
	}
}


void check_Sum_to_str(char * data_string, char * result_string, uint8_t lens) {
		char  xor_sum=0;
		uint16_t i =0;
	//	char buff[3];

		for( i=0;i <lens;i++) {
			
//		for(i=0;i<lens;i++){
			xor_sum ^= data_string[i];		//xor 계산
//			i++;
		}
//		itoa(xor_sum, result_string, 16);
		number_to_2hex( xor_sum , result_string);			//string 으로 변환
		
//		sprintf(buff,"%02X", xor_sum);
//		strncpy( result_string, buff, 2);
	
}


static char *i2a(unsigned i, char *a, unsigned r)
{
    if (i / r > 0) 
        a = i2a(i / r, a, r);
    *a = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i % r];
    return a + 1;
}

char *itoa(int i, char *a, int r)
{
    if ((r < 2) || (r > 36))
        r = 10;
    if (i < 0) {
        *a = '-';
        *i2a(-(unsigned)i, a + 1, r) = 0;
    } else 
        *i2a(i, a, r) = 0;
    return a;
} 


char * floatToString(char * outstr, double val, uint8_t precision, uint8_t widthp){        // folat to String Converter
  char temp[16];
  uint8_t i;

  // compute the rounding factor and fractional multiplier
  double roundingFactor = 0.5;
  unsigned long mult = 1;
  for (i = 0; i < precision; i++)
  {
    roundingFactor /= 10.0;
    mult *= 10;
  }
  
  temp[0]='\0';
  outstr[0]='\0';

  if(val < 0.0){
    strcpy(outstr,"-\0");
    val = -val;
  }

  val += roundingFactor;

  strcat(outstr, itoa(((int)val),temp,10));  //prints the int part
  if( precision > 0) {
    unsigned long frac;
    unsigned long mult = 1;
    uint8_t padding = precision -1;
    unsigned long frac1;

    strcat(outstr, ".\0"); // print the decimal point
    while(precision--)
      mult *=10;

    if(val >= 0)
      frac = (val - ((int)val)) * mult;
    else
      frac = (((int)val)- val ) * mult;
     frac1 = frac;

    while(frac1 /= 10)
      padding--;

    while(padding--)
      strcat(outstr,"0\0");

    strcat(outstr,itoa(frac,temp,10));
  }

  // generate space padding 
  if ((widthp != 0)&&(widthp >= strlen(outstr))){
    uint8_t J=0;
    J = widthp - strlen(outstr);
    
    for (i=0; i< J; i++) {
      temp[i] = ' ';
    }

    temp[i++] = '\0';
    strcat(temp,outstr);
    strcpy(outstr,temp);
  }
  
  return outstr;
}



uint8_t data_checkSum(uint8_t * str, uint16_t lens) {
		uint8_t  sum=0;
		uint16_t i =0;
	//	while( * str != '\0' && i<256) {
		for(i=0;i<lens;i++){
			sum ^= * (str+i);		//xor 계산
			//i++;
		}
		return sum;
	
}

