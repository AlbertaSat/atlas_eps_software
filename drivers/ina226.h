/** @file ina226.h 
*   @brief INA226 Driver Definition File
*   @date 16-Dec-2022
*   @author Stefan Damkjar, Junqi Zhu
*
*/

/** 
 *  @defgroup INA226 INA226
 *  @brief INA226 Current and Power Monitor Module.
 *  
 *  The INA226 is a current shunt, bus voltage, and power monitor with an I2C 
 *  interface. Includes programmable calibration values, conversions times, and
 *  averaging.
 *
 *	Related Files
 *   - ina226.h
 *   - ina226.c
 *   - port_i2c.h
 *   - stdint.h
 */

#ifndef DRIVERS_INA226_H_
#define DRIVERS_INA226_H_

#include "port_i2c.h"
#include "stdint.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define INA226_BUSVOLTAGELSB (1250) /* Bus voltage LSB in uV */
#define INA226_SHUNTVOLTAGELSB (2500) /* Bus voltage LSB in nV */


								                  /*	A1	|	A0 	*/
								                  /* ---------- */
#define INA226_ADDR40     (0x40U)  /* 	GND	|	GND	*/
#define INA226_ADDR41     (0x41U)  /* 	GND	|	VS	*/
#define INA226_ADDR42     (0x42U)  /* 	GND	|	SDA	*/
#define INA226_ADDR43     (0x43U)  /* 	GND	|	SCL	*/
#define INA226_ADDR44     (0x44U)  /* 	VS	|	GND	*/
#define INA226_ADDR45     (0x45U)  /* 	VS	|	VS	*/
#define INA226_ADDR46     (0x46U)  /* 	VS	|	SDA	*/
#define INA226_ADDR47     (0x47U)  /* 	VS	|	SCL	*/
#define INA226_ADDR48     (0x48U)  /* 	SDA	|	GND	*/
#define INA226_ADDR49     (0x49U)  /* 	SDA	|	VS	*/
#define INA226_ADDR4A     (0x4AU)  /* 	SDA	|	SDA	*/
#define INA226_ADDR4B     (0x4BU)  /* 	SDA	|	SCL	*/
#define INA226_ADDR4C     (0x4CU)  /* 	SCL	|	GND	*/
#define INA226_ADDR4D     (0x4DU)  /* 	SCL	|	VS	*/
#define INA226_ADDR4E     (0x4EU)  /* 	SCL	|	SDA	*/
#define INA226_ADDR4F     (0x4FU)  /* 	SCL	|	SCL	*/

