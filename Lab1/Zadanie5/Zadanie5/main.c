/*
 * Zadanie5.c
 *
 * Created: 21.04.2022 13:29:07
 * Author : Student_PL
 */ 
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRA=0xFF;
    while (1) 
    {
		PORTA|=0b10000000;
		_delay_ms(100);
		PORTA|=0b11000000;
		_delay_ms(100);
		PORTA|=0b11100000;
		_delay_ms(100);
		PORTA|=0b11110000;
		_delay_ms(100);
		
		PORTA&=0b00001111;
		_delay_ms(100);
		
		PORTA|=0b00000001;
		_delay_ms(100);
		PORTA|=0b00000011;
		_delay_ms(100);
		PORTA|=0b00000111;
		_delay_ms(100);
		PORTA|=0b00001111;
		_delay_ms(100);
		
		PORTA&=0b11110000;
		_delay_ms(100);
    }
}

