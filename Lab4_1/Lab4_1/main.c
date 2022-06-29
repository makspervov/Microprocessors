/*
 * Lab4_1.c
 *
 * Created: 12.05.2022 12:25:18
 * Author : Maksym
 */ 

#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>

void getkey()
{
	uint8_t i, x, sk;
	uint8_t dt = 0;
	for(i = 4; i < 8; i++)
	{
		PORTB = ~_BV(i); // wprowadz 0 na i-tej pozycji i 1 na innych pozycjach
		_delay_ms(1);
		sk = PINB;
		
		if (sk == 0xFF)
		{
			PORTA = 0xFF;
			break;
		}
		
		x=PINB&0x0F; // odczytaj i zapamietaj stan klawiatury
		if (x == (PINB&0x0F))
		{
			switch(x)
			{
				case 0x00001111:{
					 PORTA = 0;
					 break;
				}
		
				case 0x00001110{
					dt++;
					PORTA = i - 3;
					break;
				}
			
				case 0x00001101:{
					dt++;
					PORTA = i + 1;
					break;
				}
			
				case 0x00001011:{
					PORTA = i + 5;
					break;
				}
			
				case 0x00000111:{
					PORTA = i + 9;
					break;
				}			
				default: {break;}
			}	
			if (dt > 1){PORTA = 0xFF;}
		}
	}
}

int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x00;		//konfiguracja diod (zrobyv i nie trogaj!!!)
	
	DDRB = 0xF0;
	PORTB = 0x0F;		//konfiguracja klawiatury (zrobyv i nie trogaj!!!)
	while (1)
	{
		getkey();
	}
}

