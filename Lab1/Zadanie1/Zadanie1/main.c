/*
 * Zadanie1.c
 *
 * Created: 21.04.2022 12:12:29
 * Author : mpervov
 */ 
#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif
#include <avr/io.h>
#include <util/delay.h>

void seven_to_zero{
		PORTA|=0b11000000;
		_delay_ms(500);
		PORTA&=0b01111111;
		_delay_ms(500);
		
		PORTA|=0b01100000;
		_delay_ms(500);
		PORTA&=0b10111111;
		_delay_ms(500);
		
		PORTA|=0b00110000;
		_delay_ms(500);
		PORTA&=0b11011111;
		_delay_ms(500);
		
		PORTA|=0b00011000;
		_delay_ms(500);
		PORTA&=0b11101111;
		_delay_ms(500);
		
		PORTA|=0b00001100;
		_delay_ms(500);
		PORTA&=0b11110111;
		_delay_ms(500);
		
		PORTA|=0b00000110;
		_delay_ms(500);
		PORTA&=0b11111011;
		_delay_ms(500);
		
		PORTA|=0b00000011;
		_delay_ms(500);	
		PORTA&=0b11111110;
		_delay_ms(1000);
}
	
void zero_to_seven{
		PORTA|=0b00000110;
		_delay_ms(1000);
		PORTA&=0b11111101;
		_delay_ms(1000);
		
		PORTA|=0b00001100;
		_delay_ms(1000);
		PORTA&=0b11111011;
		_delay_ms(1000);
		
		PORTA|=0b00011000;
		_delay_ms(1000);
		PORTA&=0b11110111;
		_delay_ms(1000);
		
		PORTA|=0b00110000;
		_delay_ms(1000);
		PORTA&=0b11101111;
		_delay_ms(1000);
		
		PORTA|=0b01100000;
		_delay_ms(1000);
		PORTA&=0b11011111;
		_delay_ms(1000);
		
		PORTA|=0b11000000;
		_delay_ms(1000);
		PORTA&=0b10111111;
}

int main(void)
{
	DDRA=0xFF;
    while (1) 
    {
		zero_to_seven();
		seven_to_zero();
    }
}

