/*
 * Cw1.c
 *
 * Created: 2015-11-04 18:11:46
 *  Author: Administrator
 */ 

#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>

void setup()
{
	DDRA = 0xFF;
	DDRB = 0x01;
	
}


void zad1()
{
	PORTA = 1;
	int8_t go_right = 1;
	while(1)
	{
		if(go_right)
		{
			PORTA = PORTA*2;
		}
		else
		{
			PORTA = PORTA/2;
		}
		
		_delay_ms(400);
		
		if(PORTA == 0x80)
		{
			go_right = 0;
		}
		else if(PORTA == 0x01)
		{
			go_right = 1;
		}
	}
}


unsigned long light_time(unsigned long delay, uint8_t brightnes)
{
	return delay*brightnes/400;
}

void zad2()
{
	unsigned long full_delay = 20;
	uint8_t brightnes = 0;
	uint8_t rise = 1;
	
	while(1)
	{
		PORTA = 1;
		_delay_ms(light_time(full_delay, brightnes));
		
		PORTA = 0;
		_delay_ms(full_delay - light_time(full_delay, brightnes));
		
		brightnes += rise;
		if(brightnes == 400 || brightnes == 0)
		{
			rise = -rise;
		}
	}
	// a = 1 | 2 = 3
}

void zad3()
{
	uint8_t[] tab = {};
}

int main(void)
{
	setup();
    
	zad2();
}