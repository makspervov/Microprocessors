/*
 * Zadanie2.c
 *
 * Created: 28.04.2022 12:58:22
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
		0b00000011,			//wyswietlanie cyfry 0
		0b10011111,			//wyswietlanie cyfry 1
		0b00100101,			//wyswietlanie cyfry 2
		0b00001101,			//wyswietlanie cyfry 3
		0b10011001,			//wyswietlanie cyfry 4
		0b01001001,			//wyswietlanie cyfry 5
		0b01000001,			//wyswietlanie cyfry 6
		0b00011111,			//wyswietlanie cyfry 7
		0b00000001,			//wyswietlanie cyfry 8
		0b00001001			//wyswietlanie cyfry 9
	};
	
	//int czas;
	
    while (1) 
    {
		for (uint8_t i = 2; i<=142; i+=7)		//wyswietlanie znakow od 2 do 142
		{
			for (uint8_t j = 0; j < 125; j++)	//petla stworzona dla poprawnego wyswietlania lizcb
			{
				if (i<10)						//liczby jednocyfrowe
				{	
					PORTB = ~_BV(3);
					PORTA = tab[i];
					_delay_ms(4);
				}
			
				else if (i >= 10 && i < 100)	//liczby dwocyfrowe
				{
					PORTB = ~_BV(3);
					PORTA = tab[i%10];
					_delay_ms(2);
					
					PORTB = ~_BV(2);
					PORTA = tab[i/10];
					_delay_ms(2);
				}
			
				else							//liczby trzycyfrowe
				{
					PORTB = ~_BV(3);
					PORTA = tab[i%10];
					_delay_ms(1);
				
					PORTB = ~_BV(2);
					PORTA = tab[(i / 10) % 10];
					_delay_ms(1);
				
					PORTB = ~_BV(1);
					PORTA = tab[1];				//lub PORTA = tab[i/100];
					_delay_ms(2);
				}
			}
		}
    }
	return 0;
}



