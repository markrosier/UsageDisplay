//****************************************************************************
//
//  interrupt.c
//
//  Iota Electronics Limited 2015
//
//****************************************************************************

#include "system.h"
#include "timer.h"
#include "interrupt.h"
//#include "motorcontrol.h"
//#include "eventhandler.h"
//#include "sounds.h"
#include "usagecounter.h"


void initInterrupt( void )
{
  INTCONbits.PEIE = 1; //Enable Peripheral Interrupt
  INTCONbits.GIE = 1; //Enable INTs globally
}

void disableInterrupts( void )
{
  INTCONbits.GIE = 0;
}

void enableInterrupts( void )
{
  INTCONbits.GIE = 1;
}

void interrupt ISRCode( )
{
 // keyInterrupt();
  timerInterrupt( );
 // timer2Interrupt();
//  timer4Interrupt();
 // timer6Interrupt();
}
