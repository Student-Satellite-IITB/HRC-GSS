#include <avr/io.h>
#include "AT24C256.h"
#include "I2C.h"

void eepromWriteByte(uint8_t* deviceAddress, uint8_t* wordAddress1, uint8_t* wordAddress2, uint8_t dataByte)
{
	I2CTransmitData(*deviceAddress, *wordAddress1, *wordAddress2, dataByte, 0);					//Send data byte to current location in EEPROM
	
	if(*wordAddress2==255)										//Check whether second word address byte is 0xFF, meaning 255 data bytes have been written, hence first word address bytes needs to be changed
	{
		*wordAddress2=0;										//Reset second word address byte
		*(wordAddress1)=*(wordAddress1)+1;									//Increment first word address byte by 1
	}
}

uint8_t eepromReadByteRandom(uint8_t* deviceAddress, uint8_t* wordAddress1, uint8_t* wordAddress2)
{
	uint8_t slaveAddress=*deviceAddress & 0xFE;									//Set slave address for initial dummy write to EEPROM
	I2CTransmitData(*deviceAddress, *wordAddress1, *wordAddress2, 0, 1);					//Send initial dummy write to EEPROM
	uint8_t dataByte=I2CReceiveData(*deviceAddress);								//Receive data byte from EEPROM using I2C
	return dataByte;
}

uint8_t eepromReadByteCurrentAddress(uint8_t* deviceAddress)
{
	uint8_t dataByte=I2CReceiveData(*deviceAddress);						//Receive data byte from address already stored in EEPROM
	return dataByte;
}