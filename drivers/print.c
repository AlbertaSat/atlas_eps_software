/** @file print.c 
*   @brief UART IO processing functions implementation file
*   @date 16-Dec-2022
*   @author Stefan Damkjar, Junqi Zhu
*
*/

#include "print.h"
#include "port_uart.h"
#include "stdint.h"

static char  StringBuf[PRINT_BUFFER_SIZE];


/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/


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
PRINT_Err_TypeDef PRINT_Print(PORT_UART_Reg_TypeDef *uart,
                                uint32_t length,
                                char *data)
{
  return (PRINT_Err_TypeDef)PORT_UART_Send(uart,length,data);
}

/***************************************************************************//**
 * @brief
 *   Print a single byte.
 *
 * @param[in] uart
 *   Pointer to UART peripheral register block.
 *
 * @param[in] data
 *   Byte to print.
 *
 * @return
 *   Returns 0 if no error.
 ******************************************************************************/
PRINT_Err_TypeDef PRINT_PrintChar(PORT_UART_Reg_TypeDef *uart,
                                  char data)
{
  return (PRINT_Err_TypeDef)PORT_UART_SendByte(uart,data);
}

/***************************************************************************//**
 * @brief
 *   Print null terminated string.
 *
 * @param[in] uart
 *   Pointer to UART peripheral register block.
 *
 * @param[in] data
 *   Pointer to null terminated string to print. (MUST BE NULL TERMINATED)
 *
 * @return
 *   Returns 0 if no error.
 ******************************************************************************/
PRINT_Err_TypeDef PRINT_PrintString(PORT_UART_Reg_TypeDef *uart,
                                    char* data)
{

  int i = 0;
  PRINT_Err_TypeDef ret = PRINT_Err_NoError;

  for(i = 0;data[i]!='\0'  && i<PRINT_BUFFER_SIZE ;i++){
    ret = PRINT_PrintChar(uart,data[i]);
    if ( ret != PRINT_Err_NoError )
    {
      return ret;
    }
  }

  return ret;

}

/***************************************************************************//**
 * @brief
 *   Print null terminated string followed by new-line character.
 *
 * @param[in] uart
 *   Pointer to UART peripheral register block.
 *
 * @param[in] data
 *   Pointer to null terminated string to print.  (MUST BE NULL TERMINATED)
 *
 * @return
 *   Returns 0 if no error.
 ******************************************************************************/
PRINT_Err_TypeDef PRINT_PrintStringln(PORT_UART_Reg_TypeDef *uart,
                                      char* data)
{

  PRINT_Err_TypeDef ret = PRINT_Err_NoError;

  ret = PRINT_PrintString(uart,data);
  if ( ret != PRINT_Err_NoError )
  {
    return ret;
  }

  ret = PRINT_PrintChar(uart,'\r');
  if ( ret != PRINT_Err_NoError )
  {
    return ret;
  }

  return PRINT_PrintChar(uart,'\n');

}

/***************************************************************************//**
 * @brief
 *   Print time in HH:MM:SS.XXX format, calculated from ms tick count.
 *
 * @param[in] uart
 *   Pointer to UART peripheral register block.
 *
 * @param[in] data
 *   Tick count in ms.
 *
 * @return
 *   Returns 0 if no error.
 ******************************************************************************/
PRINT_Err_TypeDef PRINT_PrintTimeFromMS(PORT_UART_Reg_TypeDef *uart,
                          uint32_t currentTime)
{
  uint32_t msec = currentTime % 1000;

  currentTime /= 1000;

  uint8_t sec = currentTime % 60;

  currentTime /= 60;

  uint8_t min = currentTime % 60;

  currentTime /= 60;

  StringBuf[0] = 0x30 + (currentTime / 10);
  StringBuf[1] = 0x30 + (currentTime % 10);
  StringBuf[2] = ':';
  StringBuf[3] = 0x30 + (min / 10);
  StringBuf[4] = 0x30 + (min % 10);
  StringBuf[5] = ':';
  StringBuf[6] = 0x30 + (sec / 10);
  StringBuf[7] = 0x30 + (sec % 10);
  StringBuf[8] = '.';
  StringBuf[9] = 0x30 + (msec / 100);
  StringBuf[10] = 0x30 + ((msec / 10) % 10);
  StringBuf[11] = 0x30 + (msec % 10);

  return PRINT_Print(uart,12,StringBuf);
}


