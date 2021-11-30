#include <avr/io.h>

/* Initializes TWI registers to set microcontroller as master
*/
void I2CInit();

/* Sends data byte to EEPROM for storage at given address
* 
* Parameters
* deviceAddress			Address of EEPROM in which data is to be stored
* firstWordAddress		Word address byte 1
* secWordAddress		Word address byte 2
* data					8 bit data to be stored
* rw					Operation to be performed: 0-write, 1-read
*/
void I2CTransmitData(uint8_t deviceAddress, uint8_t firstWordAddress, uint8_t secWordAddress, uint8_t data, int rw);

/* Sends data in TWI data register from microcontroller to EEPROM
*/
void I2CSendData();

/* Generates Start condition for TWI
*/
void I2CSendStart();

/* Generated stop condition for TWI
*/
void I2CSendStop();

/* Sends NACK when data byte has been received from EEPROM
*/
void I2CSendNACK();

/* Returns data byte received from EEPROM
*
* Parameter
* deviceAddress			Address of EEPROM in which data is to be stored
*/
uint8_t I2CReceiveData(uint8_t deviceAddress);