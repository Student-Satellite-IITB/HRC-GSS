/*Image Storage using frequencies already calculated by PC*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "AT24C256.h"
#include "I2C.h"
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	sei();										//Enable global interrupts
	uint8_t data;										//8 bit data which will be received at once
	unsigned int byteCount=0;					//Initializing byte count of data to be stored
	setUART();											//Initialize UART in microcontroller to receive data from PC
	I2CInit();											//Initialize microcontroller as master for I2C for EEPROM interfacing
	
	
	uint8_t deviceAddressByte1=0b10100000, wordAddressByte1=0, wordAddressByte2=0;						//Initialize device address and word address bytes
	
	/* Storage in EEPROM */
	for(byteCount=0; byteCount<32768; byteCount++)
	{
		data=UARTReceive();																		//Receive data byte from PC
		eepromWriteByte(&deviceAddressByte1, &wordAddressByte1, &wordAddressByte2, data);					//Write the received data byte to EEPROM at given address
	}
}
