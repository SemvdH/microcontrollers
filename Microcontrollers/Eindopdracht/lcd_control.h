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

/************************************************************************/
/* inits display in 4 bit mode                                          */
/************************************************************************/
void init_4bits_mode(void);
/************************************************************************/
/* write string to the lcd                                              */
/************************************************************************/
void lcd_write_string(const char *str);
/************************************************************************/
/* write character to the lcd                                           */
/************************************************************************/
void lcd_write_character(unsigned char byte);
/************************************************************************/
/* write command to the lcd                                             */
/************************************************************************/
void lcd_write_command(unsigned char byte);
/************************************************************************/
/* clear the lcd                                                        */
/************************************************************************/
void lcd_clear();
/************************************************************************/
/* write int to the lcd                                                 */
/************************************************************************/
void lcd_write_int(int number);
/************************************************************************/
/* write double to the lcd                                              */
/************************************************************************/
void lcd_write_double(char prefix[], double number, char suffix[]);



#endif /* LCD_CONTROL_H_ */