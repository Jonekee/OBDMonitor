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
	b->visible = 1;
	b->text = text;
}

void button_set_visible(struct button *b, uint8_t v)
{
	b->visible = v;
}

void button_set_pressed(struct button *b, uint8_t p)
{
	b->pressed = p;
}

void button_paint(struct widget *wid, uint16_t x, uint16_t y)
{
	struct button *btn = (struct button *)wid;
	if (btn->visible) {
		struct rectangle rect;
			rect.x = x;
			rect.y = y;
			rect.w = btn->base.w;
			rect.h = btn->base.h;
		if (btn->pressed) {
			lcd_driver_rectangle(&rect, 5, 0xFFFF);
		} else {
			lcd_driver_rectangle(&rect, 5, 0xF800);
		}
	}
}

int button_touch(struct widget *wid, enum touch_type type)
{
	return 1;
}
