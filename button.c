#include "button.h"
#include "lcd_driver.h"

static void button_paint(struct widget *b, uint16_t x, uint16_t y);
static int button_touch(struct widget *wid, enum touch_type type);

extern void button_init(struct button *b, uint16_t id, uint16_t w, uint16_t h, struct unicode text)
{
	widget_init(&(b->base), id, w, h);
	b->base.paint = button_paint;
	b->base.touch = button_touch;
	b->pressed = 0;
	b->text = text;
}

void button_set_pressed(struct button *b, uint8_t p)
{
	b->pressed = p;
}

void button_paint(struct widget *wid, uint16_t x, uint16_t y)
{
	struct button *btn = (struct button *)wid;
	struct rectangle rect;
	rect.x = x;
	rect.y = y;
	rect.w = btn->base.w;
	rect.h = btn->base.h;
	lcd_driver_rectangle(&rect, 5, 0xFFFF);
}

int button_touch(struct widget *wid, enum touch_type type)
{
	struct button *btn = (struct button *)wid;
	if (TOUCH_TYPE_PRESS == type) {
		if (0 == btn->pressed) {
			btn->pressed = 1;
			return 1;
		}
	} else if (TOUCH_TYPE_RELEASE == type) {
		if (1 == btn->pressed) {
			btn->pressed = 0;
			return 1;
		}
	}
	return 0;
}
