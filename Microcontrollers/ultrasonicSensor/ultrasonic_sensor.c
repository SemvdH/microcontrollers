/*
 * ultrasonic_sensor.c
 *
 * Created: 24-3-2021 13:04:52
 *  Author: Sem
 */ 

#define F_CPU 10e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd_control.h"

static uint16_t timer_dist = 0;

enum interrupt_status {INTERRUPT_FALLING, INTERRUPT_RISING};

static enum interrupt_status int_stat = INTERRUPT_RISING;

void wait_us(unsigned int us)
{
	for(int i = 0; i < us; i++)
	{
		_delay_us(1);
	}
}

void wait_ms(unsigned int ms)
{
	
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}
void ultrasonic_init()
{
	DDRG = 0xFF; // port g all output. pin 0 is trig, the rest is for debug
	DDRD = 0x00; // port D pin 0 on input. 0 is echo and also interrupt
	
	EICRA = 0x03; // interrupt PORTD on pin 0, rising edge
	
	EIMSK |= 0x01; // enable interrupt on pin 0 (INT0)
	
	TCCR1A = 0b00000000; // initialize timer1, prescaler=256
	TCCR1B = 0b00001100; // CTC compare A, RUN
	
	sei(); // turn on interrupt system
}

void ultrasonic_send_pulse()
{
	PORTG = 0x00; // 10 us low pulse
	wait_us(10);
	PORTG = 0x01;
}

void ultrasonic_handle_interrupt()
{
	// if the interrupt was generated on a rising edge (start sending echo)
	if (int_stat == INTERRUPT_RISING)
	{
		// set interrupt pin 0 on PORTD to falling edge
		EICRA = 0x02;
		
		// reset the time in timer1
		TCNT1 = 0x00;
		
		// set interrupt status
		int_stat = INTERRUPT_FALLING;
	} else
	// else if it was generated on a falling edge (end sending echo)
	{
		// set interrupt pin 0 on PORTD to rising edge
		EICRA = 0x03;
		
		// read timer1 into time_dist
		timer_dist = TCNT1;
		
		// set interrupt status
		int_stat = INTERRUPT_RISING;
	}
}

uint16_t ultrasonic_get_timer_dist()
{
	return timer_dist;
}

