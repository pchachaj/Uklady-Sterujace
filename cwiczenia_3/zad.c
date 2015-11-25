/*
 * GccApplication1.c
 *
 * Created: 2015-11-25 18:13:57
 *  Author: Administrator
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>

uint8_t digits[] = 
{
	///kgfedcba
	~0b00111111, //0
	~0b00000110, //1
	~0b01011011, //2
	~0b01001111, //3
	~0b01100110, //4
	~0b01101101, //5
	~0b01111101, //6
	~0b00000111, //7
	~0b01111111, //8
	~0b01101111 
};
uint16_t time = 0;
uint16_t ms = 0;

void zad1()
{ 
	DDRA=0xff;
	DDRC=0xff;

	PORTC=~0b00000000;
	while(1)
	{
		for(int i=0; i<4; i++)
		{
			PORTC = ~(1 << i);
			PORTA = digits[i];
			_delay_ms(1);
		}
	}
}

void display_number(uint16_t number, uint16_t idx)
{
	if(number > 9999)
		return;

	PORTC = ~(1 << idx);
	uint16_t digit = (number / (uint16_t)pow(10, idx)) % 10;
	PORTA = digits[digit];
}

void zad2()
{
	DDRA=0xff;
	DDRC=0xff;

	PORTC=~0b00000000;
	while(1)
	{
		display_number(time, ms%4);
		_delay_ms(1);
		++ms;
		if(ms>=1000)
		{
			ms = 0;
			++time;
		}
		if (time == 9999)
			time = 0;
	}
}

ISR(TIMER0_COMP_vect)
{
	display_number(time,ms%4);
	++ms;
	if(ms == 1000)
	{
		ms = 0;
		++time;
	}
}

void zad3()
{
	DDRA=0xff;
	DDRC=0xff;

	PORTC=~0b00000000;

	TIMSK |= (1 << OCIE0);
	TCCR0 |= (1 << WGM01) | (1 << CS00) | (1 << CS01);
	OCR0=250;
	sei();
	while(1) { }
}

int main(void)
{
	zad3();
}
