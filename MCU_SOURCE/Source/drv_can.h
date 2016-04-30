#pragma once


//extern CanTxMsg TxMessage;

//rxd id
//#define CAN_ID_AFR  0x1FF
//#define CAN_ID_ASIC_STAT1  0x300
//#define CAN_ID_ASIC_STAT2  0x301
//#define CAN_ID_ASIC_RAW  0x302
//#define CAN_ID_ADC  0x304


//인디게이터는 컨트로러와 송수신 주소가 바뀜
#define CAN_ID_TRANSCEIVER_CONFIG  0x010
#define CAN_ID_RECEIVE_CONFIG  0x011


#define GPS_COORD_ID					0x30
#define GPS_ALT_SPEED_ID		0x31
#define RTC_VALUE_ID				0x33

#define RC_SIGNAL1_ID				0x80
#define RC_SIGNAL2_ID				0x81




#define IMU_1_ROLL_PITCH_ID			0x021
#define IMU_YAW_ID											0x022
#define IMU_2_ROLL_PITCH_ID			0x023
#define CAMERA_CONTROL_ID			0x024
#define CAMERA_STATUS_ID		0x025

//txd id
#define ADC_STAT_ID		0x508




#define CAN_BAUDRATE_1000      /* 1MBps   */
//#define CAN_BAUDRATE_500	// 500kBps 

//#define CAN_ALT_FUNCTION_USE

#define CAN_MSG_CH_NO  MAX_CTAS_T_CH_NUM

/* #define CAN_BAUDRATE  250*/  /* 250kBps */
/* #define CAN_BAUDRATE  125*/  /* 125kBps */
/* #define CAN_BAUDRATE  100*/  /* 100kBps */ 
/* #define CAN_BAUDRATE  50*/   /* 50kBps  */ 
/* #define CAN_BAUDRATE  20*/   /* 20kBps  */ 
/* #define CAN_BAUDRATE  10*/   /* 10kBps  */ 
/* Private macro -------------------------------------------------------------*/
//extern CanTxMsg TxMessage;;
//extern CanTxMsg CTAS1;
//extern CanTxMsg CTAS_MSG[];
//extern CanTxMsg CTAST_Reg1;
//extern CanTxMsg CTAST_Reg2;
//extern CanTxMsg CTAST_Reg3;
//extern CanTxMsg CTAST_Reg4;
extern CanTxMsg SYSTEM_ETC;

#define __CAN1_USED__  
#ifndef CAN_ALT_FUNCTION_USE
	#define CANx		CAN
  #define CAN_GPIO_CLK   		  RCC_AHBPeriph_GPIOA       
	#define CAN_CLK										RCC_APB1Periph_CAN
  #define CAN_GPIO_PORT       GPIOA  
  #define CAN_RX_PIN             GPIO_Pin_11
  #define CAN_TX_PIN             GPIO_Pin_12
  #define CAN1_RX_PIN_Source            GPIO_PinSource11
  #define CAN1_TX_PIN_Source            GPIO_PinSource12
	
	#define CAN_AF_PORT			GPIO_AF_4
	
#else
  #define RCC_APB2Periph_GPIO_CAN1    RCC_APB2Periph_GPIOB       
  #define GPIO_CAN1                   GPIOB  
  #define GPIO_Pin_CAN1_RX            GPIO_Pin_8
  #define GPIO_Pin_CAN1_TX            GPIO_Pin_9
#endif

//#ifdef  __CAN1_USED__
//  #define CANx                       CAN1
//  #define GPIO_CAN                   GPIO_CAN1
//  #define GPIO_Remapping_CAN         GPIO_Remap1_CAN1
//  #define GPIO_CAN                   GPIO_CAN1
//  #define GPIO_Pin_CAN_RX            GPIO_Pin_CAN1_RX
//  #define GPIO_Pin_CAN_TX            GPIO_Pin_CAN1_TX

