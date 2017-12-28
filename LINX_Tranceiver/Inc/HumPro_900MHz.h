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


#define HUMPRO_nCRESP()             HAL_GPIO_ReadPin(nCRESP_GPIO_Port, nCRESP_Pin)
#define HUMPRO_nCTS()               HAL_GPIO_ReadPin(nCTS_GPIO_Port,   nCTS_Pin)
#define HUMPRO_nCmdResponse()       (HUMPRO_nCRESP() == GPIO_PIN_RESET)
#define HUMPRO_nClearToSend()       (HUMPRO_nCTS()   == GPIO_PIN_RESET)



#define NILL                        (0xFF)  // inavlid address for both voltile and non-vol memories
#define IGNR                        (0xAA)  // ignore

// HumPRO Series Configuration Registers
/*

|-------------------|------------|-------------|--------|------------------|-------------------------------------------------------|
|        Name       |   NV Addr  |   Vol Addr  |   R/W  |   Default Value  |    Description                                        |
|-------------------|------------|-------------|--------|------------------|-------------------------------------------------------|
|   CRCERRS			|            |   0x40	   | R/W	|   0x00	       |    CRC Error Count                                    |
|   HOPTABLE		|   0x00	 |   0x4B	   | R/W	|   0x00	       |    Channel Hop Table                                  |
|   TXPWR			|	0x02	 |   0x4D	   | R/W	|   0x0A	       |    Transmit Power                                     |
|   UARTBAUD		|   0x03	 |   0x4E	   | R/W	|   0x01	       |    UART data rate                                     |
|   ADDMODE			|	0x04	 |   0x4F	   | R/W	|   0x04	       |    Addressing mode                                    |
|   DATATO			|	0x05	 |   0x50	   | R/W	|   0x10	       |    Data timeout                                       |
|   MAXTXRETRY		|   0x07	 |   0x52	   | R/W	|   0x1A	       |    Maximum Transmit Retries                           |
|   ENCRC			|	0x08	 |   0x53	   | R/W	|   0x01	       |    Enable CRC checking                                |
|   BCTRIG			|	0x09	 |   0x54	   | R/W	|   0x40	       |    Byte Count trigger                                 |
|   SHOWVER			|	0x0A 	 |	           | R/W	|   0x01	       |    Show version on startup                            |
|   ENCSMA			|	0x0B	 |   0x56	   | R/W	|   0x01	       |    Enable CSMA                                        |
|   IDLE			|	0x0D	 |   0x58	   | R/W	|   0x00	       |    Idle Mode                                          |
|   WAKEACK			|	0x0E	 |   0x59	   | R/W	|   0x01	       |    UART Acknowledge on Wake                           |
|   UDESTID3		|   0x0F	 |   0x5A	   | R/W	|   0xFF	       |    Destination Address for User Packet Type, extended |
|   UDESTID2		|   0x10	 |   0x5B	   | R/W	|   0xFF	       |    Destination Address for User Packet Type, extended |
|   UDESTID1		|   0x11	 |   0x5C	   | R/W	|   0xFF	       |    Destination Address for User Packet Type           |
|   UDESTID0		|   0x12	 |   0x5D	   | R/W	|   0xFF	       |    Destination Address for User Packet Type           |
|   USRCID3			|	0x13	 |   0x5E	   | R/W	|   0xFF	       |    Source Address for User Packet Type, extended      |
|   USRCID2			|	0x14	 |   0x5F	   | R/W	|   0xFF	       |    Source Address for User Packet Type, extended      |
|   USRCID1			|	0x15	 |   0x60	   | R/W	|   0xFF	       |    Source Address for User Packet Type                |
|   USRCID0			|	0x16	 |   0x61	   | R/W	|   0xFF	       |    Source Address for User Packet Type                |
|   UMASK3			|	0x17	 |   0x62	   | R/W	|   0xFF	       |    Address Mask for User Packet Type, extended        |
|   UMASK2			|	0x18	 |   0x63	   | R/W	|   0xFF	       |    Address Mask for User Packet Type, extended        |
|   UMASK1			|	0x19	 |   0x64	   | R/W	|   0xFF	       |    Address Mask for User Packet Type                  |
|   UMASK0			|	0x1A	 |   0x65	   | R/W	|   0xFF	       |    Address Mask for User Packet Type                  |
|   DESTDSN3		|	0x1D	 |	 0x68	   | R/W	|   0xFF	       |    Destination Device Serial Number                   |
|   DESTDSN2		|	0x1E	 |	 0x69	   | R/W	|   0xFF	       |    Destination Device Serial Number                   |
|   DESTDSN1		|	0x1F	 |	 0x6A	   | R/W	|   0xFF	       |    Destination Device Serial Number                   |
|   DESTDSN0		|	0x20	 |   0x6B	   | R/W	|   0xFF	       |    Destination Device Serial Number                   |
|   EXMASK			|   0x21	 |   0x6C	   | R/W	|   0x00	       |    Exception Mask to activate EX                      |
|   CMDHOLD			|   0x23	 |   0x6E	   | R/W	|   0x00	       |    Hold RF data when nCMD pin is low                  |
|   COMPAT			|   0x25	 |   0x70	   | R/W	|   0x02	       |    Compatibility                                      |
|   AUTOADDR		|   0x26	 |   0x71	   | R/W	|   0x00	       |    Automatic Reply Address                            |
|   MYDSN3			|   0x34	 |	           | R		|                  |    Factory programmed Serial Number                   |
|   MYDSN2			|   0x35	 |	           | R		|                  |    Factory programmed Serial Number                   |
|   MYDSN1			|   0x36	 |	           | R		|                  |    Factory programmed Serial Number                   |
|   MYDSN0			|   0x37	 |	           | R		|                  |    Factory programmed Serial Number                   |
|   CUSTID1			|   0x39	 |	           | R	    |   0xFF	       |    Factory programmed customer ID                     |
|   CUSTID0			|   0x3A	 |	           | R	    |   0xFF	       |    Factory programmed customer ID                     |
|   CRSSI			|   0x3F	 |	           | R/W	|                  |    Carrier Sense minimum RSSI                         |
|   RELEASE			|   0x78	 |	           | R	    |   0xBA	       |    Release number                                     |
|   EXCEPT			|	         |   0x79	   | R	    |   0x00	       |    Exception code                                     |
|   PRSSI			|	         |   0x7B	   | R	    |   0x00	       |    Packet RSSI                                        |
|   ARSSI			|	         |   0x7C	   | R	    |   0x00	       |    Ambient RSSI                                       |
|   FWVER3			|   0xC0	 |	           | R		|                  |    Firmware version, major                            |
|   FWVER2			|   0xC1	 |	           | R		|                  |    Firmware version, minor                            |
|   FWVER1			|   0xC2	 |	           | R		|                  |    Firmware version, increment                        |
|   FWVER0			|   0xC3	 |	           | R		|                  |    Firmware version, suffix                           |
|   NVCYCLE1		|	0xC4	 |	           | R		|                  |    NV Refresh Cycles, MS                              |
|   NVCYCLE0		|	0xC5	 |	           | R		|                  |    NV Refresh Cycles, LS                              |
|   LSTATUS			|	         |   0xC6	   | R		|                  |    Output line status                                 |
|   CMD				|            |   0xC7	   | W		|                  |    Command register                                   |
|   SECSTAT			|	         |   0xC9	   | R		|                  |    Security Status                                    |
|   JOINST			|	         |   0xCA	   | R	    |   0x00	       |    Join Status                                        |
|   EEXFLAG2		|		     |   0xCD	   | R/W	|   0x00	       |    Extended exception flags                           |
|   EEXFLAG1		|		     |   0xCE	   | R/W	|   0x00	       |    Extended exception flags                           |
|   EEXFLAG0		|		     |   0xCF	   | R/W	|   0x00	       |    Extended exception flags                           |
|   EEXMASK2		|	0x80	 |   0xD0	   | R/W	|   0x00	       |    Extended exception mask                            |
|   EEXMASK1		|	0x81	 |   0xD1	   | R/W	|   0x00	       |    Extended exception mask                            |
|   EEXMASK0		|	0x82	 |   0xD2	   | R/W	|   0x00	       |    Extended exception mask                            |
|   PKTOPT			|   0x83	 |   0xD3	   | R/W	|   0x00	       |    Packet options                                     |
|   SECOPT			|   0x84	 |   0xD4	   | R/W	|   0xFF	       |    Security Options                                   |
|   LASTNETAD[3]	|   0x8C	 |	           | R/W	|   0x00	       |    Last Network Address Assigned                      |
|   LASTNETAD[2]	|   0x8D	 |	           | R/W	|   0x00	       |    Last Network Address Assigned                      |
|   LASTNETAD[1]	|   0x8E	 |	           | R/W	|   0x00	       |    Last Network Address Assigned                      |
|   LASTNETAD[0]	|   0x8F	 |	           | R/W	|   0x00	       |    Last Network Address Assigned                      |
|-------------------|------------|-------------|--------|------------------|-------------------------------------------------------|

*/



