/*******************************************************************************
* File Name: PWR_CTR2.c  
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
#include "PWR_CTR2.h"

static PWR_CTR2_BACKUP_STRUCT  PWR_CTR2_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PWR_CTR2_Sleep
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
*  \snippet PWR_CTR2_SUT.c usage_PWR_CTR2_Sleep_Wakeup
*******************************************************************************/
void PWR_CTR2_Sleep(void)
{
    #if defined(PWR_CTR2__PC)
        PWR_CTR2_backup.pcState = PWR_CTR2_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PWR_CTR2_backup.usbState = PWR_CTR2_CR1_REG;
            PWR_CTR2_USB_POWER_REG |= PWR_CTR2_USBIO_ENTER_SLEEP;
            PWR_CTR2_CR1_REG &= PWR_CTR2_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PWR_CTR2__SIO)
        PWR_CTR2_backup.sioState = PWR_CTR2_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PWR_CTR2_SIO_REG &= (uint32)(~PWR_CTR2_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PWR_CTR2_Wakeup
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
*  Refer to PWR_CTR2_Sleep() for an example usage.
*******************************************************************************/
void PWR_CTR2_Wakeup(void)
{
    #if defined(PWR_CTR2__PC)
        PWR_CTR2_PC = PWR_CTR2_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PWR_CTR2_USB_POWER_REG &= PWR_CTR2_USBIO_EXIT_SLEEP_PH1;
            PWR_CTR2_CR1_REG = PWR_CTR2_backup.usbState;
            PWR_CTR2_USB_POWER_REG &= PWR_CTR2_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PWR_CTR2__SIO)
        PWR_CTR2_SIO_REG = PWR_CTR2_backup.sioState;
    #endif
}


/* [] END OF FILE */
