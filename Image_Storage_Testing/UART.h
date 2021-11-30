#include <avr/io.h>

volatile uint8_t data8bit;					//8 bit data to be received from PC

/* Initializes the UART registers for receiving data with baud rate=9600
*/
void setUART();

/* Returns the 8 bit data received from PC
*/
uint8_t UARTReceive();