/***
 * Exported types -------------------------------------------------------------
***/
/***
 * Exported enums -------------------------------------------------------------
***/
typedef enum HUMPRO_CONFIG_REG_NAMES  {

    FIRST_REGISTER,

    CRCERRS	    = FIRST_REGISTER ,
    HOPTABLE    ,
    TXPWR	    ,
    UARTBAUD    ,
    ADDMODE	    ,
    DATATO	    ,
    MAXTXRETRY  ,
    ENCRC	    ,
    BCTRIG	    ,
    SHOWVER	    ,
    ENCSMA	    ,
    IDLE	    ,
    WAKEACK	    ,
    UDESTID3    ,
    UDESTID2    ,
    UDESTID1    ,
    UDESTID0    ,
    USRCID3	    ,
    USRCID2	    ,
    USRCID1	    ,
    USRCID0	    ,
    UMASK3	    ,
    UMASK2	    ,
    UMASK1	    ,
    UMASK0	    ,
    DESTDSN3    ,
    DESTDSN2    ,
    DESTDSN1    ,
    DESTDSN0    ,
    EXMASK	    ,
    CMDHOLD	    ,
    COMPAT	    ,
    AUTOADDR    ,
    MYDSN3	    ,
    MYDSN2	    ,
    MYDSN1	    ,
    MYDSN0	    ,
    CUSTID1	    ,
    CUSTID0	    ,
    CRSSI	    ,
    RELEASE	    ,
    EXCEPT	    ,
    PRSSI	    ,
    ARSSI	    ,
    FWVER3	    ,
    FWVER2	    ,
    FWVER1	    ,
    FWVER0	    ,
    NVCYCLE1    ,
    NVCYCLE0    ,
    LSTATUS	    ,
    CMD		    ,
    SECSTAT	    ,
    JOINST	    ,
    EEXFLAG2    ,
    EEXFLAG1    ,
    EEXFLAG0    ,
    EEXMASK2    ,
    EEXMASK1    ,
    EEXMASK0    ,
    PKTOPT	    ,
    SECOPT	    ,
    LASTNETAD_3 ,
    LASTNETAD_2 ,
    LASTNETAD_1 ,
    LASTNETAD_0 ,

    LAST_REGISTER,

} HUMPRO_CONFIG_REG_NAMES_E;

