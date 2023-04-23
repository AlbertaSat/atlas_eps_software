/** @file port_i2c.h 
*   @brief Portable frontend for I2C Peripheral using TI HAL libraries.
*   @date 19-Dec-2022
*   @author Stefan Damkjar, Junqi Zhu
*
*/

/** 
 *  @defgroup PORT_I2C PORT_I2C
 *  @brief Portable I2C Peripheral Frontend Module for TI HAL libraries.
 *
 *	Related Files
 *   - port_i2c.h
 *   - port_i2c.c
 *   - i2c.h
 *   - stdint.h
 */

#ifndef DRIVERS_PORT_I2C_H_
#define DRIVERS_PORT_I2C_H_

#include "i2c.h"
#include "stdint.h"

typedef i2cBASE_t PORT_I2C_Reg_TypeDef;

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define PORT_I2C_MAX_RETRIES (100000)

#define PORT_I2C (i2cREG1)

/** 
 *  @addtogroup PORT_I2C
 *  @{
 */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** @enum PORT_I2C_Err_TypeDef
*   @brief Alias names for PORT_I2C errors.
*/

typedef enum
{
  PORT_I2C_Err_NoError   = 0U,           /**< No error*/
  PORT_I2C_Err_AL        = I2C_AL_INT,   /**< Arbitration lost*/
  PORT_I2C_Err_NACK      = I2C_NACK_INT  /**< No acknowledgment */
} PORT_I2C_Err_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

PORT_I2C_Err_TypeDef PORT_I2C_Send(PORT_I2C_Reg_TypeDef *i2c,
                            uint32_t addr,
                            uint32_t length,
                            uint8_t *data   );

PORT_I2C_Err_TypeDef PORT_I2C_Receive(PORT_I2C_Reg_TypeDef *i2c,
                            uint32_t addr,
                            uint32_t length,
                            uint8_t *data   );


/**@}*/

#endif /* DRIVERS_PORT_I2C_H_ */
