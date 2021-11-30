#include <avr/io.h>


/* Writes 8 bit data into the EEPROM at given address
*
* Parameters
* deviceAddress				Device address byte of EEPROM
* wordAddress1				First word address byte of EEPROM
* wordAddress2				Second word address byte of EEPROM
* dataByte					8 bit data to be sent to EEPROM
*/
void eepromWriteByte(uint8_t* deviceAddress, uint8_t* wordAddress1, uint8_t* wordAddress2, uint8_t dataByte);

/* Read data byte using random read method of EEPROM
*
* Parameters
* deviceAddress			Address of EEPROM from which data is to be received
* firstWordAddress		Word address byte 1
* secWordAddress		Word address byte 2
*/
uint8_t eepromReadByteRandom(uint8_t* deviceAddress, uint8_t* wordAddress1, uint8_t* wordAddress2);

/* Read data byte using Current Address read method of EEPROM
*
* Parameter
* deviceAddress			Address of EEPROM from which data is to be received
*/
uint8_t eepromReadByteCurrentAddress(uint8_t* deviceAddress);