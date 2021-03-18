/*
 * ultrasonicSensor.c
 *
 * Created: 17-3-2021 09:47:12
 * Author : Sem
 
 interrupt op rising edge in echo,
	dan timer1 aanzetten -> timer1 want 16 bits en willen nauwkeurig afstand kunnen meten, en afstand kan van 2 cm tot 4 m, dus willen zeker zijn dat het past
	en interrupt zetten op falling edge in echo
	als falling edge interrupt geeft ->
		waarde uit timer1 uitlezen
		en formule gebruiken high level time * velocity (340M/S) / 2
		timer1 uitzetten
		interrupt weer op rising edge van echo zetten
		

 
 */ 
#define F_CPU 20e6

#include <avr/io.h>
#include <util/delay.h>

#include "lcd_control.h"

enum interrupt_status {INTERRUPT_FALLING, INTERRUPT_RISING};
	
static enum interrupt_status int_stat = INTERRUPT_RISING;

void wait_us(unsigned int us)
{
	for(int i = 0; i < us; i++)
	{
		_delay_us(1);
	}
}

void wait_ms(unsigned int ms)
{
	
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

void ultrasonic_send_pulse()
{
	PORTG = 0x00; // 10 us low pulse
	wait_us(10);
	PORTG = 0x01;
}

ISR(INT0_vect)
{
	// set interrupt pin 0 on PORTD to falling edge
	if (int_stat == INTERRUPT_RISING)
	{
		
		int_stat = INTERRUPT_FALLING;
	} else {
		
		int_stat = INTERRUPT_RISING;
	}
	
}


int main(void)
{
	DDRG = 0x01; // port g pin 0 on output, 1 on input. 0 is trig, 1 is echo
	
	EICRA |= 0x03; // interrupt PORTD on pin 0, rising edge
	
	EIMSK |= 0x01; // enable interrupt on pin 0 (INT0)
	
	sei(); // turn on interrupt system
	
    /* Replace with your application code */
    while (1) 
    {
		ultrasonic_send_pulse();
		
		wait_ms(100);
    }
}



