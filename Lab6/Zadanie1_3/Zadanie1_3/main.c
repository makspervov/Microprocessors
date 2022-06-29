/*
 * Zadanie1_3.c
 *
 * Created: 02.06.2022 12:26:01
 * Author : Maksym Pervov
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#ifndef F_CPU
# define F_CPU 1000000UL
#endif

#define LCD_DDR DDRB
#define LCD_PORT PORTB
#define LCD_RS 2
#define LCD_EN 3
#define LCD_DB4 4
#define LCD_DB5 5
#define LCD_DB6 6
#define LCD_DB7 7

void clearPosition(uint8_t b){	//funckja komend
	LCD_PORT |= _BV(LCD_EN);	//zezwalamy komunikajce z LCD
	LCD_PORT = (b & 0xF0)|(LCD_PORT & 0x0F);//wysy?amy 4 starsze bity
	LCD_PORT &= ~(_BV(LCD_EN));	//m?wimy, ?e b?dziemy wysy?ali dane
	asm volatile("nop");		//jeden cykl mikroproc.	
	LCD_PORT |= _BV(LCD_EN);	//zezwalamy komunikajce z LCD
	LCD_PORT = ((b & 0x0F) << 4)|(LCD_PORT & 0x0F);//wysy?amy 4 m?odsze bity
	LCD_PORT &= ~(_BV(LCD_EN));	//m?wimy, ?e b?dziemy wysy?ali dane
	_delay_ms(50);
}

void clearLCD(){
	LCD_PORT &= ~(_BV(LCD_RS));
	clearPosition(0x01);		//rejestr 0x01 - wyczy?? tekst z LCD
	LCD_PORT |= _BV(LCD_RS);	//zapisujemy dane
	_delay_ms(60);
}

void LCDinit(){
	LCD_DDR = (0xF0)|(_BV(LCD_RS))|(_BV(LCD_EN));
	LCD_PORT = 0;	//wyzerowanie portu
	LCD_PORT &= ~(_BV(LCD_RS));	//dajemy komende
	
	clearPosition(0b00101000);	//inicjalizuj 4-bitowy tryb + 2 linie 5*7 macierz
	LCD_PORT |= _BV(LCD_RS);
	LCD_PORT |= _BV(LCD_RS);
	
	clearPosition(0b00000110);	//inicjalizuj przesuni?cie kursora w prawo
	LCD_PORT |= _BV(LCD_RS);
	LCD_PORT &= ~(_BV(LCD_RS));
	
	clearPosition(0b00001100);	//wy?wietlaj przy wy?aczonym kursorze
	LCD_PORT |= _BV(LCD_RS);	//m?wimy, ?e b?dziemy zapisywali dane
	
	clearLCD();
}

void setCursor(unsigned char w, unsigned char h)
{
	LCD_PORT &= ~(_BV(LCD_RS));	//m?wimy, ?e podajemy komend?
	clearPosition((w*0x40+h)|(0x80));//0x80 - 1 linia, 0x40 - tej 1/2 linii
	LCD_PORT |= _BV(LCD_RS);	//m?wimy, ?e podajemy dane
	_delay_ms(5);
}

void write(char *text, int8_t lenght){
	int8_t i = 0;
	setCursor(0,0);				//ustawiamy kursor na pocz?tek
	while (i < lenght){
		clearPosition(text[i]); //czy?cimy na pozycji i
		if(i==16){				//jezeli tekst wiekszy od 16
			setCursor(1,0);		//ustawiamy na poczatek pierwszej linijki
		}
		i++;
	}
}

/*void LCDclear_y(unsigned char n, unsigned char lenght){
	setCursor(n, lenght);
	while (n<=16)
	{
		clearPosition(' ');
		n++;
	}
}*/

void LCDclear_y(char number, char lenght) {
	setCursor(number,number-1);		//ustawiam kursor na linijke oraz wiersz
	for(char i = number; i < lenght; i++)
	{
		if(i > 16 ) {
			setCursor(1, 0);		//przemie?cienie na now? linijk?
			clearPosition(0b00010100);//przemie?cienie kursora w prawo
		}
		else{clearPosition(0b00010100);}
	}
}

void zadanie1()
{
	LCDinit();
	char text[] = "Hello World     !!! I love you";
	write(text,30);				//wypisanie tekstu
	LCDclear_y(0,11);			//oczy?cienie LCD z pewnej pozycji i dlugo?ci?
}

void zadanie3()
{
	char symbol1[] = {'?','?','?','?','?','?','?','?','?','ˆ'};
	char symbol2[] = {'U','b','e','r','k','o','t'};
	char symbol3[] = {'T','h','u','r','s','d','a','y'};
	LCDinit();
	while(1)
	{
		write(symbol1, 10);		//wypisanie tekstu
		_delay_ms(500);			//op??nienie co 0,5 s
		clearLCD();				//oczy?ccienie LCD
		write(symbol2, 7);		//wypisanie tekstu
		_delay_ms(500);			//op??nienie co 0,5 s
		clearLCD();				//oczy?ccienie LCD
		write(symbol3, 8);		//wypisanie tekstu
		_delay_ms(500);			//op??nienie co 0,5 s		
		clearLCD();				//oczy?ccienie LCD
	}
}

int main(void)
{
	zadanie1();				//funkcja zadania 1
	//zadanie3();				//Funkcja zadania 3
    while (1){}
}
