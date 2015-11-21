#ifndef _LCD_DRIVER_H
#define _LCD_DRIVER_H

#include <stdint.h>

struct rectangle {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
};

extern void lcd_driver_hw_init(void);

extern void lcd_driver_open(void);

extern void lcd_driver_clear(void);

extern void lcd_driver_rectangle(struct rectangle *rect, uint16_t l, uint16_t c);

extern void lcd_draw_point(uint16_t x, uint16_t y, uint16_t c);

extern void lcd_driver_close(void);

#endif
