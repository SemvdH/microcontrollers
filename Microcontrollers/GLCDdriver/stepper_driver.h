/*
 * stepper_driver.h
 *
 * Created: 10-Mar-21 12:35:30 PM
 *  Author: lemms
 */ 


#ifndef STEPPER_DRIVER_H_
#define STEPPER_DRIVER_H_

#include <stdbool.h>

void init_stepper_driver();
void stepper_rotate(uint16_t steps);
void stepper_rotate_full_rotation_CW();
void stepper_rotate_full_rotation_CCW();

#endif /* STEPPER_DRIVER_H_ */