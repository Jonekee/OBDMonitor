#include "lcd_driver_if.h"
#include "lcd_driver.h"

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

void lcd_driver_rectangle(struct rectangle *rect, uint16_t l, uint16_t c)
{
	uint16_t t;
	uint16_t p;
	for (t = rect->x; t < rect->w + rect->x; t++) {
		for (p = rect->y; p < rect->y + l; p++) {
			driver->opt->draw_point(&(driver->dev), t, p, c);
			driver->opt->draw_point(&(driver->dev), t, p + rect->h, c);
		}
	}
	for (t = rect->y; t < rect->h + rect->y + l; t++) {
		for (p = rect->x; p < rect->x + l; p++) {
			driver->opt->draw_point(&(driver->dev), p, t, c);
			driver->opt->draw_point(&(driver->dev), p + rect->w, t, c);
		}
	}
}

void lcd_driver_close(void)
{
	driver->opt->close(&(driver->dev));
}
