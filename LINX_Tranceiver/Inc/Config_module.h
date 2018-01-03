/*****************************************************************************
*   @file        Config_module.h
*   @Author      Firmware Team
*   @date        28 Dec 2017 - 05.53pm
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
28 Dec 2017 - 05.53pm:
    By : ...
        Rev 1.0 : Config_module.h file template created.
 -----------------------------------------------------------------------------

===============================================================================


===============================================================================
******************************************************************************/



/* Recursive include guard */
#ifndef 	Config_module_h
	#define Config_module_h


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
extern uint8_t     USRCID [4];
extern uint8_t     UDESTID[4];

extern uint8_t     module_id[];

/***
 * Exported functions declaration ---------------------------------------------
***/

/***
 * Exported Task declaration --------------------------------------------------
***/






#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end include guard	*/


//////////////////////////////// End of File //////////////////////////////////




//////////////////////////////// Scrach Area //////////////////////////////////
