/* 
 * File:   usagecounter.h
 * Author: Mark Rosier
 *
 * Iota Electronics Ltd 2015
 */

#ifndef USAGECOUNTER_H
#define	USAGECOUNTER_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "params.h"

#define END_OF_LIFE_HOURS       USAGE_EXPIRY
#define END_OF_LIFE_MINUTES     END_OF_LIFE_HOURS * 60
#define USAGE_COUNTER_PERIOD    15000
#define TICKS_PER_SECOND        500
#define SECONDS_PER_MINUTE      60

  
void initTimer6( void );
void timer6Interrupt( void );
void displayUsage( void );
void usageCounterInit( void );
void usageCounterService( void );
void setUsageCounterOff( void );
void setUsageCounterOn( void );

#ifdef	__cplusplus
}
#endif

#endif	/* USAGECOUNTER_H */

