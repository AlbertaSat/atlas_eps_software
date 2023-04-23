/** @file port_uart.h 
*   @brief Portable frontend for UART Peripheral using TI HAL libraries.
*   @date 20-Dec-2022
*   @author Stefan Damkjar, Junqi Zhu
*
*/

/** 
 *  @defgroup PORT_UART PORT_UART
 *  @brief Portable UART Peripheral Frontend Module for TI HAL libraries.
 *
 *	Related Files
 *   - port_uart.h
 *   - port_uart.c
 *   - sci.h
 *   - stdint.h
 */

#ifndef DRIVERS_PORT_UART_H_
#define DRIVERS_PORT_UART_H_

#include "sci.h"
#include "stdint.h"

typedef sciBASE_t PORT_UART_Reg_TypeDef;

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define PORT_UART_UART0 (scilinREG)
#define PORT_UART_ISR sciNotification
#define PORT_UART_Init sciInit
#define PORT_UART_Enable_ISR sciEnableNotification

/** 
 *  @addtogroup PORT_UART
 *  @{
 */


/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** @enum PORT_UART_Err_TypeDef
*   @brief Alias names for PORT_UART errors.
*/

typedef enum
{
  PORT_UART_Err_NoError   = 0U,           /**< No error*/
  PORT_UART_Err_FE      =  SCI_FE_INT, /**< Framing error*/
  PORT_UART_Err_OE      =  SCI_OE_INT, /**< Overrun error*/
  PORT_UART_Err_PE      =  SCI_PE_INT  /**< Parity error*/ 
} PORT_UART_Err_TypeDef;

/** @enum PORT_UART_Err_TypeDef
*   @brief Alias names for PORT_UART interrupt flags.
*/

typedef enum
{
  PORT_UART_Flags_FE      =  SCI_FE_INT, /**< Framing error flag*/
  PORT_UART_Flags_OE      =  SCI_OE_INT, /**< Overrun error flag*/
  PORT_UART_Flags_PE      =  SCI_PE_INT,  /**< Parity error flag*/ 
  PORT_UART_Flags_RX      =  SCI_RX_INT,  /**< Receive buffer ready flag*/ 
  PORT_UART_Flags_TX      =  SCI_TX_INT,  /**< Transmit buffer ready flag*/ 
  PORT_UART_Flags_WAKE      =  SCI_WAKE_INT,  /**< Wakeup flag*/ 
  PORT_UART_Flags_BREAK      =  SCI_BREAK_INT  /**< Break detect flag*/ 
} PORT_UART_Flags_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

PORT_UART_Err_TypeDef PORT_UART_SendByte(PORT_UART_Reg_TypeDef *uart,
                                         char data);

PORT_UART_Err_TypeDef PORT_UART_Send(PORT_UART_Reg_TypeDef *uart,
                                        uint32_t length,
                                        char *data);

PORT_UART_Err_TypeDef PORT_UART_Receive(PORT_UART_Reg_TypeDef *uart,
                                        uint32 length,
                                        char *data);

/**@}*/

#endif /* DRIVERS_PORT_UART_H_ */