#define INA226_CONFIG_MODE 				      (0x7UL << 0)
#define _INA226_CONFIG_MODE_SHIFT 		  0
#define _INA226_CONFIG_MODE_MASK 		    0x7UL
#define _INA226_CONFIG_MODE_POWERDOWN1 	0x0UL
#define _INA226_CONFIG_MODE_SVTRIG	  	0x1UL
#define _INA226_CONFIG_MODE_BVTRIG  	  0x2UL
#define _INA226_CONFIG_MODE_SBTRIG  	  0x3UL
#define _INA226_CONFIG_MODE_POWERDOWN2 	0x4UL
#define _INA226_CONFIG_MODE_SVCONT  	  0x5UL
#define _INA226_CONFIG_MODE_BVCONT  	  0x6UL
#define _INA226_CONFIG_MODE_SBCONT  	  0x7UL
#define _INA226_CONFIG_MODE_DEFAULT 	  (_INA226_CONFIG_MODE_SBCONT)
#define INA226_CONFIG_MODE_POWERDOWN1  	(_INA226_CONFIG_MODE_POWERDOWN1 << 0)
#define INA226_CONFIG_MODE_SVTRIG	  	  (_INA226_CONFIG_MODE_SVTRIG << 0)
#define INA226_CONFIG_MODE_BVTRIG  		  (_INA226_CONFIG_MODE_BVTRIG << 0)
#define INA226_CONFIG_MODE_SBTRIG  		  (_INA226_CONFIG_MODE_SBTRIG << 0)
#define INA226_CONFIG_MODE_POWERDOWN2  	(_INA226_CONFIG_MODE_POWERDOWN2 << 0)
#define INA226_CONFIG_MODE_SVCONT  		  (_INA226_CONFIG_MODE_SVCONT << 0)
#define INA226_CONFIG_MODE_BVCONT  		  (_INA226_CONFIG_MODE_BVCONT << 0)
#define INA226_CONFIG_MODE_SBCONT  		  (_INA226_CONFIG_MODE_SBCONT << 0)
#define INA226_CONFIG_MODE_DEFAULT 		  (_INA226_CONFIG_MODE_DEFAULT << 0)
#define INA226_CONFIG_VSHCT				      (0x7UL << 3)
#define _INA226_CONFIG_VSHCT_SHIFT		  3
#define _INA226_CONFIG_VSHCT_MASK		    0x38UL
#define _INA226_CONFIG_VSHCT_140US		  0x0UL
#define _INA226_CONFIG_VSHCT_204US		  0x1UL
#define _INA226_CONFIG_VSHCT_332US		  0x2UL
#define _INA226_CONFIG_VSHCT_588US		  0x3UL
#define _INA226_CONFIG_VSHCT_1100US		  0x4UL
#define _INA226_CONFIG_VSHCT_2116US		  0x5UL
#define _INA226_CONFIG_VSHCT_4156US		  0x6UL
#define _INA226_CONFIG_VSHCT_8244US		  0x7UL
#define _INA226_CONFIG_VSHCT_DEFAULT	  (_INA226_CONFIG_VSHCT_2116US)
#define INA226_CONFIG_VSHCT_140US		    (_INA226_CONFIG_VSHCT_140US << 3)
#define INA226_CONFIG_VSHCT_204US		    (_INA226_CONFIG_VSHCT_204US << 3)
#define INA226_CONFIG_VSHCT_332US		    (_INA226_CONFIG_VSHCT_332US << 3)
#define INA226_CONFIG_VSHCT_588US		    (_INA226_CONFIG_VSHCT_588US << 3)
#define INA226_CONFIG_VSHCT_1100US		  (_INA226_CONFIG_VSHCT_1100US << 3)
#define INA226_CONFIG_VSHCT_2116US		  (_INA226_CONFIG_VSHCT_2116US << 3)
#define INA226_CONFIG_VSHCT_4156US		  (_INA226_CONFIG_VSHCT_4156US << 3)
#define INA226_CONFIG_VSHCT_8244US		  (_INA226_CONFIG_VSHCT_8244US << 3)
#define INA226_CONFIG_VSHCT_DEFAULT		  (_INA226_CONFIG_VSHCT_DEFAULT << 3)
#define INA226_CONFIG_VBUSCT 			      (0x7UL << 6)
#define _INA226_CONFIG_VBUSCT_SHIFT		  6
#define _INA226_CONFIG_VBUSCT_MASK		  0x700UL
#define _INA226_CONFIG_VBUSCT_140US		  0x0UL
#define _INA226_CONFIG_VBUSCT_204US		  0x1UL
#define _INA226_CONFIG_VBUSCT_332US		  0x2UL
#define _INA226_CONFIG_VBUSCT_588US		  0x3UL
#define _INA226_CONFIG_VBUSCT_1100US	  0x4UL
#define _INA226_CONFIG_VBUSCT_2116US	  0x5UL
#define _INA226_CONFIG_VBUSCT_4156US	  0x6UL
#define _INA226_CONFIG_VBUSCT_8244US	  0x7UL
#define _INA226_CONFIG_VBUSCT_DEFAULT	  (_INA226_CONFIG_VBUSCT_2116US)
#define INA226_CONFIG_VBUSCT_140US		  (_INA226_CONFIG_VBUSCT_140US << 6)
#define INA226_CONFIG_VBUSCT_204US		  (_INA226_CONFIG_VBUSCT_204US << 6)
#define INA226_CONFIG_VBUSCT_332US		  (_INA226_CONFIG_VBUSCT_332US << 6)
#define INA226_CONFIG_VBUSCT_588US		  (_INA226_CONFIG_VBUSCT_588US << 6)
#define INA226_CONFIG_VBUSCT_1100US		  (_INA226_CONFIG_VBUSCT_1100US << 6)
#define INA226_CONFIG_VBUSCT_2116US		  (_INA226_CONFIG_VBUSCT_2116US << 6)
#define INA226_CONFIG_VBUSCT_4156US		  (_INA226_CONFIG_VBUSCT_4156US << 6)
#define INA226_CONFIG_VBUSCT_8244US		  (_INA226_CONFIG_VBUSCT_8244US << 6)
#define INA226_CONFIG_VBUSCT_DEFAULT	  (_INA226_CONFIG_VBUSCT_DEFAULT << 6)
#define INA226_CONFIG_AVG    			      (0x7UL << 9)
#define _INA226_CONFIG_AVG_SHIFT		    9
#define _INA226_CONFIG_AVG_MASK			    0xE00UL
#define _INA226_CONFIG_AVG_1SAMPLE     	0x0UL
#define _INA226_CONFIG_AVG_4SAMPLE     	0x1UL
#define _INA226_CONFIG_AVG_16SAMPLE    	0x2UL
#define _INA226_CONFIG_AVG_64SAMPLES   	0x3UL
#define _INA226_CONFIG_AVG_128SAMPLES  	0x4UL
#define _INA226_CONFIG_AVG_256SAMPLES  	0x5UL
#define _INA226_CONFIG_AVG_512SAMPLES  	0x6UL
#define _INA226_CONFIG_AVG_1024SAMPLES 	0x7UL
#define _INA226_CONFIG_AVG_DEFAULT		  (_INA226_CONFIG_AVG_1SAMPLE)
#define INA226_CONFIG_AVG_1SAMPLE      	(_INA226_CONFIG_AVG_1SAMPLE << 9)
#define INA226_CONFIG_AVG_4SAMPLE      	(_INA226_CONFIG_AVG_4SAMPLE << 9)
#define INA226_CONFIG_AVG_16SAMPLE     	(_INA226_CONFIG_AVG_16SAMPLE << 9)
#define INA226_CONFIG_AVG_64SAMPLES    	(_INA226_CONFIG_AVG_64SAMPLES << 9)
#define INA226_CONFIG_AVG_128SAMPLES   	(_INA226_CONFIG_AVG_128SAMPLES << 9)
#define INA226_CONFIG_AVG_256SAMPLES   	(_INA226_CONFIG_AVG_256SAMPLES << 9)
#define INA226_CONFIG_AVG_512SAMPLES   	(_INA226_CONFIG_AVG_512SAMPLES << 9)
#define INA226_CONFIG_AVG_1024SAMPLES  	(_INA226_CONFIG_AVG_1024SAMPLES << 9)
#define INA226_CONFIG_AVG_DEFAULT		    (_INA226_CONFIG_AVG_DEFAULT << 9)
#define INA226_CONFIG_RST    			      (0x1UL << 15)
#define _INA226_CONFIG_RST_SHIFT		    15
#define _INA226_CONFIG_RST_MASK			    0x8000
#define INA226_MASKEN_LEN				        (0x1UL << 0)
#define _INA226_MASKEN_LEN_SHIFT		    0
#define _INA226_MASKEN_LEN_MASK			    0x1UL
#define _INA226_MASKEN_LEN_DEFAULT		  0x0UL
#define INA226_MASKEN_LEN_DEFAULT 		  (_INA226_MASKEN_LEN_DEFAULT << 0)
#define INA226_MASKEN_APOL				      (0x1UL << 1)
#define _INA226_MASKEN_APOL_SHIFT		    1
#define _INA226_MASKEN_APOL_MASK		    0x2UL
#define _INA226_MASKEN_APOL_DEFAULT		  0x0UL
#define INA226_MASKEN_APOL_DEFAULT 		  (_INA226_MASKEN_APOL_DEFAULT << 0)
#define INA226_MASKEN_OVF				        (0x1UL << 2)
#define _INA226_MASKEN_OVF_SHIFT		    2
#define _INA226_MASKEN_OVF_MASK			    0x4UL
#define _INA226_MASKEN_OVF_DEFAULT		  0x0UL
#define INA226_MASKEN_OVF_DEFAULT 		  (_INA226_MASKEN_OVF_DEFAULT << 0)
#define INA226_MASKEN_CVRF				      (0x1UL << 3)
#define _INA226_MASKEN_CVRF_SHIFT		    3
#define _INA226_MASKEN_CVRF_MASK		    0x8UL
#define _INA226_MASKEN_CVRF_DEFAULT		  0x0UL
#define INA226_MASKEN_CVRF_DEFAULT 		  (_INA226_MASKEN_CVRF_DEFAULT << 0)
#define INA226_MASKEN_AFF				        (0x1UL << 4)
#define _INA226_MASKEN_AFF_SHIFT		    4
#define _INA226_MASKEN_AFF_MASK			    0x20UL
#define _INA226_MASKEN_AFF_DEFAULT		  0x0UL
#define INA226_MASKEN_AFF_DEFAULT 		  (_INA226_MASKEN_AFF_DEFAULT << 0)
#define INA226_MASKEN_CNVR				      (0x1UL << 10)
#define _INA226_MASKEN_CNVR_SHIFT		    10
#define _INA226_MASKEN_CNVR_MASK		    0x400UL
#define _INA226_MASKEN_CNVR_DEFAULT		  0x0UL
#define INA226_MASKEN_CNVR_DEFAULT 		  (_INA226_MASKEN_CNVR_DEFAULT << 0)
#define INA226_MASKEN_POL				        (0x1UL << 11)
#define _INA226_MASKEN_POL_SHIFT		    11
#define _INA226_MASKEN_POL_MASK			    0x800UL
#define _INA226_MASKEN_POL_DEFAULT		  0x0UL
#define INA226_MASKEN_POL_DEFAULT 		  (_INA226_MASKEN_POL_DEFAULT << 0)
#define INA226_MASKEN_BUL				        (0x1UL << 12)
#define _INA226_MASKEN_BUL_SHIFT		    12
#define _INA226_MASKEN_BUL_MASK			    0x1000UL
#define _INA226_MASKEN_BUL_DEFAULT		  0x0UL
#define INA226_MASKEN_BUL_DEFAULT 		  (_INA226_MASKEN_BUL_DEFAULT << 0)
#define INA226_MASKEN_BOL				        (0x1UL << 13)
#define _INA226_MASKEN_BOL_SHIFT		    13
#define _INA226_MASKEN_BOL_MASK			    0x2000UL
#define _INA226_MASKEN_BOL_DEFAULT		  0x0UL
#define INA226_MASKEN_BOL_DEFAULT 		  (_INA226_MASKEN_BOL_DEFAULT << 0)
#define INA226_MASKEN_SUL				        (0x1UL << 14)
#define _INA226_MASKEN_SUL_SHIFT		    14
#define _INA226_MASKEN_SUL_MASK			    0x4000UL
#define _INA226_MASKEN_SUL_DEFAULT		  0x0UL
#define INA226_MASKEN_SUL_DEFAULT 		  (_INA226_MASKEN_SUL_DEFAULT << 0)
#define INA226_MASKEN_SOL				        (0x1UL << 15)
#define _INA226_MASKEN_SOL_SHIFT		    15
#define _INA226_MASKEN_SOL_MASK			    0x8000UL
#define _INA226_MASKEN_SOL_DEFAULT		  0x0UL
#define INA226_MASKEN_SOL_DEFAULT 		  (_INA226_MASKEN_SOL_DEFAULT << 0)

