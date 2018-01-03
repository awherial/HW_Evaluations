/*****************************************************************************
*   @file        cbuf.h
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


/********************* INTERFACE CHANGE LIST **********************************

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

===============================================================================
05 Apr 2017 - 11.33am:
By : ...
Rev 1.0 : cbuf.h file template created.
-----------------------------------------------------------------------------

===============================================================================


===============================================================================
******************************************************************************/



/* Recursive include guard */
#ifndef 	cbuf_h
#define cbuf_h


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
typedef enum {

    INSERT_AT_FRONT,
    INSERT_AT_BACK,
    OVERWRITE_AT_FRONT,
    OVERWRITE_AT_BACK,
    PULL_FROM_FRONT,
    PULL_FROM_BACK,

} ACCESS_TYPE_E;

/***
* Exported constants ---------------------------------------------------------
***/
/***
* Exported Structures --------------------------------------------------------
***/
typedef struct {

    uint16_t    head;
    uint16_t    tail;
    uint16_t    size;
    uint16_t    elements_count;
    uint16_t    element_size;
    char       *elements_p;

} cbuf_t;

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
void    cbuf_init  (cbuf_t *cbuf_p, uint16_t  element_size, uint16_t n_elements, char * buf_ptr);
uint8_t cbuf_put   (cbuf_t *cbuf_p, char * data_ptr, ACCESS_TYPE_E  type);
uint8_t cbuf_get   (cbuf_t *cbuf_p, char * data_ptr, ACCESS_TYPE_E  type);
uint8_t cbuf_full  (cbuf_t *cbuf_p);
uint8_t cbuf_empty (cbuf_t *cbuf_p);
void    cbuf_flush (cbuf_t *cbuf_p);





#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end include guard	*/


//////////////////////////////// End of File //////////////////////////////////




//////////////////////////////// Scrach Area //////////////////////////////////
