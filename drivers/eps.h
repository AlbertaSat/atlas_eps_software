/** @file eps.h 
*   @brief EPS Board Definition File
*   @date 20-Dec-2022
*   @author Stefan Damkjar, Junqi Zhu
*
*/

/** 
 *  @defgroup EPS EPS
 *  @brief Portable I2C Driver Wrapper Module for TI HAL libraries.
 *
 *	Related Files
 *   - eps.h
 *   - eps.c
 *   - stdint.h
 */

#ifndef DRIVERS_EPS_H_
#define DRIVERS_EPS_H_

#include "port_i2c.h"
#include "print.h"
#include "stdint.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define EPS_MAX_ARGS (10)

#define EPS_COMMAND_READ 

/*****************************************/
//  I2C Addresses
/*****************************************/

#define EPS_I2CADDR_OUTPUT01 (INA226_ADDR40 ^ 0x5F) /* populated */
#define EPS_I2CADDR_OUTPUT02 (INA226_ADDR41 ^ 0x5F) /* populated */
#define EPS_I2CADDR_OUTPUT03 (INA226_ADDR42 ^ 0x5F) /* populated */
#define EPS_I2CADDR_OUTPUT04 (INA226_ADDR43 ^ 0x5F)
#define EPS_I2CADDR_OUTPUT05 (INA226_ADDR44 ^ 0x5F)
#define EPS_I2CADDR_OUTPUT06 (INA226_ADDR45 ^ 0x5F)
#define EPS_I2CADDR_OUTPUT07 (INA226_ADDR46 ^ 0x5F)
#define EPS_I2CADDR_OUTPUT08 (INA226_ADDR47 ^ 0x5F)
#define EPS_I2CADDR_OUTPUT09 (INA226_ADDR48 ^ 0x5F)
#define EPS_I2CADDR_OUTPUT10 (INA226_ADDR49 ^ 0x5F)
#define EPS_I2CADDR_OUTPUT11 (INA226_ADDR4A ^ 0x5F)
#define EPS_I2CADDR_OUTPUT12 (INA226_ADDR4B ^ 0x5F)
#define EPS_I2CADDR_OUTPUT13 (INA226_ADDR4C ^ 0x5F)
#define EPS_I2CADDR_OUTPUT14 (INA226_ADDR4D ^ 0x5F)
#define EPS_I2CADDR_OUTPUT15 (INA226_ADDR4E ^ 0x5F)
#define EPS_I2CADDR_OUTPUT16 (INA226_ADDR4F ^ 0x5F)
#define EPS_I2CADDR_OUTPUT17 (INA226_ADDR4C) /* populated */
#define EPS_I2CADDR_OUTPUT18 (INA226_ADDR4E) /* populated */

#define EPS_I2CADDR_3V3BUS   (INA226_ADDR4B) 
#define EPS_I2CADDR_1V2BUS   (INA226_ADDR49)
#define EPS_I2CADDR_5V0BUS   (INA226_ADDR4D)
#define EPS_I2CADDR_BATBUS   (INA226_ADDR44) /* populated */

#define EPS_I2CADDR_EPS3V3   (INA226_ADDR46)
#define EPS_I2CADDR_EPS1V2   (INA226_ADDR4A)
#define EPS_I2CADDR_PV3V3    (INA226_ADDR47)

/**
 * @todo Fix addresses for final version
 */
#define EPS_I2CADDR_MPPT1    (INA226_ADDR49) /*(INA3221_ADDR40)*/ /* populated */
#define EPS_I2CADDR_MPPT2    /*(INA3221_ADDR41)*/
#define EPS_I2CADDR_MPPT3    /*(INA3221_ADDR42)*/
#define EPS_I2CADDR_MPPT4    /*(INA3221_ADDR43)*/

#define EPS_I2CADDR_RTC      /*(RV3032_ADDR51)*/

/*****************************************/
//  Current sense resistors in mOhm
/*****************************************/

/**
 * @todo Fix sense resistor values (all to 5)
 */
#define EPS_SENSERESISTOR_OUTPUT01 (100)
#define EPS_SENSERESISTOR_OUTPUT02 (100)
#define EPS_SENSERESISTOR_OUTPUT03 (100)
#define EPS_SENSERESISTOR_OUTPUT04 (5)
#define EPS_SENSERESISTOR_OUTPUT05 (5)
#define EPS_SENSERESISTOR_OUTPUT06 (5)
#define EPS_SENSERESISTOR_OUTPUT07 (5)
#define EPS_SENSERESISTOR_OUTPUT08 (5)
#define EPS_SENSERESISTOR_OUTPUT09 (5)
#define EPS_SENSERESISTOR_OUTPUT10 (5)
#define EPS_SENSERESISTOR_OUTPUT11 (5)
#define EPS_SENSERESISTOR_OUTPUT12 (5)
#define EPS_SENSERESISTOR_OUTPUT13 (5)
#define EPS_SENSERESISTOR_OUTPUT14 (5)
#define EPS_SENSERESISTOR_OUTPUT15 (5)
#define EPS_SENSERESISTOR_OUTPUT16 (5)
#define EPS_SENSERESISTOR_OUTPUT17 (100)
#define EPS_SENSERESISTOR_OUTPUT18 (100)

#define EPS_SENSERESISTOR_3V3BUS   (5)
#define EPS_SENSERESISTOR_1V2BUS   (5)
#define EPS_SENSERESISTOR_5V0BUS   (5)
#define EPS_SENSERESISTOR_BATBUS   (100)

#define EPS_SENSERESISTOR_EPS3V3   (5)
#define EPS_SENSERESISTOR_EPS1V2   (5)
#define EPS_SENSERESISTOR_PV3V3    (5)

#define EPS_SENSERESISTOR_MPPT1    (5)  
#define EPS_SENSERESISTOR_MPPT2    (5)
#define EPS_SENSERESISTOR_MPPT3    (5)
#define EPS_SENSERESISTOR_MPPT4    (5)

/** 
 *  @addtogroup EPS
 *  @{
 */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/
typedef enum
{
  EPS_Err_NoError     = 0, /**< No error*/
  EPS_Err_Syntax = 1  /**< Invalid syntax (see manual for help)*/
} EPS_Err_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

EPS_Err_TypeDef EPS_runCommand(char * function,
                            char * arg[EPS_MAX_ARGS],
                            uint8_t numArgs);

/**@}*/

#endif /* DRIVERS_EPS_H_ */
