/*
 * stepper_driver.h
 *
 * Created: 10-Mar-21 12:35:30 PM
 *  Author: lemms
 */ 


#ifndef STEPPER_DRIVER_H_
#define STEPPER_DRIVER_H_

#include <stdbool.h>

#define STEPS_EACH_PULSE 32
#define STEPPER_SPEED 200
#define COMPARE_VALUE (255 - STEPPER_SPEED)

enum rotation_wise {
	ClockWise,
	CounterClockWise
};

/************************************************************************/
/* init ports and timers for stepperdriver.                             */
/************************************************************************/
void init_stepper_driver();
/************************************************************************/
/* set the rotationangle and turn on stepper                            */
/************************************************************************/
void stepper_rotate_angle(uint16_t steps, enum rotation_wise rot);
/************************************************************************/
/* stepper stop rotating                                                */
/************************************************************************/
void stepper_rotate_stop();
/************************************************************************/
/* set the event for the ultrasonic pulse                               */
/************************************************************************/
void set_snap_event(void (*snap_event_p)(uint8_t));

#endif /* STEPPER_DRIVER_H_ */