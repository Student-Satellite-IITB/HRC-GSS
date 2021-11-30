#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2C.h"

void I2CInit()
{
	TWBR=0x01;					//Set bit rate for TWI
	TWSR=0x00;					//Set Prescaler bits
	TWCR = (1 << TWEN) | (1 << TWIE);
}

void I2CTransmitData(uint8_t deviceAddress, uint8_t firstWordAddress, uint8_t secWordAddress, uint8_t data, int rw)
{
	I2CSendStart();
	while((TWSR & 0xF8)!= 0x08);
	TWDR=deviceAddress;
	I2CSendData();
	while((TWSR & 0xF8)!= 0x18);
	TWDR=firstWordAddress;
	I2CSendData();
	while((TWSR & 0xF8)!= 0x28);
	TWDR=secWordAddress;
	I2CSendData();
	while((TWSR & 0xF8)!= 0x28);
	if(rw==0)
	{
		TWDR=data;
		I2CSendData();
		while((TWSR & 0xF8)!= 0x28);
		I2CSendStop();
	}
	else
	{
		return;
	}
}

uint8_t I2CReceiveData(uint8_t deviceAddress)
{
	uint8_t dataByte;
	I2CSendStart();
	while(((TWSR & 0xF8)!= 0x08) || ((TWSR & 0xF8)!= 0x10));
	TWDR=deviceAddress;
	I2CSendData();
	while((TWSR & 0xF8)!= 0x40);
	I2CSendNACK();
	while((TWSR & 0xF8)!=0x58);
	dataByte=TWDR;
	I2CSendStop();
	return dataByte;
}

void I2CSendStart()
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

void I2CSendData()
{
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

void I2CSendStop()
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

void I2CSendNACK()
{
	TWCR= (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}