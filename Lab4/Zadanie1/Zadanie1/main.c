/*
 * Zadanie1.c
 *
 * Created: 19.05.2022 12:11:28
 * Author : Student_PL
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void getkey()
{
	uint8_t x, sk;		//inicjalizacja zmiennych x i sk
	uint8_t dt = 0;		//zmienna sluzy do obslugi nacisniec wiecej niz jeden przycisk
	for (uint8_t i = 4; i < 8; i++)
	{
		PORTA= ~_BV(i); // wprowadz 0 na i-tej pozycji i 1 na innych pozycjach
		_delay_ms(1);	//opoznienie co 1 ms
		sk = PINA;		//odczyt stanu klawiatury
		if(sk == 0xFF)	//sprawdzanie stanu klawiatury
		{
			PORTB = 0xFF;	//jesli nacisnieto 2 i wiecej przyciskow niech wszystkie diody zaswieca
			break;
		}
		_delay_ms(1);	//opoznienie co 1 ms
		x=PINA&0x0F;	// odczyt i zapamietowanie stanu klawiatury
		if (x == (PINA&0x0F))//petla if eliminujaca mozliwosc wystapienia drgania stykow
		{
			switch(x)	//petla switch zalezna od zmiennej x, w ktorej znajduje sie odczytany stan klawiatury
			{
				case 0b00001111:	//jesli zaden przycisk nie jest wcisniety
				{
					PORTB=0;		//zaden diod nie swieci
					break;
				}
		
				case 0b00001110:	//jesli wcisnieto przycisk z wiersza 1
				{
					dt++;			//inkrementacja zmiennej dt
					PORTB = i-3;	//zaswiecenie numeru przyciska w postaci binarnej (od 1 do 4)
					break;
				}
			
				case 0b00001101:	//jesli wcisnieto przycisk z wiersza 2
				{
					dt++;			//inkrementacja zmiennej dt
					PORTB = i+1;	//zaswiecenie numeru przyciska w postaci binarnej (od 5 do 8)
					break;
				}
			
				case 0b00001011:	//jesli wcisnieto przycisk z wiersza 3
				{
					dt++;			//inkrementacja zmiennej dt
					PORTB = i+5;	//zaswiecenie numeru przyciska w postaci binarnej (od 9 do 12)
					break;
				}
				
				case 0b00000111:	//jesli wcisnieto przycisk z wiersza 4
				{
					dt++;			//inkrementacja zmiennej dt
					PORTB = i+9;	//zaswiecenie numeru przyciska w postaci binarnej (od 13 do 16)
					break;
				}
				
				default:			//jesli zadna instrukcja nie byla wykonana, znaczy to, ze wcisnieto dwa i wiecej przyciski
				{
					PORTB = 0xFF;	//zaswiecenie wszystkich diod
					break;
				}
			}
			if (dt > 1)				// jesli podczas wykonania instrukcji case wartosc dt jest wiecej niz 1, znaczy to, ze wcisnieto dwa i wiecej przyciski 
			{
				PORTB = 0xFF;		//zaswiecenie wszystkich diod
			}
		}
	}
}

int main(void)
{
	DDRA = 0xF0;	//ustawienie 4 najmlodszych bitow na wejscia i 4 najstarszych na wyjscia
	PORTA = 0x0F;	//ustawienie 4 najmlodszych bitow na wejscia podciagniete i 4 najstarszych na 0
	
	DDRB = 0xFF;	//ustawianie kierunku danych dla diod na wyjscie
	PORTB = 0x00;	//ustawianie wszystkich diod na 0
	
    while (1) 
    {
		getkey();	// wywolanie funkcji getkey()
    }
}

