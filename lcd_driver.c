#include "lcd_driver_if.h"

#define NT35510_BASE 0x6C00007E

struct lcd_driver {
	struct lcd_device *dev;
	struct lcd_opt *opt;
};

extern struct lcd_opt nt35510_opt;

static struct lcd_driver lcd_drivers[] = {
	{(struct lcd_device *)NT35510_BASE, &nt35510_opt}
};

static struct lcd_driver *driver = &(lcd_drivers[0]);

extern struct lcd_opt nt35510_opt;

void lcd_driver_hw_init(void)
{
	driver->opt->hw_init();
}

void lcd_driver_open(void)
{
	driver->opt->open(driver->dev);
}

void lcd_driver_close(void)
{
	driver->opt->close(driver->dev);
}