// #else /*__CAN2_USED__*/
//  #define CANx                       CAN2
//  #define GPIO_CAN                   GPIO_CAN2
////  #define GPIO_Remapping_CAN             GPIO_Remap_CAN2
//  #define GPIO_CAN                   GPIO_CAN2
//  #define GPIO_Pin_CAN_RX            GPIO_Pin_CAN2_RX
//  #define GPIO_Pin_CAN_TX            GPIO_Pin_CAN2_TX
// #endif  /* __CAN1_USED__ */



typedef struct can_txd_list_t{
	uint32_t resendTime;
	bool (*function)(uint32_t  );
	uint32_t  StdId;
	
}can_txd_list_t;

typedef struct can_rxd_t{
	uint16_t  StdId;
	uint8_t	ExtId;
	uint32_t IDE;
	uint8_t DLC;
	uint8_t FMI;
}can_rxd_t;



typedef struct
{
  uint32_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

  uint32_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

  uint8_t IDE;     /*!< Specifies the type of identifier for the message that 
                        will be received. This parameter can be a value of 
                        @ref CAN_identifier_type */

  uint8_t RTR;     /*!< Specifies the type of frame for the received message.
                        This parameter can be a value of 
                        @ref CAN_remote_transmission_request */

  uint8_t DLC;     /*!< Specifies the length of the frame that will be received.
                        This parameter can be a value between 0 to 8 */

  uint8_t Data[8]; /*!< Contains the data to be received. It ranges from 0 to 
                        0xFF. */

  uint8_t FMI;     /*!< Specifies the index of the filter the message stored in 
                        the mailbox passes through. This parameter can be a 
                        value between 0 to 0xFF */
} CanQueueType;
//FMI는 수신시에만 해당되므로 메모리 카피시 주의!!

typedef struct can_rxd_type_t{
void *ptr;
uint32_t id;
uint32_t IDE;	//CAN_ID_STD
uint8_t DLC;
uint8_t start_bit;
uint8_t bit_length;
const uint8_t type; // vartype_e
double scale;
double offset;
void (*function)(void);

}can_rxd_type_t;


typedef struct can_rxd_data_list_t{
	
	//imu1 roll pitch 
		int32_t imu1_roll;
		int32_t imu1_pitch;
		int32_t imu1_yaw;
	
		int32_t imu2_roll;
		int32_t imu2_pitch;
		int32_t imu2_yaw;
	
		uint16_t sensor_board_loop_time_us;
	
		uint16_t light_adc;
		int16_t light_differen;
		bool shutter_status;
		bool focus_status;
		bool capture_complit_falg;
		bool capture_time_out_falg;
		bool save_data_flag;
	
		uint16_t trig_count;
		uint16_t photo_count;
	

}can_rxd_data_list_t;
	
	

extern can_rxd_data_list_t rxd_data;


void can_bus_init(void);

void CAN_TXD(void);

static void CAN_Config(void);
//static void NVIC_Config(void);

void Init_RxMes(CanRxMsg *RxMessage);     


#ifndef STM32F10X_CL
void USB_LP_CAN1_RX0_IRQHandler(void);
#else
void CAN1_RX0_IRQHandler(void);
#endif


//static bool write_room_condition(uint32_t id);
static bool adc_condition(uint32_t id);
static uint8_t  CAN_TXD_enQueue_Config(void);
static uint8_t  CAN_RXD_queue_to_deQueue_Config(void);

static void data_set_value(const can_rxd_type_t * var, const int32_t value);
//static void CAN_RXD_data_update(CanQueueType * rxd_data) ;
//static uint8_t CAN_TXD_enQueue_Config(void);
static void CAN_TXD_sterimming (void );

static void CAN_RXD_data_update(const CanQueueType * rxd_data);

uint8_t CAN_RXD_Queue_Handller (void );
void CAN_TXD_Time_Handller_en_queue(void) ;
