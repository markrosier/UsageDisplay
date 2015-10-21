/* 
 * File:   config.h
 * Author: Mark Rosier
 *
 * Iota Electronics Limited 2015
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

//*****************************************************************************
//* Dependencies
//*****************************************************************************

#include "system.h"

//*****************************************************************************
//* Defines Typedefs and Classes
//*****************************************************************************

#define DEFAULT_SOUND_ON              0
#define DEFAULT_RUNNING_MINUTES       0

typedef struct
{
  char ConfigVersion;
  bool soundOn;
  DWORD runningMinutes;
  WORD CheckCRC;

} CConfig;

//*****************************************************************************
//* Constants
//*****************************************************************************

#define CONFIG_VERSION              'D'
#define CONFIG_START_ADDRESS         0

//*****************************************************************************
//* Variables
//*****************************************************************************
extern CConfig	Config;

//****************************************************************************
//* Prototypes
//*****************************************************************************
void configInit(void);
void configWrite( void );
void configReset( void );
bool configRead( void );

//****************************************************************************
//* Local Prototypes
//*****************************************************************************
void writeEEPROM( BYTE * data, int length );
void readEEPROM( BYTE * data, int length );

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

