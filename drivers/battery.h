/** @file battery.h 
*   @brief Battery Board Definition File
*   @date 20-Dec-2022
*   @author Stefan Damkjar, Junqi Zhu
*
*/

/** 
 *  @defgroup BATTERY BATTERY
 *  @brief Portable I2C Driver Wrapper Module for TI HAL libraries.
 *
 *	Related Files
 *   - battery.h
 *   - battery.c
 *   - stdint.h
 *   - ina226.h
 */

#ifndef DRIVERS_BATTERY_H_
#define DRIVERS_BATTERY_H_

#include "ina226.h"
#include "stdint.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/*****************************************/
//  I2C Addresses
/*****************************************/

/**
 * @todo Fix addresses for final version
 */
#define BATTERY_I2CADDR_TEMP      /*(MAX6698_ADDR38)*/               /* populated */
#define BATTERY_I2CADDR_CURR1     (INA226_ADDR48)/*(INA226_ADDR40)*/ /* populated */
#define BATTERY_I2CADDR_CURR2     (INA226_ADDR45)

/*****************************************/
//  Current sense resistors in mOhm
/*****************************************/

#define BATTERY_SENSERESISTOR_TEMP      (5)
#define BATTERY_SENSERESISTOR_CURR1     (5)
#define BATTERY_SENSERESISTOR_CURR1     (5)

/** 
 *  @addtogroup BATTERY
 *  @{
 */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/


/**@}*/

#endif /* DRIVERS_BATTERY_H_ */
