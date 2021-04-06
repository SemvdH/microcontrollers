/*
 * lcd_controlc.c
 *
 * Created: 24-2-2021 11:55:12
 *  Author: Sem
 */ 
#define F_CPU 10e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd_control.h"

void _delay_ms(double __ms);

void lcd_clear() {
	lcd_write_command (0x01);						//Clear display
	_delay_ms(2);
	lcd_write_command (0x80);						//Cursor back to start
}

void lcd_strobe_lcd_e(void) {
	
	sbi_porta(LCD_E);	// E high
	_delay_ms(1);
	cbi_porta(LCD_E);  	// E low
	_delay_ms(2);
	
}

void sbi_portc(int index){
	PORTC |= (1<<index);
}


void cbi_portc(int index){
	PORTC &= ~(1<<index);
}

void sbi_porta(int index){
	PORTA |= (1<<index);
}


void cbi_porta(int index){
	PORTA &= ~(1<<index);
}

void init_4bits_mode(void) {
	
	// PORTC output mode and all low (also E and RS pin)
	
	// Init I/O
	DDRC = 0xFF;			// PORTD(7) output, PORTD(6:0) input
	PORTC = 0xFF;
	
	DDRA = 0xFF;
	PORTC = 0x00;
	PORTA = 0x00;
	
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
	
	// return home
	lcd_write_command(0x02);
	lcd_strobe_lcd_e();
}

void lcd_write_character(unsigned char byte){
	
	
	//upper nibble
	PORTC = byte;
	sbi_porta(LCD_RS);
	lcd_strobe_lcd_e();
	
	//lower nibble
	PORTC = (byte<<4);
	sbi_porta(LCD_RS);
	lcd_strobe_lcd_e();
	
}

void lcd_write_command(unsigned char byte){
	
	//upper nibble
	PORTC = byte;
	cbi_porta(LCD_RS);
	lcd_strobe_lcd_e();
	
	//lower nibble
	PORTC = (byte<<4);
	cbi_porta(LCD_RS);
	lcd_strobe_lcd_e();

}

void lcd_write_string(const char *str) {
	
	for(;*str; str++){
		lcd_write_character(*str);
	}
}

void lcd_move_right(void){
	
	lcd_write_command(0x1E);
}

void lcd_write_int(int number)
{
	int length = snprintf(NULL, 0, "%d", number);
	char str[length + 1];
	snprintf(str, length + 1, "%d", number);
	lcd_write_string(str);
}

void lcd_write_double(char prefix[], float number, char suffix[])
{
	int length = snprintf(NULL, 0, "%s: %.3f %s", prefix, number, suffix);
	char str[length + 1];
	snprintf(str, length + 1, "%s: %.3f %s", prefix, number, suffix);
	lcd_write_string(str);
}

void lcd_write_ultrasonic_value(float number)
{
	int length = snprintf(NULL, 0, "%f CM", number);
	char str[length + 1];
	snprintf(str, length + 1, "%f CM", number);
	lcd_write_string(str);
}
