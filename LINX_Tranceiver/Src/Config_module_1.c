/******************************************************************************
*   @file        Config_module_1.c
*   @Author      Firmware Team
*   @date        28 Dec 2017 - 05.15pm
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



/*********************** SOURCE REVISION LOG **********************************
	This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

===============================================================================
 28 Dec 2017 - 05.15pm:
    By : ...
        Rev 1.0 : Config_module_1.c file template created.
 ------------------------------------------------------------------------------

===============================================================================

===============================================================================
******************************************************************************/




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
#include "Config_module.h"


/***
 * External Function Declarations (external dependencies) ---------------------
***/
/***
 * External Variable Declarations (external dependencies) ---------------------
***/
/***
 * Global Variables Defination ------------------------------------------------
***/
uint8_t     USRCID [4] = {0xFF, 0xFF, 0xFF, 0x01};
uint8_t     UDESTID[4] = {0xFF, 0xFF, 0xFF, 0x02};

uint8_t     module_id[] = "M1";//"humpro-900:01";

/* Private [static] - File Specific */
/* Private Structures ---------------------------------------------------------
***/
/***
 * Private Unions -------------------------------------------------------------
***/
/***
 * Private typedefs -----------------------------------------------------------
***/
/***
 * Private defines ------------------------------------------------------------
***/
/***
 * Private macros -------------------------------------------------------------
***/
/***
 * Private Enums --------------------------------------------------------------
***/
/***
 * Private variables ----------------------------------------------------------
***/
/***
 * Private Functions Declaration ----------------------------------------------
***/



/***
 *  ISR Definations -----------------------------------------------------------
***/

/**
 * @name   ISR
 * @brief   interrupt service routine.
 * @ingroup interrupts
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 */


/* Private function Definations ---------------------------------------------*/
/**
 * @name    Private function
 * @brief   visible / called within this file..
 * @ingroup private / static
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 * Example Usage:
 * @code
 *    example_nada(3); // Do nothing 3 times.
 * @endcode
 */




/* Public [Global] - Visible to all */

/***
 * Global Functions Defination ------------------------------------------------
***/

/**
 * @name    Public function
 * @brief   visible / can be called in entire project from any file..
 * @ingroup Global / public
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 * Example Usage:
 * @code
 *    example_nada(3); // Do nothing 3 times.
 * @endcode
 */


/**
 * @name    Public function
 * @brief   visible / can be called in entire project from any file..
 * @ingroup Global / public
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 */



/***
 * Independent Task Definations -----------------------------------------------
***/

/**
 * @name    Independent Task
 * @brief   visible / can be called in entire project from any file..
 * @ingroup Global / public
 *
 * @param
 *
 * @retval TRUE   Successfully did nothing.
 * @retval FALSE  Oops, did something.
 *
 */






/**
 * @see Dio_Init
 *
 * <br><b> - HISTORY OF CHANGES - </b>
 *
 * <table align="left" style="width:800px">
 * <tr><td> Date       </td><td> Software Version </td><td> Initials </td><td> Description </td></tr>
 * <tr><td> 09/01/2015 </td><td> 0.5.0            </td><td> JWB      </td><td> Interface Created </td></tr>
 * </table><br><br>
 * <hr>
 */

//////////////////////////////// End of File //////////////////////////////////




//////////////////////////////// Scrach Area //////////////////////////////////
