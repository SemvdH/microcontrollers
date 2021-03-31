/***************************************************************************
 * Osama's Lab KS0108 GLCD library; a library that facilitates interfacing KS0108 based GLCDs.
 *
 *   Copyright (C) 2010-2012  Osama's Lab
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Affero General Public License as
 *   published by the Free Software Foundation, either version 3 of the
 *   License.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Affero General Public License for more details.
 *
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/> 
 **************************************************************************/
#define F_CPU 10e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/delay.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef unsigned char byte;
//DEBUG
//#define DEBUG_READ 0
//#define DEBUG_GLCD 0
//----------------------
#define E_DELAY 10
#define DATAPORT PORTC
#define CONTROLPORT	PORTB
#define CONTTROLDDR DDRB
#define DATADDR DDRC
#define DATAPIN PINC
#define GLCD_CS1 (1<<0)
#define GLCD_CS2 (1<<1)
#define GLCD_RST  (1<<3)
#define GLCD_RW  (1<<2)
#define GLCD_EN  (1<<4)   
#define GLCD_CS_ACTIVE_LOW   1  //Define this if your GLCD CS 
                              //is active low (refer to datasheet)
                                                          

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void wait_us(int us)
{
	for (int i=0; i<us; i++)
	{
		_delay_us( 1 );		// library function (max 30 ms at 8MHz)
	}
	
}

void GLCD_init()
{
	
	DATADDR = 0xFF; // port c all output
	CONTTROLDDR = 0xFF; // PORTB all output
	CONTROLPORT |= (GLCD_CS1) | (GLCD_CS2) | (GLCD_RST);
	
	wait(20);
	
}

void GLCD_command(char command)
{
	DATAPORT = command;
	CONTROLPORT &= ~GLCD_RST;
	CONTROLPORT &= ~GLCD_RW;
	CONTROLPORT |= GLCD_EN;
	
	wait_us(5);
	
	CONTROLPORT &= ~GLCD_EN;
	wait_us(5);
	
}

void trigger()
{
	CONTROLPORT |= GLCD_EN;	//EN high
	_delay_us(E_DELAY);
	CONTROLPORT &= ~GLCD_EN;	//EN low
	_delay_us(E_DELAY);
}
//----------------------
void glcd_on()
{
	#ifdef GLCD_CS_ACTIVE_LOW
	CONTROLPORT &= ~CS1;	//Activate both chips
	CONTROLPORT &= ~CS2;
	#else
	CONTROLPORT |= CS1;	//Activate both chips
	CONTROLPORT |= CS2;
	#endif
	CONTROLPORT = ~GLCD_RST | ~GLCD_RW;	//RS low --> command
	DATAPORT = 0b0011111; //OFF command
	trigger();
}     
//----------------------
void glcd_off()
{
	#ifdef GLCD_CS_ACTIVE_LOW
	CONTROLPORT &= ~CS1;	//Activate both chips
	CONTROLPORT &= ~CS2;
	#else
	CONTROLPORT |= CS1;	//Activate both chips
	CONTROLPORT |= CS2;
	#endif
	CONTROLPORT = ~GLCD_RST | ~GLCD_RW;	//RS low --> command
	DATAPORT = 0b0011110; //OFF command
	trigger();
}
  

int main(void)
{
	GLCD_init();
	glcd_off();
	while (1)
	{
		
		
		
	}
} 
//----------------------
