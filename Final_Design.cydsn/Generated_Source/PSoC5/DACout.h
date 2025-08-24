/*******************************************************************************
* File Name: DACout.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DACout_H) /* Pins DACout_H */
#define CY_PINS_DACout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DACout_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DACout__PORT == 15 && ((DACout__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DACout_Write(uint8 value);
void    DACout_SetDriveMode(uint8 mode);
uint8   DACout_ReadDataReg(void);
uint8   DACout_Read(void);
void    DACout_SetInterruptMode(uint16 position, uint16 mode);
uint8   DACout_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DACout_SetDriveMode() function.
     *  @{
     */
        #define DACout_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DACout_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DACout_DM_RES_UP          PIN_DM_RES_UP
        #define DACout_DM_RES_DWN         PIN_DM_RES_DWN
        #define DACout_DM_OD_LO           PIN_DM_OD_LO
        #define DACout_DM_OD_HI           PIN_DM_OD_HI
        #define DACout_DM_STRONG          PIN_DM_STRONG
        #define DACout_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DACout_MASK               DACout__MASK
#define DACout_SHIFT              DACout__SHIFT
#define DACout_WIDTH              1u

/* Interrupt constants */
#if defined(DACout__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DACout_SetInterruptMode() function.
     *  @{
     */
        #define DACout_INTR_NONE      (uint16)(0x0000u)
        #define DACout_INTR_RISING    (uint16)(0x0001u)
        #define DACout_INTR_FALLING   (uint16)(0x0002u)
        #define DACout_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DACout_INTR_MASK      (0x01u) 
#endif /* (DACout__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DACout_PS                     (* (reg8 *) DACout__PS)
/* Data Register */
#define DACout_DR                     (* (reg8 *) DACout__DR)
/* Port Number */
#define DACout_PRT_NUM                (* (reg8 *) DACout__PRT) 
/* Connect to Analog Globals */                                                  
#define DACout_AG                     (* (reg8 *) DACout__AG)                       
/* Analog MUX bux enable */
#define DACout_AMUX                   (* (reg8 *) DACout__AMUX) 
/* Bidirectional Enable */                                                        
#define DACout_BIE                    (* (reg8 *) DACout__BIE)
/* Bit-mask for Aliased Register Access */
#define DACout_BIT_MASK               (* (reg8 *) DACout__BIT_MASK)
/* Bypass Enable */
#define DACout_BYP                    (* (reg8 *) DACout__BYP)
/* Port wide control signals */                                                   
#define DACout_CTL                    (* (reg8 *) DACout__CTL)
/* Drive Modes */
#define DACout_DM0                    (* (reg8 *) DACout__DM0) 
#define DACout_DM1                    (* (reg8 *) DACout__DM1)
#define DACout_DM2                    (* (reg8 *) DACout__DM2) 
/* Input Buffer Disable Override */
#define DACout_INP_DIS                (* (reg8 *) DACout__INP_DIS)
/* LCD Common or Segment Drive */
#define DACout_LCD_COM_SEG            (* (reg8 *) DACout__LCD_COM_SEG)
/* Enable Segment LCD */
#define DACout_LCD_EN                 (* (reg8 *) DACout__LCD_EN)
/* Slew Rate Control */
#define DACout_SLW                    (* (reg8 *) DACout__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DACout_PRTDSI__CAPS_SEL       (* (reg8 *) DACout__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DACout_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DACout__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DACout_PRTDSI__OE_SEL0        (* (reg8 *) DACout__PRTDSI__OE_SEL0) 
#define DACout_PRTDSI__OE_SEL1        (* (reg8 *) DACout__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DACout_PRTDSI__OUT_SEL0       (* (reg8 *) DACout__PRTDSI__OUT_SEL0) 
#define DACout_PRTDSI__OUT_SEL1       (* (reg8 *) DACout__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DACout_PRTDSI__SYNC_OUT       (* (reg8 *) DACout__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DACout__SIO_CFG)
    #define DACout_SIO_HYST_EN        (* (reg8 *) DACout__SIO_HYST_EN)
    #define DACout_SIO_REG_HIFREQ     (* (reg8 *) DACout__SIO_REG_HIFREQ)
    #define DACout_SIO_CFG            (* (reg8 *) DACout__SIO_CFG)
    #define DACout_SIO_DIFF           (* (reg8 *) DACout__SIO_DIFF)
#endif /* (DACout__SIO_CFG) */

/* Interrupt Registers */
#if defined(DACout__INTSTAT)
    #define DACout_INTSTAT            (* (reg8 *) DACout__INTSTAT)
    #define DACout_SNAP               (* (reg8 *) DACout__SNAP)
    
	#define DACout_0_INTTYPE_REG 		(* (reg8 *) DACout__0__INTTYPE)
#endif /* (DACout__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DACout_H */


/* [] END OF FILE */
