/*******************************************************************************
* File Name: UART_Dbg.h
* Version 1.50
*
* Description:
*  This file provides constants and parameter values for the Software Transmit
*  UART Component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_SW_TX_UART_UART_Dbg_H
#define CY_SW_TX_UART_UART_Dbg_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

#define UART_Dbg_BAUD_RATE                      (115200u)
#define UART_Dbg_PIN_STATIC_MODE                (1u)


/***************************************
*        Function Prototypes
***************************************/
#if(UART_Dbg_PIN_STATIC_MODE == 1u)
    void UART_Dbg_Start(void) ;
#else
    void UART_Dbg_StartEx(uint8 port, uint8 pin) ;
#endif /* (UART_Dbg_PIN_STATIC_MODE == 1u) */

void UART_Dbg_Stop(void) ;
void UART_Dbg_PutChar(uint8 txDataByte) ;
void UART_Dbg_PutString(const char8 string[]) ;
void UART_Dbg_PutArray(const uint8 array[], uint32 byteCount) ;
void UART_Dbg_PutHexByte(uint8 txHexByte) ;
void UART_Dbg_PutHexInt(uint16 txHexInt) ;
void UART_Dbg_PutCRLF(void) ;

#endif /* CY_SW_TX_UART_UART_Dbg_H */


/* [] END OF FILE */
