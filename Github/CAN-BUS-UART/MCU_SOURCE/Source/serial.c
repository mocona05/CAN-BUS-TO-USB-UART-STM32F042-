/*
 * This file is part of baseflight
 * Licensed under GPL V3 or modified DCL - see https://github.com/multiwii/baseflight/blob/master/README.md
 */

#include "board.h"
//#include "imu.h"

//#include "cli.h"
//#include "telemetry_common.h"
#define INBUF_SIZE 128


//master_t mcfg;  // master config struct with data independent from profiles

typedef enum serialState_t {
    IDLE,
    HEADER_START,
    HEADER_M,
    HEADER_ARROW,
    HEADER_SIZE,
    HEADER_CMD,
} serialState_t;


typedef  struct mspPortState_t {
    serialPort_t *port;
    uint8_t checksum;
    uint8_t indRX;
    uint8_t inBuf[INBUF_SIZE];
    uint8_t cmdMSP;
    uint8_t offset;
    uint8_t dataSize;
    serialState_t c_state;
} mspPortState_t;

static mspPortState_t ports[2];
static mspPortState_t *currentPortState = &ports[0];
static int numTelemetryPorts = 0;
static bool pendReboot = false;



void serialInit(uint32_t baudrate)
{
//    int idx;

    numTelemetryPorts = 0;
    core.mainport = uartOpen(USART1, NULL, baudrate, MODE_RXTX);
    ports[0].port = core.mainport;
    numTelemetryPorts++;

//    // additional telemetry port available only if spektrum sat isn't already assigned there
//    if (hw_revision >= NAZE32_SP  && !mcfg.spektrum_sat_on_flexport) {
//        core.flexport = uartOpen(USART3, NULL, baudrate, MODE_RXTX);
 //       ports[1].port = core.flexport;
//        numTelemetryPorts++;
//    }

//    // calculate used boxes based on features and fill availableBoxes[] array
//    memset(availableBoxes, 0xFF, sizeof(availableBoxes));

//    idx = 0;
//    availableBoxes[idx++] = BOXARM;
//    if (sensors(SENSOR_ACC)) {
//        availableBoxes[idx++] = BOXANGLE;
//        availableBoxes[idx++] = BOXHORIZON;
//    }
//    if (sensors(SENSOR_BARO)) {
//        availableBoxes[idx++] = BOXBARO;
//        if (feature(FEATURE_VARIO))
//            availableBoxes[idx++] = BOXVARIO;
//    }
//    if (sensors(SENSOR_ACC) || sensors(SENSOR_MAG)) {
//        availableBoxes[idx++] = BOXMAG;
//        availableBoxes[idx++] = BOXHEADFREE;
//        availableBoxes[idx++] = BOXHEADADJ;
//    }
//    if (feature(FEATURE_SERVO_TILT))
//        availableBoxes[idx++] = BOXCAMSTAB;
//    if (feature(FEATURE_GPS)) {
//        availableBoxes[idx++] = BOXGPSHOME;
//        availableBoxes[idx++] = BOXGPSHOLD;
//    }
//    if (mcfg.mixerConfiguration == MULTITYPE_FLYING_WING || mcfg.mixerConfiguration == MULTITYPE_AIRPLANE || mcfg.mixerConfiguration == MULTITYPE_CUSTOM_PLANE)
//        availableBoxes[idx++] = BOXPASSTHRU;
//    availableBoxes[idx++] = BOXBEEPERON;
//    if (feature(FEATURE_INFLIGHT_ACC_CAL))
//        availableBoxes[idx++] = BOXCALIB;
//    availableBoxes[idx++] = BOXOSD;
//    if (feature(FEATURE_TELEMETRY && mcfg.telemetry_switch))
//        availableBoxes[idx++] = BOXTELEMETRY;
//    if (mcfg.mixerConfiguration == MULTITYPE_CUSTOM_PLANE) {
//        availableBoxes[idx++] = BOXSERVO1;
//        availableBoxes[idx++] = BOXSERVO2;
//        availableBoxes[idx++] = BOXSERVO3;
//    }

//    numberBoxItems = idx;
}





//static const box_t boxes[] = {
//    { BOXARM, "ARM;", 0 },
//    { BOXANGLE, "ANGLE;", 1 },
//    { BOXHORIZON, "HORIZON;", 2 },
//    { BOXBARO, "BARO;", 3 },
//    { BOXVARIO, "VARIO;", 4 },
//    { BOXMAG, "MAG;", 5 },
//    { BOXHEADFREE, "HEADFREE;", 6 },
//    { BOXHEADADJ, "HEADADJ;", 7 },
//    { BOXCAMSTAB, "CAMSTAB;", 8 },
//    { BOXCAMTRIG, "CAMTRIG;", 9 },
//    { BOXGPSHOME, "GPS HOME;", 10 },
//    { BOXGPSHOLD, "GPS HOLD;", 11 },
//    { BOXPASSTHRU, "PASSTHRU;", 12 },
//    { BOXBEEPERON, "BEEPER;", 13 },
//    { BOXLEDMAX, "LEDMAX;", 14 },
//    { BOXLEDLOW, "LEDLOW;", 15 },
//    { BOXLLIGHTS, "LLIGHTS;", 16 },
//    { BOXCALIB, "CALIB;", 17 },
//    { BOXGOV, "GOVERNOR;", 18 },
//    { BOXOSD, "OSD SW;", 19 },
//    { BOXTELEMETRY, "TELEMETRY;", 20 },
//    { BOXSERVO1, "SERVO1;", 21 },
//    { BOXSERVO2, "SERVO2;", 22 },
//    { BOXSERVO3, "SERVO3;", 23 },
//    { CHECKBOXITEMS, NULL, 0xFF }
//};

