#include "Variables.h"
#include "func.h"
#include "adc.h"
#include "T661X.h"
#include "RHT.h"
#include "config.h"


void ADC_Measu (void) {
  static float PCB_temp=((((float)analogRead(TEMP_PIN)-Temp_sensor_Offset))/Temp_sensor_divider);
  static float Pressure1=((((float)analogRead(PRESSURE1_PIN)-Press_sensor_Offset))/Press_sensor_divider);
  static float Pressure2=((((float)analogRead(PRESSURE2_PIN)-Press_sensor_Offset))/Press_sensor_divider);




        analogReference(DEFAULT);    //MCU DEFULT AVCC 3.3V ADC Ref
        float temp = ((((float)analogRead(TEMP_PIN)-Temp_sensor_Offset))/Temp_sensor_divider);     //0 ~ 100 deg_C Display


    //    analogReference(INTERNAL);    //MCU Internal 1.1V ADC Ref
        float press1=((((float)analogRead(PRESSURE1_PIN)-Press_sensor_Offset))/Press_sensor_divider);
        float press2=((((float)analogRead(PRESSURE2_PIN)-Press_sensor_Offset))/Press_sensor_divider);
//            Pressure1 =press1;
//            Pressure2 =press2;
            
          PCB_temp = (PCB_temp *9 + temp)/10;    ////온도값의 이동평균처리
          Pressure1 = (Pressure1*4 + press1)/5;  // 압력센서1 이동평균처리
          Pressure2 = (Pressure2*4 + press2)/5;  // 압력센서2 이동평균처리

          Measu->P1_Press = Pressure1;
          Measu->P2_Press = Pressure2;
          Measu->PCB_Temp = PCB_temp;

}

void reaADC (void) {
    uint32_t msNow;
    static uint32_t  controlCycleTime, elapsedTime, oldTime;
    msNow = millis();
    elapsedTime = elapsedTime + (msNow - oldTime);
    oldTime = msNow;   

    if(controlCycleTime + ADC_READ_CYCLE_TIME <= elapsedTime) {   // TIME 의 간격으로 실행
        controlCycleTime = elapsedTime;
        ADC_Measu();
    }
  
}



