/*
 * Zadanie3.c
 *
 * Created: 28.04.2022 13:49:08
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
	srand(time(NULL));
	
	unsigned char tab[4] = 
	{
		0b11000110,			//wyswietlanie kwadratu na gorze
		0b00111010,			//wyswietlanie kwadratu na dolu
		0b10011110,			//wyswietlanie litery E
		0b11110010			//wyswietlanie cyfry 3
	};
    
    while (1) 
    {
		for (uint8_t i = 0; i < 4; i++)		//petla sluzy do wyswietlania znaku kolejowo
		{
			PORTB = ~_BV(i);				//ustawianie kolumny po kolei
			PORTA = ~(tab[rand()%2]);		//ustawianie z czterech zapisanych znakow dwa znaki
			_delay_ms(500);
			}
    }
}

