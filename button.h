#ifndef _BUTTON_H
#define _BUTTON_H

#include "widget.h"

struct button {
	struct widget base;
	uint8_t pressed;
};

extern void button_init(struct button *b, uint16_t id, uint16_t w, uint16_t h);

#endif

