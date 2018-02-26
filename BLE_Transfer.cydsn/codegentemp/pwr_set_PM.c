/*******************************************************************************
* File Name: pwr_set.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "pwr_set.h"

static pwr_set_BACKUP_STRUCT  pwr_set_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: pwr_set_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet pwr_set_SUT.c usage_pwr_set_Sleep_Wakeup
*******************************************************************************/
void pwr_set_Sleep(void)
{
    #if defined(pwr_set__PC)
        pwr_set_backup.pcState = pwr_set_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            pwr_set_backup.usbState = pwr_set_CR1_REG;
            pwr_set_USB_POWER_REG |= pwr_set_USBIO_ENTER_SLEEP;
            pwr_set_CR1_REG &= pwr_set_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(pwr_set__SIO)
        pwr_set_backup.sioState = pwr_set_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        pwr_set_SIO_REG &= (uint32)(~pwr_set_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: pwr_set_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to pwr_set_Sleep() for an example usage.
*******************************************************************************/
void pwr_set_Wakeup(void)
{
    #if defined(pwr_set__PC)
        pwr_set_PC = pwr_set_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            pwr_set_USB_POWER_REG &= pwr_set_USBIO_EXIT_SLEEP_PH1;
            pwr_set_CR1_REG = pwr_set_backup.usbState;
            pwr_set_USB_POWER_REG &= pwr_set_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(pwr_set__SIO)
        pwr_set_SIO_REG = pwr_set_backup.sioState;
    #endif
}


/* [] END OF FILE */
