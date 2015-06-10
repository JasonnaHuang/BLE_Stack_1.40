/**************************************************************************************************
  Filename:       hal_led.h
  Revised:        $Date: 2007-07-06 10:42:24 -0700 (Fri, 06 Jul 2007) $
  Revision:       $Revision: 13579 $

  Description:    This file contains the interface to the LED Service.


  Copyright 2005-2007 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, 
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com. 
**************************************************************************************************/

#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "hal_board.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/* LEDS - The LED number is the same as the bit position */
#define HAL_GPIO_ZM516X_RESET     0x01
#define HAL_GPIO_ZM516X_DEF     0x02
#define HAL_GPIO_ZM516X_SLEEP     0x04
#define HAL_GPIO_ZM516X_WAKEUP     0x08
#define HAL_GPIO_ZM516X_MOTOR1     0x10
#define HAL_GPIO_ZM516X_MOTOR2     0x20 
#define HAL_GPIO_ZM516X_ALL   (HAL_GPIO_ZM516X_RESET | HAL_GPIO_ZM516X_DEF | HAL_GPIO_ZM516X_SLEEP | HAL_GPIO_ZM516X_WAKEUP | HAL_GPIO_ZM516X_MOTOR1 | HAL_GPIO_ZM516X_MOTOR1)
#define HAL_GPIO_ZM516X_KEY1     0x80
#define HAL_GPIO_ZM516X_KEY2     0x40 

/* Defaults */
#define HAL_LED_DEFAULT_MAX_LEDS      4
#define HAL_LED_DEFAULT_DUTY_CYCLE    5
#define HAL_LED_DEFAULT_FLASH_COUNT   50
#define HAL_LED_DEFAULT_FLASH_TIME    1000

/*********************************************************************
 * TYPEDEFS
 */


/*********************************************************************
 * GLOBAL VARIABLES
 */

/*
 * Initialize LED Service.
 */
extern void HalGpioInit( void );

/*
 * Set the LED ON/OFF/TOGGLE.
 */
extern uint8 HalGpioSet( uint8 led, uint8 mode );


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
