
#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>

#include "string.h"
#include "Variables.h"
#include "config.h"
#include "func.h"
#include "adc.h"
#include "T661X.h"
#include "RHT.h"

#define HOME_LAN

char buff[20];    // * Measu point buffer
uint8_t errorCount =0;



// Enter a MAC address, IP address and Portnumber for your Server below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
#if defined HOME_LAN
IPAddress serverIP(192,168,219,12);
IPAddress gateway(192,168,219, 1);
#else
IPAddress serverIP(192,9,230,231);
IPAddress gateway(192,9,230, 254);
#endif
IPAddress subnet(255, 255, 255, 0);
int serverPort=2500;
 
// Initialize the Ethernet server library
// with the IP address and port you want to use
EthernetServer server(serverPort);
boolean alreadyConnected = false; // whether or not the client was connected previously 
 
//String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete 
str_Data clientStr;
char strBuffer[100]; 

 
void setup() {
      extSensorBoard_Reset();
     pinMode(W5200_REST_PIN,OUTPUT);
    digitalWrite(W5200_REST_PIN,LOW);
    delay(1000); 
    digitalWrite(W5200_REST_PIN,HIGH);
    T661xInit();
    //  UART_Init();
    // reserve 200 bytes for the inputString:
    //inputString.reserve(50);
    
    
    // start the Ethernet connection and the server:
    //  Ethernet.begin(mac, serverIP);
    Ethernet.begin(mac, serverIP, gateway, subnet);
    server.begin();
     Init_RHT();
     pinMode(LED_PIN,OUTPUT);
     LED_OFF;
    
    wdt_enable (WDTO_8S);  // reset after one second, if no "pat the dog" received
    Measu = ( all_Data *)buff;
}



void loop() { ///////////////////////////////////////////////////-------------------------main loop ----------------------------------------------

  static uint8_t i =0;
  static char  clientString[100];
  
  // wait for a new client:
  EthernetClient client = server.available();
      if(client.connected()) {
          if (client) {
            if (client.available() > 0) {
            // read the bytes incoming from the client:
            char thisChar = client.read();
              if(thisChar == '\n') {
                cliSet(clientString);
                
                  i=0;
      
                   //   thisChar="";
              }
              else {
                clientString[i] = thisChar;
                i++;
           //     thisChar="";
              }
          }
          }  //if(client)
      }
      else {
          delay(1);    //receive the data wait
          client.stop();
      }
  
       reaADC();      //---------------------- Pressure & PCB Temperture Measuring    ------------------//
       T661xStasusControl();    //-----------------CO2 SENSOR Measuring--------------------// 
       readRHT_Sensor();  //-----------------Temperature & Humidity  Measuring--------------------// 
       

       Measu->Status = (0xF0 & (RHT.Status<<4)) | (CO2.Status & 0x0F);

  // when the client sends the first byte, say hello:
 // if (client) {
 //   if (!alreadyConnected) {
      // clead out the input buffer:
 //    client.flush();    
 //     Serial.println("We have a new client");
  //    client.println("Hello, client!"); 
 //     alreadyConnected = true;
 //   } 

       if(RHT.Status == MEAS_OK) {
         errorCount=0;
       }
       else {
         errorCount++;
       }

       if(errorCount < 3) {
          wdt_reset ();  // give me another second to do stuff (pat the dog)
       }

} //-------------------------------------------------------------------------------end main loop  ----------------------------------


const clivalue_t valueTable[] = {
    {"CO2", CO2_PPM  },
    { "Temp",RHT_Temp  },
    { "Humi", RHT_Humi  },
    { "RHT_STAT",  },
    { "Pressure1", P1_Press },
    { "Pressure2", P2_Press },
    { "PCB_TEMP", PCB_Temp },
    { "STATUS", STATUS },
 //   { "ALL", PCB_Temp },
    
};

