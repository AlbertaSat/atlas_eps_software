/** @file i2c_port.h 
*   @brief I2C Driver Wrapper Definition File for TI HAL libraries
*   @date 19-Dec-2022
*   @author Stefan Damkjar, Junqi Zhu
*
*/

/** 
 *  @defgroup I2C_PORT I2C_PORT
 *  @brief Portable I2C Driver Wrapper Module for TI HAL libraries.
 *
 *	Related Files
 *   - i2c_port.h
 *   - i2c_port.c
 *   - i2c.h
 *   - stdint.h
 */

#ifndef DRIVERS_I2C_PORT_H_
#define DRIVERS_I2C_PORT_H_

#include "i2c.h"
#include "stdint.h"

typedef i2cBASE_t I2C_PORT_Reg_TypeDef;

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define I2C_PORT_DELAY (0)
#define I2C_PORT_MAX_RETRIES (100000)

/** 
 *  @addtogroup I2C_PORT
 *  @{
 */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** @enum I2C_PORT_Err_TypeDef
*   @brief Alias names for I2C_PORT errors.
*/

typedef enum
{
  I2C_PORT_Err_NoError   = 0U,           /**< No error*/
  I2C_PORT_Err_AL        = I2C_AL_INT,   /**< Arbitration lost*/
  I2C_PORT_Err_NACK      = I2C_NACK_INT  /**< No acknowledgment */
} I2C_PORT_Err_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

I2C_PORT_Err_TypeDef I2C_PORT_Send(I2C_PORT_Reg_TypeDef *i2c,
                            uint32_t addr,
                            uint32_t length,
                            uint8_t *data   );

I2C_PORT_Err_TypeDef I2C_PORT_Receive(I2C_PORT_Reg_TypeDef *i2c,
                            uint32_t addr,
                            uint32_t length,
                            uint8_t *data   );


/**@}*/

#endif /* DRIVERS_INA226_H_ */
