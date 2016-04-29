/******************************************************************
  DHT Temperature & Humidity Sensor library for Arduino.
  CO2 SENSOR (T661X)
  Features:


  Changelog:
   2014-02-26: Initial version
 ******************************************************************/
#include "stddef.h"

//extern all_Data Meas;
extern uint8_t errorCount;


#define EXT_SENSOR_BOARD_RESET_PIN   7
#define W5200_REST_PIN       4
#define LED_PIN        A1
#define   LED_OFF        digitalWrite(LED_PIN,LOW)
#define   LED_ON        digitalWrite(LED_PIN,HIGH)
#define   LED_TOGGLE    digitalWrite(LED_PIN,!digitalRead(LED_PIN))
 
// Thanks to Maurice Beelen, nms277, Akesson Karlpetter, and Orly Andico for these fixes.
#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
  #include <new.h>
  #include <wiring_private.h> // cby and sbi defined here
#else
  #include <WProgram.h>
  #include <pins_arduino.h>
  #ifndef   LIBCALL_PINCHANGEINT
    #include "../cppfix/cppfix.h"
  #endif
#endif





