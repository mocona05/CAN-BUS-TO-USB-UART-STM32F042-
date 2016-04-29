/******************************************************************
  DHT Temperature & Humidity Sensor library for Arduino.
  CO2 SENSOR (T661X)
  Features:


  Changelog:
   2014-02-26: Initial version
 ******************************************************************/
#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

extern all_Data   * Measu ;

void num_2hex(uint8_t number, char * string);           // UART 2-digit hex number 
char * floatToString(char * outstr, double val, byte precision, byte widthp);        // folat to String Converter
//static char *ftoa(float x, char *floatString);
void extSensorBoard_Reset (void);

