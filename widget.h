#ifndef _WIDGET_H
#define _WIDGET_H

#include <stdint.h>

struct widget {
	void (*paint)(struct widget *wid, uint16_t x, uint16_t y);
};

extern void widget_paint(struct widget *wid, uint16_t x, uint16_t y);

#endif
