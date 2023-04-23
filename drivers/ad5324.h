/** @file ad5324.h 
*   @brief AD5324 Driver Definition File
*   @date 16-Dec-2022
*   @author Stefan Damkjar, Junqi Zhu
*
*/

/** 
 *  @defgroup AD5324 AD5324
 *  @brief AD5324 4-channel 12-bit buffered voltage DAC.
 *  
 *  The AD5324 is a c4-channel 12-bit buffered voltage DAC with a 3-wire serial
 *  interface that is compatible with SPI interface standards.
 *
 *	Related Files
 *   - ad5324.h
 *   - ad5324.c
 *   - gio.h
 *   - het.h
 */

#ifndef DRIVERS_AD5324_H_
#define DRIVERS_AD5324_H_		

#include "gio.h"
#include "het.h"
#include "mibspi.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define AD5324_SCLK_PIN     (9U)
#define AD5324_SCLK_PORT    (mibspiPORT3)

#define AD5324_NSYNC_PIN    (16U)
#define AD5324_NSYNC_PORT   (hetPORT1)

#define AD5324_DIN_PIN      (10U)
#define AD5324_DIN_PORT     (mibspiPORT3)

#define AD5324_DATA              (0xFFUL << 0)
#define _AD5324_DATA_SHIFT       0
#define _AD5324_DATA_MASK        0xFFFUL
#define _AD5324_DATA_DEFAULT     0x0UL
#define AD5324_DATA_DEFAULT      (_AD5324_DATA_DEFAULT << 0)
#define AD5324_UPDATE            (0x1 << 12)
#define _AD5324_UPDATE_SHIFT     12
#define _AD5324_UPDATE_MASK      0x1000UL
#define _AD5324_UPDATE_ENABLE    0x0UL
#define _AD5324_UPDATE_DISABLE   0x1UL
#define _AD5324_UPDATE_DEFAULT   _AD5324_UPDATE_ENABLE
#define AD5324_UPDATE_ENABLE     (_AD5324_UPDATE_ENABLE << 12)
#define AD5324_UPDATE_DISABLE    (_AD5324_UPDATE_DISABLE << 12)
#define AD5324_UPDATE_DEFAULT    (_AD5324_UPDATE_DEFAULT << 12)
#define AD5324_MODE              (0x1 << 13)
#define _AD5324_MODE_SHIFT       13
#define _AD5324_MODE_MASK        0x2000UL
#define _AD5324_MODE_POWERDOWN   0x0UL
#define _AD5324_MODE_ENABLE      0x1UL
#define _AD5324_MODE_DEFAULT     _AD5324_MODE_POWERDOWN
#define AD5324_MODE_POWERDOWN    (_AD5324_MODE_POWERDOWN << 13)
#define AD5324_MODE_ENABLE       (_AD5324_MODE_ENABLE << 13)
#define AD5324_MODE_DEFAULT      (_AD5324_MODE_DEFAULT << 13)
#define AD5324_CHANNEL           (0x3 << 14)
#define _AD5324_CHANNEL_SHIFT     14
#define _AD5324_CHANNEL_MASK     0xC000UL
#define _AD5324_CHANNEL_A        0x0UL
#define _AD5324_CHANNEL_B        0x1UL
#define _AD5324_CHANNEL_C        0x2UL
#define _AD5324_CHANNEL_D        0x3UL
#define _AD5324_CHANNEL_DEFAULT  _AD5324_CHANNEL_A
#define AD5324_CHANNEL_A         (_AD5324_CHANNEL_A << 14)
#define AD5324_CHANNEL_B         (_AD5324_CHANNEL_B << 14)
#define AD5324_CHANNEL_C         (_AD5324_CHANNEL_C << 14)
#define AD5324_CHANNEL_D         (_AD5324_CHANNEL_D << 14)
#define AD5324_CHANNEL_DEFAULT   (_AD5324_CHANNEL_DEFAULT << 14)

/** 
 *  @addtogroup AD5324
 *  @{
 */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** @enum AD5324_Update_TypeDef
*   @brief Alias names for AD5324 update modes.
*/

typedef enum
{
  AD5324_UpdateEnable = 0U, /**< All DAC outputs update after write (default)*/ 
  AD5324_UpdateDisable = 1U /**< Only input register is updated (No change to DAC
                                outputs)*/
} AD5324_Update_TypeDef;

/** @enum AD5324_Channel_TypeDef
*   @brief Alias names for AD5324 enable or powerdown mode.
*/

typedef enum
{
  AD5324_ModePowerDown = 0U, /**< All DAC outputs enter high impedance state
                                (default)*/
  AD5324_ModeEnable = 1U     /**< Normal operation (All DAC outputs enabled)*/
} AD5324_Mode_TypeDef;

/** @enum AD5324_Channel_TypeDef
*   @brief Alias names for AD5324 channels.
*/

typedef enum
{
  AD5324_ChannelA = 0U, /**< Address DAC channel A (default)*/
  AD5324_ChannelB = 1U, /**< Address DAC channel B (default)*/
  AD5324_ChannelC = 2U, /**< Address DAC channel C (default)*/
  AD5324_ChannelD = 3U  /**< Address DAC channel D (default)*/
} AD5324_Channel_TypeDef;

/** @enum AD5324_Err_TypeDef
*   @brief Alias names for AD5324 errors.
*/

typedef enum
{
  AD5324_Err_NoError     = 0, /**< No error*/
  AD5324_Err_ValTooLarge = 1  /**< DAC value too large (must be <=4095)*/
} AD5324_Err_TypeDef;


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void AD5324_Init ();

AD5324_Err_TypeDef AD5324_Write (AD5324_Channel_TypeDef channel,
                                AD5324_Update_TypeDef update,
                                AD5324_Mode_TypeDef mode,
                                uint16_t val);

/**@}*/

#endif /* DRIVERS_AD5324_H_ */
