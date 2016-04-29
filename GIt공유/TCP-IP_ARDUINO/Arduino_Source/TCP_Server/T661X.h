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

enum CO2Status { NO_ERR=0, WARMUP=1, CALIB=2, IDLE_MODE=3, SELF_TEST=7, DISCONNCTION=4 };
enum T661xControlStatus { DISC, READ_STATUS, STREAM, PPM_READING, TIME_OUT};


struct CO2_Data_t {
    uint16_t CO2_PPM;
//    float Elevation;
    uint8_t Status;
//    uint8_t mode;
};

struct CO2_CMD {
    char command[8];
    char receiveData[16];
    uint8_t cmdStatus;
  //  uint8_t dataSize;
   // uint16_t result;
    bool update;
   // uint32_t cycleTime;
};

extern char rxdString[30];    //Uart rxd buffer
extern CO2_Data_t CO2;
extern CO2_CMD T661x;
//#define READ_PPM_CMD  {0xFF,0xFE,0x02, 0x02, 0x03}
  
#define T661X_FLAG        0xFF
#define T661X_ADDRESS      0xFE
#define T661X_RESP          0xFA
#define T661X_CMD_READ      0x02
#define T661X_CMD_WRITE    0x01
#define T661X_SERIAL_NO    0x01

#define CMD_READ            0x02
#define CMD_READ_GAS_PPM    0x0203
#define CMD_STASUS          0xB6
#define CMD_STREAM_DATA     0xBD
#define CMD_READ_ELEVATION   0x020F

#define T661x_STREAM_CONTRL_TIME_OUT   5000      //STREAM Control TIme Out
#define T661x_NORMAL_CONTROL_TIME      2000    // Menual Control Cycle Time
void T661xStasusControl (void);
void readT661x_Status(void);
//uint16_t readT661xElevation (void);
//void T661xStreamStart (void);
void T661xInit(void);
void readT661x_PPM(void);


