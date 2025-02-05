//#include <stdio.h>
//#include <string.h>
//#include <time.h>
//#include <errno.h>
//#include <stdlib.h>
//
//
//#include "gio.h"
//#include "sci.h"
//#include "reg_sci.h"
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//uint16_t counter = 0;
//int8_t rFrame[256] = {};
//const char s[2] = " ";
//
//// returns how many bytes are in the buffer
//uint16_6 sciInterfaceAvailable() {
//
//}
//
//// reads cmdLength characters in *cmd to the Debug channel (currently the FDO2 channel, we'll be using it as the Debug channel)
//void sciInterfaceRead(uint8_t *cmd, uint32 cmdLength)
//
//// writes cmdLength characters in *cmd to P1 (currently the FDO2 channel, we'll be using it as the Debug channel)
//void sciInterfaceWrite(uint8_t *cmd, uint32 cmdLength){
//    sciSend(sciREG, (cmdLength-1), (uint8_t*) cmd);
//}
//
//    // S1 = GIOB[2] // LSB
//    // S2 = GIOB[3]
//    // S3 = GIOA1[0] // MSB
//    // ~EN= GIOA1[1]
//
//    /** - Port B output values */
//    gioPORTB->DOUT = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
//    | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
//    | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
//    | (uint32) ((uint32) 1U << 3U); /* Bit 3 (S2) */
//    /** - Port B direction */
//    gioPORTB->DIR = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
//    | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
//    | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
//    | (uint32) ((uint32) 1U << 3U); /* Bit 3 (S2) */
//
//    sciSend(sciREG, (cmdLength-1), (uint8_t*) cmd);
//
//}
//
////==============================================
//
//// sends cmd
//// reads data
//void FDO2Data(uint8_t *cmd, uint32 cmdLength) {
//
//
//    while (dataReceiveFlag != 0); // volatile, do not modify
//    dataReceiveFlag = 1;
//
//    sciSend(sciREG, (cmdLength-1), (uint8_t*) cmd);
//    // sci=uart
//
//    do
//    {
//        sciReceive(sciREG, 1, &rFrame[counter]);
//        while (dataReceiveFlag != 0);
//        if (rFrame[counter] != 0x0D)
//        {
//            counter++;
//            dataReceiveFlag = 1;
//        }
//    } while (dataReceiveFlag != 0);
//
//    memcpy((char*)dest, (uint8_t*)rFrame, counter);
//        /*ERROR Detection:
//        1. Check for the error code.
//        */
//    token = strtok(dest, s);
//
//    if (strcmp(token, error) == NULL)
//    {
//        /* walk through other tokens */
//        token = strtok(NULL, s);
//        printf("Communication error. Error code: %s\n", token );
//    }
//        /*
//        2. Check for the checksum error.
//        */
//    else if (strcmp(token, "#VERS") == NULL)
//    {
//        token = strtok(NULL, s);
//        strcpy(o2Sensor[0].id, token);
//        token = strtok(NULL, s);
//        strcpy(o2Sensor[0].oxyChannel, token);
//        token = strtok(NULL, s);
//        strcpy(o2Sensor[0].rev, token);
//        token = strtok(NULL, s);
//        strcpy(o2Sensor[0].model, token);
//    }
//
//    else if (strcmp(token, "#IDNR") == NULL)
//    {
//        token = strtok(NULL, s);
//        strcpy(o2Sensor[0].uniqueID, token);
//    }
//
//    else if (strcmp(token, "#MOXY") == NULL)
//    {
//        token = strtok(NULL, s);
//        o2Sensor[0].partialOxy = atof(token);
//        o2Sensor[0].partialOxy *= 0.001;
//        printf("O2 Concentration: %f hPa\n", o2Sensor[0].partialOxy);
//        token = strtok(NULL, s);
//        o2Sensor[0].temperature = atof(token);
//        o2Sensor[0].temperature *= 0.001;
//        printf("temperature: %f C\n", o2Sensor[0].temperature);
//        token = strtok(NULL, s);
//        printf("status: %lu\n", o2Sensor[0].status);
//    }
//
//    else if (strcmp(token, "#MRAW") == NULL)
//    {
//        token = strtok(NULL, s);
//        o2Sensor[0].partialOxy = atof(token);
//        o2Sensor[0].partialOxy *= 0.001;
//        printf("[sweeepO2=%f\n", o2Sensor[0].partialOxy);
//        token = strtok(NULL, s);
//        o2Sensor[0].temperature = atof(token);
//        o2Sensor[0].temperature *= 0.001;
//        printf("[temp=%f]\n", o2Sensor[0].temperature);
//        token = strtok(NULL, s);
//        o2Sensor[0].status = llabs (atoll(token));          //unsigned 32 bit
////        printf("status: %lu\n", o2Sensor[0].status);
//        token = strtok(NULL, s);
//        o2Sensor[0].dphi = atoll(token);
//        o2Sensor[0].dphi *= 0.001;
////        printf("Phase Shift: %f degrees\n", o2Sensor[0].dphi);
//        token = strtok(NULL, s);
//        o2Sensor[0].signalIntensity = atoll(token);
//        o2Sensor[0].signalIntensity *= 0.001;
////        printf("Signal Intensity: %f mV\n", o2Sensor[0].signalIntensity);
//        token = strtok(NULL, s);
//        o2Sensor[0].ambientLight = atoll(token);
//        o2Sensor[0].ambientLight *= 0.01;
////        printf("Ambient Light: %f mV\n", o2Sensor[0].ambientLight);
//        token = strtok(NULL, s);
//        o2Sensor[0].ambientPressure = atoll(token);
//        o2Sensor[0].ambientPressure *= 0.001;
//        printf("[pressure=%f]\n", o2Sensor[0].ambientPressure);
//        token = strtok(NULL, s);
//        o2Sensor[0].relativeHumidity = llabs(atoll(token));   //unsigned 32 bit
//        o2Sensor[0].relativeHumidity *= 0.001;
//        printf("[humidity=%f]\n", o2Sensor[0].relativeHumidity);
//        printf("[O2conc=%f]\n",(100*o2Sensor[0].partialOxy/o2Sensor[0].ambientPressure));
//    }
//}
