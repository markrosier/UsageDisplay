//************************************************************************
//
// usagecounter.c
// Records the number of minutes the unit has been running
//
// Iota Electronics Limited 2015
//
//************************************************************************

#include "system.h"
#include "timer.h"
#include "usagecounter.h"
//#include "sounds.h"
#include "config.h"

bool unitIsDead = false;

BYTE usageCounterTimer = 0;

WORD ticksPerSecondCounter = 0;
WORD secondsCounter = 0;

WORD secondsSinceOn = 0;

bool minuteFlag = false;
bool UCToggle = false;
bool usageCounterOn = false;


void usageCounterInit( void )
{
  usageCounterTimer = timerGet ();
  timerSet( usageCounterTimer, 1000 );
}

void usageCounterService( void )
{
  int i ;
    
  if ( timerRead(usageCounterTimer) == EXPIRED )
  {
    int hours = (int) (Config.runningMinutes /60);
    int thousands = hours / 1000;
    int hundreds = (hours % 1000)/100;
    int tens = (hours % 100)/10;
       
    for ( i = 0; i < thousands; i++)
    {
      YELLOW_LED = LED_ON;
      timerDelay( 300 );
      YELLOW_LED = LED_OFF;
      timerDelay( 300 );
    }
  
    for ( i = 0; i < hundreds; i++)
    {
      RED_LED = LED_ON;
      timerDelay( 300 );
      RED_LED = LED_OFF;
      timerDelay( 300 );
    }

    for ( i = 0; i < tens; i++)
    {
      GREEN_LED = LED_ON;
      timerDelay( 300 );
      GREEN_LED = LED_OFF;
      timerDelay( 300 );
    }
  
    timerSet( usageCounterTimer, USAGE_COUNTER_PERIOD );
  }
}



