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
#define F_CPU 10e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd_control.h"
#include "ultrasonic_sensor.h"

ISR(INT0_vect)
{
	ultrasonic_handle_interrupt();
}


int main(void)
{
	
	ultrasonic_init();
	init_4bits_mode();
	
	_delay_ms(10);
	
	lcd_clear();


    while (1) 
    {
		ultrasonic_send_pulse();
		
		lcd_clear();
		lcd_write_int(ultrasonic_get_timer_dist());
		
		
		wait_ms(100);
    }
}



