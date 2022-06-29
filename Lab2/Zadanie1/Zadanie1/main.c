/*
 * Zadanie1.c
 *
 * Created: 28.04.2022 12:25:47
 * Author : Student_PL
 */ 
#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


int main(void)
{
    DDRA=0xFF;
	DDRB=0x0F;
	
	unsigned char tab[10] = 
	{
		0b00000011,			//0
		0b10011111,			//1
		0b00100101,			//2
		0b00001101,			//3
		0b10011001,			//4
		0b01001001,			//5
		0b01000001,			//6
		0b00011111,			//7
		0b00000001,			//8
		0b11110110			//9
	};
	
    while (1) 
    {
		//Rok urodzenia - 2003
		PORTB = ~_BV(0);	// ustawienie pierwszej kolumny
		PORTA = tab[2];		// ustawienie liczby 2
		_delay_ms(2);
		
		PORTB = ~_BV(1);	// ustawienie drugiej kolumny
		PORTA = tab[0];		// ustawianie liczby 0
		_delay_ms(2);
		
		PORTB = ~_BV(2);	// ustawienie trzeciej kolumny
		PORTA = tab[0];		// ustawianie liczby 0
		_delay_ms(2);
		
		PORTB = ~_BV(3);	// ustawienie czwartej kolumny
		PORTA = tab[3];		// ustawianie liczby 3
		_delay_ms(2);
    }
	return 0;
}

