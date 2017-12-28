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
uint8_t  nvl_shadow_regs[LAST_REGISTER];
uint8_t  vol_shadow_regs[LAST_REGISTER];

//    const HUMPRO_CONFIG_REG_NAMES_E     reg_name;
//    const uint8_t                       nvl_addr;
//    const uint8_t                       vlt_addr;
//    const READ_WRITE_OPRN_E             rd_write;
//    const uint8_t                       def_value;
//    const uint8_t                     * nvl_reg_p;
//    const uint8_t                     * vlt_reg_p;
//    const char                        * dscr_text;

//                        //  reg_name;   nvl_addr;  vlt_addr;  rd_write;  def_value;     * nvl_reg_p;                * vlt_reg_p;                * dscr_text;
//const humpro_regs_t   TEST = { /* CRCERRS */   NO_ADDR,    0x40,       RW,         0x00,   &nvl_shadow_regs[CRCERRS],   &vol_shadow_regs[CRCERRS],   "CRC Error Count"};
const humpro_regs_t   hum_pro_regs[LAST_REGISTER] = {
    //  reg_name:        nvl_addr;  vlt_addr;  rd_write;  def_value;     * nvl_reg_p;                        * vlt_reg_p;                * dscr_text;
    {/* CRCERRS	    */   NILL,      0x40,       RW,         0x00,   &nvl_shadow_regs[CRCERRS	 ],   &vol_shadow_regs[CRCERRS	  ],   "CRC Error Count"                                       },
    {/* HOPTABLE    */   0x00,      0x4B,       RW,         0x00,   &nvl_shadow_regs[HOPTABLE    ],   &vol_shadow_regs[HOPTABLE   ],   "Channel Hop Table"                                     },
    {/* TXPWR	    */   0x02,      0x4D,       RW,         0x0A,   &nvl_shadow_regs[TXPWR	     ],   &vol_shadow_regs[TXPWR	  ],   "Transmit Power"                                        },
    {/* UARTBAUD    */   0x03,      0x4E,       RW,         0x01,   &nvl_shadow_regs[UARTBAUD    ],   &vol_shadow_regs[UARTBAUD   ],   "UART data rate"                                        },
    {/* ADDMODE	    */   0x04,      0x4F,       RW,         0x04,   &nvl_shadow_regs[ADDMODE	 ],   &vol_shadow_regs[ADDMODE	  ],   "Addressing mode"                                       },
    {/* DATATO	    */   0x05,      0x50,       RW,         0x10,   &nvl_shadow_regs[DATATO	     ],   &vol_shadow_regs[DATATO	  ],   "Data timeout"                                          },
    {/* MAXTXRETRY  */   0x07,      0x52,       RW,         0x1A,   &nvl_shadow_regs[MAXTXRETRY  ],   &vol_shadow_regs[MAXTXRETRY ],   "Maximum Transmit Retries"                              },
    {/* ENCRC	    */   0x08,      0x53,       RW,         0x01,   &nvl_shadow_regs[ENCRC	     ],   &vol_shadow_regs[ENCRC	  ],   "Enable CRC checking"                                   },
    {/* BCTRIG	    */   0x09,      0x54,       RW,         0x40,   &nvl_shadow_regs[BCTRIG	     ],   &vol_shadow_regs[BCTRIG	  ],   "Byte Count trigger"                                    },
    {/* SHOWVER	    */   0x0A,      NILL,       RW,         0x01,   &nvl_shadow_regs[SHOWVER	 ],   &vol_shadow_regs[SHOWVER	  ],   "Show version on startup"                               },
    {/* ENCSMA	    */   0x0B,      0x56,       RW,         0x01,   &nvl_shadow_regs[ENCSMA	     ],   &vol_shadow_regs[ENCSMA	  ],   "Enable CSMA"                                           },
    {/* IDLE	    */   0x0D,      0x58,       RW,         0x00,   &nvl_shadow_regs[IDLE	     ],   &vol_shadow_regs[IDLE	      ],   "Idle Mode"                                             },
    {/* WAKEACK	    */   0x0E,      0x59,       RW,         0x01,   &nvl_shadow_regs[WAKEACK	 ],   &vol_shadow_regs[WAKEACK	  ],   "UART Acknowledge on Wake"                              },
    {/* UDESTID3    */   0x0F,      0x5A,       RW,         0xFF,   &nvl_shadow_regs[UDESTID3    ],   &vol_shadow_regs[UDESTID3   ],   "Destination Address for User Packet Type, extended"    },
    {/* UDESTID2    */   0x10,      0x5B,       RW,         0xFF,   &nvl_shadow_regs[UDESTID2    ],   &vol_shadow_regs[UDESTID2   ],   "Destination Address for User Packet Type, extended"    },
    {/* UDESTID1    */   0x11,      0x5C,       RW,         0xFF,   &nvl_shadow_regs[UDESTID1    ],   &vol_shadow_regs[UDESTID1   ],   "Destination Address for User Packet Type"              },
    {/* UDESTID0    */   0x12,      0x5D,       RW,         0xFF,   &nvl_shadow_regs[UDESTID0    ],   &vol_shadow_regs[UDESTID0   ],   "Destination Address for User Packet Type"              },
    {/* USRCID3	    */   0x13,      0x5E,       RW,         0xFF,   &nvl_shadow_regs[USRCID3	 ],   &vol_shadow_regs[USRCID3	  ],   "Source Address for User Packet Type, extended"         },
    {/* USRCID2	    */   0x14,      0x5F,       RW,         0xFF,   &nvl_shadow_regs[USRCID2	 ],   &vol_shadow_regs[USRCID2	  ],   "Source Address for User Packet Type, extended"         },
    {/* USRCID1	    */   0x15,      0x60,       RW,         0xFF,   &nvl_shadow_regs[USRCID1	 ],   &vol_shadow_regs[USRCID1	  ],   "Source Address for User Packet Type"                   },
    {/* USRCID0	    */   0x16,      0x61,       RW,         0xFF,   &nvl_shadow_regs[USRCID0	 ],   &vol_shadow_regs[USRCID0	  ],   "Source Address for User Packet Type"                   },
    {/* UMASK3	    */   0x17,      0x62,       RW,         0xFF,   &nvl_shadow_regs[UMASK3	     ],   &vol_shadow_regs[UMASK3	  ],   "Address Mask for User Packet Type, extended"           },
    {/* UMASK2	    */   0x18,      0x63,       RW,         0xFF,   &nvl_shadow_regs[UMASK2	     ],   &vol_shadow_regs[UMASK2	  ],   "Address Mask for User Packet Type, extended"           },
    {/* UMASK1	    */   0x19,      0x64,       RW,         0xFF,   &nvl_shadow_regs[UMASK1	     ],   &vol_shadow_regs[UMASK1	  ],   "Address Mask for User Packet Type"                     },
    {/* UMASK0	    */   0x1A,      0x65,       RW,         0xFF,   &nvl_shadow_regs[UMASK0	     ],   &vol_shadow_regs[UMASK0	  ],   "Address Mask for User Packet Type"                     },
    {/* DESTDSN3    */   0x1D,      0x68,       RW,         0xFF,   &nvl_shadow_regs[DESTDSN3    ],   &vol_shadow_regs[DESTDSN3   ],   "Destination Device Serial Number"                      },
    {/* DESTDSN2    */   0x1E,      0x69,       RW,         0xFF,   &nvl_shadow_regs[DESTDSN2    ],   &vol_shadow_regs[DESTDSN2   ],   "Destination Device Serial Number"                      },
    {/* DESTDSN1    */   0x1F,      0x6A,       RW,         0xFF,   &nvl_shadow_regs[DESTDSN1    ],   &vol_shadow_regs[DESTDSN1   ],   "Destination Device Serial Number"                      },
    {/* DESTDSN0    */   0x20,      0x6B,       RW,         0xFF,   &nvl_shadow_regs[DESTDSN0    ],   &vol_shadow_regs[DESTDSN0   ],   "Destination Device Serial Number"                      },
    {/* EXMASK	    */   0x21,      0x6C,       RW,         0x00,   &nvl_shadow_regs[EXMASK	     ],   &vol_shadow_regs[EXMASK	  ],   "Exception Mask to activate EX"                         },
    {/* CMDHOLD	    */   0x23,      0x6E,       RW,         0x00,   &nvl_shadow_regs[CMDHOLD	 ],   &vol_shadow_regs[CMDHOLD	  ],   "Hold RF data when nCMD pin is low"                     },
    {/* COMPAT	    */   0x25,      0x70,       RW,         0x02,   &nvl_shadow_regs[COMPAT	     ],   &vol_shadow_regs[COMPAT	  ],   "Compatibility"                                         },
    {/* AUTOADDR    */   0x26,      0x71,       RW,         0x00,   &nvl_shadow_regs[AUTOADDR    ],   &vol_shadow_regs[AUTOADDR   ],   "Automatic Reply Address"                               },
    {/* MYDSN3	    */   0x34,      NILL,       RO,         IGNR,   &nvl_shadow_regs[MYDSN3	     ],   &vol_shadow_regs[MYDSN3	  ],   "Factory programmed Serial Number"                      },
    {/* MYDSN2	    */   0x35,      NILL,       RO,         IGNR,   &nvl_shadow_regs[MYDSN2	     ],   &vol_shadow_regs[MYDSN2	  ],   "Factory programmed Serial Number"                      },
    {/* MYDSN1	    */   0x36,      NILL,       RO,         IGNR,   &nvl_shadow_regs[MYDSN1	     ],   &vol_shadow_regs[MYDSN1	  ],   "Factory programmed Serial Number"                      },
    {/* MYDSN0	    */   0x37,      NILL,       RO,         IGNR,   &nvl_shadow_regs[MYDSN0	     ],   &vol_shadow_regs[MYDSN0	  ],   "Factory programmed Serial Number"                      },
    {/* CUSTID1	    */   0x39,      NILL,       RO,         0xFF,   &nvl_shadow_regs[CUSTID1	 ],   &vol_shadow_regs[CUSTID1	  ],   "Factory programmed customer ID"                        },
    {/* CUSTID0	    */   0x3A,      NILL,       RO,         0xFF,   &nvl_shadow_regs[CUSTID0	 ],   &vol_shadow_regs[CUSTID0	  ],   "Factory programmed customer ID"                        },
    {/* CRSSI	    */   0x3F,      NILL,       RW,         IGNR,   &nvl_shadow_regs[CRSSI	     ],   &vol_shadow_regs[CRSSI	  ],   "Carrier Sense minimum RSSI"                            },
    {/* RELEASE	    */   0x78,      NILL,       RO,         0xBA,   &nvl_shadow_regs[RELEASE	 ],   &vol_shadow_regs[RELEASE	  ],   "Release number"                                        },
    {/* EXCEPT	    */   NILL,      0x79,       RO,         0x00,   &nvl_shadow_regs[EXCEPT	     ],   &vol_shadow_regs[EXCEPT	  ],   "Exception code"                                        },
    {/* PRSSI	    */   NILL,      0x7B,       RO,         0x00,   &nvl_shadow_regs[PRSSI	     ],   &vol_shadow_regs[PRSSI	  ],   "Packet RSSI"                                           },
    {/* ARSSI	    */   NILL,      0x7C,       RO,         0x00,   &nvl_shadow_regs[ARSSI	     ],   &vol_shadow_regs[ARSSI	  ],   "Ambient RSSI"                                          },
    {/* FWVER3	    */   0xC0,      NILL,       RO,         IGNR,   &nvl_shadow_regs[FWVER3	     ],   &vol_shadow_regs[FWVER3	  ],   "Firmware version, major"                               },
    {/* FWVER2	    */   0xC1,      NILL,       RO,         IGNR,   &nvl_shadow_regs[FWVER2	     ],   &vol_shadow_regs[FWVER2	  ],   "Firmware version, minor"                               },
    {/* FWVER1	    */   0xC2,      NILL,       RO,         IGNR,   &nvl_shadow_regs[FWVER1	     ],   &vol_shadow_regs[FWVER1	  ],   "Firmware version, increment"                           },
    {/* FWVER0	    */   0xC3,      NILL,       RO,         IGNR,   &nvl_shadow_regs[FWVER0	     ],   &vol_shadow_regs[FWVER0	  ],   "Firmware version, suffix"                              },
    {/* NVCYCLE1    */   0xC4,      NILL,       RO,         IGNR,   &nvl_shadow_regs[NVCYCLE1    ],   &vol_shadow_regs[NVCYCLE1   ],   "NV Refresh Cycles, MS"                                 },
    {/* NVCYCLE0    */   0xC5,      NILL,       RO,         IGNR,   &nvl_shadow_regs[NVCYCLE0    ],   &vol_shadow_regs[NVCYCLE0   ],   "NV Refresh Cycles, LS"                                 },
    {/* LSTATUS	    */   NILL,      0xC6,       RO,         IGNR,   &nvl_shadow_regs[LSTATUS	 ],   &vol_shadow_regs[LSTATUS	  ],   "Output line status"                                    },
    {/* CMD		    */   NILL,      0xC7,       WO,         IGNR,   &nvl_shadow_regs[CMD		 ],   &vol_shadow_regs[CMD		  ],   "Command register"                                      },
    {/* SECSTAT	    */   NILL,      0xC9,       RO,         IGNR,   &nvl_shadow_regs[SECSTAT	 ],   &vol_shadow_regs[SECSTAT	  ],   "Security Status"                                       },
    {/* JOINST	    */   NILL,      0xCA,       RO,         0x00,   &nvl_shadow_regs[JOINST	     ],   &vol_shadow_regs[JOINST	  ],   "Join Status"                                           },
    {/* EEXFLAG2    */   NILL,      0xCD,       RW,         0x00,   &nvl_shadow_regs[EEXFLAG2    ],   &vol_shadow_regs[EEXFLAG2   ],   "Extended exception flags"                              },
    {/* EEXFLAG1    */   NILL,      0xCE,       RW,         0x00,   &nvl_shadow_regs[EEXFLAG1    ],   &vol_shadow_regs[EEXFLAG1   ],   "Extended exception flags"                              },
    {/* EEXFLAG0    */   NILL,      0xCF,       RW,         0x00,   &nvl_shadow_regs[EEXFLAG0    ],   &vol_shadow_regs[EEXFLAG0   ],   "Extended exception flags"                              },
    {/* EEXMASK2    */   0x80,      0xD0,       RW,         0x00,   &nvl_shadow_regs[EEXMASK2    ],   &vol_shadow_regs[EEXMASK2   ],   "Extended exception mask"                               },
    {/* EEXMASK1    */   0x81,      0xD1,       RW,         0x00,   &nvl_shadow_regs[EEXMASK1    ],   &vol_shadow_regs[EEXMASK1   ],   "Extended exception mask"                               },
    {/* EEXMASK0    */   0x82,      0xD2,       RW,         0x00,   &nvl_shadow_regs[EEXMASK0    ],   &vol_shadow_regs[EEXMASK0   ],   "Extended exception mask"                               },
    {/* PKTOPT	    */   0x83,      0xD3,       RW,         0x00,   &nvl_shadow_regs[PKTOPT      ],   &vol_shadow_regs[PKTOPT     ],   "Packet options"                                        },
    {/* SECOPT	    */   0x84,      0xD4,       RW,         0xFF,   &nvl_shadow_regs[SECOPT	     ],   &vol_shadow_regs[SECOPT	  ],   "Security Options"                                      },
    {/* LASTNETAD_3 */   0x8C,      NILL,       RW,         0x00,   &nvl_shadow_regs[LASTNETAD_3 ],   &vol_shadow_regs[LASTNETAD_3],   "Last Network Address Assigned"                         },
    {/* LASTNETAD_2 */   0x8D,      NILL,       RW,         0x00,   &nvl_shadow_regs[LASTNETAD_2 ],   &vol_shadow_regs[LASTNETAD_2],   "Last Network Address Assigned"                         },
    {/* LASTNETAD_1 */   0x8E,      NILL,       RW,         0x00,   &nvl_shadow_regs[LASTNETAD_1 ],   &vol_shadow_regs[LASTNETAD_1],   "Last Network Address Assigned"                         },
    {/* LASTNETAD_0 */   0x8F,      NILL,       RW,         0x00,   &nvl_shadow_regs[LASTNETAD_0 ],   &vol_shadow_regs[LASTNETAD_0],   "Last Network Address Assigned"                         },

};

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
void humpro_delay_ms        (uint32_t            delay);
void flush_uart_rcv_channel (UART_HandleTypeDef *huart);

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
void flush_uart_rcv_channel (UART_HandleTypeDef *huart)     {

    uint8_t     dummy_bytes[10];

    //HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
    HAL_UART_Receive(&huart5, dummy_bytes, 10, 100);

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
ERROR_TYPE_E   humpro_init       (void)   {

    uint8_t     dummy_byte[10];

    //uint32_t    *temp_ptr = (uint32_t*)hum_pro_regs;

    HUMPRO_POWER_DOWN   ();
    humpro_delay_ms     (10);
    HUMPRO_POWER_UP     ();
    humpro_delay_ms     (10);

    HUMPRO_CHIP_RESET   ();
    humpro_delay_ms     (1);
    HUMPRO_CHIP_unRESET ();
    humpro_delay_ms     (30);

    HUMPRO_CHIP_RESET   ();
    humpro_delay_ms     (1);
    HUMPRO_CHIP_unRESET ();
    humpro_delay_ms     (30);

    HUMPRO_CHIP_RESET   ();
    humpro_delay_ms     (1);
    HUMPRO_CHIP_unRESET ();
    humpro_delay_ms     (30);

    // remove / flush junk if any
    HAL_UART_Receive(&huart5, dummy_byte, 10, 300);

    return  HUM_PRO_SUCCESS;
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
ERROR_TYPE_E   humpro_update_all_regs (void)   {

    HUMPRO_CONFIG_REG_NAMES_E     regs;
    const humpro_regs_t         * rec_p;

    regs  = FIRST_REGISTER;
    rec_p = hum_pro_regs;
    while (regs < LAST_REGISTER)
    {
        if (rec_p->rd_write != WO) {
            if (rec_p->nvl_addr != NILL)    {
                humpro_read_reg_addr (rec_p->nvl_addr, rec_p->nvl_reg_p);
            }
            if (rec_p->vlt_addr != NILL)    {
                humpro_read_reg_addr (rec_p->vlt_addr, rec_p->vlt_reg_p);
            }
        }
        else    {
             // write only registers
                // nop
        }
        rec_p++;
        regs++;
    }

    return  HUM_PRO_SUCCESS;
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
ERROR_TYPE_E   humpro_read_reg_id (HUMPRO_CONFIG_REG_NAMES_E reg_id, MEMORY_TYPE_E  mem, uint8_t  * value_p)   {

    const humpro_regs_t   * rec_p;
    ERROR_TYPE_E            result = HUM_PRO_SUCCESS;
    uint8_t                 reg_addr;
    uint8_t               * register_p;


    rec_p = hum_pro_regs;

    // validate reg-id
    if (reg_id >= LAST_REGISTER)   {
        return HUM_PRO_INVALID_REG_ID;    // error in valid reg-id
    }

    // validate reg-address
    if (mem == VOLATILE)    {   // volatile?
        reg_addr   = rec_p[reg_id].vlt_addr;
        register_p = rec_p[reg_id].vlt_reg_p;
    }
    else {  // non-volatile
        reg_addr   = rec_p[reg_id].nvl_addr;
        register_p = rec_p[reg_id].nvl_reg_p;
    }
    if (reg_addr == NILL) {
        return HUM_PRO_INVALID_REG_ADDR;    // error invalid reg-address
    }

    // validate read / write access..
    if (rec_p[reg_id].rd_write == WO)    {  // write only?
        return HUM_PRO_INVALID_READ_ACCESS;         // invalid read access
    }

    result = (ERROR_TYPE_E)humpro_read_reg_addr (reg_addr, value_p);

    if (result == HUM_PRO_ACK)  {
        *register_p = *value_p;     // updating shadow register
    }

    return  result;
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
ERROR_TYPE_E   humpro_write_reg_id (HUMPRO_CONFIG_REG_NAMES_E reg_id, MEMORY_TYPE_E  mem, uint8_t  value)   {

    const humpro_regs_t   * rec_p;
    ERROR_TYPE_E            result = HUM_PRO_SUCCESS;
    uint8_t                 vol_reg_addr   = NILL;
    //uint8_t               * vol_register_p = NILL;
    uint8_t                 nvl_reg_addr   = NILL;
    //uint8_t               * nvl_register_p = NILL;


    rec_p = hum_pro_regs;

    // validate reg-id
    if (reg_id >= LAST_REGISTER)   {
        return HUM_PRO_INVALID_REG_ID;    // error in valid reg-id
    }

    // validate reg-address
    if (mem & VOLATILE)    {   // volatile?
        vol_reg_addr   = rec_p[reg_id].vlt_addr;
        //vol_register_p = rec_p[reg_id].vlt_reg_p;
    }
    if(mem & NON_VOL) {  // non-volatile
        nvl_reg_addr   = rec_p[reg_id].nvl_addr;
        //nvl_register_p = rec_p[reg_id].nvl_reg_p;
    }
    if (vol_reg_addr == NILL  &&  nvl_reg_addr == NILL) {
        return HUM_PRO_INVALID_REG_ADDR;    // error invalid reg-address
    }

    // validate read / write access..
    if (rec_p[reg_id].rd_write == RO)    {  // read only?
        return HUM_PRO_INVALID_WRITE_ACCESS;         // invalid write access
    }


    if (vol_reg_addr != NILL)   {
        result |= (ERROR_TYPE_E)humpro_write_reg_addr (vol_reg_addr, value);
        // no shadow reg-update
    }
    if (nvl_reg_addr != NILL)   {
        result |= (ERROR_TYPE_E)humpro_write_reg_addr (nvl_reg_addr, value);
        // no shadow reg-update
    }


      // no shadow reg-update for write operations, unless read-back and verified from the device
//    if (result == HUM_PRO_ACK)  {
//        *register_p = *reg_value;    // updating shadow register
//    }

    return  result;
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
uint8_t     test_counter1, test_counter2;

uint8_t   humpro_read_reg_addr  (uint8_t  reg_addr, uint8_t  * const reg_ptr)  {

    // todo -- use sample code logic provided

    uint8_t     send_bytes[5];
    uint8_t     received_bytes[5];


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


    // wait till module is free to accept data
    while (!HUMPRO_nClearToSend())          // keep waiting as module is busy
        test_counter1++;

    //HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
    HAL_UART_Transmit(&huart5, send_bytes, 2 + send_bytes[1], 1000);

    // receive response ..
        // wait @ 5 msecs for volatile R/W & 31.5 msecs for non-volatile update
    while (!HUMPRO_nCmdResponse())          // keep waiting as module is busy
        test_counter2++;

    //humpro_delay_ms (3);
    //HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
    HAL_UART_Receive(&huart5, received_bytes, 3, 1000);

    if ( (received_bytes[0] == 0x06)  &&  (received_bytes[1] == reg_addr))  {   // ACK ?  && Address ?
        *reg_ptr = received_bytes[2];
    }
    else {
        // nop
    }

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

uint8_t     test_counter3, test_counter4;

uint8_t   humpro_write_reg_addr  (uint8_t  reg_addr, uint8_t  reg_value)  {

    // todo -- use sample code logic provided

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

    if (reg_value > 0x80)    {
        send_bytes[1]++;        // modify the size
        send_bytes[++index] = 0xFE;   // size
        send_bytes[++index] = reg_value - 0x80;    // reg address
    }
    else {
        send_bytes[++index] = reg_value;           // reg address
    }


    // wait till module is free to accept data
    while (!HUMPRO_nClearToSend())          // keep waiting as module is busy
        test_counter3++;

    flush_uart_rcv_channel (&huart5);

    //HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
    HAL_UART_Transmit(&huart5, send_bytes, 2 + send_bytes[1], 1000);

    //humpro_delay_ms (3);

    // receive response ..
    while (!HUMPRO_nCmdResponse())          // keep waiting as module is busy
        test_counter4++;
    //HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
    HAL_UART_Receive(&huart5, received_bytes, 1, 1000);

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
