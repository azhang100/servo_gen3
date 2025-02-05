/*
 * SmartLungGasSensing.c
 *
 *  Created on: Dec 12, 2022
 *      Author: NKS
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>

//extern "C" {
#include "SmartLungGasSensing.h"
//}

#include "gio.h"
#include "sci.h"
#include "reg_sci.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t DeviceInfo[] = { "#VERS\r\n" }; //collect device information.
uint8_t UniqueID[] = { "#IDNR\r\n" }; //collect device unique ID.
uint8_t readOxy[] = { "#MOXY\r\n" }; //collect oxygen concentration+Ambient temperature .
uint8_t readOxyRAW[] = { "#MRAW \r\n" }; //collect oxygen concentration+Gas temperature+Ambient pressure.
uint8_t setBaudRate[] = { "#BAUD 9600 \r\n" }; // change the baud rate to 115200.
uint8_t disableBroadcast[] = { "#BCST 0 \r\n" };

void co2SensorInit(void)
{
    uint32 test = 0x0000;
//    gioSetDirection(gioPORTA, 1);
//    gioSetDirection(gioPORTB, 1);
    gioSetBit(gioPORTA, 1, 0); // Initialize the enable pin for serial multiplexer

    /** - Port B output values */
    gioPORTB->DOUT = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
    | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
    | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
    | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

    /** - Port B direction */
    gioPORTB->DIR = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
    | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
    | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
    | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

    gioSetBit(gioPORTA, 0, 0); /* Bit 0 (S3) */

    test = gioGetPort(gioPORTB);
}


void inletO2Init(void)
{
    uint32 test = 0x0000;
    clock_t start_t, end_t;
    double total_t;

//    gioSetDirection(gioPORTA, 1);
//    gioSetDirection(gioPORTB, 1);
    gioSetBit(gioPORTA, 1, 0); // Initialize the enable pin for serial multiplexer

    /** - Port B output values */
    gioPORTB->DOUT = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
    | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
    | (uint32) ((uint32) 1U << 2U) /* Bit 2 (S1) */
    | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

    /** - Port B direction */
    gioPORTB->DIR = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
    | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
    | (uint32) ((uint32) 1U << 2U) /* Bit 2 (S1) */
    | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

//    gioSetBit(gioPORTA, 0, 0); /* Bit 0 (S3) */

    test = gioGetPort(gioPORTB);

    start_t = clock();
//    printf("Starting of the program, start_t = %ld\n", start_t);

//    FDO2Data(setBaudRate, sizeof(setBaudRate), inletO2);

//    FDO2Data(readOxy, sizeof(readOxy), inletO2);

    FDO2Data(readOxyRAW, sizeof(readOxyRAW), inletO2);

    end_t = clock();
//    printf("End of the big loop, end_t = %ld\n", end_t);

    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//    printf("Total time taken by CPU: %f\n", total_t  );
}

void exhaustO2Init(void)
{
    uint32 test = 0x0000;
    clock_t start_t, end_t;
    double total_t;
    time_t rawtime;
    struct tm * timeinfo;

//    gioSetDirection(gioPORTA, 1);
//    gioSetDirection(gioPORTB, 1);
//    gioSetBit(gioPORTA, 1, 0); // Initialize the enable pin for serial multiplexer

    /** - Port B output values */
    gioPORTB->DOUT = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
    | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
    | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
    | (uint32) ((uint32) 1U << 3U); /* Bit 3 (S2) */

    /** - Port B direction */
    gioPORTB->DIR = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
    | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
    | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
    | (uint32) ((uint32) 1U << 3U); /* Bit 3 (S2) */

//    gioSetBit(gioPORTA, 0, 0); /* Bit 0 (S3) */

    test = gioGetPort(gioPORTB);

    start_t = clock();
    printf("Starting of the program, start_t = %ld\n", start_t);

//    FDO2Data(setBaudRate, sizeof(setBaudRate), outletO2);

    FDO2Data(readOxyRAW, sizeof(readOxyRAW), outletO2);

    FDO2Data(readOxy, sizeof(readOxy), outletO2);

    FDO2Data(readOxyRAW, sizeof(readOxyRAW), outletO2);

    end_t = clock();
    printf("End of the big loop, end_t = %ld\n", end_t);

    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", total_t  );
}

void bloodFlowSensorInit(void)
{
    uint32 test = 0x0000;
    time_t rawtime;
    struct tm * timeinfo;

//    gioSetDirection(gioPORTA, 1);
//    gioSetDirection(gioPORTB, 1);
    gioSetBit(gioPORTA, 1, 0); // Initialize the enable pin for serial multiplexer

    /** - Port B output values */
    gioPORTB->DOUT = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
    | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
    | (uint32) ((uint32) 1U << 2U) /* Bit 2 (S1) */
    | (uint32) ((uint32) 1U << 3U); /* Bit 3 (S2) */

    /** - Port B direction */
    gioPORTB->DIR = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
    | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
    | (uint32) ((uint32) 1U << 2U) /* Bit 2 (S1) */
    | (uint32) ((uint32) 1U << 3U); /* Bit 3 (S2) */

    gioSetBit(gioPORTA, 0, 0); /* Bit 0 (S3) */

    test = gioGetPort(gioPORTB);
}


