#ifndef _LCD_DRIVER_IF_H
#define _LCD_DRIVER_IF_H

#include <stdint.h>

struct lcd_dev {
	uint16_t cmd_reg;
	uint16_t dat_reg;
};

struct lcd_device {
	struct lcd_dev *dev;
	uint16_t width;
	uint16_t height;
};

struct lcd_opt {
	void (*open)(struct lcd_device *dev);
	void (*draw_point)(struct lcd_device *dev, uint16_t x, uint16_t y, uint16_t color);
	void (*close)(struct lcd_device *dev);
};

#endif
