/*
 * stepper_driver.h
 *
 * Created: 10-Mar-21 12:35:30 PM
 *  Author: lemms
 */ 


#ifndef STEPPER_DRIVER_H_
#define STEPPER_DRIVER_H_

#include <stdbool.h>

enum rotation_wise {
	ClockWise,
	CounterClockWise
};

void init_stepper_driver();
void stepper_rotate(uint16_t steps);
void stepper_rotate_angle(uint16_t steps, enum rotation_wise rot);
void stepper_rotate_stop();
void set_snap_event(void (*snap_event_p)(uint8_t));

#endif /* STEPPER_DRIVER_H_ */