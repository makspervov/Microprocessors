#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#define F_CPU 1000000L

#define LCD_DDR DDRB
#define LCD_PORTA PORTB
#define LCD_RS 2
#define LCD_EN 3
#define LCD_DB4 4
#define LCD_DB5 5
#define LCD_DB6 6
#define LCD_DB7 7

void wypisz(uint8_t b)
{
	LCD_PORTA |=_BV(LCD_EN);
	LCD_PORTA = (b & 0xF0)|(LCD_PORTA & 0x0F);
	LCD_PORTA &= ~(_BV(LCD_EN));
	asm volatile("nop");
	LCD_PORTA |= _BV(LCD_EN);
	LCD_PORTA = ((b & 0x0F)<<4)|(LCD_PORTA & 0x0F);
	LCD_PORTA &= ~(_BV(LCD_EN));
	_delay_ms(50);
}

void LCDclear()
{
	LCD_PORTA &= ~(_BV(LCD_RS));
	wypisz(0x01);
	LCD_PORTA |= _BV(LCD_RS);
	_delay_ms(60);
}

void inicjalizacjaLCD()
{
	LCD_DDR = (0xF0)|(_BV(LCD_RS))|(_BV(LCD_EN));
	LCD_PORTA = 0;
	LCD_PORTA &= ~(_BV(LCD_RS));
	
	wypisz(0b00101000);
	LCD_PORTA |= _BV(LCD_RS);
	LCD_PORTA |= _BV(LCD_RS);

	wypisz(0b00000110);
	LCD_PORTA |= _BV(LCD_RS);
	LCD_PORTA &= ~(_BV(LCD_RS));

	wypisz(0b00001100);
	LCD_PORTA |= _BV(LCD_RS);

	LCDclear();
}

set_kursor_LCD(unsigned char w, unsigned char h)
{
	LCD_PORTA &= ~(_BV(LCD_RS));
	wypisz((w*0x40+h)|0x80);
	LCD_PORTA |= _BV(LCD_RS);
	_delay_ms(5);
}

void napisz(char *tekst, int8_t dlugosc)
{
	int8_t i=0;
	set_kursor_LCD(0,0);
	while (i<dlugosc)
	{
		if(i==16)
		{
			set_kursor_LCD(1,0);
		}
		wypisz(tekst[i]);
		i++;
	}
}

void LCDclear_y(unsigned char k, unsigned char l)
{
	set_kursor_LCD(k,l);
	while (k<=16)
	{
		wypisz(' ');
		k++;
	}
}


void zadanie1()
{
	char tekst[]={'H','e','l','l','o',' ','w','o','r','l','d',' ','H','E','L','L','O','!','!','!'};
	inicjalizacjaLCD();
	napisz(tekst,20);
	LCDclear_y(0,5);
}

void zadanie3()
{
	char symbol1[]={'M','O','N','D','A','Y'};
	char symbol2[]={'T','U','E','S','D','A','Y'};
	char symbol3[]={'W','E','D','N','E','S','D','A','Y'};
	inicjalizacjaLCD();
	while(1)
	{
		napisz(symbol1,6);
		_delay_ms(400);
		LCDclear();
		napisz(symbol2,7);
		_delay_ms(400);
		LCDclear();
		napisz(symbol3,9);
		_delay_ms(400);
		LCDclear();
	}

}

int main(void)
{
	zadanie1();
	//zadanie3();
	while (1)
	{
	}
}