/** 
 *  @addtogroup INA226
 *  @{
 */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** @enum INA226_Address_TypeDef
*   @brief Alias names for INA226 I2C addresses in 8-bit format.
*/
typedef enum
{
  INA226_Addr40  =  0x40, /**< A1=GND	|	A0=GND	*/
  INA226_Addr41  =  0x41, /**< A1=GND	|	A0=VS	  */
  INA226_Addr42  =  0x42, /**< A1=GND	|	A0=SDA	*/
  INA226_Addr43  =  0x43, /**< A1=GND	|	A0=SCL	*/
  INA226_Addr44  =  0x44, /**< A1=VS	|	A0=GND	*/
  INA226_Addr45  =  0x45, /**< A1=VS	|	A0=VS	  */
  INA226_Addr46  =  0x46, /**< A1=VS	|	A0=SCA	*/
  INA226_Addr47  =  0x47, /**< A1=VS	|	A0=SCL	*/
  INA226_Addr48  =  0x48, /**< A1=SDA	|	A0=GND	*/
  INA226_Addr49  =  0x49, /**< A1=SDA	|	A0=VS	  */
  INA226_Addr4A  =  0x4A, /**< A1=SDA	|	A0=SDA	*/
  INA226_Addr4B  =  0x4B, /**< A1=SDA	|	A0=SCL	*/
  INA226_Addr4C  =  0x4C, /**< A1=SCL	|	A0=GND	*/
  INA226_Addr4D  =  0x4D, /**< A1=SCL	|	A0=VS	  */
  INA226_Addr4E  =  0x4E, /**< A1=SCL	|	A0=SDA	*/
  INA226_Addr4F  =  0x4F  /**< A1=SCL	|	A0=SCL	*/
} INA226_Address_TypeDef;


