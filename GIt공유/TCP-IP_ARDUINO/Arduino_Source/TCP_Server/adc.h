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

#define ADC_READ_CYCLE_TIME 100      //ms

 /**********************       Temperature Sensor      ************************/
 /*
 LM61-BIZ   
  100 degC = +1600mV
   85 degC = +1450mV
   25 degC = +850mV
    0 degC = +600mV
  -25 degC = +350mV
  -30 degC = +300mV
 */

    #define Temp_sensor_degFV     0.01      //degC/V
    #define Temp_sensor_0degC_V     0.6   // Output Voltage at 0˚C

    #define TEMP_PIN    A4      //PD4
    #define PRESSURE1_PIN    A3      //PD3
    #define PRESSURE2_PIN    A2      //PD2
 
 //   #define Temp_Reg_PullUp  1000      //ohm
 //   #define Temp_Reg_PullDown  1000    //ohm
 //   #define Temp_sensor_ADCRef     3.36    // ADC Ref Voltage
    #define Temp_sensor_ADCRef     3.163    // ADC Ref Voltage  v3 board

//    #define Temp_Reg_Ratio  ((float)Temp_Reg_PullDown/(Temp_Reg_PullUp+Temp_Reg_PullDown))
    #define Temp_Reg_Ratio  (float)1.0//((float)Temp_Reg_PullDown/(Temp_Reg_PullUp+Temp_Reg_PullDown))
    #define Temp_sensor_Offset     ((((float)Temp_sensor_0degC_V/Temp_sensor_ADCRef)*1023)*Temp_Reg_Ratio)
    #define Temp_sensor_divider   ((((float)Temp_sensor_degFV/Temp_sensor_ADCRef)*1023)*Temp_Reg_Ratio)
 

 /**********************       Pressure Sensor      ************************/
//    #define Press_sensor_MPaFV     1.5968      // 16mA*499ohm/5.0MPa =1.996 MPa/V
//    #define Press_sensor_0Mpa_V     1.996   // Output 4mA *499ohM = 1.996V
    #define Press_sensor_MPaFV     1.3761      // DIRECT MEASURING SET
    #define Press_sensor_0Mpa_V     1.690   // DIRECT MEASURING SET
    #define Press_Reg_PullUp  2000      //10kohm
    #define Press_Reg_PullDown  1000    //1kohm
    #define Press_sensor_ADCRef     3.163    // ADC Ref Voltage
    #define Press_Reg_Ratio  ((float)Press_Reg_PullDown/(Press_Reg_PullUp+Press_Reg_PullDown))
    #define Press_sensor_Offset     ((((float)Press_sensor_0Mpa_V/Press_sensor_ADCRef)*1023)*Press_Reg_Ratio)
    #define Press_sensor_divider   ((((float)Press_sensor_MPaFV/Press_sensor_ADCRef)*1023)*Press_Reg_Ratio)




void ADC_Measu (void);
void reaADC (void);
