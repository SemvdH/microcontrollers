/*
 * main.c
 *
 * Created: 11-Feb-21 11:01:07 PM
 *  Author: lemms
 */ 


#define F_CPU 10e6
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2

void _delay_ms(double __ms);
void lcd_strobe_lcd_e(void);
void sbi_portc(int index);
void cbi_portc(int index);
void init_4bits_mode(void);
void lcd_write_string(const char *str);
void lcd_add_character(unsigned char byte);
void lcd_add_command(unsigned char byte);

int main(void)
{
	init_4bits_mode();
	
	
	
    while(1)
    {
	
        //TODO:: Please write your application code 
    }
}

void lcd_strobe_lcd_e(void) {
	sbi_portc(LCD_E);	// E high
	_delay_ms(1);
	cbi_portc(LCD_E);  	// E low
	_delay_ms(1);
}

void sbi_portc(int index){
	PORTC |= (1<<index);
}

void cbi_portc(int index){
	PORTC &= ~(1<<index);
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
	
	lcd_write_string("Pintebaas");
}

void lcd_add_character(unsigned char byte){
	
	//upper nibble
	PORTC = byte;
	sbi_portc(LCD_RS);
	lcd_strobe_lcd_e();
	
	//lower nibble
	PORTC = (byte<<4);
	sbi_portc(LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_add_command(unsigned char byte){
	
	//upper nibble
	PORTC = byte;
	cbi_portc(LCD_RS);
	lcd_strobe_lcd_e();
	
	//lower nibble
	PORTC = (byte<<4);
	cbi_portc(LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_write_string(const char *str) {
	
	for(;*str; str++){
		lcd_add_character(*str);
	}
}

void lcd_move_right(void){
	
	lcd_add_command(0x1E);
}