#include "lcd_driver_if.h"

#define NT35510_BASE 0x6C00007E

struct lcd_driver {
	struct lcd_device dev;
	struct lcd_opt *opt;
};

extern struct lcd_opt nt35510_opt;

static struct lcd_driver lcd_drv = {
	{(struct lcd_dev *)NT35510_BASE, 480, 800},
	&nt35510_opt
};

static struct lcd_driver *driver = &lcd_drv;

extern struct lcd_opt nt35510_opt;

void lcd_driver_open(void)
{
	driver->opt->open(&(driver->dev));
}

void lcd_driver_close(void)
{
	driver->opt->close(&(driver->dev));
}
