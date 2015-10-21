/* 
 * File:   params.h
 * Author: Iota Electronics Limited
 *
 * Created on 27 July 2014, 13:12
 * for I2R Medical Limited
 */

#ifndef PARAMS_H
#define	PARAMS_H

// Parameters to contol the Motor's High Speed
// HIGH_SPEED_ON_PERIOD and HIGH_SPEED_LOW_PERIOD can define the speed at 
// the motor pulses, the motor can run contuously if the Off period is zero
// in which case the On period can be anything
// HIGH_SPEED_DUTY_CYCLE defines the actual speed the motor runs at
// 100 = the motor running at its maximum possible speed.
// 30 = typically the lowest speed that the motor will turn at.

#define HIGH_SPEED_ON_PERIOD        1 * SECONDS
#define HIGH_SPEED_OFF_PERIOD       0
#define HIGH_SPEED_PWM_DUTY_CYCLE   50  //percent

// Parameters to contol the Motor's Low Speed
// LOW_SPEED_ON_PERIOD and LOW_SPEED_LOW_PERIOD can define the speed at
// the motor pulses, the motor can run contuously if the Off period is zero
// in which case the On period can be anything
// LOW_SPEED_DUTY_CYCLE defines the actual speed the motor runs at
// 100 = the motor running at its maximum possible speed.
// 30 = typically the lowest speed that the motor will turn at.

#define LOW_SPEED_ON_PERIOD         1 * SECONDS    //milli-seconds
#define LOW_SPEED_OFF_PERIOD        0
#define LOW_SPEED_PWM_DUTY_CYCLE    20  //percent

// MOTOR_INITIAL_SPEED_PERIOD defines the time in minutes the motor
// is running at the higher speed from pressing the On Button
#define MOTOR_INITIAL_SPEED_PERIOD  1 /*Minute(s)*/

// PWM_FACTOR_FOR_CHARGER_ATTACHED defines the amount the duty cycle is 
// reduced by when the 12V charger supply is attached.  Otherwise the 
// motor will run a lot faster when running of the charger than when running
//  from the battery

#define HIGH_SPEED_PWM_FACTOR_FOR_CHARGER_ATTACHED      60  // percent
#define LOW_SPEED_PWM_FACTOR_FOR_CHARGER_ATTACHED       45  // percent


// BATTERY_LOW_THRESHOLD is the battery voltage level at which the
// Yellow LED comes on to show that the battery is running low
// formula for battery voltage is Integer( (Voltage * 1/4.9)*1024/2.048)
//  = integer (V * 102)
#define BATTERY_LOW_THRESHOLD     714  // 7.00V

// BATTERY_CRITICAL_THRESHOLD is the battery Voltage level at which the unit
// stops running at this point the system turns itself off
// formula for battery voltage is Integer( (Voltage * 1/4.9)*1024/2.048)
//  = integer (V * 102)
#define BATTERY_CRITICAL_THRESHOLD      662  // 6.5V

// CHARGING_CURRENT_THRESHOLD is the current flowing from the battery 
// charger to the battery below which the battery is deemed to be charged
// formula for the charger current is input mv = current mA
#define CHARGING_CURRENT_THRESHOLD  150  // 150mA

// AUDIBLE_ALARM_ENABLED if defined as 1 means that the buzzer is enabled
// if defined as 0 means that the buzzer is disabled/muted
#define AUDIBLE_ALARM_ENABLED 1

// ALARM_PERIOD is the time between audible warnings when the Microswitch is
// closed and/or the proximity switch is open
// please note that the maximum period allowed is 32 Seconds
#define ALARM_PERIOD  20 * SECONDS

// USAGE_EXPIRY is the number of hours the system will run before issuing a
// warning
#define USAGE_EXPIRY 936 // hours

// USAGE_EXPIRY_GRACE_PERIOD is the number of extra hours the system
// will run before the unit becomes non operative
#define USAGE_EXPIRY_GRACE_PERIOD 72 //hours

// USAGE_GRACE_PERIOD_WARNING_PERIOD is the number of hours during the grace
// period between warnings
#define USAGE_GRACE_PERIOD_WARNING_PERIOD 8 //hours


#endif	/* PARAMS_H */

