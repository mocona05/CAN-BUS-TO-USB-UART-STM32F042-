#include "board.h"
#include "can_queue.h"
/* Private variables ---------------------------------------------------------*/
CanRxMsg RxMessage;    

//CanTxMsg TxMessage;
uint8_t KeyNumber = 0x0;

#define CONFIG_QUEUE_DISABLE
#define CAN_TXD_DISABLE


can_rxd_data_list_t rxd_data;

void can_bus_init(void) {

		RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
		SYSCFG->CFGR1 |= SYSCFG_CFGR1_PA11_PA12_RMP;
		CAN_Config();
//		CAN_ITConfig(CAN, CAN_IT_FMP0, ENABLE);
}




#ifndef CAN_TXD_DISABLE
can_txd_list_t can_txd_list[] = {
	{1000, adc_condition, 		ADC_STAT_ID},

};
#define CAN_TXD_COUNT (sizeof(can_txd_list) / sizeof(can_txd_list[0]))
#endif


can_rxd_type_t can_rxd_list[] = {
	
		{&rxd_data.imu1_roll, IMU_1_ROLL_PITCH_ID, CAN_ID_STD, 8,  0, 32, VAR_INT32, 1, 0,   NULL },
		{&rxd_data.imu1_pitch, IMU_1_ROLL_PITCH_ID, CAN_ID_STD, 8,  32, 32, VAR_INT32, 1, 0,    },
		{&rxd_data.imu1_yaw, IMU_YAW_ID, CAN_ID_STD, 8,  0, 32, VAR_INT32, 1, 0,    },
		
		{&rxd_data.imu2_roll, IMU_2_ROLL_PITCH_ID, CAN_ID_STD, 8,  0, 32, VAR_INT32, 1, 0,   NULL },
		{&rxd_data.imu2_pitch, IMU_2_ROLL_PITCH_ID, CAN_ID_STD, 8,  32, 32, VAR_INT32, 1, 0,    },
		{&rxd_data.imu2_yaw, IMU_YAW_ID, CAN_ID_STD, 8,  32, 32, VAR_INT32, 1, 0,    },

		
		{&rxd_data.shutter_status, CAMERA_STATUS_ID, CAN_ID_STD, 8,  0, 1, VAR_UINT8, 1, 0, NULL   },
		{&rxd_data.focus_status, CAMERA_STATUS_ID, CAN_ID_STD, 8,  1, 1, VAR_UINT8, 1, 0, NULL   },
		{&rxd_data.capture_complit_falg, CAMERA_STATUS_ID, CAN_ID_STD, 8,  2, 1, VAR_UINT8, 1, 0, NULL   },
		{&rxd_data.capture_time_out_falg, CAMERA_STATUS_ID, CAN_ID_STD, 8,  3, 1, VAR_UINT8, 1, 0, NULL   },
		
		{&rxd_data.light_adc, CAMERA_STATUS_ID, CAN_ID_STD, 8,  8, 16, VAR_UINT16, 1, 0,    },
		{&rxd_data.light_differen, CAMERA_STATUS_ID, CAN_ID_STD, 8,  24, 16, VAR_INT16, 1, 0,    },
		{&rxd_data.sensor_board_loop_time_us, CAMERA_STATUS_ID, CAN_ID_STD, 8,  40, 16, VAR_UINT16, 1, 0, NULL   },

		{&rxd_data.trig_count, CAMERA_CONTROL_ID, CAN_ID_STD, 8,  16, 16, VAR_UINT16, 1, 0, NULL   },
		{&rxd_data.photo_count, CAMERA_CONTROL_ID, CAN_ID_STD, 8,  32, 16, VAR_UINT16, 1, 0, NULL   },
		
};
#define CAN_RXD_COUNT (sizeof(can_rxd_list) / sizeof(can_rxd_list[0]))

//static bool write_room_condition(uint32_t id) {
//		CanQueueType txd_msg;
//		txd_msg.StdId = id;
//		txd_msg.DLC =2;
//		txd_msg.ExtId = 0x01;
//		txd_msg.IDE = 	CAN_ID_STD;
//		txd_msg.RTR = CAN_RTR_DATA;
//		
//		txd_msg.Data[0] = (uint8_t)((uint16_t)Oxy.Po);
//		txd_msg.Data[1] = (uint8_t)((uint16_t)Oxy.Po>>8);

//		if(CAN_enqueue(&CAN_txd_queue, txd_msg) != QUEUE_SUCCESS){ 
//				return  QUEUE_ERROR;
//		}
//		return QUEUE_SUCCESS;			
//}

#ifndef	CAN_TXD_DISABLE

