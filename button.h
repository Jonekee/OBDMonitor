#ifndef _BUTTON_H
#define _BUTTON_H

#include "common.h"
#include "widget.h"

struct button {
	struct widget base;
	uint8_t type;
	uint8_t w;
	uint8_t h;
	uint8_t pressed;
	uint8_t visible;
	struct unicode text;
};

extern void button_init(struct button *b, uint8_t type, uint16_t w, uint16_t h, struct unicode text);

extern void button_set_visible(struct button *b, uint8_t v);

extern void button_set_pressed(struct button *b, uint8_t p);

#endif

