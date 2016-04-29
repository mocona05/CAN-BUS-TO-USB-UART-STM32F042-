#include "Variables.h"
#include "config.h"
#include "T661X.h"
char rxdString[30];    //Uart rxd buffer
CO2_CMD T661x;
CO2_Data_t CO2;




void T661xInit(void) {
    memset(rxdString,'\0',sizeof(rxdString));
    Serial.begin(19200);
    T661x.cmdStatus = DISC;
    CO2.Status = DISCONNCTION;
    T661x.update=false;
  //  T661x.result =0x00;
 //   T661x.result =0x01;

}



void readT661x_Status(void) {
    memset(T661x.command,'\0',sizeof(T661x.command));
    T661x.command[0] = T661X_FLAG;
    T661x.command[1] = T661X_ADDRESS;
    T661x.command[2] = 0x01;    //data size
    T661x.command[3] = CMD_STASUS;    // data  
    T661x.cmdStatus = READ_STATUS;
    while (Serial.read() >= 0);    //serial buffer clear
    memset(rxdString,'\0',sizeof(rxdString));  //rxd 수신버퍼 클리어
    Serial.print(T661x.command);  //Status 전송 요청
}

void readT661x_PPM(void) {
    memset(T661x.command,'\0',sizeof(T661x.command));
    T661x.command[0] = T661X_FLAG;
    T661x.command[1] = T661X_ADDRESS;
    T661x.command[2] = 0x02;    //data size
    T661x.command[3] = T661X_CMD_READ;    // data  
    T661x.command[4] = 0x03;    // data  
    T661x.cmdStatus = PPM_READING;
    while (Serial.read() >= 0);    //serial buffer clear
    memset(rxdString,'\0',sizeof(rxdString));  //rxd 수신버퍼 클리어
    Serial.print(T661x.command);  //OC2 PPM 전송 요청
}

inline void T661xStreamStart (void) {
     memset(T661x.command,'\0',sizeof(T661x.command));
     T661x.command[0] = T661X_FLAG;
     T661x.command[1] = T661X_ADDRESS;
     T661x.command[2] = 0x01;    //data size
     T661x.command[3] = CMD_STREAM_DATA;    // command
     T661x.cmdStatus = STREAM;
    while (Serial.read() >= 0);    //serial buffer clear
    memset(rxdString,'\0',sizeof(rxdString));  //rxd 수신버퍼 클리어
    Serial.print(T661x.command);  //STREAM MODE START 요청
}

void T661xStasusControl (void) {
 //   bool timeOutF = false;
    uint32_t msNow;
  //  static uint32_t oldTime=millis();
    static uint32_t  controlCycleTime, elapsedTime, oldTime;
    msNow = millis();
    elapsedTime = elapsedTime + (msNow - oldTime);
    oldTime = msNow;   

    
    switch(T661x.cmdStatus) {
        case DISC:
          LED_OFF;
         CO2.Status = DISCONNCTION;
     //     readT661x_Status();
          T661x.cmdStatus =  READ_STATUS;
          break;
          
        case READ_STATUS:
          if(CO2.Status == NO_ERR){
      //      T661x.cycleTime =0;    // STREAM Time Out Timer Reset 
            T661xStreamStart();        //상태값에 에러가 없다면 스트리밍 모드 시작
            controlCycleTime = elapsedTime;
          }
          else {
              if(controlCycleTime +T661x_NORMAL_CONTROL_TIME <= elapsedTime) {   //T661x_NORMAL_CONTROL_TIME 의 간격으로 실행
                  controlCycleTime = elapsedTime;
                  LED_TOGGLE;
                  readT661x_Status();        //에러가 있다면 상태값을 다시 읽어옴
              }
          }
          break;
        case STREAM:
             LED_ON;
             if(T661x.update==true) {
                  T661x.update=false;
                  controlCycleTime = elapsedTime;
             } 
             if(controlCycleTime +T661x_STREAM_CONTRL_TIME_OUT <= elapsedTime) {   //STREAM CONTROL TIME OUT
                T661x.cmdStatus = DISC;
                 LED_OFF;
             }        
        
//            T661x.cmdStatus = (T661xStreamTimeOutCheck()?STREAM:DISC);    //Time out check
            break;
    }

}

