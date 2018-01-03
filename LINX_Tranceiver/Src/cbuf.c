/******************************************************************************
*   @file        cbuf.c
*   @Author      Firmware Team
*   @date        05 Apr 2017 - 11.33am
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
05 Apr 2017 - 11.33am:
By : ...
Rev 1.0 : cbuf.c file template created.
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
#include <string.h>

/***
* Third Party Library Includes -----------------------------------------------
***/
/***
* Project Library Includes ---------------------------------------------------
***/
#include "cbuf.h"


/***
* External Function Declarations (external dependencies) ---------------------
***/
/***
* External Variable Declarations (external dependencies) ---------------------
***/
/***
* Global Variables Defination ------------------------------------------------
***/

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
void cbuf_init (cbuf_t *cbuf_p, uint16_t  element_size, uint16_t n_elements, char * buf_ptr)    {

    cbuf_p->elements_p    = buf_ptr;
    cbuf_p->element_size  = element_size;
    cbuf_p->size          = n_elements;
    cbuf_p->elements_count = 0;
    cbuf_p->head = 0;
    cbuf_p->tail = 0;

}


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
uint8_t cbuf_put   (cbuf_t *cbuf_p, char * data_ptr, ACCESS_TYPE_E  type)   {

    if (cbuf_full (cbuf_p)) {
        if (type == INSERT_AT_FRONT || type == INSERT_AT_BACK)
            return  0;
    }
    else {
        if (type == OVERWRITE_AT_FRONT)
            type = INSERT_AT_FRONT;
        else if (type == OVERWRITE_AT_BACK)
            type = INSERT_AT_BACK;
    }

    switch (type)
    {
        case INSERT_AT_FRONT:
        memcpy (cbuf_p->elements_p + (cbuf_p->head * cbuf_p->element_size), data_ptr, cbuf_p->element_size);
        cbuf_p->head++;
        if (cbuf_p->head >= cbuf_p->size)    {
            cbuf_p->head = 0;
        }
        cbuf_p->elements_count++;
        break;
        case OVERWRITE_AT_FRONT:
        memcpy (cbuf_p->elements_p + (cbuf_p->head * cbuf_p->element_size), data_ptr, cbuf_p->element_size);
        break;
        case INSERT_AT_BACK :
        memcpy (cbuf_p->elements_p + (cbuf_p->tail * cbuf_p->element_size), data_ptr, cbuf_p->element_size);
        cbuf_p->tail++;
        if (cbuf_p->tail >= cbuf_p->size)    {
            cbuf_p->tail = 0;
        }
        cbuf_p->elements_count++;
        break;
        case OVERWRITE_AT_BACK:
        memcpy (cbuf_p->elements_p + (cbuf_p->tail * cbuf_p->element_size), data_ptr, cbuf_p->element_size);
        break;
    }

    return  1;

}


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
uint8_t cbuf_get   (cbuf_t *cbuf_p, char * data_ptr, ACCESS_TYPE_E  type)   {

    if (cbuf_empty (cbuf_p)) {
        return  0;
    }

    switch (type)
    {
        case PULL_FROM_FRONT:
        if (cbuf_p->head)
            cbuf_p->head--;
        else
            cbuf_p->head = cbuf_p->size - 1;
        memcpy (data_ptr, cbuf_p->elements_p + (cbuf_p->head * cbuf_p->element_size), cbuf_p->element_size);
        cbuf_p->elements_count--;
        break;
        case PULL_FROM_BACK :
        if (cbuf_p->tail)
            cbuf_p->tail--;
        else
            cbuf_p->tail = cbuf_p->size - 1;
        memcpy (data_ptr, cbuf_p->elements_p + (cbuf_p->tail * cbuf_p->element_size), cbuf_p->element_size);
        cbuf_p->elements_count--;
        break;
    }

    return  1;

}

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
uint8_t cbuf_full  (cbuf_t *cbuf_p) {

    if (cbuf_p->elements_count >= cbuf_p->size)
        return  1;
    // else
    return  0;

}

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
uint8_t cbuf_empty (cbuf_t *cbuf_p) {

    if (cbuf_p->elements_count == 0)
        return  1;
    // else
    return  0;

}


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
void    cbuf_flush (cbuf_t *cbuf_p) {

    cbuf_p->elements_count = 0;
    cbuf_p->head = 0;
    cbuf_p->tail = 0;

}



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
