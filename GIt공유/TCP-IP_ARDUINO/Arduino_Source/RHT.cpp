#include "Variables.h"
#include "config.h"
#include "RHT.h"
#include "PinChangeInt.h"

uint8_t pulseCount=0;
uint8_t time_us[50];
 RHT_Data RHT;

inline void decodeBit (void) {      //RHT-xx data pin Pin Change Measuring
  static uint32_t lastTime=0, RisingTime=0;
  uint32_t microNow = micros();
    if (PCintPort::pinState==HIGH) {
        RisingTime = microNow;
    }
    else {
        time_us[pulseCount]  =(uint8_t) (microNow - RisingTime);
        pulseCount++;
    }
    lastTime = microNow;
 
}


//inline void RHT_SensorControl(RHT_Data * data) {
inline void RHT_SensorControl(void) {

  uint8_t dataString[5]={0,0,0,0,0};
    uint8_t *pString = &dataString[0];
    uint32_t timeoutStart;
    uint8_t sensor_status=0, byte_sum=0;
    uint16_t data_sum=0;

    pinMode(DATA_PIN, INPUT);// digitalWrite(DATA_PIN, HIGH);
//    PCintPort::attachInterrupt(DATA_PIN, &decodeBit, CHANGE);    
    RHT.Status = DISCONNECT;

    digitalWrite(DATA_PIN,LOW);
    pinMode(DATA_PIN,OUTPUT);
//    digitalWrite(DATA_PIN,LOW);
    delayMicroseconds(START_DELAY);
    pinMode(DATA_PIN,INPUT);
    delayMicroseconds(WAIT_DELAY);
    timeoutStart = millis();
    pulseCount=0;
    memset(time_us,0,sizeof(time_us));
    
        while(pulseCount < 41) {
           if((timeoutStart + RHT_TIME_OUT) < millis()) {    //Start Sync Signal Time out Check !!
               RHT.Status = TIMEOUT;
               return;              //break while loop
           }
        }  //while 
          if(sensor_status != TIMEOUT) {      //all data receive   
              if(time_us[0] < BIT_HIGH_TIME) {    //sensor response check
                   RHT.Status = DISCONNECT;
                   return;
              }
              else {    //sensor response OK!
                    for(uint8_t j=0;j<5;j++) {      // receive sensor data 5byte copy
                      for(uint8_t k=0;k<8;k++) {
                          pString[j] = (pString[j]<<1) + (time_us[(j*8)+k+1] >= BIT_HIGH_TIME? 1:0);    //Sync Pulse는 제외 하기 위해서 k+1 함
                      }
                      if(j<4) {
                          data_sum += pString[j];//  no data check 
                          byte_sum += pString[j];    //temp & humi data sum , last 8bit data
                      }  
                   }
                   if(byte_sum == pString[4] && data_sum != 0) {    //check sum & data value checking
                       RHT.Status = MEAS_OK;
                       RHT.Humi = (uint16_t)(dataString[0]<<8) + (dataString[1]);    //humidity *10 
                       RHT.Temp = (uint16_t)(dataString[2]<<8) + (dataString[3]);    //temperature *10
                       return;
                   }
                   else {      //check sum error
                       RHT.Status = CHEKSUM_ERR;
                       return;
                   }
              }// Sensor response check
          }    //if(sensor_status != TIMEOUT)

//    if(data->Status == MEAS_OK) {    // Measuring Data Update
//    }
}

void Init_RHT (void) {
    pinMode(DATA_PIN, INPUT); digitalWrite(DATA_PIN, HIGH);
    PCintPort::attachInterrupt(DATA_PIN, &decodeBit, CHANGE);    
    RHT.Status = DISCONNECT;
}


void readRHT_Sensor (void) {
    uint32_t msNow;
    static uint32_t  controlCycleTime, elapsedTime, oldTime;
    msNow = millis();
    elapsedTime = elapsedTime + (msNow - oldTime);
    oldTime = msNow;   

    if(controlCycleTime + RHT_READING_CYCLE_TIME <= elapsedTime) {   // TIME 의 간격으로 실행
        controlCycleTime = elapsedTime;
//        RHT_SensorControl(&RHT);
        RHT_SensorControl();
    }
  
}


/*
inline uint8_t readRHT(uint8_t * data)  {    // RHT sensor receive value to bit
    uint32_t timeoutStart;
    uint8_t sensor_status=0, sum_value=0;
    

    uint8_t *pString = data;
    pinMode(DATA_PIN,OUTPUT);
    digitalWrite(DATA_PIN,LOW);
    delayMicroseconds(START_DELAY);
    pinMode(DATA_PIN,INPUT);
    delayMicroseconds(WAIT_DELAY);
    timeoutStart = millis();
    pulseCount=0;
    memset(time_us,0,sizeof(time_us));
        while(pulseCount < 41) {
           if((timeoutStart + RHT_TIME_OUT) < millis()) {    //Time out !!
               sensor_status = TIMEOUT;
               return sensor_status;      //break for loop
           }
        }  //while 
          if(sensor_status != TIMEOUT) {      //all data receive   
              if(time_us[0] < BIT_HIGH_TIME) {    //sensor response check
                    sensor_status = DISCONNECT;
                    return sensor_status; 
              }
              else {    //sensor response OK!
                    for(uint8_t j=0;j<5;j++) {      // receive sensor data 5byte copy
                      for(uint8_t k=0;k<8;k++) {
                          pString[j] = (pString[j]<<1) + (time_us[(j*8)+k+1] >= BIT_HIGH_TIME? 1:0);    //Sync Pulse는 제외 하기 위해서 k+1 함
                      }
                      if(j<4) {
                          sum_value += pString[j];    //temp & humi data sum , last 8bit data
                      }  
                   }
                   
                   if(sum_value == pString[4]) {    //check sum checking
                       sensor_status = MEAS_OK;
                   }
                   else {      //check sum error
                       sensor_status = CHEKSUM_ERR;
                   }
                  return sensor_status;
              }// Sensor response check
          }    //if(sensor_status != TIMEOUT)
                  return sensor_status;
}
*/

