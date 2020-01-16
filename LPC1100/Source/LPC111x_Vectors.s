/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 2014 - 2018 SEGGER Microcontroller GmbH             *
*                                                                    *
*           www.segger.com     Support: support@segger.com           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* conditions are met:                                                *
*                                                                    *
* - Redistributions of source code must retain the above copyright   *
*   notice, this list of conditions and the following disclaimer.    *
*                                                                    *
* - Neither the name of SEGGER Microcontroller GmbH                  *
*   nor the names of its contributors may be used to endorse or      *
*   promote products derived from this software without specific     *
*   prior written permission.                                        *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED.                                                        *
* IN NO EVENT SHALL SEGGER Microcontroller GmbH BE LIABLE FOR        *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
*********************************************************************/

/*****************************************************************************
 *                         Preprocessor Definitions                          *
 *                         ------------------------                          *
 * VECTORS_IN_RAM                                                            *
 *                                                                           *
 *   If defined, an area of RAM will large enough to store the vector table  *
 *   will be reserved.                                                       *
 *                                                                           *
 *****************************************************************************/

  .syntax unified
  .code 16

  .section .init, "ax"
  .align 2

/*****************************************************************************
 * Default Exception Handlers                                                *
 *****************************************************************************/

  .thumb_func
  .weak NMI_Handler
NMI_Handler:
  b .

  .thumb_func
  .weak HardFault_Handler
HardFault_Handler:
  b .

  .thumb_func
  .weak SVC_Handler
SVC_Handler:
  b .

  .thumb_func
  .weak PendSV_Handler
PendSV_Handler:
  b .

  .thumb_func
  .weak SysTick_Handler
SysTick_Handler:
  b .

  .thumb_func
Dummy_Handler:
  b .

#if defined(__OPTIMIZATION_SMALL)

  .weak PIO0_0_IRQHandler
  .thumb_set PIO0_0_IRQHandler,Dummy_Handler

  .weak PIO0_1_IRQHandler
  .thumb_set PIO0_1_IRQHandler,Dummy_Handler

  .weak PIO0_2_IRQHandler
  .thumb_set PIO0_2_IRQHandler,Dummy_Handler

  .weak PIO0_3_IRQHandler
  .thumb_set PIO0_3_IRQHandler,Dummy_Handler

  .weak PIO0_4_IRQHandler
  .thumb_set PIO0_4_IRQHandler,Dummy_Handler

  .weak PIO0_5_IRQHandler
  .thumb_set PIO0_5_IRQHandler,Dummy_Handler

  .weak PIO0_6_IRQHandler
  .thumb_set PIO0_6_IRQHandler,Dummy_Handler

  .weak PIO0_7_IRQHandler
  .thumb_set PIO0_7_IRQHandler,Dummy_Handler

  .weak PIO0_8_IRQHandler
  .thumb_set PIO0_8_IRQHandler,Dummy_Handler

  .weak PIO0_9_IRQHandler
  .thumb_set PIO0_9_IRQHandler,Dummy_Handler

  .weak PIO0_10_IRQHandler
  .thumb_set PIO0_10_IRQHandler,Dummy_Handler

  .weak PIO0_11_IRQHandler
  .thumb_set PIO0_11_IRQHandler,Dummy_Handler

  .weak PIO1_0_IRQHandler
  .thumb_set PIO1_0_IRQHandler,Dummy_Handler

  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Dummy_Handler

  .weak I2C_IRQHandler
  .thumb_set I2C_IRQHandler,Dummy_Handler

  .weak CT16B0_IRQHandler
  .thumb_set CT16B0_IRQHandler,Dummy_Handler

  .weak CT16B1_IRQHandler
  .thumb_set CT16B1_IRQHandler,Dummy_Handler

  .weak CT32B0_IRQHandler
  .thumb_set CT32B0_IRQHandler,Dummy_Handler

  .weak CT32B1_IRQHandler
  .thumb_set CT32B1_IRQHandler,Dummy_Handler

  .weak SPI0_IRQHandler
  .thumb_set SPI0_IRQHandler,Dummy_Handler

  .weak UART_IRQHandler
  .thumb_set UART_IRQHandler,Dummy_Handler

  .weak ADC_IRQHandler
  .thumb_set ADC_IRQHandler,Dummy_Handler

  .weak WDT_IRQHandler
  .thumb_set WDT_IRQHandler,Dummy_Handler

  .weak BOD_IRQHandler
  .thumb_set BOD_IRQHandler,Dummy_Handler

  .weak FMC_IRQHandler
  .thumb_set FMC_IRQHandler,Dummy_Handler

  .weak GPIO3_IRQHandler
  .thumb_set GPIO3_IRQHandler,Dummy_Handler

  .weak GPIO2_IRQHandler
  .thumb_set GPIO2_IRQHandler,Dummy_Handler

  .weak GPIO1_IRQHandler
  .thumb_set GPIO1_IRQHandler,Dummy_Handler

  .weak GPIO0_IRQHandler
  .thumb_set GPIO0_IRQHandler,Dummy_Handler

