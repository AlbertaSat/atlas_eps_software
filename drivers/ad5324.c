/** @file ad5324.c 
*   @brief AD5324 Driver Implementation File
*   @date 16-Dec-2022
*   @author Stefan Damkjar, Junqi Zhu
*
*/

#include "ad5324.h"


/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

void AD5324_Init ()
{
    gioSetDirection(AD5324_SCLK_PORT,(AD5324_SCLK_PORT->DIR)|(0x1<<AD5324_SCLK_PIN));
    gioSetDirection(AD5324_NSYNC_PORT,(AD5324_NSYNC_PORT->DIR)|(0x1<<AD5324_NSYNC_PIN));
    gioSetDirection(AD5324_DIN_PORT,(AD5324_DIN_PORT->DIR)|(0x1<<AD5324_DIN_PIN));
    
}

/***************************************************************************//**
 * @brief
 *   Set content of DAC5324.
 *
 * @param[in] spi
 *   Pointer to SPI peripheral register block.
 *
 * @param[in] channel
 *   Configure which DAC channel to write to.
 *
 * @param[in] update
 *   Configure DAC update mode.
 *
 * @param[in] mode
 *   Configure DAC mode (enable or powerdown)
 * 
 * @param[in] val
 *   Value used when writing to data bits.
 *
 * @return
 *   Returns 0 if no error.
 ******************************************************************************/
AD5324_Err_TypeDef AD5324_Write (AD5324_Channel_TypeDef channel,
                                AD5324_Update_TypeDef update,
                                AD5324_Mode_TypeDef mode,
                                uint16_t val)
{
    uint8_t i = 0;
    uint8_t t = 0;

    /* Check if DAC value exceeds limit (must be <= 4095) */
    if ( val > 0xFFF ) return AD5324_Err_ValTooLarge;

    /* Build data word */
    val = val | ((channel << _AD5324_CHANNEL_SHIFT) |
                 (update  << _AD5324_UPDATE_SHIFT ) |
                 (mode    << _AD5324_MODE_SHIFT   ));

    /* Clear and set clock */
    //gioSetBit(AD5324_SCLK_PORT,AD5324_SCLK_PIN,0);
    //gioSetBit(AD5324_SCLK_PORT,AD5324_SCLK_PIN,1);

    /* Assert nSync */
    gioSetBit(AD5324_NSYNC_PORT,AD5324_NSYNC_PIN,0);

    for(t=0;t<0x80;t++);

    /* Shift out bits with clock edges */
    for ( i = 0; i <= 15; i++)
    {
        gioSetBit(AD5324_DIN_PORT,AD5324_DIN_PIN, (val & 0x8000) >> 15 );
        for(t=0;t<0x80;t++);
        val = val << 1;
        gioSetBit(AD5324_SCLK_PORT,AD5324_SCLK_PIN,0);
        for(t=0;t<0x80;t++);
        gioSetBit(AD5324_SCLK_PORT,AD5324_SCLK_PIN,1);
        for(t=0;t<0x80;t++);
    }

    /* Reset nSync */
    gioSetBit(hetPORT1,16,1);

    /* Return no error */
    return AD5324_Err_NoError;
}
