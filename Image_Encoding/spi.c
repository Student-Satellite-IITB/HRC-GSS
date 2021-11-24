#include <avr/io.h>
#include "spi.h"

/* Initialise SPI registers for microcontroller to work as master
*/
void SPISetMaster()
{
	DDRB=0b10110000;
	SPCR=(1<<SPIE)|(1<<SPE)|(1<<MSTR);
	SPSR=0x00;
}


/* Send 8 bit data using SPI
*
* Parameter
* data      8 Bit data to be sent
*/
void SPI_send8(int data)
{
	SPDR = data;
}


/* Send 16 bit data using SPI by breaking into least significant and most significant 8 bits of data
*
* Parameter
* data      16 Bit data to be sent
*/
void SPI_send16(int data)
{
	int mostSignificantByte = ((data>>8) & 0x00FF);
	int leastSignificantByte = (data & 0x00FF);
	SPI_send8(mostSignificantByte);
	SPI_send8(leastSignificantByte);
}