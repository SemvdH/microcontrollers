/*
 * lcd_control.h
 *
 * Created: 24-2-2021 11:56:16
 *  Author: Sem
 */ 


#ifndef LCD_CONTROL_H_
#define LCD_CONTROL_H_

#define LCD_E 	6
#define LCD_RS	4

void _delay_ms(double __ms);
void lcd_strobe_lcd_e(void);
void sbi_portc(int index);
void cbi_portc(int index);
void sbi_porta(int index);
void cbi_porta(int index);
void init_4bits_mode(void);
void lcd_write_string(const char *str);
void lcd_write_character(unsigned char byte);
void lcd_write_command(unsigned char byte);
void lcd_clear();
void lcd_write_int(int number);



#endif /* LCD_CONTROL_H_ */