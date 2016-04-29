#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

typedef struct  {
    uint16_t   CO2_PPM;
 //   uint8_t   CO2_Status;
    int16_t   RHT_Temp;
    uint16_t  RHT_Humi;
    uint8_t   Status;
    float  PCB_Temp;
    float   P1_Press;
    float   P2_Press;
    
}all_Data;

 //all_Data   * Measu ;

typedef struct {
    const char *name;
  //  const uint8_t type; // vartype_e
 //   void *ptr;
 //   const int32_t min;
 //   const int32_t max;
	
	void (* function) (void);
	
} clivalue_t;

/*
typedef enum {
    VAR_UINT8,
    VAR_INT8,
    VAR_UINT16,
    VAR_INT16,
    VAR_UINT32,
    VAR_FLOAT
} vartype_e;
*/


/*
struct rcData_t
{
 uint32_t microsRisingEdge;
 uint32_t microsLastUpdate;
 uint16_t rx;
 bool     update;
 bool     valid;
 float    rcSpeed;
 float    setpoint;
};

rcData_t rcData[RC_DATA_SIZE];
float rcLPF_tc = 1.0;

struct config_t
{
  int16_t rcGain;
  int16_t rcLPF;             // low pass filter for RC absolute mode, units=1/10 sec
  bool rcModePPM;            // RC mode, true=common RC PPM channel, false=separate RC channels 
  int8_t rcChannelPitch;     // input channel for pitch
  int8_t rcChannelRoll;      // input channel for roll
  int16_t rcMid;             // rc channel center ms
}config;


void setDefaultParameters(){
    config.rcGain = 5;
    config.rcLPF = 20;  
    config.rcModePPM = false;
    config.rcMid = MID_RC;
}


enum rcInput { PPM=0, CPPM=1 };

*/