//// this is calculated at startup based on enabled features.
//static uint8_t availableBoxes[CHECKBOXITEMS];
//// this is the number of filled indexes in above array
//static uint8_t numberBoxItems = 0;
//// from mixer.c
//extern int16_t motor_disarmed[MAX_MOTORS];
// cause reboot after MSP processing complete
//static bool pendReboot = false;

//static const char pidnames[] =
//    "ROLL;"
//    "PITCH;"
//    "YAW;"
//    "ALT;"
//    "Pos;"
//    "PosR;"
//    "NavR;"
//    "LEVEL;"
//    "MAG;"
//    "VEL;";


//static int numTelemetryPorts = 0;

// static uint8_t checksum, indRX, inBuf[INBUF_SIZE];
// static uint8_t cmdMSP;



//// evaluate all other incoming serial data
static void evaluateOtherData(uint8_t sr)
{
    if (sr == '#')
        cliProcess();
    else if (sr == mcfg.reboot_character)
        systemReset(true);      // reboot to bootloader
		
//		else if (sr =='@'){
//			 osd_eeprom_update();			
//		}
}


void serialize8(uint8_t a)
{
    serialWrite(currentPortState->port, a);
    currentPortState->checksum ^= a;
}

void serialize32(uint32_t a)
{
    serialize8(a & 0xFF);
    serialize8((a >> 8) & 0xFF);
    serialize8((a >> 16) & 0xFF);
    serialize8((a >> 24) & 0xFF);
}

void serialize16(int16_t a)
{
    serialize8(a & 0xFF);
    serialize8((a >> 8) & 0xFF);
}

uint8_t read8(void)
{
    return currentPortState->inBuf[currentPortState->indRX++] & 0xff;
}

uint16_t read16(void)
{
    uint16_t t = read8();
    t += (uint16_t)read8() << 8;
    return t;
}

uint32_t read32(void)
{
    uint32_t t = read16();
    t += (uint32_t)read16() << 16;
    return t;
}

void headSerialResponse(uint8_t err, uint8_t s)
{
    serialize8('$');
    serialize8('M');
    serialize8(err ? '!' : '>');
    currentPortState->checksum = 0;               // start calculating a new checksum
    serialize8(s);
    serialize8(currentPortState->cmdMSP);
}

void headSerialReply(uint8_t s)
{
    headSerialResponse(0, s);
}

void headSerialError(uint8_t s)
{
    headSerialResponse(1, s);
}

void tailSerialReply(void)
{
    serialize8(currentPortState->checksum);
}

void s_struct(uint8_t *cb, uint8_t siz)
{
    headSerialReply(siz);
    while (siz--)
        serialize8(*cb++);
}

void serializeNames(const char *s)
{
    const char *c;
    for (c = s; *c; c++)
        serialize8(*c);
}

//void serializeBoxNamesReply(void)
//{
//    int i, idx, j, flag = 1, count = 0, len;

//reset:
//    // in first run of the loop, we grab total size of junk to be sent
//    // then come back and actually send it
//    for (i = 0; i < numberBoxItems; i++) {
//        idx = availableBoxes[i];
//        len = strlen(boxes[idx].boxName);
//        if (flag) {
//            count += len;
//        } else {
//            for (j = 0; j < len; j++)
//                serialize8(boxes[idx].boxName[j]);
//        }
//    }

//    if (flag) {
//        headSerialReply(count);
//        flag = 0;
//        goto reset;
//    }
//}



void serialCom(void)
{
    uint8_t c;
    int i;

    for (i = 0; i < numTelemetryPorts; i++) {
        currentPortState = &ports[i];

        // in cli mode, all serial stuff goes to here. enter cli mode by sending #
        if (cliMode) {
            cliProcess();
            return;
        }
//				else if (osd_eeprom_update_Mode) {
//						osd_eeprom_update();
//						return;
//				}

        if (pendReboot)
            systemReset(false); // noreturn

        while (serialTotalBytesWaiting(currentPortState->port)) {
            c = serialRead(currentPortState->port);

            if (currentPortState->c_state == IDLE) {
                currentPortState->c_state = (c == '$') ? HEADER_START : IDLE;
//                if (currentPortState->c_state == IDLE && !f.ARMED)
                evaluateOtherData(c); // if not armed evaluate all other incoming serial data
            } else if (currentPortState->c_state == HEADER_START) {
                currentPortState->c_state = (c == 'M') ? HEADER_M : IDLE;
            } else if (currentPortState->c_state == HEADER_M) {
                currentPortState->c_state = (c == '<') ? HEADER_ARROW : IDLE;
            } else if (currentPortState->c_state == HEADER_ARROW) {
                if (c > INBUF_SIZE) {       // now we are expecting the payload size
                    currentPortState->c_state = IDLE;
                    continue;
                }
                currentPortState->dataSize = c;
                currentPortState->offset = 0;
                currentPortState->checksum = 0;
                currentPortState->indRX = 0;
                currentPortState->checksum ^= c;
                currentPortState->c_state = HEADER_SIZE;      // the command is to follow
            } else if (currentPortState->c_state == HEADER_SIZE) {
                currentPortState->cmdMSP = c;
                currentPortState->checksum ^= c;
                currentPortState->c_state = HEADER_CMD;
            } else if (currentPortState->c_state == HEADER_CMD && currentPortState->offset < currentPortState->dataSize) {
                currentPortState->checksum ^= c;
                currentPortState->inBuf[currentPortState->offset++] = c;
            } else if (currentPortState->c_state == HEADER_CMD && currentPortState->offset >= currentPortState->dataSize) {
                if (currentPortState->checksum == c) {        // compare calculated and transferred checksum
 //                   evaluateCommand();      // we got a valid packet, evaluate it
                }
                currentPortState->c_state = IDLE;
            }
        }
    }
}

