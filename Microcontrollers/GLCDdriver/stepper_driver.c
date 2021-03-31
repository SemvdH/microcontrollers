/*
 * stepper_driver.c
 * PORTB
 * Created: 10-Mar-21 12:21:47 PM
 * Author: lemms
 */ 
#define F_CPU 10e6

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>

#define BIT(x)			(1 << (x))

uint8_t CCW[8] = {0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};
uint8_t CW[8] = {0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};

/*
 Een timer met interupt routine.
 
 in de interump routine een state machine voor de 8 nibbles
 elke keer dat de interupt routine wordt geroepen wordt de state
 incremented. hier houd je ook een var bij om de relatieve
 positie te weten van de stappenmotor.
 
 Nog een timer voor microstepping.
 
 Timers:
 timer voor de speed.
 stappen van 100ms naar 10ms
 prescaler = 255
*/

enum rotation_wise{
	CW,
	CCW
};
	
rotation_wise rotation;

void stepper_rotate_full_rotation_CW();
void stepper_rotate_full_rotation_CCW();

void set_stepper_state(uint8_t count){
	if(rotation == CW){
		PORTE = CW[count];
	} else {
		PORTE = CCW[count];
	}
}

void (*snap_event)(uint8_t);

void set_snap_event(void (*snap_event_p)(uint8_t)){
	snap_event = snap_event_p;
}

uint16_t steps_to_do = 0;
uint8_t stepper_state = 0;
ISR( TIMER2_COMP_vect ){
	TCNT2 = 0;
	
	set_stepper_state(stepper_state);
		
	if(stepper_state < 7){
		stepper_state++;
	} else {
		//OCR2 = ADCH;
		stepper_state = 0;
		
		if(steps_to_do == 0){
			TCCR2 = 0b00000000;
			if(rotation == CW){
				stepper_rotate_full_rotation_CW();
			} else {
				stepper_rotate_full_rotation_CCW();
			}
		} else {
			
			if(steps_to_do % 32 == 0){
				
				if(PORTG == 0x01){
					PORTG = 0x00;
				} else if (PORTG == 0x00){
					PORTG = 0x01;
				}
				
				if(snap_event != NULL)
					snap_event(steps_to_do);
			}
			
			steps_to_do--;
		}
	}
}

void stepper_rotate_full_rotation_CW(){
	steps_to_do = 512;
	rotation_wise = CW;
	TCCR2 = 0b00001100;
}

void stepper_rotate_full_rotation_CCW(){
	steps_to_do = 512;
	rotation_wise = CCW;
	TCCR2 = 0b00001100;
}

void stepper_rotate(uint16_t steps){
	steps_to_do = steps;
	TCCR2 = 0b00001100;
}

void init_stepper_driver(){
	rotation = CW;
	DDRE = 0xff;
	DDRG = 0xff;
	PORTG = 0x01;
	PORTE = 0x00;
	OCR2 = 50;
	TIMSK = BIT(7);
	sei();
}