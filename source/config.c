// Config.c Module
//*****************************************************************************
//*
//*          Iota Electronics Limited
//*
//*****************************************************************************
//* REVISION HISTORY
//*
//*
//*****************************************************************************

//*****************************************************************************
//* Compiler Directives
//*****************************************************************************

//*****************************************************************************
//* Dependencies
//*****************************************************************************

#include "config.h"
#include <xc.h>
#include "x41.h"

//*****************************************************************************
//* Constants
//*****************************************************************************

//*****************************************************************************
//* Variables
//*****************************************************************************

CConfig	Config;

void writeEEPROM( BYTE * data, int length )
{
  int i;
  for (i = 0; i < length; i++)
    eeprom_write( CONFIG_START_ADDRESS + i, * data++);
}

void readEEPROM( BYTE * data, int length )
{
  int i;
    for (i = 0; i < length; i++)
    *data++ = eeprom_read( CONFIG_START_ADDRESS + i );

}

//*****************************************************************************
//*  Function:	configInit
//*  Arguments:	None
//*  Action:	Initialises Config - resets if corrupt
//*  Returns:	None
//*****************************************************************************
void configInit(void)
{
  // Get config data from eeprom
    configRead();
//      configReset();
}

//*****************************************************************************
//*  Function:	configReset
//*  Arguments:	None
//*  Action:	Resets the configuration to default values
//*  Returns:	None
//*****************************************************************************
void configReset( void )
{
  Config.ConfigVersion = CONFIG_VERSION;
  Config.runningMinutes = DEFAULT_RUNNING_MINUTES;
  Config.soundOn = DEFAULT_SOUND_ON;
  
   // Now save it
  configWrite();
}

//*****************************************************************************
//*  Function:	configRead
//*  Arguments:	None
//*  Action:	Reads the configuration from EEPROM
//*  Returns:	if succcesful read
//*				
//*****************************************************************************

bool configRead( void )
{
  WORD checkCRC = 0;
  int i;
  BYTE rByte;
  BYTE * pByte;
  
  readEEPROM ( (BYTE *)&Config, sizeof(Config));
  
  int configSize = sizeof(Config);
  for ( i = 0; i < configSize - 2; i ++)
  {
    pByte = (BYTE *) &Config;
    rByte =  * (pByte + i);
    checkCRC = fast_crc_byte( checkCRC, rByte);
  }
      
  // Check config data is valid
  if ( Config.CheckCRC != checkCRC )
  {
    return false;
  }

  return true;
}

//*****************************************************************************
//*  Function:	configWrite
//*  Arguments:	None
//*  Action:	Writes the configuration to EEPROM
//*  Returns:	None
//*****************************************************************************

void configWrite( void )
{
  WORD checkCRC = 0;
  int i;
  BYTE rByte;
  BYTE * pByte;

  int configSize = sizeof(Config);
  for ( i = 0; i < configSize - 2; i ++)
  {
    pByte = (BYTE *) &Config;
    rByte =  * (pByte + i);
    checkCRC = fast_crc_byte( checkCRC, rByte);
  }

  Config.CheckCRC = checkCRC;
  writeEEPROM ( (BYTE *)&Config, sizeof(Config));
}

