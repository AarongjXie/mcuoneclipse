/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : KIN1.h
**     Project     : FRDM-K64F_Zork
**     Processor   : MK64FN1M0VLQ12
**     Component   : KinetisTools
**     Version     : Component 01.040, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-12-02, 21:22, # CodeGen: 12
**     Abstract    :
**
**     Settings    :
**          Component name                                 : KIN1
**          Utility                                        : UTIL1
**          SDK                                            : MCUC1
**          Shell                                          : Disabled
**     Contents    :
**         SoftwareReset          - void KIN1_SoftwareReset(void);
**         UIDGet                 - uint8_t KIN1_UIDGet(KIN1_UID *uid);
**         UIDSame                - bool KIN1_UIDSame(const KIN1_UID *src, const KIN1_UID *dst);
**         UIDtoString            - uint8_t KIN1_UIDtoString(const KIN1_UID *uid, uint8_t *buf, size_t bufSize);
**         GetKinetisFamilyString - KIN1_ConstCharPtr KIN1_GetKinetisFamilyString(void);
**         GetPC                  - void* KIN1_GetPC(void);
**         GetSP                  - void* KIN1_GetSP(void);
**         SetPSP                 - void KIN1_SetPSP(void *setval);
**         SetLR                  - void KIN1_SetLR(uint32_t setval);
**         InitCycleCounter       - void KIN1_InitCycleCounter(void);
**         ResetCycleCounter      - void KIN1_ResetCycleCounter(void);
**         EnableCycleCounter     - void KIN1_EnableCycleCounter(void);
**         DisableCycleCounter    - void KIN1_DisableCycleCounter(void);
**         GetCycleCounter        - uint32_t KIN1_GetCycleCounter(void);
**         Deinit                 - void KIN1_Deinit(void);
**         Init                   - void KIN1_Init(void);
**
** * Copyright (c) 2014-2018, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file KIN1.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup KIN1_module KIN1 module documentation
**  @{
*/         

#ifndef __KIN1_H
#define __KIN1_H

/* MODULE KIN1. */
#include "MCUC1.h" /* SDK and API used */
#include "KIN1config.h" /* configuration */

#include <stddef.h> /* for size_t */
#if KIN1_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h" /* Command line shell */
#endif


#ifndef __BWUserType_KIN1_ConstCharPtr
#define __BWUserType_KIN1_ConstCharPtr
  typedef const uint8_t *KIN1_ConstCharPtr; /* Pointer to constant string */
#endif


#if MCUC1_CONFIG_CORTEX_M >= 3 /* only for Cortex-M3 or higher */
  /* DWT (Data Watchpoint and Trace) registers, only exists on ARM Cortex with a DWT unit */
  #define KIN1_DWT_CONTROL             (*((volatile uint32_t*)0xE0001000))
    /*!< DWT Control register */
  #define KIN1_DWT_CYCCNTENA_BIT       (1UL<<0)
    /*!< CYCCNTENA bit in DWT_CONTROL register */
  #define KIN1_DWT_CYCCNT              (*((volatile uint32_t*)0xE0001004))
    /*!< DWT Cycle Counter register */
  #define KIN1_DEMCR                   (*((volatile uint32_t*)0xE000EDFC))
    /*!< DEMCR: Debug Exception and Monitor Control Register */
  #define KIN1_TRCENA_BIT              (1UL<<24)
    /*!< Trace enable bit in DEMCR register */
#endif

typedef struct {
  uint8_t id[16]; /* 128 bit ID */
} KIN1_UID;

typedef enum {
  KIN1_FAMILY_K10_K12,                 /* K10 or K12 */
  KIN1_FAMILY_K20_K22,                 /* K10 or K12 */
  KIN1_FAMILY_K30_K11_K61,             /* K30, K11 or K61 */
  KIN1_FAMILY_K40_K21,                 /* K40 or K21 */
  KIN1_FAMILY_K70,                     /* K70 */
  KIN1_FAMILY_UNKONWN,                 /* Unknown */
  KIN1_FAMILY_LAST                     /* Must be last one! */
} KIN1_FAMILY;

#define KIN1_PARSE_COMMAND_ENABLED  KIN1_CONFIG_PARSE_COMMAND_ENABLED
  /*!< set to 1 if method ParseCommand() is present, 0 otherwise */

#ifdef __cplusplus
extern "C" {
#endif

void KIN1_SoftwareReset(void);
/*
** ===================================================================
**     Method      :  SoftwareReset (component KinetisTools)
**
**     Description :
**         Performs a reset of the device
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint8_t KIN1_UIDGet(KIN1_UID *uid);
/*
** ===================================================================
**     Method      :  UIDGet (component KinetisTools)
**
**     Description :
**         Return the 128bit UID of the device
**     Parameters  :
**         NAME            - DESCRIPTION
**       * uid             - Pointer to 
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

bool KIN1_UIDSame(const KIN1_UID *src, const KIN1_UID *dst);
/*
** ===================================================================
**     Method      :  UIDSame (component KinetisTools)
**
**     Description :
**         Compares two UID
**     Parameters  :
**         NAME            - DESCRIPTION
**       * src             - Pointer to 
**         Variable_1      - 
**     Returns     :
**         ---             - TRUE if the same, FALSE otherwise
** ===================================================================
*/

uint8_t KIN1_UIDtoString(const KIN1_UID *uid, uint8_t *buf, size_t bufSize);
/*
** ===================================================================
**     Method      :  UIDtoString (component KinetisTools)
**
**     Description :
**         Returns the value of the UID as string
**     Parameters  :
**         NAME            - DESCRIPTION
**         uid             - 
**       * buf             - Pointer to 
**         bufSize         - 
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

KIN1_ConstCharPtr KIN1_GetKinetisFamilyString(void);
/*
** ===================================================================
**     Method      :  GetKinetisFamilyString (component KinetisTools)
**
**     Description :
**         Determines the Kinetis Familiy based on SIM_SDID register
**     Parameters  : None
**     Returns     :
**         ---             - String describing the Kinetis Family
** ===================================================================
*/

void* KIN1_GetPC(void);
/*
** ===================================================================
**     Method      :  GetPC (component KinetisTools)
**
**     Description :
**         returns the program counter
**     Parameters  : None
**     Returns     :
**         ---             - program counter
** ===================================================================
*/

void* KIN1_GetSP(void);
/*
** ===================================================================
**     Method      :  GetSP (component KinetisTools)
**
**     Description :
**         returns the stack pointer
**     Parameters  : None
**     Returns     :
**         ---             - stack pointer
** ===================================================================
*/

void KIN1_SetPSP(void *setval);
/*
** ===================================================================
**     Method      :  SetPSP (component KinetisTools)
**
**     Description :
**         sets the process stack pointer
**     Parameters  :
**         NAME            - DESCRIPTION
**         setval          - new PSP value
**     Returns     : Nothing
** ===================================================================
*/

void KIN1_SetLR(uint32_t setval);
/*
** ===================================================================
**     Method      :  SetLR (component KinetisTools)
**
**     Description :
**         Sets the link register
**     Parameters  :
**         NAME            - DESCRIPTION
**         setval          - new LR value
**     Returns     : Nothing
** ===================================================================
*/

#if MCUC1_CONFIG_CORTEX_M >= 3 /* only for Cortex-M3 or higher */
#define KIN1_InitCycleCounter() \
  KIN1_DEMCR |= KIN1_TRCENA_BIT
  /*!< TRCENA: Enable trace and debug block DEMCR (Debug Exception and Monitor Control Register */
/*
** ===================================================================
**     Method      :  InitCycleCounter (component KinetisTools)
**
**     Description :
**         Initializes the cycle counter, available if the core has a
**         DWT (Data Watchpoint and Trace) unit, usually present on
**         M3/M4/M7
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#endif

#if MCUC1_CONFIG_CORTEX_M >= 3 /* only for Cortex-M3 or higher */
#define KIN1_ResetCycleCounter() \
  KIN1_DWT_CYCCNT = 0
  /*!< Reset cycle counter */
/*
** ===================================================================
**     Method      :  ResetCycleCounter (component KinetisTools)
**
**     Description :
**         Reset the cycle counter (set it to zero)
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#endif

#if MCUC1_CONFIG_CORTEX_M >= 3 /* only for Cortex-M3 or higher */
#define KIN1_EnableCycleCounter() \
  KIN1_DWT_CONTROL |= KIN1_DWT_CYCCNTENA_BIT
  /*!< Enable cycle counter */
/*
** ===================================================================
**     Method      :  EnableCycleCounter (component KinetisTools)
**
**     Description :
**         Enables counting the cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#endif

#if MCUC1_CONFIG_CORTEX_M >= 3 /* only for Cortex-M3 or higher */
#define KIN1_DisableCycleCounter() \
  KIN1_DWT_CONTROL &= ~KIN1_DWT_CYCCNTENA_BIT
  /*!< Disable cycle counter */
/*
** ===================================================================
**     Method      :  DisableCycleCounter (component KinetisTools)
**
**     Description :
**         Disables the cycle counter.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#endif

#if MCUC1_CONFIG_CORTEX_M >= 3 /* only for Cortex-M3 or higher */
#define KIN1_GetCycleCounter() \
  KIN1_DWT_CYCCNT
  /*!< Read cycle counter register */
/*
** ===================================================================
**     Method      :  GetCycleCounter (component KinetisTools)
**
**     Description :
**         Return the current cycle counter value
**     Parameters  : None
**     Returns     :
**         ---             - cycle counter
** ===================================================================
*/
#endif

void KIN1_Deinit(void);
/*
** ===================================================================
**     Method      :  Deinit (component KinetisTools)
**
**     Description :
**         Driver de-initialization routine
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void KIN1_Init(void);
/*
** ===================================================================
**     Method      :  Init (component KinetisTools)
**
**     Description :
**         Driver initialization routine
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END KIN1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
/* ifndef __KIN1_H */
/*!
** @}
*/
