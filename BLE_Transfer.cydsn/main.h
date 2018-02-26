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
#ifndef _MAIN_H_
#define _MAIN_H_
/****************Compiler Flags Go Here *******************/
#define BLE_TEST
/**********************************************************/

/************* All include files put here ****************/    
#include "debug.h"
#include "pwr_set.h"
#include "debug.h"
#include "cytypes.h"
/*********************************************************/

/************* All defines put here **********************/
#define TRUE 0x1 
#define FALSE 0x0 

#define SET_DCDC_2_0V() pwr_set_Write(0x0)
#define SET_DCDC_2_8V() pwr_set_Write(0x1)
/*********************************************************/


/************** All function declerations here ***********/
CY_ISR_PROTO(WakeupIsrHandler); 
/*********************************************************/

#endif 

/* [] END OF FILE */