typedef enum READ_WRITE_OPRN  {

    RO,
    WO,
    RW,

} READ_WRITE_OPRN_E;

typedef enum MEMORY_TYPE  {

    NON_VOL  = 0x01,
    VOLATILE = 0x80,

} MEMORY_TYPE_E;

typedef enum ERROR_TYPE  {

    HUM_PRO_SUCCESS,

    HUM_PRO_ACK             = 0x06,
    HUM_PRO_NACK            = 0x15,
    HUM_PRO_INVALID_REG_ID,
    HUM_PRO_INVALID_REG_ADDR,
    HUM_PRO_INVALID_READ_ACCESS,
    HUM_PRO_INVALID_WRITE_ACCESS,

} ERROR_TYPE_E;


/***
 * Exported constants ---------------------------------------------------------
***/
/***
 * Exported Structures --------------------------------------------------------
***/
typedef struct humpro_regs    {

//    const HUMPRO_CONFIG_REG_NAMES_E     reg_name;
    const uint8_t                       nvl_addr;
    const uint8_t                       vlt_addr;
    const READ_WRITE_OPRN_E             rd_write;
    const uint8_t                       def_value;
    uint8_t * const                     nvl_reg_p;
    uint8_t * const                     vlt_reg_p;
    const char                        * dscr_text;

} humpro_regs_t;



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
extern uint8_t              humpro_nvl_regs[];
extern uint8_t              humpro_vol_regs[];
extern const humpro_regs_t  hum_pro_regs[];

/***
 * Exported functions declaration ---------------------------------------------
***/
ERROR_TYPE_E    humpro_init               (void);
ERROR_TYPE_E    humpro_update_all_regs    (void);
void            humpro_print_regs         (MEMORY_TYPE_E mem);
void            humpro_print_version      (void);
void            humpro_print_addrsng_mode (void);
void            humpro_print_address      (void);
void            humpro_print_config       (void);
ERROR_TYPE_E    humpro_read_reg_id        (HUMPRO_CONFIG_REG_NAMES_E reg_id, MEMORY_TYPE_E  vol, uint8_t  * value_p);
ERROR_TYPE_E    humpro_write_reg_id       (HUMPRO_CONFIG_REG_NAMES_E reg_id, MEMORY_TYPE_E  mem, uint8_t      value);

uint8_t   humpro_read_reg_addr      (uint8_t  reg_addr, uint8_t  * const reg_ptr);
uint8_t   humpro_write_reg_addr     (uint8_t  reg_addr, uint8_t  value);


/***
 * Exported Task declaration --------------------------------------------------
***/






#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end include guard	*/


//////////////////////////////// End of File //////////////////////////////////




//////////////////////////////// Scrach Area //////////////////////////////////
