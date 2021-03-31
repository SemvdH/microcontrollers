/*
 * stepper_driver.h
 *
 * Created: 10-Mar-21 12:35:30 PM
 *  Author: lemms
 */ 


#ifndef STEPPER_DRIVER_H_
#define STEPPER_DRIVER_H_

#include <stdbool.h>

void stepper_rotate(uint16_t steps);
void init_stepper_driver();

#endif /* STEPPER_DRIVER_H_ */