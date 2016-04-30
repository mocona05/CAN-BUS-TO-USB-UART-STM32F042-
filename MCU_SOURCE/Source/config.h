#pragma once


typedef enum { FREQ_ADJ, 
												OFFSET_ADJ, 
												REMODTE_CAN, 
												REMOTE_UART,
}_control_mode; 

#ifdef ENABLE_UART
typedef struct serialPort {

    const struct serialPortVTable *vTable;

    portMode_t mode;
    uint32_t baudRate;

    uint32_t rxBufferSize;
    uint32_t txBufferSize;
    volatile uint8_t *rxBuffer;
    volatile uint8_t *txBuffer;
    uint32_t rxBufferHead;
    uint32_t rxBufferTail;
    uint32_t txBufferHead;
    uint32_t txBufferTail;

    // FIXME rename member to rxCallback
    serialReceiveCallbackPtr callback;
} serialPort_t;


typedef struct core_t {
    serialPort_t *mainport;
//    serialPort_t *flexport;
    serialPort_t *gpsport;
} core_t;
#endif


typedef struct sys_t {
			uint32_t cycleTime;
			uint16_t volume;
			uint8_t button;
	
			bool long_push_center_flag;
			bool short_push_center_flag;
			float DAC_gain;
			int32_t DAC_p_p_volt;
			int16_t vr_gain_100x;
			float waveform_freq;
			uint16_t vr_gen_rpm;
			int16_t offset_voltage_mv;
			bool vr_sig_generation;
			uint8_t adj_mode;
//			bool rxd_gain;
//			bool rxd_freq;

			uint16_t st_freq_100x;
			uint16_t st_duty_100x;
			uint16_t st_mVrms;
			bool st_sig_generation;
			bool stystem_start_flag;

} sys_t;


typedef struct vr_generator_t {
		uint16_t vr_cycle_freq;
		int16_t offset_mv;
		int16_t vr_gain_100x;
		bool vr_sig_generation;
		bool vr_default_set;
	
		uint16_t st_freq_100x;
		uint16_t st_duty_100x;
		bool st_sig_generation;
		bool st_default_set;
	
		uint16_t raw_volume;
}vr_generator_t;


extern vr_generator_t  vr_gen;
extern sys_t sys;

#ifdef ENABLE_UART
extern core_t core;
#endif