#else

  .thumb_func
  .weak PIO0_0_IRQHandler
PIO0_0_IRQHandler:
  b .

  .thumb_func
  .weak PIO0_1_IRQHandler
PIO0_1_IRQHandler:
  b .

  .thumb_func
  .weak PIO0_2_IRQHandler
PIO0_2_IRQHandler:
  b .

  .thumb_func
  .weak PIO0_3_IRQHandler
PIO0_3_IRQHandler:
  b .

  .thumb_func
  .weak PIO0_4_IRQHandler
PIO0_4_IRQHandler:
  b .

  .thumb_func
  .weak PIO0_5_IRQHandler
PIO0_5_IRQHandler:
  b .

  .thumb_func
  .weak PIO0_6_IRQHandler
PIO0_6_IRQHandler:
  b .

  .thumb_func
  .weak PIO0_7_IRQHandler
PIO0_7_IRQHandler:
  b .

  .thumb_func
  .weak PIO0_8_IRQHandler
PIO0_8_IRQHandler:
  b .

  .thumb_func
  .weak PIO0_9_IRQHandler
PIO0_9_IRQHandler:
  b .

  .thumb_func
  .weak PIO0_10_IRQHandler
PIO0_10_IRQHandler:
  b .

  .thumb_func
  .weak PIO0_11_IRQHandler
PIO0_11_IRQHandler:
  b .

  .thumb_func
  .weak PIO1_0_IRQHandler
PIO1_0_IRQHandler:
  b .

  .thumb_func
  .weak SPI1_IRQHandler
SPI1_IRQHandler:
  b .

  .thumb_func
  .weak I2C_IRQHandler
I2C_IRQHandler:
  b .

  .thumb_func
  .weak CT16B0_IRQHandler
CT16B0_IRQHandler:
  b .

  .thumb_func
  .weak CT16B1_IRQHandler
CT16B1_IRQHandler:
  b .

  .thumb_func
  .weak CT32B0_IRQHandler
CT32B0_IRQHandler:
  b .

  .thumb_func
  .weak CT32B1_IRQHandler
CT32B1_IRQHandler:
  b .

  .thumb_func
  .weak SPI0_IRQHandler
SPI0_IRQHandler:
  b .

  .thumb_func
  .weak UART_IRQHandler
UART_IRQHandler:
  b .

  .thumb_func
  .weak ADC_IRQHandler
ADC_IRQHandler:
  b .

  .thumb_func
  .weak WDT_IRQHandler
WDT_IRQHandler:
  b .

  .thumb_func
  .weak BOD_IRQHandler
BOD_IRQHandler:
  b .

  .thumb_func
  .weak FMC_IRQHandler
FMC_IRQHandler:
  b .

  .thumb_func
  .weak GPIO3_IRQHandler
GPIO3_IRQHandler:
  b .

  .thumb_func
  .weak GPIO2_IRQHandler
GPIO2_IRQHandler:
  b .

  .thumb_func
  .weak GPIO1_IRQHandler
GPIO1_IRQHandler:
  b .

  .thumb_func
  .weak GPIO0_IRQHandler
GPIO0_IRQHandler:
  b .

#endif

/*****************************************************************************
 * Vector Table                                                              *
 *****************************************************************************/

  .section .vectors, "ax"
  .align 2
  .global _vectors
  .extern __stack_end__
  .extern Reset_Handler

_vectors:
  .word __stack_end__
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word SVC_Handler
  .word 0 /* Reserved */
  .word 0 /* Reserved */
  .word PendSV_Handler
  .word SysTick_Handler
  .word PIO0_0_IRQHandler
  .word PIO0_1_IRQHandler
  .word PIO0_2_IRQHandler
  .word PIO0_3_IRQHandler
  .word PIO0_4_IRQHandler
  .word PIO0_5_IRQHandler
  .word PIO0_6_IRQHandler
  .word PIO0_7_IRQHandler
  .word PIO0_8_IRQHandler
  .word PIO0_9_IRQHandler
  .word PIO0_10_IRQHandler
  .word PIO0_11_IRQHandler
  .word PIO1_0_IRQHandler
  .word Dummy_Handler /* Reserved */
  .word SPI1_IRQHandler
  .word I2C_IRQHandler
  .word CT16B0_IRQHandler
  .word CT16B1_IRQHandler
  .word CT32B0_IRQHandler
  .word CT32B1_IRQHandler
  .word SPI0_IRQHandler
  .word UART_IRQHandler
  .word Dummy_Handler /* Reserved */
  .word Dummy_Handler /* Reserved */
  .word ADC_IRQHandler
  .word WDT_IRQHandler
  .word BOD_IRQHandler
  .word FMC_IRQHandler
  .word GPIO3_IRQHandler
  .word GPIO2_IRQHandler
  .word GPIO1_IRQHandler
  .word GPIO0_IRQHandler
_vectors_end:

#ifdef VECTORS_IN_RAM
  .section .vectors_ram, "ax"
  .align 2
  .global _vectors_ram

_vectors_ram:
  .space _vectors_end - _vectors, 0
#endif
