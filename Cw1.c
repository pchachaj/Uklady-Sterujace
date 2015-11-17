/*
Karol Jurek
Pawel Chahaj
*/

#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>

/* Zadanie 1: Zmusic diode do mrugania co jedna sekunde */
void zad1()
{
	while(1)
	{
		PORTA = 0b10000000;
		_delay_ms(1000);
		PORTA = 0;
		_delay_ms(1000);
	}
}

/* Zadanie 2. Zaswiecic diody po przycisniecu przycisku PIN0 */
void zad2()
{
	PORTA = 0;	
	PORTB = 1;
	
	while(1)
	{
		if (PINB & 1)
			PORTA = 255;
		else
			PORTA = 0;
	}
}

/* Zadanie 3. Mruganie diodami w formie weza (1-diodowy) */
void zad3()
{
	PORTA = 0b10000000;
	int8_t go_right = 1;
	while(1)
	{
		if(go_right)
			PORTA = (PORTA >> 1);
		else
			PORTA = (PORTA << 1);
		
		_delay_ms(1000);
		
		if(PORTA == 0b10000000)
			go_right = 1;
		else if(PORTA == 0b00000001)
			go_right = 0;
	}
}

/* Zadanie 4 Przygasanie diod */
unsigned long light_time(unsigned long delay, uint8_t brightnes)
{
	return delay * brightnes / 400;
}

void zad4()
{
	unsigned long full_delay = 20;
	uint8_t brightnes = 0;
	uint8_t rise = 1;
	while(1)
	{
		PORTA = 255;
		_delay_ms(light_time(full_delay, brightnes));
		
		PORTA = 0;
		_delay_ms(full_delay - light_time(full_delay, brightnes));
		
		brightnes += rise;
		if(brightnes == 200 || brightnes == 0)
			rise = -rise;
	}
}

/* Zadanie 5 Fala */
void zad5()
{
	unsigned long full_delay = 30;
	uint8_t brightnes = 0;
	uint8_t rise = 1;
	PORTA = 0b10000000;
	uint8_t pin;
	
	while(1)
	{
		pin = PORTA;		
		_delay_ms(light_time(full_delay, brightnes));
		PORTA = 0;			
		_delay_ms(full_delay - light_time(full_delay, brightnes));
		PORTA = pin;
		
		brightnes += rise;
		if (brightnes == 200)
		{
			rise = -rise;						
		} else if(brightnes == 0) {
			PORTA = (PORTA >> 1);
			rise = -rise;						
		}	
	}
}

int main(void)
{
	DDRA = 0xff;
	DDRB = 0;
	//zad1();
	//zad2();
	//zad3();
	//zad4();
	zad5();
}
