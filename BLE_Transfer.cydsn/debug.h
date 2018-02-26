/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef _DEBUG_H_
#define _DEBUG_H_
    

#include<stdio.h> 
#include<stdarg.h> 
#include "string.h"
#include "UART_Dbg.h"

/** highly unstable don't use this **/
#ifdef __PRINT_F_RISKY
#define SK_PRINTF(format,args...)   sk_printf(format, ##args) 
#else
#define SK_PRINTF(format,args...)
#endif 

#define DBG_PRINTF(format,args...)  printf(format, ##args);
    
void sk_printf(char *,...);

void DebugCode(const char* txt); 

    
#endif 

/* [] END OF FILE */
