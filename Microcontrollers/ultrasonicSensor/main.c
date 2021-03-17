/*
 * ultrasonicSensor.c
 *
 * Created: 17-3-2021 09:47:12
 * Author : Sem
 
 ultrasoon op timer 1 want 16 bits
 timer aanzetten met tccrn1
 interrupt op falling edge van echo
 in interrupt timer op 0 zetten en tccrn1 op 0
 interrupt op rising edge in echo,
	dan timer aanzetten
	en interrupt zetten op falling edge in echo
	als falling edge interrupt geeft ->
		waarde uit timer uitlezen
		en formule gebruiken high level time * velocity (340M/S) / 2
 
 */ 
#define F_CPU 20e6

#include <avr/io.h>
#include <util/delay.h>

#include "lcd_control.h"

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


int main(void)
{
	DDRG = 0x01; // port g pin 0 on output, 1 on input. 0 is trig, 1 is echo
	
	
    /* Replace with your application code */
    while (1) 
    {
		PORTG = 0x00; // 10 us low pulse
		wait_us(10);
		PORTG = 0x01;
		
		wait_ms(100);
    }
}



