#include "button.h"

extern void button_init(struct button *b, uint8_t type, uint16_t w, uint16_t h, struct unicode text)
{
	if (b) {
		b->type = type;
		b->pressed = 0;
		b->visible = 0;
		b->w = w;
		b->h = h;
		b->text = text;
	}
}

void button_set_visible(struct button *b, uint8_t v)
{
	if (b) {
		b->visible = v;
	}
}

void button_set_pressed(struct button *b, uint8_t p)
{
	if (b) {
		b->pressed = p;
	}
}

