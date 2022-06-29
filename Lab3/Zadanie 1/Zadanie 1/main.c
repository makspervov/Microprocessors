/*
 * Zadanie 1.c
 *
 * Created: 05.05.2022 12:27:24
 * Author : mpervov
 */ 
# define F_CPU 1000000UL
# include <avr/io.h>
# include <util/delay.h>

void timer10ms()
{
	while(!(TIFR & (1 << OCF0))){};
	TIFR |= _BV(OCF0);
}

void czas_1s()
{
	for(uint8_t i = 0; i <100; i++)
	{
		timer10ms();
	}
}

int main(void)
{
	OCR0 = 40;
	DDRA = 0x01;
	PORTA = 0x00;
	TCCR0 |= _BV(CS02) | _BV(WGM01);
	
    while (1) 
    {
		PORTA ^= _BV(PA0);
		czas_1s();
    }
}