void serialEvent(void) {
  const char header[3] = {T661X_FLAG,T661X_RESP,'\0'};    //0xFF, 0xFA
  static char * ptr =NULL,* pStr = &rxdString[0]; 
  while (Serial.available()) {
    if( pStr- (&rxdString[0]) >= sizeof(rxdString)) {   //오버플로워 방지
        pStr = &rxdString[0];
    } 
    if(&rxdString[0] == '\0') {  // clear 감지
        pStr = &rxdString[0];
    }   
      * pStr= (char )Serial.read(); 
      pStr++;

      ptr = (strstr(rxdString, header));  // 수신 문자열에 헤더값이 있는지 검색
      if( ptr !='\0' && '\0'!= (*(ptr+2)) && (* (ptr+2)) <= (pStr- (ptr+3))) {    //수신받은문자와 수신헤더와 일치하며 data길이 != null 이며 data갯수가 수신받은 data 갯수가 일치하거나 클경
               memset(T661x.receiveData,'\0',sizeof(T661x.receiveData));
              memcpy(T661x.receiveData,  (ptr+3),  * (ptr+2) );    //DATA 만 카피
         //     T661x.dataSize = *(ptr+2);
             switch(T661x.cmdStatus) {
                 case READ_STATUS:
                      CO2.Status = (0xFF & T661x.receiveData[0]);
                      break;

                 case STREAM:
                 case PPM_READING:
                    CO2.CO2_PPM = ((0xFF & T661x.receiveData[0])<<8) + (0xFF & T661x.receiveData[1]);
                    break;             
             }
/*             
              if( (* (ptr+2)) >1) {    // 수신받은 data 2byate일경우 
                // T661x.result =  ((0xFF & T661x.receiveData[0])<<8) + (0xFF & T661x.receiveData[1]);
              }
              else {      //수신받은 data가 1byte일경우
                T661x.result = (0xFF & T661x.receiveData[0]);
              }
*/              
              memset(rxdString,'\0',sizeof(rxdString));
              pStr = &rxdString[0];
              T661x.update = true;
       }
  }
}

/*

inline uint8_t sensorRead (void) {
   uint32_t msNow;
   uint32_t oldTime=0;
   uint32_t elapsedTime=0;
   uint8_t sensor_status=0;


     oldTime = millis();
      while( !T661x.update) {
           msNow = millis();
           elapsedTime = elapsedTime + (msNow - oldTime);
           oldTime =  msNow;
           if(elapsedTime>T661x_STREAM_CYCLE_TIME) {    //Response Time out check
               sensor_status =TIMEOUT;
               break;
           }
           else {
               sensor_status = OK;
           }
      }
       Serial.print('0');
//      Serial.print(T661x.update);
 //      return sensor_status;
}
*/

/*
uint8_t communiSensor (CO2_CMD * cmd) {
 //  uint16_t gas_ppm =0x00;
   char command[7];
   char *pStr ;
   char *pCmd = cmd->command;
   char *pValue = cmd->value;
   uint8_t length=0;
   uint32_t msNow;
   uint32_t oldTime=0;
   uint32_t elapsedTime=0;
    uint8_t i=0;
    uint8_t sensor_status=0;

   memset(command,'\0',sizeof(command));
   while( *pCmd !='\0') {    //data길이 계산
     command[3+length] =  * pCmd;
     length++;
     pCmd++;
   }
   command[2] = length;
   command[0] = T661X_FLAG;
   command[1] =T661X_ADDRESS;

    serial_flush_buffer();    //Serial Buffer Clear !!

    Serial.print(command);
    memset(command,'\0',sizeof(command));
    pStr = &command[0];

     oldTime = millis();
      while( i <  cmd->respNum+3) {    //HEADER + ADDRESS+ DATA
          if (Serial.available()) {
            * pStr = Serial.read();
            pStr++;
            i++;
          }
          
          else {    //Time Out Check
              msNow = millis();
             elapsedTime = elapsedTime + (msNow - oldTime);
             oldTime =  msNow;
             if(elapsedTime>T661x_Response_time) {    //Response Time out check
                 sensor_status =TIMEOUT;
                 break;
             }
          } 
       }//while
      if(sensor_status != TIMEOUT) {
          if((0xFF &command[0]) == T661X_FLAG && (0xFF & command[1]) == T661X_RESP ) {        //header command OK
              for(i=0;i < command[2];i++) {
                 *pValue = command[i+3];
                 pValue++;
               }
           //   gas_ppm = ((0xFF & command[3])<<8) + (0xFF & command[4]);
              sensor_status = OK;
          
          }
          else {
              sensor_status = CHEKSUM_ERR;
          }
        
   //     return gas_ppm;
      return sensor_status;
      }
}

*/
/*
uint16_t readT661xElevation (void) {
     uint16_t elevation =0x00;
     CO2_CMD sendData;
     uint8_t cmdStatus=0;
     memset(sendData.command,'\0',sizeof(sendData.command));
 //    memset(sendData.value,'\0',sizeof(sendData.value));
     sendData.command[0] = 0x02;
     sendData.command[1] = 0x0F;
  //   sendData.respNum=2;

      if(sensorRead() == OK) {
        // elevation = ((0xFF & sendData.value[0])<<8) + (0xFF & sendData.value[1]);    //feet
        elevation = T661x.result; 
      } 
    return  elevation;
}

*/
