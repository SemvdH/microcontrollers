/*
 * stepper_driver.c
 * PORTB
 * Created: 10-Mar-21 12:21:47 PM
 * Author: lemms
 */ 
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>

#include "stepper_driver.h"

#define BIT(x)			(1 << (x))

// states for stepper to rotate counterclockwise
uint8_t CCW[8] = {0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};
// states for stepper to rotate clockwise
uint8_t CW[8] = {0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};

// value for how many steps each turn.	
uint16_t steps_each_turn = 0;
// value for the amount of steps still to do.
uint16_t steps_to_do = 0;
// which of the stepper states is set currently.
uint8_t stepper_state = 0;

// current rotation wise. (CW or CCW)	
enum rotation_wise rotation;

void stepper_rotate_full_rotation_CW();
void stepper_rotate_full_rotation_CCW();

void set_stepper_state(uint8_t count){
	if(rotation == ClockWise){
		PORTE = CW[count];
	} else {
		PORTE = CCW[count];
	}
}

void (*snap_event)(uint8_t);

void set_snap_event(void (*snap_event_p)(uint8_t)){
	snap_event = snap_event_p;
}

ISR( TIMER2_COMP_vect ){
	
	TCNT2 = 0;
	
	set_stepper_state(stepper_state);
		
	if(stepper_state < 7){
		stepper_state++;
	} else {
		
		stepper_state = 0;
		
		if(steps_to_do == 0){
			
			// change rotation if the steps todo is 0.
			if(rotation == ClockWise){
				rotation = CounterClockWise;
			} else {
				rotation = ClockWise;
			}
			
			// set the steps to do again.
			steps_to_do = steps_each_turn;
			
		} else {
			
			// if the stepper step value is at a multiplier of 32 then make snap event.
			if(steps_to_do % STEPS_EACH_PULSE == 0){
				
				if(snap_event != NULL)
					snap_event(steps_to_do);
			}
			
			steps_to_do--;
		}
	}
}

void stepper_rotate_angle(uint16_t steps, enum rotation_wise rot){
	steps_to_do = steps;
	steps_each_turn = steps;
	rotation = rot;
	TCCR2 = 0b00001100;
}

void stepper_rotate_stop(){
	TCCR2 = 0b00000000;
}

void init_stepper_driver(){
	DDRE = 0xff;
	DDRG = 0xff;
	PORTG = 0x01;
	PORTE = 0x00;
	OCR2 = 150;
	TIMSK = BIT(7);
	sei();
}