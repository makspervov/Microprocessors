/*
 * Zadanie3.c
 *
 * Created: 21.04.2022 12:50:11
 * Author : mpervov
 */ 
#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRA=0xFF;
    while (1) 
    {
		PORTA|=0b10000000;
		_delay_ms(1000);
		PORTA|=0b11000000;
		_delay_ms(1000);
		PORTA|=0b11100000;
		_delay_ms(1000);
		PORTA|=0b11110000;
		_delay_ms(1000);
		PORTA|=0b11111000;
		_delay_ms(1000);
		PORTA|=0b11111100;
		_delay_ms(1000);
		PORTA|=0b11111110;
		_delay_ms(1000);
		PORTA|=0b11111111;
		_delay_ms(1000);
		PORTA&=0b00000000;
    }
}

