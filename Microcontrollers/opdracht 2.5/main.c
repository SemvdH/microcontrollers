/*
 * main.c
 *
 * Created: 11-Feb-21 11:01:07 PM
 *  Author: lemms
 */ 


#define F_CPU 8e6
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);

int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
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