/** @enum INA226_Register_TypeDef
*   @brief Alias names for INA226 registers.
*/
typedef enum
{
  INA226_RegConfig 		=   0x00,  /**< Configuration register                  */
  INA226_RegShuntV 		=   0x01,  /**< Shunt voltage register (read-only)      */
  INA226_RegBusV 			= 	0x02,  /**< Bus voltage register (read-only)        */
  INA226_RegPower 	  = 	0x03,  /**< Power register (read-only)              */
  INA226_RegCurr 			= 	0x04,  /**< Current register (read-only)            */
  INA226_RegCalib 		= 	0x05,  /**< Calibration register                    */
  INA226_RegMaskEn 		= 	0x06,  /**< Mask/Enable register                    */
  INA226_RegAlertLim 	=   0x07,  /**< Alert limit register                    */
  INA226_RegManufID   =   0xFE,  /**< Manufacturer ID register                */
  INA226_RegDieID     =   0xFF   /**< Die ID register                         */
} INA226_Register_TypeDef;


/** @enum INA226_Mode_TypeDef
*   @brief Alias names for INA226 modes.
*/
typedef enum
{
  INA226_ModePowerDown 		=   0,/**< Power-down mode                          */
  INA226_ModeShuntTrig 		=   1,/**< Shunt voltage, triggered mode            */
  INA226_ModeBusTrig 		= 	2,  /**< Bus voltage, triggered mode              */
  INA226_ModeShuntBusTrig 	=	3,/**< Shunt and bus, triggered mode            */
  INA226_ModePowerDown2 	= 	4,/**< Power-down mode                          */
  INA226_ModeShuntCont 		= 	5,/**< Shunt voltage, continuous mode           */
  INA226_ModeBusCont 		= 	6,	/**< Bus voltage, continuous mode             */
  INA226_RegShuntBusTrig 	= 	7 /**< Shunt and bus, continuous mode (default) */
} INA226_Mode_TypeDef;


