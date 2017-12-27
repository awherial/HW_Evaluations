/*****************************************************************************
*   @file        HumPro_900MHz.h
*   @Author      Firmware Team
*   @date        26 Dec 2017 -  05.51pm
*   @project
*   @module
*   @version     v1.0.0
*   @brief
*
*
*
*
*******************************************************************************
* Copyright (c) 2011, Ducere Technologies. All rights reserved.
* Unauthorised copying/redistribution and  its use in  source and binary forms,
* with or without modification, is not permitted. Proprietary and confidential.
*
* Attention:
*   All  information   contained  herein  is,  and   remains  the  property  of
*   Ducere     Technologies     Private     Limited,     Hyderabad,      India.
*   The intellectual and technical concepts contained herein are proprietary to
*   Ducere   Technologies  and  may  be  covered by patents in process, and are
*   protected   by   trade   secret   or   copyright law. Dissemination of this
*   information   or  reproduction  of  this material  is  strictly  forbidden.
******************************************************************************/


/********************* INTERFACE CHANGE LIST **********************************

	This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

===============================================================================
26 Dec 2017 -  05.51pm:
    By : ...
        Rev 1.0 : HumPro_900MHz.h file template created.
 -----------------------------------------------------------------------------

===============================================================================


===============================================================================
******************************************************************************/



/* Recursive include guard */
#ifndef 	HumPro_900MHz_h
	#define HumPro_900MHz_h


#ifdef __cplusplus
 extern "C" {
#endif


/******************************************************************************
* Includes
******************************************************************************/
/***
 * Standard C Library Includes ------------------------------------------------
***/
#include <stdint.h>

/***
 * Third Party Library Includes -----------------------------------------------
***/
/***
 * Project Library Includes ---------------------------------------------------
***/



/***
 * Exported define ------------------------------------------------------------
***/
#define HUMPRO_POWER_UP()           HAL_GPIO_WritePin(nPOWER_DOWN_GPIO_Port, nPOWER_DOWN_Pin, GPIO_PIN_SET)
#define HUMPRO_POWER_DOWN()         HAL_GPIO_WritePin(nPOWER_DOWN_GPIO_Port, nPOWER_DOWN_Pin, GPIO_PIN_RESET)

#define HUMPRO_CHIP_RESET()         HAL_GPIO_WritePin(Chip_nRESET_GPIO_Port, Chip_nRESET_Pin, GPIO_PIN_RESET)
#define HUMPRO_CHIP_unRESET()       HAL_GPIO_WritePin(Chip_nRESET_GPIO_Port, Chip_nRESET_Pin, GPIO_PIN_SET)

#define HIGH                        GPIO_PIN_SET
#define LOW                         GPIO_PIN_RESET
#define HUMPRO_nCOMMAND_LINE(x)     HAL_GPIO_WritePin(nCMD_GPIO_Port, nCMD_Pin, x)



/***
 * Exported types -------------------------------------------------------------
***/
/***
 * Exported enums -------------------------------------------------------------
***/
/***
 * Exported constants ---------------------------------------------------------
***/
/***
 * Exported Structures --------------------------------------------------------
***/
/***
 * Exported Unions ------------------------------------------------------------
***/
/***
 * Exported typedef -----------------------------------------------------------
***/
/***
 * Exported macros ------------------------------------------------------------
***/
/***
 * Exported Variables declaration ---------------------------------------------
***/
/***
 * Exported functions declaration ---------------------------------------------
***/
uint8_t   humpro_init       (void);
uint8_t   humpro_read_reg   (uint8_t  reg_addr, uint8_t  * received_bytes);
uint8_t   humpro_write_reg  (uint8_t  reg_addr, uint8_t  value);


/***
 * Exported Task declaration --------------------------------------------------
***/






#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end include guard	*/


//////////////////////////////// End of File //////////////////////////////////




//////////////////////////////// Scrach Area //////////////////////////////////
