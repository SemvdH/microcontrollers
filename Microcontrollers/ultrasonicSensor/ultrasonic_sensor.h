/*
 * ultrasonic_sensor.h
 *
 * Created: 24-3-2021 13:14:50
 *  Author: Sem
 */ 


void ultrasonic_init();
void ultrasonic_send_pulse();
uint16_t ultrasonic_get_timer_dist();
void ultrasonic_handle_interrupt();
