/*
 * USART.c
 *
 * Created: 6/18/2023 12:25:08 AM
 * Author : JMS
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define BAUD_RATE 9600
#define MY_UBRR 103

void USART_Init(int ubrr);
void USART_Transmit(char dt);
char USART_Recieve();
void USART_TX_String(char *str);

char c;

int main(void)
{
    USART_Init(MY_UBRR);
	_delay_ms(100);

	USART_TX_String("Janith");
	
    while (1) 
    {
		c = USART_Recieve();
		USART_Transmit(c);
    }
	return 0;
}

void USART_Init(int ubrr)
{
	UBRR0H = (ubrr>>8); //baud rate set
	UBRR0L = (ubrr);
	
	UCSR0C |=(1<<USBS0)| (1<<UCSZ00)|(1<<UCSZ01); // set frame to 8bits 2 stop bits
	
	UCSR0B |= (1<< TXEN0) | (1<< RXEN0); //enable tx and rx
}

void USART_Transmit(char dt)
{
	while(!(UCSR0A & (1<<UDRE0))); //wait until data register is emtpy
	
	UDR0 = dt;
}

char USART_Recieve()
{
	while((UCSR0A & (1<<RXC0))==0);
	return UDR0;
}

void USART_TX_String(char *str)
{
	int i = 0;
	
	while(str[i]!=0)
	{
		USART_Transmit(str[i]);
		i++;
	}
	
}