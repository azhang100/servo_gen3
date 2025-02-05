/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "gio.h"
#include "sci.h"
#include "het.h"
#include "system.h"
#include "SmartLungGasSensing.h"
#include "servo_functions.h"

#include "sfc5500_commands.h"
#include "sfc5500_data.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

uint8   emacAddress[6U] =   {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
uint32  emacPhyAddress  =   0U;

int main(void)
{
/* USER CODE BEGIN (3) */
    char string[]={};
    float targetO2Concentration = 37.00f;       // in mmHg
    float sweepFlow = 100.00f;                  // in ml/min

    error_type error = no_error;
    char productName[256];
//    char articleCode[256];
//    char serialNumber[256];
//    dataPacket status;
//    float current_co2_level = 0;
//    float targetSetPoint = 0.05f;           // normalized
//    float currentSetPoint = 0.00f;          // normalized
//    float measuredCO2Flow = 0.0f;             // normalized
    float measuredSweepFlow = 0.00f;             // ml/min
    float measuredAirFlow = 0.00f;               // ml/min
    float measuredCO2Flow = 0.00f;              // ml/min
    float measuredO2Flow = 0.00f;               // ml/min
//    float targetFlow = 2.0f;                  // in L/min
//    float targetConcentration = 100.0f;       // in %
//    float targetO2Concentration = 37.00f;       // in mmHg
    float targetCO2Concentration = 0.00f;      // in mmHg
    float tEGCO2 = 20.00f;                     // in mmHg
//    float measuredCO2Concentration = 0.00f;
    float current_time = 0;
//    uint8_t co2_count = 0;
//    float EGCO2 = 0.0f                      // in mmHg
//    float Kp = 1;
    uint8_t p = 0;
    float tpCO2 = 40.0f;
//    float tEGO2 = 0.00f;        // in mmHg
    float Ambient_Pressure = 0.00f;     // in mmHg

        //========================================================================
        /* Initialize the necessary peripherals of the micro-controller */
        sciInit();
        gioInit();
        /* Initialize HET driver */
        hetInit();

        sciSetBaudrate (sciREG, 19200);
        sciSetBaudrate (scilinREG,115200);

        /* Set the direction of the GIOA port to be output */
        gioSetDirection(gioPORTA, 0XFFFFFFFF);

        /* Peripheral initialization Done */
        //=========================================================================
        /* Enable all interrupts & interrupt handlers*/
        _enable_IRQ();
        _enable_interrupt_();

        /* enable IRQ handlers */

        /* Interrupt enabling Done */

        sciEnableNotification(sciREG, SCI_RX_INT);
        sciEnableNotification(scilinREG, SCI_RX_INT);

//        gioSetDirection(gioPORTB, 1);

//        gioSetDirection(gioPORTA, 1);

//        gioSetBit(gioPORTA, 0, 1);

//        gioSetBit(gioPORTA, 1, 1);

//        gioSetBit(gioPORTA, 2, 1);

//        gioSetBit(gioPORTA, 5, 1);

        /** - Port B output values */


        /* - Port B direction */
//        gioPORTB->DIR = (uint32) ((uint32) 1U << 0U) /* Bit 0 */
//        | (uint32) ((uint32) 1U << 1U) /* Bit 1 */
//        | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
//        | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

//        gioPORTB->DOUT = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
//        | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
//        | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
//        | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

//        gioPORTB->DOUT = (uint32) ((uint32) 1U << 0U) /* Bit 0 */
//        | (uint32) ((uint32) 1U << 1U) /* Bit 1 */
//        | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
//        | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

//        gioPORTB->DOUT = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
//        | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
//        | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
//        | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

//        gioPORTB->DOUT = (uint32) ((uint32) 1U << 0U) /* Bit 0 */
//        | (uint32) ((uint32) 1U << 1U) /* Bit 1 */
//        | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
//        | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

//        gioPORTB->DOUT = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
//        | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
//        | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
//        | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

//        gioPORTB->DOUT = (uint32) ((uint32) 1U << 0U) /* Bit 0 */
//        | (uint32) ((uint32) 1U << 1U) /* Bit 1 */
//        | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
//        | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

//        gioPORTB->DOUT = (uint32) ((uint32) 0U << 0U) /* Bit 0 */
//        | (uint32) ((uint32) 0U << 1U) /* Bit 1 */
//        | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
//        | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

//        gioPORTB->DOUT = (uint32) ((uint32) 1U << 0U) /* Bit 0 */
//       | (uint32) ((uint32) 1U << 1U) /* Bit 1 */
//        | (uint32) ((uint32) 0U << 2U) /* Bit 2 (S1) */
//        | (uint32) ((uint32) 0U << 3U); /* Bit 3 (S2) */

//        co2SensorInit();
//
//        sciSetBaudrate (sciREG, 9600);
//
//        CO2_sensor_init();
//
//        get_CO2_val();
//
//        sciSetBaudrate (sciREG, 19200);
//
//        inletO2Init();

//        bloodFlowSensorInit();

//        calculateSetPoint(targetO2Concentration, sweepFlow);

        STATUS = Servo_On;
        MODE = CO2_CONTROL;

        pwmStart( hetRAM1, pwm0);
        pwmSetDuty(hetRAM1, pwm0, 15);

        //BRIAN CODE
        while(1) {
            co2SensorInit();
            sciSetBaudrate (sciREG, 9600);
            CO2_sensor_init();
//            measureCurrentFlows(&measuredAirFlow, &measuredO2Flow, &measuredCO2Flow);
//            measuredSweepFlow = (measuredAirFlow * 1.0f) + (measuredO2Flow * 1.0f) + (measuredCO2Flow * 1.0f);
            EGCO2 = get_CO2_val();
            float* tSweep = egco2PID(&EGCO2);
            calculateSetPoint(37, tSweep);
        }

////        while (1) {
//
////            pwmSetDuty(hetRAM1, pwm0, 10);
////            pwmSetDuty(hetRAM1, pwm0, 20);
////            pwmSetDuty(hetRAM1, pwm0, 30);
////            pwmStop(hetRAM1, pwm0);
//            co2SensorInit();
//            sciSetBaudrate (sciREG, 9600);
//            CO2_sensor_init();
//            get_CO2_val();
//          //Change the controller setting
//            calculateSetPoint(targetO2Concentration, sweepFlow);
//          // Measure current sweep flows
//            measureCurrentFlows(&measuredAirFlow, &measuredO2Flow, &measuredCO2Flow);
//            measuredSweepFlow = (measuredAirFlow * 1.0f) + (measuredO2Flow * 1.0f) + (measuredCO2Flow * 1.0f);
//            printf("Measured Sweep flow: %6.2f%\t\t ml/min\n", measuredSweepFlow);
//
//            sciSetBaudrate (sciREG, 19200);
//            inletO2Init();
////        }
//
//        while (1) {
//
//                         if (STATUS == Servo_On)
//                         {
////                             if (MODE == MEASUREMENT)
////                             {
////                                 pwm_pre_error = 0;
////                                 pwm_integral = 0;
////                                 pwm_integralUpdated = 0;
////                                 pwm_saturation = 0;
////                                 pwm_error = 0;
////                                 pwm_derivative = 0;
////                                 EGCO2 = 0;
////                                 pCO2 = 0;
////
//////                                 while (EGCO2 >= 0.8*pCO2)
//////                                 {
//////                                      tEGCO2 = 0;
//////                                 }
////
////                                sweepFlow = 0.4;
////                                for (p=0; p<80; p++)
////                                {
////                                    //Change the controller setting
////                                     calculateSetPoint(targetO2Concentration, sweepFlow);
////                                     // Measure current sweep flows
////                                     measureCurrentFlows(&measuredAirFlow, &measuredO2Flow, &measuredCO2Flow);
////                                     measuredSweepFlow = (measuredAirFlow * 1.0f) + (measuredO2Flow * 1.0f) + (measuredCO2Flow * 1.0f);
////                                     printf("Measured Sweep flow: %6.2f%\t\t ml/min\n", measuredSweepFlow);
////                                     // request co2 value
////                                     co2SensorInit();
////                                     sciSetBaudrate (sciREG, 9600);
////                                     CO2_sensor_init();
////                                     get_CO2_val();
////                                     if (EGCO2 >= pCO2)
////                                     {
////                                         pCO2 = EGCO2;
////                                     }
//////                                     store_data(current_time, tEGCO2, pCO2, EGCO2, sweepFlow*20200.0f, measuredSweepFlow, Ambient_Pressure);
////                                }
////                                tEGCO2 = calculate_tEGCO2(tpCO2, pCO2);
////                                // Store the collected data
//////                                store_data(current_time, tEGCO2, pCO2, EGCO2, sweepFlow*10000.0f, measuredSweepFlow, Ambient_Pressure);
////                                MODE = CO2_CONTROL;
////                             }
//
//                             /* CO2 Level Control Mode Control Loop */
//                      if (MODE == CO2_CONTROL)
//                      {
//                          for (p=0; p<240; p++)
//                          {
//                              // request co2 value
//                              co2SensorInit();
//                              sciSetBaudrate (sciREG, 9600);
//                              CO2_sensor_init();
//                              get_CO2_val();
//                              // Calculate the target Sweep Flow
//                              sweepFlow = calculate_PWM(tEGCO2, EGCO2);
//                              printf("tsweepFlow: %6.2f%\t\t\n", sweepFlow);
//                              //Change the controller setting
//                              calculateSetPoint(targetO2Concentration, sweepFlow);
//                              // Measure current sweep flows
//                              measureCurrentFlows(&measuredAirFlow, &measuredO2Flow, &measuredCO2Flow);
//                              measuredSweepFlow = (measuredAirFlow * 1.0f) + (measuredO2Flow * 1.0f) + (measuredCO2Flow * 1.0f);
//                              // Display the value
//                              printf("tEGCO2: %6.2f%\t\t mmHg\n", tEGCO2);
//                              printf("Measured Sweep flow: %6.2f%\t\t ml/min\n", measuredSweepFlow);
//                              // Store the collected data
// //                             store_data(current_time, tEGCO2, pCO2, EGCO2, sweepFlow*10000.0f, measuredSweepFlow, Ambient_Pressure);
//                          }
//       //                          MODE = MEASUREMENT;
//       //                      }
//
//
////                             if (MODE == CO2_CONTROL)
////                             {
////                                 for (p=0; p<240; p++)
////                                 {
//////                                     pressError = ABP2_getPressure(Ambient_Pressure_Sensor, &Ambient_Pressure);
////                                     // request co2 value
////                                     get_CO2_val();
////                                     // Calculate the target Sweep Flow
////                                     sweepFlow = calculate_PWM(tEGCO2, EGCO2);
////                                     //Change the controller setting
////                                     calculateSetPoint(targetO2Concentration, sweepFlow);
////                                     // Measure current sweep flows
////                                     measureCurrentFlows(&measuredAirFlow, &measuredO2Flow, &measuredCO2Flow);
////                                     measuredSweepFlow = (measuredAirFlow * 1.0f) + (measuredO2Flow * 1.0f) + (measuredCO2Flow * 1.0f);
////                                     // Display the value
////                                     printf("tEGCO2: %6.2f%\t\t mmHg\n", tEGCO2);
////                                     printf("Measured Sweep flow: %6.2f%\t\t ml/min\n", measuredSweepFlow);
////                                     // Store the collected data
//// //                                    store_data(current_time, tEGCO2, targetO2Concentration, EGCO2, measuredSweepFlow, measuredO2Flow, Ambient_Pressure);
////       //                              store_data(current_time, tEGCO2, pCO2, EGCO2, sweepFlow*10000.0f, measuredSweepFlow, Ambient_Pressure);
////                                 }
////                                 //MODE = MEASUREMENT;
////                             }
////
//                         }
//                         }
//        }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* USER CODE END */
