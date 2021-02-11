/*
 * Opdracht 2.2.c
 *
 * Created: 10-2-2021 10:58:13
 * Author : Sem
 */ 
#define F_CPU 10e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}
/************************************************************************/
/* interrupt 1
walk the light 1 down                                                                     */
/************************************************************************/
ISR( INT1_vect ) {
	if (PORTC == 0b10000000)
	{
		PORTC == 0b00000001;
	} else {
		PORTC = PORTC << 1;
	}
	
	
}

/************************************************************************/
/* interrupt 2
walk the light 1 up                                                                     */
/************************************************************************/
ISR( INT2_vect ) {
	if (PORTC == 0b00000001)
	{
		PORTC = 0b10000000;
	}
	PORTC = PORTC >> 1;
}


int main(void)
{
    /* Replace with your application code */
	
	// Init I/O
	DDRD = 0xF0;			// PORTD (7:4) is output, (3:0) is input
	DDRC = 0xFF;
	
	// Init Interrupt hardware
	EICRA |= 0x2C;			// INT2 falling edge, INT1 rising edge
	EIMSK |= 0x06;			// Enable INT2 & INT1
	
	PORTC = 0x01; // init the first bit
	
	sei(); // enable input mechanism
	
    while (1) 
    {
		
    }
}

void lcd_strobe_lcd_e(void) {
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			
	PORTC &= ~(1<<LCD_E);  	// E low
}

void init_4bits_mode(void) {
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	PORTC = 0x20;	// (0x28 for 2 lines)
	lcd_strobe_lcd_e();
}

void init_4bits_mode(void) {
	
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;
	
	PORTC = 0x20;	// function for 4-bit 1 row
	lcd_strobe_lcd_e();

	PORTC = 0x20;   // function high nibble 4-bit 2 row
	lcd_strobe_lcd_e();
	PORTC = 0x80;	// function low nibble 4-bit 2 row
	lcd_strobe_lcd_e();

	PORTC = 0x00;   // function high nibble turn on visible blinking-block cursor
	lcd_strobe_lcd_e();
	PORTC = 0xF0;   // function low nibble turn on visible blinking-block cursor
	lcd_strobe_lcd_e();

	PORTC = 0x00;   // Entry mode set high nibble
	lcd_strobe_lcd_e();
	PORTC = 0x60;	// Entry mode set low nibble
	lcd_strobe_lcd_e();
}