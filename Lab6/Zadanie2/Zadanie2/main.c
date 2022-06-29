#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#define F_CPU 1000000L

#define LCD_DDR DDRB
#define LCD_PORT PORTB
#define LCD_RS 2
#define LCD_EN 3
#define LCD_DB4 4
#define LCD_DB5 5
#define LCD_DB6 6
#define LCD_DB7 7

volatile uint8_t t = 0;
volatile uint8_t liczba = 0;
volatile uint8_t newLiczba = 0;
volatile uint8_t newLiczba1 = 0;

void LCD_send(uint8_t b){ //funckja komend
	LCD_PORT |= _BV(LCD_EN); //zezwalamy komunikajce z LCD
	LCD_PORT = (b & 0xF0)|(LCD_PORT & 0x0F);//wysy?amy 4 starsze bity
	LCD_PORT &= ~(_BV(LCD_EN));//m?wimy, ?e b?dziemy wysy?ali dane
	asm volatile("nop"); //jeden cykl mikroproc.
	LCD_PORT |= _BV(LCD_EN); //zezwalamy komunikajce z LCD
	LCD_PORT = ((b & 0x0F) << 4)|(LCD_PORT & 0x0F);//wysy?amy 4 m?odsze bity
	LCD_PORT &= ~(_BV(LCD_EN));//m?wimy, ?e b?dziemy wysy?ali dane
	_delay_ms(50);
}

void clearLCD(){
	LCD_PORT &= ~(_BV(LCD_RS));
	LCD_send(0x01); //rejestr 0x01 - wyczy?? tekst z LCD
	LCD_PORT |= _BV(LCD_RS); //zapisujemy dane
	_delay_ms(60);
}

void LCDinit(){
	LCD_DDR = (0xF0)|(_BV(LCD_RS))|(_BV(LCD_EN));
	LCD_PORT = 0; //wyzerowanie portu
	LCD_PORT &= ~(_BV(LCD_RS));//dajemy komende
	LCD_send(0b00101000); //inicjalizuj 4-bitowy tryb + 2 linie 5*7 macierz
	LCD_PORT |= _BV(LCD_RS);
	LCD_PORT |= _BV(LCD_RS);
	LCD_send(0b00000110); //inicjalizuj przesuni?cie kursora w prawo
	LCD_PORT |= _BV(LCD_RS);
	LCD_PORT &= ~(_BV(LCD_RS));
	LCD_send(0b00001100); //wy?wietlaj przy wy?aczonym kursorze
	LCD_PORT |= _BV(LCD_RS); //m?wimy, ?e b?dziemy zapisywali dane
	clearLCD();
}

void setCursor(unsigned char w, unsigned char h)
{
	LCD_PORT &= ~(_BV(LCD_RS));//m?wimy, ?e podajemy komend?
	LCD_send((w*0x40+h)|(0x80));//0x80 - 1 linia, 0x40 - tej 1/2 linii
	LCD_PORT |= _BV(LCD_RS); //m?wimy, ?e podajemy dane
	_delay_ms(5);
}

void write(char *text, int8_t lenght){
	int8_t i = 0;
	setCursor(0,0); //ustawiamy kursor na pocz?tek
	while (i < lenght){//czy?cimy na pozycji i
		if(i==16){ //jezeli tekst wiekszy od 16
			setCursor(1,0); //ustawiamy na poczatek pierwszej linijki
		}
		LCD_send(text[i]); 
		i++;
	}
}

void LCDclear_y(unsigned char lenght, unsigned char n){
	setCursor(lenght, n);
	while (lenght<=16)
	{
		LCD_send(' ');
		lenght++;
	}
}

void wypiszCyfre(uint8_t cyfra)
{
	setCursor(2, 7);
	if (cyfra > 9)
	{
		LCD_send('1');
		cyfra -= 10;
	}
	LCD_send(cyfra+'0');
}

void getkey()
{
	char x;
	while(1)
	{
		for (uint8_t i = 4; i < 8; i++)
		{
			PORTA= ~_BV(i);
			_delay_ms(1);
			x=PINA&0x0F;
			switch(x)
			{
				case 0b00001110: 
				{
					LCDclear_y(2, 7);
					liczba = ( i - 3) | 0x30;
					wypiszCyfre(liczba);
					break;
				}
				case 0b00001101:
				{
					LCDclear_y(2, 7);
					liczba = (i + 1) | 0x30;
					wypiszCyfre(liczba);
					break;
				}
				case 0b00001011:
				{
					liczba = (i + 5);
					wypiszCyfre(liczba);
					break;
				}
				case 0b00000111:
				{
					LCDclear_y(2, 7);
					liczba = (i + 9);
					wypiszCyfre(liczba);
					break;
				}
			}
		}
	}
}

int main(void)
{
	DDRA = 0xF0;
	
	LCDinit();
	char tekst[] = "M. Pervov Przycisk nr:";
	write(tekst, 22);//wypisanie tekstu
	
	while (1){}
}