/*
 * ultrasonic_sensor.h
 *
 * Created: 24-3-2021 13:14:50
 *  Author: Sem
 */ 


/************************************************************************/
/* init the ultrasonic sensor driver                                    */
/************************************************************************/
void ultrasonic_init();
/************************************************************************/
/* send a pulse from the ultrasonic sensor                              */
/************************************************************************/
void ultrasonic_send_pulse();
/************************************************************************/
/* get the value of the timer which equals time taken for sound to		*/
/* return    			                                                */
/************************************************************************/
uint16_t ultrasonic_get_timer_dist();
/************************************************************************/
/* handle for the interrupt                                             */
/************************************************************************/
void ultrasonic_handle_interrupt();
/************************************************************************/
/* set a event for when the ultrasonic has a new value.                 */
/************************************************************************/
void set_value_trigger_event(void (*value_set_event_p)(uint16_t));
