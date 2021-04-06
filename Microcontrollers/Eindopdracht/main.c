/*
 * Eindopdracht.c
 *
 * Created: 31-3-2021 09:42:17
 * Author : Sem, Guilliam and Stijn.
 */ 

#define F_CPU 10e6
#define ROTAITION_ANGLE 512
// rotation with a little overhead so the starting position will not miss.
#define INIT_ROTAITION_ANGLE 600
#define MAX_DISTANCE_INIT 20

#define LCD_SET_DELAY 100

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "lcd_control.h"
#include "ultrasonic_sensor.h"
#include "stepper_driver.h"

// if true: in init mode, looking for starting point.
bool initialising = true;

ISR(INT2_vect)
{
	ultrasonic_handle_interrupt();
}

static void snap_event_trigger(uint8_t rotation){
	// when X amount of steps are taken, do pulse.
	ultrasonic_send_pulse();
}

static void ultrasoon_value_set_event(uint16_t value){
	// if the SODAR is initialising, then look for close start object.
	if(initialising){
		if(value > 0  && value < MAX_DISTANCE_INIT){
			stepper_rotate_stop();
			initialising = false;
			// when found, set the initial rotation.
			stepper_rotate_angle(ROTAITION_ANGLE, CounterClockWise);
		}
	}
}

int main(void)
{
	// initialize ultrasonic sensor driver.
	ultrasonic_init();
	// initialize LCD display in 4 bit mode.
	init_4bits_mode();
	// initialize stepper driver.
	init_stepper_driver();
	// set the event when a pulse must be sent.
	set_snap_event(&snap_event_trigger);
	// set a event for when a value has been set from the ultrasonic sensor.
	set_value_trigger_event(&ultrasoon_value_set_event);
	
	_delay_ms(10);
	
	lcd_clear();
	
	stepper_rotate_angle(INIT_ROTAITION_ANGLE, ClockWise);
    while (1) 
    {
		lcd_clear();
		// set the ultrasonic value to the lcd.
		lcd_write_ultrasonic_value(ultrasonic_get_timer_dist());
		
		wait_ms(LCD_SET_DELAY);
    }
	// stop rotating. (not necessary)
	stepper_rotate_stop();
}

