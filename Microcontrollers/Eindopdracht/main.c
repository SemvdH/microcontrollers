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
#include <stdbool.h>

#include "lcd_control.h"
#include "ultrasonic_sensor.h"
#include "stepper_driver.h"

bool initialising = true;

ISR(INT2_vect)
{
	ultrasonic_handle_interrupt();
}

static void snap_event_trigger(uint8_t rotation){
	ultrasonic_send_pulse();
}

static void ultrasoon_value_set_event(uint16_t value){
	if(initialising){
		if(value > 0  && value < 20){
			stepper_rotate_stop();
			initialising = false;
			stepper_rotate_angle(512, CounterClockWise);
		}
	}
}

int main(void)
{
    /* Replace with your application code */
	ultrasonic_init();
	init_4bits_mode();
	init_stepper_driver();
	set_snap_event(&snap_event_trigger);
	set_value_trigger_event(&ultrasoon_value_set_event);
	
	_delay_ms(10);
	
	lcd_clear();
	
	stepper_rotate_angle(600, ClockWise);
    while (1) 
    {
		// TODO change to use the stepper motor
		//ultrasonic_send_pulse(); 
		
		lcd_clear();
		lcd_write_int(ultrasonic_get_timer_dist());
		
		
		wait_ms(100);
    }
	stepper_rotate_stop();
}

