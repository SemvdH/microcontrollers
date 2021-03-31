/*
 * Eindopdracht.c
 *
 * Created: 31-3-2021 09:42:17
 * Author : Sem
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
    /* Replace with your application code */
	ultrasonic_init();
	init_4bits_mode();
	
	_delay_ms(10);
	
	lcd_clear();
    while (1) 
    {
		// TODO change to use the stepper motor
		ultrasonic_send_pulse(); 
		
		lcd_clear();
		lcd_write_int(ultrasonic_get_timer_dist());
		
		
		wait_ms(100);
    }
}

