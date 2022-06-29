/*
 * Zadanie1.c
 * Created: 26.05.2022 12:39:04
 * Author : Maksym Pervov
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect){			//definiowanie obs?ugi przerwa? z wektorem INT0
	PORTA ^= 1 << PA0;	//negowanie diody na linii 0
}
	
ISR(INT2_vect){			//definiowanie obs?ugi przerwa? z wektorem INT2
	PORTA ^= 1 << PA2;	//negowanie diody na linii 2
}

int main(void)
{
	uint8_t tmp;		//definiowanie przemiennej tmp
	DDRA = 1 << PA0 | 1 << PA2;	//PA0 i PA2 na wyj?cie
	DDRB = 0xFF;		//obs?ugiwanie PB2 dla INT2
	PORTB = 0xFF;
	DDRD = 0xFF;		//obs?ugiwanie PD2 dla INT0
	PORTD = 0xFF;
	
	tmp = MCUCR;		//zapisywanie stanu rejestru do pami?ci
	tmp &= ~(1 << ISC00) | (1 << ISC00);	//konfiguracja przerwania INT0 dla zbocza opadaj?cego
	//tmp |= 1 << ISC01 | 1 << ISC00;		//konfiguracja przerwania INT0 dla zbocza narastaj?cego
	MCUCR = tmp;
	
	MCUCSR &= ~(1 << ISC2);		//konfiguracja przerwania INT2 dla zbocza opadaj?cego
	//MCUCSR |= 1 << ISC2;		//konfiguracja przerwania INT2 dla zbocza narastaj?cego
	
	GICR |= 1 << INT0 | 1 << INT2;		//zezwolenie na przerwania dla PB2 i PD2
	GIFR |= 1 << INTF0 | 1 << INTF2;	//ustawianie flag?w w przypadku zewn?trznego przerwania 
	sei();				//inicjalizacja obs?ugi przerwa? 
	
    while (1){}
}

