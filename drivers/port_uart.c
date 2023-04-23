/** @file port_uart.c 
*   @brief Portable frontend for UART Peripheral using TI HAL libraries.
*   @date 20-Dec-2022
*   @author Stefan Damkjar, Junqi Zhu
*
*/

#include "port_uart.h"
#include "sci.h"
#include "stdint.h"

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Send a byte of data over UART peripheral.
 *
 * @param[in] uart
 *   Pointer to UART peripheral register block.
 *
 * @param[in] data
 *   Data byte to send.
 *
 * @return
 *   Returns 0 if no error.
 ******************************************************************************/

PORT_UART_Err_TypeDef PORT_UART_SendByte(PORT_UART_Reg_TypeDef *uart,char data)
{
    sciSendByte(uart,data);

    return (PORT_UART_Err_TypeDef)sciRxError(uart);
}

/***************************************************************************//**
 * @brief
 *   Print a block of data with specified length.
 *
 * @param[in] uart
 *   Pointer to UART peripheral register block.
 *
 * @param[in] length
 *   Number of uint8_t data words to transfer
 *
 * @param[in] data
 *   Pointer to data to send.
 *
 * @return
 *   Returns 0 if no error.
 ******************************************************************************/
PORT_UART_Err_TypeDef PORT_UART_Send(PORT_UART_Reg_TypeDef *uart,
                                uint32_t length,
                                char *data)
{
    sciSend(uart,length, (uint8_t*)data);
    
    return (PORT_UART_Err_TypeDef)sciRxError(uart);
}

/***************************************************************************//**
 * @brief
 *   Receive available data up to a specified length.
 *
 * @param[in] uart
 *   Pointer to UART peripheral register block.
 *
 * @param[in] data
 *   Pointer to data to send.
 *
 * @return
 *   Returns 0 if no error.
 ******************************************************************************/
PORT_UART_Err_TypeDef PORT_UART_Receive(PORT_UART_Reg_TypeDef *uart,
                                uint32 length,
                                char *data)
{
    sciReceive(uart,1, (uint8_t*)data);
    
    return (PORT_UART_Err_TypeDef)sciRxError(uart);
}
