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
#include <stdio.h>
#include <string.h>
#include "reg_system.h"
#include "i2c.h"
#include "sci.h"
#include "lin.h"
#include "rti.h"
#include "adc.h"
#include "mibspi.h"
#include "ina226.h"
#include "ad5324.h"
#include "print.h"
#include "queue.h"
#include "eps.h"
#include "battery.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

static char  StringBuf[PRINT_BUFFER_SIZE+1];
static char  CommandString[PRINT_BUFFER_SIZE+1];
static char  uartRxData;

//static char  uartTxData;
Queue * receiveBuffer;
adcData_t adc_data;
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */




    PORT_UART_Init();
    PORT_UART_Enable_ISR(PORT_UART_UART0,PORT_UART_Flags_RX);
    receiveBuffer = QUEUE_Create();

    gioInit();      //general-purpose I/O (The initialization parameters are defined in other TI tool called HalCoGen)
    i2cInit();      //i2c interface for current sensors and temp. sensors (The initialization parameters are defined in other TI tool called HalCoGen)
    hetInit();
    rtiInit();
    adcInit();
    AD5324_Init();

    /* Enable RTI Compare 0 interrupt notification */
    rtiEnableNotification(rtiNOTIFICATION_COMPARE0);

    /* start adc conversion */
    adcStartConversion(adcREG1,adcGROUP1);


    _enable_IRQ();

    PORT_UART_Receive(PORT_UART_UART0,1,&uartRxData);

    /* Start RTI Counter Block 0 */
    rtiStartCounter(rtiCOUNTER_BLOCK0);
    rtiStartCounter(rtiCOUNTER_BLOCK1);

    /* Run forever */
    while (1)
    {
        /* Do nothing...*/
    }

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */

void rtiNotification(uint32_t notification)
{
    static uint32 ch_count=0;
    static uint32 isrStartTime = 0;
    if(notification == rtiNOTIFICATION_COMPARE0)
    {
        isrStartTime = rtiGetCurrentTick(rtiCOMPARE1);

        PRINT_PrintTimeFromMS(scilinREG,rtiGetCurrentTick(rtiCOMPARE1));
        PRINT_PrintStringln(scilinREG,":\trtiNOTIFICATION_COMPARE0");

        while(rtiGetCurrentTick(rtiCOMPARE1) - isrStartTime < 100);

        while((adcIsConversionComplete(adcREG1,adcGROUP1))!=8);

        PRINT_PrintTimeFromMS(scilinREG,rtiGetCurrentTick(rtiCOMPARE1));
        PRINT_Print(scilinREG,2,":\t");

        ch_count = adcGetData(adcREG1, adcGROUP1,&adc_data);

        sprintf(StringBuf,
                "COUNT:%d,\tID:%d,\tVALUE:0x%03X",
                ch_count,
                adc_data.id,
                adc_data.value);
        PRINT_PrintStringln(scilinREG,StringBuf);

        //PRINT_PrintTimeFromMS(scilinREG,rtiGetCurrentTick(rtiCOMPARE1));
        //PRINT_Print(scilinREG,2,"\r\n");
        //printBusVoltage(EPS_I2CADDR_MPPT1);
        //printBusCurrent(EPS_I2CADDR_MPPT1,EPS_SENSERESISTOR_MPPT1);
        //AD5324_Write( AD5324_ChannelA, AD5324_UpdateEnable, AD5324_ModeEnable, 1861);


    }
}

#pragma INTERRUPT(ssiInterrupt, IRQ)
void ssiInterrupt(void)
{

    static char * function;
    static char * arg[EPS_MAX_ARGS];
    static uint8_t i = 0;

    if (systemREG1->SSIVEC & 0x1U )
    {
        function = strtok(CommandString,"(");

        for(i = 0; i<EPS_MAX_ARGS; i++)
        {
            arg[i] = strtok(NULL,",");
            if (arg[i] == NULL) break;
        }
        i = i - 1;
        arg[i] = strtok(arg[i],")");

        for(i = 0; arg[i]!=NULL && i<EPS_MAX_ARGS; i++)
        {
            arg[i] = strtok(arg[i]," ");

        }

        EPS_runCommand(function,arg,i);

    }
}

void PORT_UART_ISR(PORT_UART_Reg_TypeDef *uart, uint32_t flags)
{
    static uint8_t i = 0;

    if(flags & PORT_UART_Flags_RX)
    {
        if (uartRxData == '\r')//) || uartRxData == '\n')
        {
            if (!receiveBuffer->isEmpty(receiveBuffer))
            {
                receiveBuffer->insert(receiveBuffer,'\0');
                for (i = 0; (!receiveBuffer->isEmpty(receiveBuffer)); i++)
                {
                    CommandString[i] = receiveBuffer->remove(receiveBuffer);
                }
                systemREG1->SSISR1 = 0x7500U;
            }
        }
        else if (!receiveBuffer->isFull(receiveBuffer))
        {
            if ( uartRxData>='a' && uartRxData<='z' )
            {
                uartRxData = uartRxData - 0x20;
            }
            receiveBuffer->insert(receiveBuffer,uartRxData);
        }
        PORT_UART_Receive(uart,1,&uartRxData);

    }
}

/* USER CODE END */
