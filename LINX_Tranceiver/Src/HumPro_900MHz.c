/******************************************************************************
*   @file        HumPro_900MHz.c
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



/*********************** SOURCE REVISION LOG **********************************
	This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

===============================================================================
 26 Dec 2017 -  05.51pm:
    By : ...
        Rev 1.0 : HumPro_900MHz.c file template created.
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
#include "HumPro_900MHz.h"
#include "usart.h"


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
void humpro_delay_ms (uint32_t     delay);


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
void humpro_delay_ms (uint32_t     delay)  {

    HAL_Delay (delay);

}



/* Public [Global] - Visible to all */

/***
 * Global Functions Defination ------------------------------------------------
***/


/*
    The general serial command format for the module is:
    [FF] [Length] [Command]
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
 * Example Usage:
 * @code
 *    example_nada(3); // Do nothing 3 times.
 * @endcode
*/
uint8_t   humpro_init       (void)   {

    uint8_t     dummy_byte[10];

    HUMPRO_POWER_DOWN   ();
    humpro_delay_ms     (10);
    HUMPRO_POWER_UP     ();
    humpro_delay_ms     (10);

    HUMPRO_CHIP_RESET   ();
    humpro_delay_ms     (10);
    HUMPRO_CHIP_unRESET ();
    humpro_delay_ms     (10);

    // remove / flush junk if any
    HAL_UART_Receive(&huart5, dummy_byte, 10, 300);

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
/*
Amplified HumPROTM Series Read From Configuration Register
Command :
    Header  Size    Escape    Address
    0xFF    0x02    0xFE       REG

Response :
    ACK     Address  Value
    0x06    REG       V

Command for an Address greater than 128 (0x80)
    Header  Size    Escape    Addr1     Addr2
    0xFF    0x03    0xFE      0xFE      REG-80

Response :
    ACK     Address  Value
    0x06    REG       V
*/
uint8_t   humpro_read_reg  (uint8_t  reg_addr, uint8_t  * received_bytes)  {

    // todo -- use sample code provided

    uint8_t     send_bytes[5];


    HUMPRO_nCOMMAND_LINE (LOW);

    // prepare command ..
    send_bytes[0] = 0xFF;
    send_bytes[1] = 0x02;   // size
    send_bytes[2] = 0xFE;   // escape sequence
    if (reg_addr > 0x80)    {
        send_bytes[1]++;        // modify the size
        send_bytes[3] = 0xFE;   // escape sequence
        send_bytes[4] = reg_addr - 0x80;    // reg address
    }
    else {
        send_bytes[3] = reg_addr;           // reg address
    }

    //HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
    HAL_UART_Transmit(&huart5, send_bytes, 2 + send_bytes[1], 1000);

    // receive response ..
        // wait @ 5 msecs for volatile R/W & 31.5 msecs fir non-volatile update

    //humpro_delay_ms (3);
    //HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
    HAL_UART_Receive(&huart5, received_bytes, 3, 1000);

    HUMPRO_nCOMMAND_LINE (HIGH);

    return  received_bytes[0];  // ACK / NACK from the received packet

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
/*
Amplified HumPROTM Series Write to Configuration Register Command
1. Register and Value less than 128 (0x80) :
    Header  Size      Address      Value
    0xFF    0x02       REG           V


2. Register less than 128 (0x80) and a Value greater than or equal to 128 (0x80) :
    Header  Size    Address    Escape       Value
    0xFF    0x03    REG         0xFE        V-0x80

3. Register greater than or equal to 128 (0x80) and a Value less than 128 (0x80):
    Header  Size    Escape     Address      Value
    0xFF    0x03     0xFE     REG-0x80        V

4. Register and Value greater than or equal to 128 (0x80):
    Header  Size    Escape     Address     Escape       Value
    0xFF    0x04     0xFE     REG-0x80      0xFE       V-0x80


Response:
The module responds with an ACK (0x06). If the ACK is not received, the command
should be resent. The module responds with a NACK (0x15) if a write is attempted
to a read-only or invalid register.

Example:
    to write 01 to register 0x83, send
    FF 03 FE 03 01
*/
uint8_t   humpro_write_reg  (uint8_t  reg_addr, uint8_t  value)  {

    // todo -- use sample code provided

    uint8_t     send_bytes[6];
    uint8_t     received_bytes[3];
    uint8_t     index;


    HUMPRO_nCOMMAND_LINE (LOW);

    // prepare command ..
    send_bytes[0] = 0xFF;
    send_bytes[1] = 0x02;   // size
    index = 1;
    if (reg_addr > 0x80)    {
        send_bytes[1]++;        // modify the size
        send_bytes[++index] = 0xFE;   // size
        send_bytes[++index] = reg_addr - 0x80;    // reg address
    }
    else {
        send_bytes[++index] = reg_addr;           // reg address
    }

    if (value > 0x80)    {
        send_bytes[1]++;        // modify the size
        send_bytes[++index] = 0xFE;   // size
        send_bytes[++index] = value - 0x80;    // reg address
    }
    else {
        send_bytes[++index] = value;           // reg address
    }



    //HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
    HAL_UART_Transmit(&huart5, send_bytes, 2 + send_bytes[1], 1000);

    humpro_delay_ms (3);

    // receive response ..
    //HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
    HAL_UART_Receive(&huart5, received_bytes, 1, 1000);

    HUMPRO_nCOMMAND_LINE (HIGH);


    return  received_bytes[0];  // ACK / NACK from the received packet


}


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