static bool adc_condition(uint32_t id) {
		CanQueueType txd_msg;
		txd_msg.StdId = id;
		txd_msg.DLC =8;
		txd_msg.ExtId = 0x01;
		txd_msg.IDE = 	CAN_ID_STD;
		txd_msg.RTR = CAN_RTR_DATA;
		
		memset(txd_msg.Data, 0x00, sizeof(txd_msg.Data)/ sizeof(txd_msg.Data[0]));
		txd_msg.Data[0] = (uint8_t)(sys.cycleTime);
		txd_msg.Data[1] = (uint8_t)(sys.cycleTime>>8);
	
//		txd_msg.Data[2] = (uint8_t)(angle[PITCH]);
//		txd_msg.Data[3] = (uint8_t)(angle[PITCH]>>8);

//		txd_msg.Data[4] = ((uint8_t)heading);
//		txd_msg.Data[5] = (uint8_t)(heading>>8);
//		txd_msg.Data[6] = (uint8_t)(sys.actual_ADC[TEMP]);
//		txd_msg.Data[7] = (uint8_t)(sys.actual_ADC[TEMP]>>8);
	
//		txd_msg.Data[2] = ((int16_t)sys.actual_ADC[PHOTO]);

	
		if(CAN_enqueue(&CAN_txd_queue, txd_msg) != QUEUE_SUCCESS){ 
				return  QUEUE_ERROR;
		}
		return QUEUE_SUCCESS;			
}
#endif


#ifndef CONFIG_QUEUE_DISABLE
static uint8_t  CAN_RXD_queue_to_deQueue_Config(void){
	bool return_value=false;
	volatile static uint64_t config_rxd_buffer=0;

	while(QUEUE_SUCCESS==Config_dequeue(&rxd_config_Queue,(uint64_t *)&config_rxd_buffer)) {	//queue에서 수신값이 있을 경우 수신 값을 복사

			configSet( (uint8_t *)&config_rxd_buffer);	//수신 컨피그값  처리 함수 호출
			return_value=true;
			sys.update_config = true;
	}
	return return_value;
}
#endif

#ifndef CONFIG_QUEUE_DISABLE
static uint8_t  CAN_TXD_enQueue_Config(void) {	//queue에 config 있는 값을 전송

	CanQueueType txd_msg;
	if (!can_queue_is_full(&CAN_txd_queue)) { //TXD	 queue에 공간이 있을경우
			if(!config_queue_is_empty(&txd_config_Queue)) {		//큐에 전송 데이터가 있을경우
					Config_dequeue(&txd_config_Queue,(uint64_t *)&txd_msg.Data);
					//queue에서 송신 요청값이 있을 경우 송신 요청값을 복사
					txd_msg.StdId = CAN_ID_TRANSCEIVER_CONFIG;
					txd_msg.ExtId = 0x01;
					txd_msg.RTR = CAN_RTR_DATA;
					txd_msg.IDE = CAN_ID_STD;
					txd_msg.DLC = 0x08;
	//				CAN_Transmit(CAN1,&txd_msg);	
					if(CAN_enqueue(&CAN_txd_queue, txd_msg) != QUEUE_SUCCESS){ 
							//CAN TXD Queue가 꽉찼을경우
							return  QUEUE_ERROR;
					}
					return QUEUE_SUCCESS;		
			}
			return QUEUE_EMPT;
		}
		return QUEUE_FULL;
}
#endif

#ifndef	CAN_TXD_DISABLE
static void CAN_TXD_sterimming (void ) {				//queue에서 전송 데이터를 꺼내 CAN-BUS로 전송
	CanQueueType	dequeue_msg;
	static CanTxMsg	txd_msg;
	bool static txd_error_flag=0;
			//Queue에 data가 있고 CAN-BUS의 mail box가 비어 있을경우
			if( txd_error_flag) {	//메세지 박스가 꽉차 미전송시 이전 값  재전송
					if(CAN_TxStatus_NoMailBox !=CAN_Transmit(CAN, &txd_msg)){
								txd_error_flag=0;
					}
					else {
								return;
					}
			}
			while(QUEUE_SUCCESS==CAN_dequeue(&CAN_txd_queue,&dequeue_msg))  {
							memcpy(&txd_msg, &dequeue_msg, sizeof(txd_msg));			//크기다 다르므로 txg msg 부분만 복사
							if(CAN_TxStatus_NoMailBox !=CAN_Transmit(CAN, &txd_msg)){
										txd_error_flag=0;
							}
							else {
										txd_error_flag=1;
										return;
							}
			}
}
#endif


