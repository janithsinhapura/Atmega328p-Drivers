/*
 * pinChangeInterrupt.c
 * This example show the basic Pin Change interrupt  implementation.
 * Every time the PINB0(Pin14) changes its state, then PINB1 (Pin15) also toggles.
 * To test the result, simply attach a LED to PINB1(Pin15)
 * Created: 6/24/2023 1:07:48 PM
 * Author : Janith Sinhapura
 */ 
#define F_CPU 16000000UL //16MHZ external crystal oscillator
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(PCINT0_vect)
{
	PINB = (1<<PINB1);
}
int main(void)
{
	//set PINB0 and PINB1 output
    DDRB |=(1<<DDB1); 
	DDRB |=(1<<DDB0);
	
	
	PCICR |=(1<<PCIE0); //enable pin change interrupt
	PCMSK0 |=(1<<PCINT0); //enable pin change interrupt on PINB0 / PCINT0
	
	sei(); //enable global interrupts
	
	
    while (1) 
    {
		PINB =(1<<PINB0);
		_delay_ms(500);
    }
}



