/* 
 * File:   main.c
 * Author: Mark Rosier
 *
 * Iota electronics Limited 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "main.h"
#include "interrupt.h"
#include "hardware.h"
#include "picconfig.h"
#include "config.h"
#include "timer.h"
//#include "eventhandler.h"
//#include "motorcontrol.h"
//#include "batterymonitor.h"
//#include "sounds.h"
#include "usagecounter.h"


void kickWatchDog( void )
{
    asm("CLRWDT");
}

//*****************************************************************************
//	Function:	main
//	Arguments:	None
//  Action:         Program entry
//	Returns:	None
//*****************************************************************************
void main( void )
{
  initialise();
  while( 1 )
  {
//    eventHandlerService();
//    motorControlService();
//    batteryMonitorService();
//    soundsService();
    usageCounterService();
//    kickWatchDog();

  }
}

//*****************************************************************************
//	Function:	Initialise
//	Arguments: 	None
//	Action: 	Program Initialisation
//	Returns: 	None
//*****************************************************************************
void initialise( void )
{
  hardwareInit();
  timerInit();
//  eventHandlerInit();
//  motorControlInit();
//  batteryMonitorInit();
//  soundsInit();
  usageCounterInit();
  interruptsInit();
  configInit();
//    asm("SLEEP");

}

//*****************************************************************************
//	Function:	HardwareInit
//	Arguments: 	None
//	Action: 	Various Registers are Initialised
//	Returns: 	None
//*****************************************************************************
void hardwareInit( void )
{
  OSCCONbits.SCS = 0;
  OSCCONbits.IRCF = 0xE;
  OSCCONbits.SPLLEN = 1;

  RED_LED_DIR = OUTPUT_PIN;
  RED_LED = LED_OFF;

  GREEN_LED_DIR = OUTPUT_PIN;
  GREEN_LED = LED_OFF;

  YELLOW_LED_DIR = OUTPUT_PIN;
  YELLOW_LED = LED_OFF;

  UNUSED_LED_DIR = OUTPUT_PIN;
  UNUSED_LED_PIN_TYPE = ANALOGUE_PIN;
  UNUSED_LED = LED_OFF;

  MICROSWITCH_PIN_DIR = INPUT_PIN;

  PROXIMITY_SWITCH_PIN_DIR = INPUT_PIN;
  PROXIMITY_SWITCH_PIN_TYPE = DIGITAL_PIN;

  ON_BUTTON_PIN_DIR = INPUT_PIN;
  ON_BUTTON_PIN_TYPE = DIGITAL_PIN;
  
  PWM_PIN_DIR = OUTPUT_PIN;
  PWM_PIN_LATCH= PWM_PIN_OFF;

  ENABLE_VIN_MEASURE_PIN_DIR = OUTPUT_PIN;
  ENABLE_VIN_MEASURE_LATCH = DISABLE_VIN_MEASUREMENT;

  BATTERY_VOLTAGE_PIN_DIR = INPUT_PIN;
  BATTERY_VOLTAGE_PIN_TYPE = ANALOGUE_PIN;

  CHARGER_ATTACHED_PIN_DIR = INPUT_PIN;
  CHARGER_ATTACHED_PIN_TYPE = ANALOGUE_PIN;

}
//*****************************************************************************
//	Function:	interruptsInit
//	Arguments: 	None
//	Action: 	Interrupts Initialised
//	Returns: 	None
//*****************************************************************************
void interruptsInit( void )
{
  initInterrupt();
}


