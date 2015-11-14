#include "button.h"
#include "lcd_driver.h"

static void button_paint(struct widget *b, uint16_t x, uint16_t y);

extern void button_init(struct button *b, uint8_t type, uint16_t w, uint16_t h, struct unicode text)
{
	b->base.paint = button_paint;
	b->type = type;
	b->pressed = 0;
	b->visible = 0;
	b->w = w;
	b->h = h;
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
	(void)btn;
}
