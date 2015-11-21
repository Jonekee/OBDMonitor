#ifndef _BUTTON_H
#define _BUTTON_H

#include "common.h"
#include "widget.h"

struct button {
	struct widget base;
	uint8_t pressed;
};

extern void button_init(struct button *b, uint16_t id, uint16_t w, uint16_t h);

extern void button_set_visible(struct button *b, uint8_t v);

extern void button_set_pressed(struct button *b, uint8_t p);

#endif

