/*
 * ultrasonicSensor.c
 *
 * Created: 17-3-2021 09:47:12
 * Author : Sem
 
 timer aanzetten met tccrn2
 interrupt op falling edge van echo
 in interrupt timer op 0 zetten en tccrn2 op 0
 
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