/** @enum INA226_BusCT_TypeDef
*   @brief Alias names for INA226 bus voltage conversion time options.
*/
typedef enum
{
  INA226_BusCT140us			=	0,
  INA226_BusCT204us			=	1,
  INA226_BusCT332us			=	2,
  INA226_BusCT588us			=	3,
  INA226_BusCT1100us		=	4, 	/**< (default) */
  INA226_BusCT2116us		=	5,
  INA226_BusCT4156us		=	6,
  INA226_BusCT8244us		=	7
} INA226_BusCT_TypeDef;


/** @enum INA226_ShuntCT_TypeDef
*   @brief Alias names for INA226 shunt voltage conversion time options
*/
typedef enum
{
  INA226_ShuntCT140us		=	0,
  INA226_ShuntCT204us		=	1,
  INA226_ShuntCT332us		=	2,
  INA226_ShuntCT588us		=	3,
  INA226_ShuntCT1100us		=	4, /**< (default) */
  INA226_ShuntCT2116us		=	5,
  INA226_ShuntCT4156us		=	6,
  INA226_ShuntCT8244us		=	7
} INA226_ShuntCT_TypeDef;


/** @enum INA226_AVG_TypeDef
*   @brief Alias names for INA226 to determine the number of samples that are 
*          collected and averaged.
*/
typedef enum
{
  INA226_AVG1				=	0, /**< (default) */
  INA226_AVG4				=	1,
  INA226_AVG16			=	2,
  INA226_AVG64			=	3,
  INA226_AVG128			=	4,
  INA226_AVG256			=	5,
  INA226_AVG512			=	6,
  INA226_AVG1024		=	7
} INA226_AVG_TypeDef;

/** @enum INA226_Err_TypeDef
*   @brief Alias names for INA226 errors.
*/

typedef enum
{
  INA226_Err_NoError   = 0U,                /**< No error*/
  INA226_Err_AL        = PORT_I2C_Err_AL,   /**< Arbitration lost*/
  INA226_Err_NACK      = PORT_I2C_Err_NACK  /**< No acknowledgment */
} INA226_Err_TypeDef;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

INA226_Err_TypeDef INA226_RegisterSet(PORT_I2C_Reg_TypeDef *i2c,
                         INA226_Address_TypeDef addr,
                         INA226_Register_TypeDef reg,
                         uint16_t val);

INA226_Err_TypeDef INA226_RegisterGet(PORT_I2C_Reg_TypeDef *i2c,
                         INA226_Address_TypeDef addr,
                         INA226_Register_TypeDef reg,
                         uint16_t *val);

INA226_Err_TypeDef INA226_ReadShuntVoltage(PORT_I2C_Reg_TypeDef *i2c,
                         INA226_Address_TypeDef addr,
                         int *val);

INA226_Err_TypeDef INA226_ReadBusVoltage(PORT_I2C_Reg_TypeDef *i2c,
                         INA226_Address_TypeDef addr,
                         int *val);

INA226_Err_TypeDef INA226_ReadPower(PORT_I2C_Reg_TypeDef *i2c,
                         INA226_Address_TypeDef addr,
                         int *val);

INA226_Err_TypeDef INA226_ReadCurr(PORT_I2C_Reg_TypeDef *i2c,
                         INA226_Address_TypeDef addr,
                         int *val);

int INA226_BusVoltageToUV(int val);

int INA226_ShuntVoltageToUA(int val, uint32_t senseResistor );

/**@}*/

#endif /* DRIVERS_INA226_H_ */