void FDO2Data(uint8_t *cmd, uint32 cmdLength, struct Oxysensorinfo* o2Sensor)
{
    uint16_t counter = 0;
    uint8_t rFrame[256] = {};
    const char s[2] = " ";
    char *token;
    char error[] = {"#ERRO"};

    while (dataReceiveFlag != 0);

    dataReceiveFlag = 1;

    sciSend(sciREG, (cmdLength-1), (uint8_t*) cmd);

    do
    {
        sciReceive(sciREG, 1, &rFrame[counter]);
        while (dataReceiveFlag != 0);
        if (rFrame[counter] != 0x0D)
        {
            counter++;
            dataReceiveFlag = 1;
        }
    } while (dataReceiveFlag != 0);

    memcpy((char*)dest, (uint8_t*)rFrame, counter);
        /*ERROR Detection:
        1. Check for the error code.
        */
    token = strtok(dest, s);

    if (strcmp(token, error) == NULL)
    {
        /* walk through other tokens */
        token = strtok(NULL, s);
        printf("Communication error. Error code: %s\n", token );
    }
        /*
        2. Check for the checksum error.
        */
    else if (strcmp(token, "#VERS") == NULL)
    {
        token = strtok(NULL, s);
        strcpy(o2Sensor[0].id, token);
        token = strtok(NULL, s);
        strcpy(o2Sensor[0].oxyChannel, token);
        token = strtok(NULL, s);
        strcpy(o2Sensor[0].rev, token);
        token = strtok(NULL, s);
        strcpy(o2Sensor[0].model, token);
    }

    else if (strcmp(token, "#IDNR") == NULL)
    {
        token = strtok(NULL, s);
        strcpy(o2Sensor[0].uniqueID, token);
    }

    else if (strcmp(token, "#MOXY") == NULL)
    {
        token = strtok(NULL, s);
        o2Sensor[0].partialOxy = atof(token);
        o2Sensor[0].partialOxy *= 0.001;
        printf("O2 Concentration: %f hPa\n", o2Sensor[0].partialOxy);
        token = strtok(NULL, s);
        o2Sensor[0].temperature = atof(token);
        o2Sensor[0].temperature *= 0.001;
        printf("temperature: %f C\n", o2Sensor[0].temperature);
        token = strtok(NULL, s);
        printf("status: %lu\n", o2Sensor[0].status);
    }

    else if (strcmp(token, "#MRAW") == NULL)
    {
        token = strtok(NULL, s);
        o2Sensor[0].partialOxy = atof(token);
        o2Sensor[0].partialOxy *= 0.001;
        printf("O2 Concentration: %f hPa\n", o2Sensor[0].partialOxy);
        token = strtok(NULL, s);
        o2Sensor[0].temperature = atof(token);
        o2Sensor[0].temperature *= 0.001;
        printf("temperature: %f C\n", o2Sensor[0].temperature);
        token = strtok(NULL, s);
        o2Sensor[0].status = llabs (atoll(token));          //unsigned 32 bit
//        printf("status: %lu\n", o2Sensor[0].status);
        token = strtok(NULL, s);
        o2Sensor[0].dphi = atoll(token);
        o2Sensor[0].dphi *= 0.001;
//        printf("Phase Shift: %f degrees\n", o2Sensor[0].dphi);
        token = strtok(NULL, s);
        o2Sensor[0].signalIntensity = atoll(token);
        o2Sensor[0].signalIntensity *= 0.001;
//        printf("Signal Intensity: %f mV\n", o2Sensor[0].signalIntensity);
        token = strtok(NULL, s);
        o2Sensor[0].ambientLight = atoll(token);
        o2Sensor[0].ambientLight *= 0.01;
//        printf("Ambient Light: %f mV\n", o2Sensor[0].ambientLight);
        token = strtok(NULL, s);
        o2Sensor[0].ambientPressure = atoll(token);
        o2Sensor[0].ambientPressure *= 0.001;
        printf("Ambient Pressure: %f mbar\n", o2Sensor[0].ambientPressure);
        token = strtok(NULL, s);
        o2Sensor[0].relativeHumidity = llabs(atoll(token));   //unsigned 32 bit
        o2Sensor[0].relativeHumidity *= 0.001;
        printf("Relative Humidity: %f%%\n", o2Sensor[0].relativeHumidity);
        printf("O2 concentration: %f%%\n",(100*o2Sensor[0].partialOxy/o2Sensor[0].ambientPressure));
    }
}


#ifdef __cplusplus
}
#endif
