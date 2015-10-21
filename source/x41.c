 /**************************************************************************
 *                                                                         *
 *  Byte-wise CRC generator                       (C) J.E.T Limited 1996   *
 *                                                                         *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * File:               X41.C                                               *
 * Author:             Tim Jarvis                                          *
 * Date:               8 March 1996                                        *
 * Project:            P51                                                 *
 * Language:           C                                                   *
 * Environment:        ANSII C                                             *
 * Version:            R01                                                 *
 * Issued:             -                                                   *
 *                                                                         *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * COPYRIGHT CONTROL:                                                      *
 *     This source file remains property of Jarvis Engineering and         *
 * Technology Limited at all times.                                        *
 *                                                                         *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * DESCRIPTION:                                                            *
 *     The CRC is an interesting checksum. It has guaranteed Hamming       *
 * distance if the generator polynomial is irreducable. The X41 polynomial *
 * has been particularily well researched (by ITU-T) it has hamming        *
 * distance 4. This means it can detect up to 3 bit errors irrespective    *
 * of their position in the message. The routine fast_crc_byte() adds one  *
 * data byte into a CRC using no internal itterations. The routine takes   *
 * and returns CRC so that more than one CRC can be calculated at once.    *
 *                                                                         *
 * I have left slow_crc_byte() in place so that:                           *
 *                                                                         *
 * (A)	You can check fast and slow produce the same result               *
 * (B)   You can used slow to generate a new table for fast                *
 *                                                                         *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * MODIFICATION RECORD:                                                    *
 *                                                                         *
 **************************************************************************/

#include "system.h"
#include <stdio.h>
#include "x41.h"

#define SHIFTED_GEN_POLY 0x810	/*X41: g(x) = x16+x12+x5+1 = $1021*/
#define BOOL char						/*X41: g(x) shifted>> = $810*/

#define GEN_MAIN 0		/*TRUE if you want to compile main()*/
#define GEN_TABLE 0		/*set TRUE if wanting main() to make a new table*/
#define HIGH_BYTE_FIRST 0	/*tell me your machine's byte sex*/
											/*0=Intel, 1=Motorola*/

#define INCLUDE_FAST_CRC 1

#ifdef INCLUDE_FAST_CRC
/****************************
*		Fast FEC look-up table
*
*  The default table is for X41. If you want to use another generator then
*  set SHIFTED_GEN_POLY and GEN_TABLE compile and run then cut and paste
*  the output main writes to your file into this table.
*/
//__xdata_rom const WORD correct[] = {

const WORD correct[] = {
0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D, 
0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4, 
0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC, 
0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823, 
0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B, 
0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12, 
0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41, 
0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49, 
0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E, 
0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256, 
0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0 };

/*********************
*		fast_crc_byte()
*
*  Perform one byte of CRC calculation. This version does the algorithm
*  one byte at a time (no loops).
*
* ARGS:		csum		(short) the current CRC
*				byte		(unsigned char) the octet to add to the CRC
*
* RETURNS:	csum		(short) the updated CRC
*/

WORD fast_crc_byte( WORD csum, BYTE rbyte )
{
	BYTE thing,*um;

	um = (BYTE *)&csum;
#if HIGH_BYTE_FIRST
	thing = um[0] ^ rbyte;
	um[0] = um[1];
	um[1] = 0;
#else
	thing = um[1] ^ rbyte;
	um[1] = um[0];
	um[0] = 0;
#endif

	return( csum ^ correct[thing] );
}
#endif //INCLUDE_FAST_CRC

/*********************
*		slow_crc_byte()
*
*  Perform one byte of CRC calculation. Do it the slow way one bit
*  at a time.
*
* ARGS:		csum		(short) the current CRC
*				byte		(unsigned char) the octet to add to the CRC
*
* RETURNS:	csum		(short) the updated CRC
*/
WORD slow_crc_byte( WORD csum, BYTE rbyte )
{
	WORD res;
	BYTE m;

	m = 0x80;
	while( m )								/*m is a single bit mask shifting through byte*/
	{											/*res is flag in the Forth style of 0,-1*/
		res = ( !( m & rbyte ) -1 ) ^ ( !( csum & 0x8000 ) -1 );
		csum ^= SHIFTED_GEN_POLY & res; /*the gen polynomial /2*/
		csum <<= 1;
		if( res )							/*this does the '1' bit of the polynomial*/
			csum++;

		m >>= 1;
	}
	return( csum );
}



/************
*		main()
*
*  There are two mains. One generates a new table and writes it to the
*  filename you specify as command line argument one. The other runs
*  both CRCs over a message you supply as command line argument one.
*/
#if GEN_MAIN
#if GEN_TABLE
void main( int argc, char *argv[] )
{
	FILE *fp;
	int i;

	if( argc >= 2 )
	{
		if( ( fp = fopen( argv[1], "w" ) ) != NULL )
		{
			for( i=0; i<256; i++ )
			{
				if( (i&7) == 0 )
					fprintf( fp, "\n" );
				fprintf( fp, "0x%04X, ", slow_crc_byte( 0, i ) );
			}
		}
	}
} Z
#else
void main( int argc, char *argv[] )
{
	short csum1,csum2;
	char *ptr;

	if( argc >= 2 )
	{
		csum1 = 0;
		csum2 = 0;
		for( ptr=argv[1]; *ptr; ptr++ )
		{
			csum1 = slow_crc_byte( csum1, *ptr );
			csum2 = fast_crc_byte( csum2, *ptr );
			printf( "\n%c  %04X %04X", *ptr, csum1, csum2 );
		}
	}
}
#endif
#endif
