/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : PTE_Config.h
**     Project     : FRDM-K64F_Zork
**     Processor   : MK64FN1M0VLQ12
**     Component   : Init_GPIO
**     Version     : Component 01.006, Driver 01.06, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-12-02, 21:22, # CodeGen: 12
**     Abstract    :
**          This file implements the GPIO (PTE) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
**     Settings    :
**          Component name                                 : PTE
**          Device                                         : PTE
**          Settings                                       : 
**            Clock gate                                   : Enabled
**            Pin 0                                        : Initialize
**              Pin direction                              : Input
**              Output value                               : 0
**              Open drain                                 : <Automatic>
**              Pull resistor                              : Enabled
**              Pull selection                             : Pull Up
**              Slew rate                                  : <Automatic>
**              Drive strength                             : High
**              Interrupt/DMA request                      : <Automatic>
**              Passive filter                             : <Automatic>
**              Lock                                       : <Automatic>
**            Pin 1                                        : Initialize
**              Pin direction                              : Input
**              Output value                               : 0
**              Open drain                                 : <Automatic>
**              Pull resistor                              : Enabled
**              Pull selection                             : Pull Up
**              Slew rate                                  : <Automatic>
**              Drive strength                             : High
**              Interrupt/DMA request                      : <Automatic>
**              Passive filter                             : <Automatic>
**              Lock                                       : <Automatic>
**            Pin 2                                        : Initialize
**              Pin direction                              : Input
**              Output value                               : 0
**              Open drain                                 : <Automatic>
**              Pull resistor                              : Enabled
**              Pull selection                             : Pull Up
**              Slew rate                                  : <Automatic>
**              Drive strength                             : High
**              Interrupt/DMA request                      : <Automatic>
**              Passive filter                             : <Automatic>
**              Lock                                       : <Automatic>
**            Pin 3                                        : Initialize
**              Pin direction                              : Input
**              Output value                               : 0
**              Open drain                                 : <Automatic>
**              Pull resistor                              : Enabled
**              Pull selection                             : Pull Up
**              Slew rate                                  : <Automatic>
**              Drive strength                             : High
**              Interrupt/DMA request                      : <Automatic>
**              Passive filter                             : <Automatic>
**              Lock                                       : <Automatic>
**            Pin 4                                        : Initialize
**              Pin direction                              : Input
**              Output value                               : 0
**              Open drain                                 : <Automatic>
**              Pull resistor                              : Enabled
**              Pull selection                             : Pull Up
**              Slew rate                                  : <Automatic>
**              Drive strength                             : High
**              Interrupt/DMA request                      : <Automatic>
**              Passive filter                             : <Automatic>
**              Lock                                       : <Automatic>
**            Pin 5                                        : Initialize
**              Pin direction                              : Input
**              Output value                               : 0
**              Open drain                                 : <Automatic>
**              Pull resistor                              : Enabled
**              Pull selection                             : Pull Up
**              Slew rate                                  : <Automatic>
**              Drive strength                             : High
**              Interrupt/DMA request                      : <Automatic>
**              Passive filter                             : <Automatic>
**              Lock                                       : <Automatic>
**            Pin 6                                        : Do not initialize
**            Pin 7                                        : Do not initialize
**            Pin 8                                        : Do not initialize
**            Pin 9                                        : Do not initialize
**            Pin 10                                       : Do not initialize
**            Pin 11                                       : Do not initialize
**            Pin 12                                       : Do not initialize
**            Pin 24                                       : Do not initialize
**            Pin 25                                       : Do not initialize
**            Pin 26                                       : Do not initialize
**            Pin 27                                       : Do not initialize
**            Pin 28                                       : Do not initialize
**          Pin selection/routing                          : 
**            Pin 0                                        : Disabled
**            Pin 1                                        : Disabled
**            Pin 2                                        : Disabled
**            Pin 3                                        : Disabled
**            Pin 4                                        : Disabled
**            Pin 5                                        : Disabled
**            Pin 6                                        : Disabled
**            Pin 7                                        : Disabled
**            Pin 8                                        : Disabled
**            Pin 9                                        : Disabled
**            Pin 10                                       : Disabled
**            Pin 11                                       : Disabled
**            Pin 12                                       : Disabled
**            Pin 24                                       : Disabled
**            Pin 25                                       : Disabled
**            Pin 26                                       : Disabled
**            Pin 27                                       : Disabled
**            Pin 28                                       : Disabled
**          Interrupts                                     : 
**            Port interrupt                               : Enabled
**              Interrupt                                  : INT_PORTE
**              Interrupt request                          : <Automatic>
**              Interrupt priority                         : <Automatic>
**              ISR Name                                   : 
**          Initialization                                 : 
**            Call Init method                             : yes
**            Utilize after reset values                   : default
**     Contents    :
**         Init - void PTE_Init(void);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file PTE_Config.h                                                  
** @version 01.06
** @brief
**          This file implements the GPIO (PTE) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
*/         
/*!
**  @addtogroup PTE_Config_module PTE_Config module documentation
**  @{
*/         

#ifndef PTE_Config_H_
#define PTE_Config_H_

/* MODULE PTE. */

/* GPIOE_PSOR: PTSO&=~0x3F */
#define GPIOE_PSOR_VALUE     0x00U
#define GPIOE_PSOR_MASK      0x3FU
/* GPIOE_PCOR: PTCO|=0x3F */
#define GPIOE_PCOR_VALUE     0x3FU
#define GPIOE_PCOR_MASK      0x3FU
/* GPIOE_PDDR: PDD&=~0x3F */
#define GPIOE_PDDR_VALUE     0x00U
#define GPIOE_PDDR_MASK      0x3FU



#define PTE_AUTOINIT

/* END PTE. */
#endif /* #ifndef __PTE_Config_H_ */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
