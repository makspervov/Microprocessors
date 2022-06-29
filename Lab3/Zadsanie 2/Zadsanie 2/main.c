/*
 * Zadsanie 2.c
 *
 * Created: 05.05.2022 13:11:37
 * Author : Student_PL
 */ 
# define F_CPU 1000000UL
# include <avr/io.h>
# include <util/delay.h>


int main(void)
{
	TCCR0 |= _BV(CS02) | _BV(CS01);		
	PORTB = 0x01;		
			
	DDRA = 0x01;
	PORTA = 0x01;
	
    while (1) 
    {
		TCCR0 &= ~(_BV(CS02) | _BV(CS01) | _BV(CS00));
		while(!(TIFR & _BV(TOV0)))
		{
			PORTA = TCNT0;
			_delay_ms(200);
		}
    }
}

