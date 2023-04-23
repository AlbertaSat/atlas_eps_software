/** @file print.h 
*   @brief UART IO processing functions definition file
*   @date 16-Dec-2022
*   @author Stefan Damkjar, Junqi Zhu
*
*/

/** 
 *  @defgroup PRINT PRINT
 *  @brief Functions for processing UART IO.
 *
 *	Related Files
 *   - print.h
 *   - print.c
 *   - queue.h
 *   - stdint.h
 *   - port_uart.h
 */

#ifndef INCLUDE_PRINT_H_
#define INCLUDE_PRINT_H_

#include "port_uart.h"
#include "queue.h"
#include "stdint.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define PRINT_BUFFER_SIZE     (50U)

/** 
 *  @addtogroup PRINT
 *  @{
 */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** @enum PRINT_Err_TypeDef
*   @brief Alias names for PRINT errors.
*/

typedef enum
{
    PRINT_Err_NoError = 0,           /**< No error*/
    PRINT_Err_FE      =  PORT_UART_Err_FE, /**< Framing error flag*/
    PRINT_Err_OR      =  PORT_UART_Err_OE, /**< Overrun error flag*/
    PRINT_Err_PE      =  PORT_UART_Err_PE  /**< Parity error flag*/
} PRINT_Err_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

PRINT_Err_TypeDef PRINT_Print(PORT_UART_Reg_TypeDef *uart,
                                uint32_t length,
                                char* data);

PRINT_Err_TypeDef PRINT_PrintChar(PORT_UART_Reg_TypeDef *uart,
                                  char data);

PRINT_Err_TypeDef PRINT_PrintString(PORT_UART_Reg_TypeDef *uart,
                                    char* data);

PRINT_Err_TypeDef PRINT_PrintStringln(PORT_UART_Reg_TypeDef *uart,
                                      char* data);

PRINT_Err_TypeDef PRINT_PrintTimeFromMS(PORT_UART_Reg_TypeDef *uart,
                          uint32_t currentTime);





/**@}*/

#endif /* INCLUDE_PRINT_H_ */