static void CAN_RXD_data_update(const CanQueueType * can_rxd_data) {
		uint16_t i=0;
		uint64_t   buffer;
		uint64_t value;
		for (i=0 ; i < CAN_RXD_COUNT ; i++) {
			if (can_rxd_list[i].id == can_rxd_data->StdId &&  can_rxd_list[i].IDE  == can_rxd_data->IDE && can_rxd_list[i].DLC == can_rxd_data->DLC){
				
//					buffer = *(uint64_t *) can_rxd_data->Data;
					memcpy(&buffer, can_rxd_data->Data, sizeof(buffer));
					value =  (( buffer)>>can_rxd_list[i].start_bit)& (~(0xFFFFFFFFFFFFFFFF << can_rxd_list[i].bit_length)) ;		//최대 32bit 자료형만 변환가능
//					value =  ((*(uint64_t *)can_rxd_data->Data)>>can_rxd_list[i].start_bit) & (~(0xFFFFFFFFFFFFFFFF << can_rxd_list[i].bit_length)) ;		//최대 32bit 자료형만 변환가능

					data_set_value(&can_rxd_list[i], value);
				
					if(can_rxd_list[i].function != NULL) {
							void (*Func) (void);
							Func = can_rxd_list[i].function;		//관련된 함수 호출
							Func();							
					}
			}
		}//for

}


uint8_t  CAN_RXD_Queue_Handller (void ) {				//queue에 수신된 CAN DATA를 처리
		CanQueueType	rxd_msg;
	

			while(QUEUE_SUCCESS==CAN_dequeue(&CAN_rxd_queue,&rxd_msg))  {
#ifndef CONFIG_QUEUE_DISABLE
					CAN_RXD_queue_to_deQueue_Config();//config queue가 수신되어 있는지 확인
#endif				
					CAN_RXD_data_update(&rxd_msg);
				
					return QUEUE_SUCCESS;
			}
			return QUEUE_FULL;
			
}

#ifndef	CAN_TXD_DISABLE

void CAN_TXD_Time_Handller_en_queue(void) {		// 정해준 주기마다 DATA를 CAN TXD QUEUE에 넣음.
		static uint8_t i=0;
		static uint32_t sendTime[CAN_TXD_COUNT]={0,};
		bool (*Func) (uint32_t );
		uint32_t timeNow=0;

		timeNow = micros();
	#ifndef CONFIG_QUEUE_DISABLE
	while (QUEUE_SUCCESS == CAN_TXD_enQueue_Config()) {	//config Queue에 보낼값이 있다면.
				CAN_TXD_sterimming();
	}
	#endif	
	if (!can_queue_is_full(&CAN_txd_queue)) { //TXD	 queue에 공간이 있을경우
			for(i=0; i<CAN_TXD_COUNT; i++) {	//스트리밍 값을 que에 입력
				if ( (int64_t)sendTime[i] + can_txd_list[i].resendTime <  timeNow && timeNow >= sendTime[i]) {
						if(  can_txd_list[i].function != NULL ) {
								Func = can_txd_list[i].function;	
								if( QUEUE_SUCCESS==Func(can_txd_list[i].StdId)) {//관련된 함수 호출
										sendTime[i]= timeNow;	//Queue error가 없을경우 전송 시간을 업데이트
								}
						}
				}			
			}
		}
			CAN_TXD_sterimming();
//	}
}
#endif

static void data_set_value(const can_rxd_type_t * var, const int32_t value) {
    switch (var->type) {
        case VAR_UINT8:
            *(uint8_t *)var->ptr = (uint8_t)((double) value * var->scale + var->offset);
            break;
        case VAR_INT8:
            *(char *)var->ptr = (char)((double)value * var->scale + var->offset);
            break;

        case VAR_UINT16:
            *(uint16_t *)var->ptr = (uint16_t)((double)value * var->scale + var->offset);
            break;
        case VAR_INT16:
            *(short *)var->ptr = (int16_t)((double)value * var->scale + var->offset);
            break;

        case VAR_UINT32:
            *(uint32_t *)var->ptr = (uint32_t)((double)value * var->scale + var->offset);
            break;

        case VAR_INT32:
            *(int32_t *)var->ptr = (int32_t)((double)value * var->scale + var->offset);
            break;

        case VAR_FLOAT:
            *(float *)var->ptr = (float )((double)value * var->scale + var->offset);
            break;
    }
}

//CanTxMsg TxMessage = {0};


static void CAN_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    
  /* CAN GPIOs configuration **************************************************/

  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(CAN_GPIO_CLK, ENABLE);

  /* Connect CAN pins to AF7 */
  GPIO_PinAFConfig(CAN_GPIO_PORT, CAN1_RX_PIN_Source,	CAN_AF_PORT );
  GPIO_PinAFConfig(CAN_GPIO_PORT, CAN1_TX_PIN_Source, CAN_AF_PORT); 
  
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin =  CAN_RX_PIN  | CAN_TX_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStructure);

  /* NVIC configuration *******************************************************/
  NVIC_InitStructure.NVIC_IRQChannel = CEC_CAN_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* CAN configuration ********************************************************/  
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);
	
  /* CAN register init */
  CAN_DeInit(CANx);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = ENABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    
    
  /* CAN Baudrate = 1MBps (CAN clocked at 48 MHz) */
