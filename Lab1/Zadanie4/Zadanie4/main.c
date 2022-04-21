/*
 * Zadanie4.c
 *
 * Created: 21.04.2022 13:15:40
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
		PORTA|=0b00010000;
		_delay_ms(100);
		PORTA|=0b00110000;
		_delay_ms(100);
		PORTA|=0b01110000;
		_delay_ms(100);
		PORTA|=0b11110000;
		_delay_ms(100);
		
		PORTA&=0b00001111;
		_delay_ms(100);
		
		PORTA|=0b00001000;
		_delay_ms(100);
		PORTA|=0b00001100;
		_delay_ms(100);
		PORTA|=0b00001110;
		_delay_ms(100);
		PORTA|=0b00001111;
		_delay_ms(100);
		
		PORTA&=0b11110000;
		_delay_ms(100);
    }
}

