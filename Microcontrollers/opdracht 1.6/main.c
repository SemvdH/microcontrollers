/*
 * main.c
 *
 * Created: 03-Feb-21 9:17:12 AM
 *  Author: lemms
 */ 
# define F_CPU 10000000UL

#include <util/delay.h>
#include <avr/io.h>

typedef enum {
	false = 0,
	true = 1
} bool;

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of milliseconds
inputs:			int ms (Number of milliseconds to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void sbi(int REG, int index){
	REG |= (1<<index);
}

void cbi(int REG, int index){
	REG &= ~(1<<index);
}

int tbi(int REG, int index){
	REG ^= (1<<index);
	return REG;
}

bool checkButton(){
	return (PINC & 1);
}

bool checkButtonToggle(bool pressed){
	return (checkButton() == true) && (pressed == false);
}

/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, flipping bits on PORTD
Version :    	DMK, Initial code
*******************************************************************/
{
	bool pressed = checkButton();
	bool state = false;
	int ms = 0;
	int button = 0;
	int setTime = 1000;
	DDRD = 0b11111111;            // All pins PORTD are set to output
	DDRC = 0b00000000;			// set pint input

	while (1)
	{
		
		if(checkButtonToggle(pressed)){
			pressed = checkButton();
			state = !state;
		}

		if(pressed && !checkButton()){
			pressed = false;
		}
		
		if(state){
			setTime = 250;
		} else {
			setTime = 1000;
		}
		
		if(ms >= setTime){
			PORTD = tbi(PORTD, 0);
			ms = 0;
		}

		wait(1);
		
		ms++;
	}

	return 1;
}

