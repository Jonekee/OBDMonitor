#ifndef _LCD_DRIVER_IF_H
#define _LCD_DRIVER_IF_H

#include <stdint.h>

struct lcd_device {
	uint16_t cmd_reg;
	uint16_t dat_reg;
};

struct lcd_opt {
	void (*hw_init)(void);
	void (*open)(struct lcd_device *dev);
	void (*close)(struct lcd_device *dev);
};

#endif
