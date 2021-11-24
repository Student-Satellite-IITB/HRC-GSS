/*
 * AD9833.c
 *
 * Created: 25-09-2018 14:03:29
 *  Author: Puneet Shrivas
 */ 
#include <math.h>
#include "AD9833.h"
#include "spi.h"


/*  Sends frequency and phase of wave to AD9833 for transmission
* 
* Parameters
* frequency      Frequency of wave to be transmitted
* phase          Phase of wave to be transmitted
*/
void setAD9833(float frequency, unsigned int phase) // Zero amplitude time : 39 microseconds
{
	long frequencyRegister = (((float)frequency)*pow(2,28))/(float)FMCLK;	  //Calculate frequency to be sent to AD9833
	int MSB = (int)((frequencyRegister &  0xFFFC000) >> 14);				  //Extract first 14 bits of FreqReg and place them at last 14 bits of MSB
	int LSB = (int)((frequencyRegister & 0x3FFF));						  //Extract last 14 bits of FreqReg and place them at last 14 bits of MSB
	MSB|=0x4000;												  //Set D14,D15 = (1,0) for using FREQ0 registers, MSB has all 16 bits set
	LSB|=0x4000;     											  //Set D14,D15 = (1,0) for using FREQ0 registers, LSB has all 16 bits set
	SPI_send16(0x2100);											  //Define waveform and set reset bit
	SPI_send16(LSB);											  //Write LSBs
	SPI_send16(MSB);											  //Write MSBs
	phase&=0x0FFF;
	phase|=0xC000;												  //Set Phase write enable bytes
	//SPI_write16(0xC000);										  //Mode selection for writing to phase register bit, selection of PHASE0 register (Needs to be fixed)
	SPI_send16(phase);											  //Write Phase bytes
	SPI_send16(0x2000);											  //Unset reset bit
}


/* Returns phase of next wave from parameters of previous wave
* 
* Parameters
* prevPhase      Starting phase of previous wave
* prevFreq       Frequency of previous wave
* prevTime       Time duration of previous wave
*/
unsigned int getphase(float prevPhase,float prevFreq, float prevTime)
{
	prevTime/=1000000;																	//Convert time to microseconds
	prevPhase/=2048/PI;																	//Change scaling of Phase as required by AD9833
	float returnPhase=((fmod(prevTime,(1/prevFreq))*2*PI*prevFreq)+prevPhase)*2048/PI;	//Calculate phase completed by previous wave
	return (unsigned int) returnPhase;													//Return in 16 bit format
}