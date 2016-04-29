#include "board.h"

//#define FLASH_PAGE_COUNT 128

////#define FLASH_PAGE_SIZE                 ((uint16_t)0x400)

////// use the last KB for sensor config storage
//#define FLASH_WRITE_SENSOR_CONFIG_ADDR  (0x08000000 + (uint32_t)FLASH_PAGE_SIZE * (FLASH_PAGE_COUNT - 1))

////// use the 2nd to last KB for system config storage
//#define FLASH_WRITE_SYSTEM_CONFIG_ADDR  (0x08000000 + (uint32_t)FLASH_PAGE_SIZE * (FLASH_PAGE_COUNT - 2))


#define FLASH_PAGE_SIZE         ((uint32_t)0x00000400)   /* FLASH Page Size */
#define FLASH_USER_START_ADDR   ((uint32_t)0x08003800)   /* Start @ of user Flash area */			//14 kbyte start area = save flash size 1kbyte
#define FLASH_USER_END_ADDR     ((uint32_t)0x08004000)   /* End @ of user Flash area */
//#define DATA_32                 ((uint32_t)0x12345678)


void readEEPROM(void){
//	char value=0;
    // Read flash

//	memcpy(&sensorConfig, (char *)FLASH_WRITE_SENSOR_CONFIG_ADDR, sizeof(sensorConfig_t));

    memcpy(CUSTOM_Table, (char *)FLASH_USER_START_ADDR, sizeof(camera_ctrl_t));

//    systemConfig.yawDirection = constrain( systemConfig.yawDirection, -1.0f, 1.0f );
//	memcpy(&value, (char * )FLASH_USER_START_ADDR,1);

//		return value;
}

/////////////////////////////////////////////////////////////////////////////////

void writeEEPROM(void){


    FLASH_Status status;
    uint32_t i;
//	uint8_t status;
    FLASH_Unlock();

	

	
	
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);

    if (FLASH_ErasePage(FLASH_USER_START_ADDR) == FLASH_COMPLETE)
    {
 //       for (i = 0; i < sizeof( camera_ctrl_t)*2; i += 4)
		for (i = 0; i < (sizeof( camera_ctrl_t) * RC_DATA_SIZE)  ; i += 4)
        {
            status = FLASH_ProgramWord(FLASH_USER_START_ADDR + i, *(uint32_t *)((char *)&CUSTOM_Table + i));
            if (status != FLASH_COMPLETE)
                break; // TODO: fail
		}

    }

    FLASH_Lock();

    readEEPROM();
}









