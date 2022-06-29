#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

uint8_t count[3];//tablica liczb do operacji
uint8_t state[2];
uint8_t przycisk(uint8_t port, uint8_t pin) {
	uint8_t i = 1;
	if (port == PINA) {i=0;}
	if (port & (1 << pin)) {
		if (!(state[i] & (1 << pin))) {

			_delay_ms(10);
			return 1;
		}
	}
	else
	{
		return 0;
	}
}
uint8_t znaki(uint8_t znaczek) {
	/* przetwarzanie uint8 do 7LED */
	switch(znaczek) {
		case 0 : return 0x3F;
		case 1 : return 0x06;
		case 2 : return 0x5B;
		case 3 : return 0x4F;
		case 4 : return 0x66;
		case 5 : return 0x6D;
		case 6 : return 0x7D;
		case 7 : return 0x07;
		case 8 : return 0x7F;
		case 9 : return 0x6F;
		default: return 0xAA;
	}
	return 0xAA;
}
void wyswietl(uint8_t num) {//fukcja do wyswietlanie na 7LED
	uint8_t led[4];
	if (num <= 9999) {
		led[3]=num/1000;//ustalanie na 1 kolumnie
		led[2]=(num%1000)/100;//ustalanie na 1,2 kolumnie
		led[1]=(num%100)/10;// ustalanie na 1,2,3 kolumnie
		led[0]=num%10;//ustalanie na 1,2,3,4 kolumnie
	}
}

int main(void) {
	//deklaracja portow A,B,C,D
	DDRA = 0x00;
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0x00;
	PORTA = 0xff;
	PORTD = 0xff;
	PORTB = 0;
	PORTC = 0;
	uint8_t i,j,k;
	j=0;k=0;state[0]=0;state[1]=0;
	while (j<2) {
		wyswietl(count[j]); //pokaz wprowadzana liczbe
		for (i=0;i<8;i++) // odczytanie liczby
		if ( (przycisk( &PINA, i)) && k<4 ) {
			count[j]= (count[j] * 10) + i;
			k++;
		}
		for (i=0;i<8;i++) //odczytujemy operacje dla liczb
		if (przycisk( &PIND, i)) {
			if (!j) count[2]=i;
			j++;k=0;
		}
	}
	j=count[2];
	switch(j) {
		case 0: // dodawanie
		count[2]=count[0]+count[1];
		break;
		case 1: // odejmowanie
		count[2]=count[0]-count[1];
		break;
		case 2: // mnozenie
		count[2]=count[0]*count[1];
		break;
		case 3: // dzielenie
		count[2]=(count[0]*10)/count[1];
		break;
		case 4: //czy jest rowne
		if(count[1]=count[0]){
			count[2]=count[1];
		}
		else
		{
			break;
		}
	}
	while(1) 
	{
		wyswietl(count[2]);//wyswietlamy wynik
		return 0;
	}
}