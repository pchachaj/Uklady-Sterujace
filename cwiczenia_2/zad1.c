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

uint8_t count = 0;

ISR(INT0_vect)
{
	++count;
	PORTA = PORTA & 0b10000000;
	PORTA = (count << 1) | PORTA;
}

void setup()
{
	DDRA = 0xff;
	DDRD = 0;
	PORTD |= (1 << PD2);
	MCUCR |= (1 << ISC01) | (1 << ISC00);
	GICR |= (1 << INT0);	
	sei();
}

void blink()
{
	while(1)
	{
		PORTA ^= 1;
		_delay_ms(400);
	}
}

int main(void)
{
	setup();
    blink();
}