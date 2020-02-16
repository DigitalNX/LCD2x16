#include "lcd_lib.h"

void lcd_init() {
	lcd_execute(LCD_SET_8_BIT_MODE);
	lcd_execute(LCD_CLEARSCREEN);
	lcd_execute(LCD_TURN_ON); // With cursor but without blinking
	lcd_execute(LCD_SET_DDRAM_ADDRESS_TO_ZERO);
}

void lcd_execute(uint8_t command) {
	LCD_DATA = command;

	// Next 4 lines, turn off and on the 'enable' signal;
	// Which causes the command to run on the LCD

	_delay_ms(1);
	ctrl = (0<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl = (0<<rs)|(0<<rw)|(0<<en);

	_delay_ms(5);
}


void lcd_turn_off() {
	lcd_execute(LCD_TURN_OFF);
}

void lcd_turn_on() {
	lcd_execute(LCD_TURN_ON);
}

void lcd_write_char(char data) {
	LCD_DATA = data;

	// The cursor automatically moves to the next position
 	ctrl = (1<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl = (1<<rs)|(0<<rw)|(0<<en);
	_delay_ms(10);
}

void lcd_write_string(char *data) {
	int n = 0;
	while(data[n] != '\0') {
		lcd_write_char(data[n]);
		if (n == 15) {
			lcd_execute(0xC0); // 00 1100 0000 -> goes to address '1000000' (0x40 in Hex) (next line) 
		}
		n++;
	}
}

void lcd_clear_screen() {
	lcd_execute(LCD_CLEARSCREEN);
}
