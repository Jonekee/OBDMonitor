#include "lcd_driver_if.h"

#define NT35510_BASE 0x6C00007E

struct rectangle {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
};

static uint16_t fb[480 * 800];
static struct rectangle update_area;

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
	update_area.x = update_area.y = update_area.w = update_area.h = 0;
}

void lcd_driver_update(void)
{
	if (update_area.w * update_area.h) {
		driver->opt->draw_rectangle(&(driver->dev), update_area.x, update_area.y, update_area.w, update_area.h, fb);
		update_area.x = update_area.y = update_area.w = update_area.h = 0;
	}
}

void lcd_driver_close(void)
{
	driver->opt->close(&(driver->dev));
	update_area.x = update_area.y = update_area.w = update_area.h = 0;
}
