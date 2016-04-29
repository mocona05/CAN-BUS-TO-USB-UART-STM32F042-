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

#define RHT_READING_CYCLE_TIME    2500    //RHT-03 interval of whole process must beyond 2 seconds [ms]
#define START_DELAY  2000      //RHT-03 1ms minimum
#define WAIT_DELAY  36      //RHT-03 20~40us minimum
#define DATA_PIN    8      //PB0
#define BIT_HIGH_TIME  60    // bit 0 = 26~28us,  bit 1 = 70us
#define RHT_TIME_OUT  20    //time out 20ms

enum rhtStatus { DISCONNECT, TIMEOUT, MEAS_OK, CHEKSUM_ERR};

struct str_Data {
 char   * Name;
 char   * valueStr;
};

struct RHT_Data {
 int16_t Temp;
 uint16_t Humi;
 uint8_t Status;
};

extern RHT_Data RHT;

//void RHT_Value (RHT_Data * data);
void Init_RHT (void);
void readRHT_Sensor(void);