#if 0 // Sample-Pint : 50%
  CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;
  CAN_InitStructure.CAN_Prescaler = 3;
#else // Sample-Pint : 87.5%
  CAN_InitStructure.CAN_BS1 = CAN_BS1_13tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
  CAN_InitStructure.CAN_Prescaler = 3;

#endif
  CAN_Init(CANx, &CAN_InitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
//	  /* CAN filter init "FIFO1" */
//  CAN_FilterInitStructure.CAN_FilterNumber = 1;
//  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
//  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
//  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
//  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
//  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
//  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
//  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 1;
//  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
//  CAN_FilterInit(&CAN_FilterInitStructure);
	
//	  /* Transmit Structure preparation */
//  TxMessage.StdId = 0x321;
//  TxMessage.ExtId = 0x01;
//  TxMessage.RTR = CAN_RTR_DATA;
//  TxMessage.IDE = CAN_ID_STD;
//  TxMessage.DLC = 1;
//  
//	
//	 /* CAN FIFO0 message pending interrupt enable */
//  CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);
  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);
  
//  /* Enable FIFO 1 message pending Interrupt */
//  CAN_ITConfig(CANx, CAN_IT_FMP1, ENABLE);
}



/**
  * @brief  Initializes a Rx Message.
  * @param  CanRxMsg *RxMessage.
  * @retval None
  */
void Init_RxMes(CanRxMsg *RxMessage)
{
  uint8_t i = 0;

  RxMessage->StdId = 0;
  RxMessage->ExtId = 0;
  RxMessage->IDE = CAN_ID_STD;
  RxMessage->DLC = 0;
  RxMessage->FMI = 0;
  for (i = 0; i < 8; i++)
  {
    RxMessage->Data[i] = 0;
  }
}

//void CEC_CAN_IRQHandler(void)
//{
//	Init_RxMes( &RxMessage);
//  CAN_Receive(CAN, CAN_FIFO0, &RxMessage);
////config 수신값을 config Queue에 입력
//	
//#ifndef CONFIG_QUEUE_DISABLE	
//  if ((RxMessage.StdId == CAN_ID_RECEIVE_CONFIG)&&(RxMessage.IDE == CAN_ID_STD) && (RxMessage.DLC == 8)) {
//			if(Config_enqueue(&rxd_config_Queue, *(uint64_t*)RxMessage.Data) != CONFIG_QUEUE_SUCCESS){
//					sys.rxd_config_queue_full= true;
//			}
//  }
//	
//	else	if(CAN_enqueue(&CAN_rxd_queue, *(CanQueueType *)&RxMessage) != QUEUE_SUCCESS){ 
//#else		
//	if(CAN_enqueue(&CAN_rxd_queue, *(CanQueueType *)&RxMessage) != QUEUE_SUCCESS){ 
//#endif		
//	}	
//}


void CEC_CAN_IRQHandler(void)
{ 
			Init_RxMes( &RxMessage);
//  if (CAN_MessagePending(CANx, CAN_FIFO0) != 0) 
//  {

		CAN_Receive(CANx, CAN_FIFO0, &RxMessage);
//	}

//  if (CAN_MessagePending(CANx, CAN_FIFO1) != 0) 
//  {    
//		Init_RxMes( &RxMessage);
//		CAN_Receive(CANx, CAN_FIFO1, &RxMessage);
//	}
	if(CAN_enqueue(&CAN_rxd_queue, *(CanQueueType *)&RxMessage) != QUEUE_SUCCESS){ 
	}
}


	
//void CEC_CAN_IRQHandler(void)
//{
//  if(CAN_GetITStatus(CAN, CAN_IT_FMP0) != RESET)
//  {
//    CanRxMsg RxMessage;
//    
//    RxMessage.StdId = 0x00;
//    RxMessage.ExtId = 0x00;
//    RxMessage.IDE = 0;
//    RxMessage.DLC = 0;
//    RxMessage.FMI = 0;
//    RxMessage.Data[0] = 0x00;
//    RxMessage.Data[1] = 0x00;
//    
//    CAN_Receive(CAN, CAN_FIFO0, &RxMessage);
//    
//    if((RxMessage.ExtId == 0x1234) && (RxMessage.IDE == CAN_ID_EXT)
//       && (RxMessage.DLC == 2) && ((RxMessage.Data[1]|(RxMessage.Data[0]<<8)) == 0xDECA))
//    {
//      ret = 1; 
//    }
//    else
//    {
//      ret = 0; 
//    }
//  }
//}

