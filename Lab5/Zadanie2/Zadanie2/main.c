/*
 * Zadanie2.c
 *
 * Created: 26.05.2022 13:46:57
 * Author : Student_PL
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int n;

ISR(TIMER0_COMP_vect){
	if(n == 10){
		PORTA ^= 1 << PA0;
		n = 0;
	}
	PORTA ^= 1 << PA2;
	n++;
}


int main(void)
{
	DDRA = 0xFF;
	
	TCCR0 |= (1 << WGM01)|(1 << CS02)|(1 << CS00);
	TIMSK |= (1 << OCIE0);
	OCR0 = 97;
	
	GICR |= 1 << INT0 | 1 << INT2;
	GIFR |= 1 << INTF0 | 1 << INTF2;
	sei();
	
    while (1){}
}

