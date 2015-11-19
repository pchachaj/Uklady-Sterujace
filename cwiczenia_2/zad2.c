/*
 * GccApplication1.c
 *
 * Created: 2015-11-18 18:11:34
 *  Author: Administrator
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void setup()
{
	DDRD = 0;
	DDRB = 0xff;
	PORTD = 3;
	TCCR0 = (1 << WGM01) | (1 << WGM00) | (1 << COM01) | (1 << CS01);
	TCNT0 = 0;
	OCR0 = 0;
}

int main(void)
{
	setup();
    while(1)
	{
		if(!(PIND & 1))
			OCR0++;		
		
		if(!(PIND & 2))
			OCR0--;	
			
		_delay_ms(10);	
	}
}