void ALL_VALUE (void) {
    char  strbuf[100];
    char length_str[3] ={'\0','\0','\0'};
    char chekSumStr[3] ={'\0','\0','\0'};
    char * name = (char *)"ALL=";
    char  checkSum=0;
    uint8_t j=0;
    char * pStr = &strBuffer[0];
    
    memset(strbuf,'\0',sizeof(strbuf));
    memset(strBuffer,'\0',sizeof(strBuffer));

//    strcat(strBuffer,"ALL=");

    memset(strbuf,'\0',sizeof(strbuf));
    floatToString(strbuf,CO2.CO2_PPM,0,6);
    strcat(strBuffer,strbuf);
    strcat(strBuffer,",");

    memset(strbuf,'\0',sizeof(strbuf));
    floatToString(strbuf,(float)RHT.Temp/10,1,3);
    strcat(strBuffer,strbuf);
    strcat(strBuffer,",");


    memset(strbuf,'\0',sizeof(strbuf));
    floatToString(strbuf,(float)RHT.Humi/10,1,3);
    strcat(strBuffer,strbuf);
    strcat(strBuffer,",");

    memset(strbuf,'\0',sizeof(strbuf));
    floatToString(strbuf,Measu->PCB_Temp,1,4);
    strcat(strBuffer,strbuf);
    strcat(strBuffer,",");

    memset(strbuf,'\0',sizeof(strbuf));
    floatToString(strbuf,Measu->P1_Press,2,4);
    strcat(strBuffer,strbuf);
    strcat(strBuffer,",");

    memset(strbuf,'\0',sizeof(strbuf));
    floatToString(strbuf,Measu->P2_Press,2,4);
    strcat(strBuffer,strbuf);
    strcat(strBuffer,",");


    memset(strbuf,'\0',sizeof(strbuf));
    num_2hex(Measu->Status,strbuf);
    strcat(strBuffer,strbuf);
    strcat(strBuffer,",");
    
    //cheksum 
    for(j=0;j < strlen(strBuffer);j++) {
      if((* pStr) != ',') {
          checkSum ^= (*pStr); 
      }
        pStr++;
    }
    num_2hex(checkSum,chekSumStr);
    strcat(strBuffer,chekSumStr);
    
    //value string to heaer input
    memmove(strBuffer +strlen(name) ,strBuffer, strlen(strBuffer));  //name inpu space move
    memmove(strBuffer,name,strlen(name));

    //write to TCP/IP
    num_2hex(strlen(strBuffer),length_str);
    server.write(length_str);
    server.write(strBuffer);
}


void STATUS (void) {
   // uint8_t value = 0;
    static char statStr[3]={'\0','\0','\0'};
    
   // value = ((0x0F&Measu->CO2_Status)<<8) | (0x0F&Measu->RHT_Status) ;
    num_2hex(Measu->Status,statStr);
    clientStr.Name =(char *)"STAT=";
    memcpy(strBuffer, statStr, 3);
    clientStr.valueStr = strBuffer;

}
 
 
void CO2_PPM (void) {
    clientStr.Name =(char *)"CO2=";
    clientStr.valueStr = floatToString(strBuffer,CO2.CO2_PPM,0,6);

}

void RHT_Temp (void) {
    clientStr.Name =(char *)"TEMP=";
    clientStr.valueStr = floatToString(strBuffer,(float)RHT.Temp/10,1,3);
} 

void RHT_Humi (void) {
    clientStr.Name =(char *)"Humi=";
    clientStr.valueStr = floatToString(strBuffer,(float)RHT.Humi/10,1,3);
}
void PCB_Temp (void) {
      clientStr.Name =(char *)"PCB_Temp=";
      clientStr.valueStr = floatToString(strBuffer,Measu->PCB_Temp,1,4);
}

void P1_Press (void) {
      clientStr.Name =(char *)"Pressure1=";
      clientStr.valueStr = floatToString(strBuffer,Measu->P1_Press,2,4);
}
void P2_Press (void) {
      clientStr.Name =(char *)"Pressure2=";
      clientStr.valueStr = floatToString(strBuffer,Measu->P2_Press,2,4);
}

void Error (void) {
      clientStr.Name =(char *)"Error=";
      clientStr.valueStr =(char *)"No Value";
}

void writeString (str_Data data) {
    char sum_string[50];
    char length_str[2];
     
    memset(sum_string,'\0',sizeof(sum_string));
    memset(length_str,'\0',sizeof(length_str));
    strcpy(sum_string,data.Name);
    strcat(sum_string, data.valueStr);    //문자열 합침
    num_2hex(strlen(sum_string),length_str);
    
    server.write(length_str);
    server.write(sum_string);
}


#define VALUE_COUNT (sizeof(valueTable) / sizeof(valueTable[0]))   

 void cliSet(char *cmdline){
    uint8_t k;
    uint16_t len;
    const clivalue_t *val;
   
    len = strlen(cmdline);
          void (*Func) (void);    
//      if (len == 1 && cmdline[0] == '?') {
      if (strncasecmp(cmdline, "all",3)==0 ) {
          ALL_VALUE();
/*
        for (k = 0; k < 8; k++) {
//              val = &valueTable[i];
              if(valueTable[k].function!=NULL) {
                  Func = valueTable[k].function;		//관련된 함수 호출
                  Func();
                  writeString(clientStr);
              }
          }
*/

     RHT_Temp();
                       writeString(clientStr);

      }
       else{
 
          for (k = 0; k < VALUE_COUNT; k++) { 
              val = &valueTable[k];
              if(strncasecmp(cmdline,valueTable[k].name,strlen(valueTable[k].name)) ==0) {
                  if(valueTable[k].function!=NULL) {
                      Func = valueTable[k].function;		//관련된 함수 호출
                      Func();
                  }
                  writeString(clientStr);
                return;
              }
            
          }
          Error();                     
          writeString(clientStr);
             //not value
       }

}






