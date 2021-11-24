#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "AD9833.h"
#include "PD90.h"
#include "spi.h"
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	sei();
    SSTVInit();
	SSTVBegin();
	while(1);
}