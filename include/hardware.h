/* 
 * File:   hardware.h
 * Author: Mark Rosier
 *
 * Iota Electronics 2015
 */

#ifndef HARDWARE_H
#define	HARDWARE_H

#ifdef	__cplusplus
extern "C"
{
#endif

#define false                       0
#define true                        !false
  typedef unsigned char bool;

#define OUTPUT_PIN                  0
#define INPUT_PIN                   1
#define DISABLE_OUTPUT              1
#define ENABLE_OUTPUT		          	0

#define DIGITAL_PIN			            0
#define ANALOGUE_PIN		          	1

#define ADC_GO_NOT_DONE	            0b00000010
#define ADC_ENABLE                  0b00000001

#define LED_ON                      1
#define LED_OFF                     0

  // pin 2  Define as Digital Input
#define MICROSWITCH_PIN             PORTAbits.RA5
#define MICROSWITCH_PIN_DIR         TRISAbits.TRISA5
#define MICROSWITCH_CLOSED          0

  // pin 3  Define as Digital Input
#define PROXIMITY_SWITCH_PIN        PORTAbits.RA4
#define PROXIMITY_SWITCH_PIN_DIR    TRISAbits.TRISA4
#define PROXIMITY_SWITCH_PIN_TYPE   ANSELAbits.ANSA4
#define PROXIMITY_SWITCH_CLOSED     0

  // pin 17  Define as Digital Input
#define ON_BUTTON_PIN               PORTAbits.RA2
#define ON_BUTTON_PIN_DIR           TRISAbits.TRISA2
#define ON_BUTTON_PIN_TYPE          ANSELAbits.ANSA2
#define ON_BUTTON_PRESSED           0

  // pin 5  Define as Digital Output
#define PWM_PIN                     PORTCbits.RC5
#define PWM_PIN_LATCH               LATCbits.LATC5
#define PWM_PIN_DIR                 TRISCbits.TRISC5
#define PWM_PIN_ON                  1
#define PWM_PIN_OFF                 0

  // pin 6 Define as Digital Output
#define ENABLE_VIN_MEASURE_LATCH    LATCbits.LATC4
#define ENABLE_VIN_MEASURE_PIN_DIR  TRISCbits.TRISC4
#define ENABLE_VIN_MEASUREMENT      1
#define DISABLE_VIN_MEASUREMENT     0

  // pin 8 Define a Digital Output
#define BUZZER_PIN                  LATCbits.LATC6
#define BUZZER_PIN_DIR              TRISCbits.TRISC6
#define BUZZER_PIN_TYPE             ANSELCbits.ANSC6

  // pin 9  Define as Analogue Input
#define BATTERY_VOLTAGE_PIN         PORTCbits.RC7
#define BATTERY_VOLTAGE_PIN_DIR     TRISCbits.TRISC7
#define BATTERY_VOLTAGE_PIN_TYPE    ANSELCbits.ANSC7
#define BATTERY_VOLTAGE_CHANNEL     9

  // pin 10
#define GREEN_LED                   LATBbits.LATB7
#define GREEN_LED_DIR               TRISBbits.TRISB7

  // pin 11  Define as Digital Output
#define RED_LED                     LATBbits.LATB6
#define RED_LED_DIR                 TRISBbits.TRISB6

  // pin 12  Define as Digital Output
#define YELLOW_LED                  LATBbits.LATB5
#define YELLOW_LED_DIR              TRISBbits.TRISB5
#define YELLOW_LED_TYPE             ANSELBbits.ANSB5

  // Pin 13 Not used
#define UNUSED_LED                  LATBbits.LATB4
#define UNUSED_LED_DIR              TRISBbits.TRISB4
#define UNUSED_LED_PIN_TYPE         ANSELBbits.ANSB4

  // pin 15 Define as Digital Input
#define CHARGER_ATTACHED_PIN        PORTCbits.RC1
#define CHARGER_ATTACHED_PIN_DIR    TRISCbits.TRISC1
#define CHARGER_ATTACHED_PIN_TYPE   ANSELCbits.ANSC1
#define CHARGER_ATTACHED_CHANNEL     5
#define CHARGER_ATTACHED            1

  // pin 16 Define as Analogue input
#define CHARGER_CURRENT_PIN         PORTCbits.RC0
#define CHARGER_CURRENT_PIN_DIR     TRISCbits.TRISC0
#define CHARGER_CURRENT_PIN_TYPE    ANSELCbits.ANSC0
#define CHARGER_CURRENT_CHANNEL     4
  

// Using Internal Clock of 8 MHz
#define OSC_FREQUENCY 16000000L
// Delay Function
#define	_delay_us(x) { unsigned char us; \
		       us = (x)/(32000000/OSC_FREQUENCY)|1; \
		       while(--us != 0) continue; }


#ifdef	__cplusplus
}
#endif



#endif	/* HARDWARE_H */

