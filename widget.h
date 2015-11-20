#ifndef _WIDGET_H
#define _WIDGET_H

#include <stdint.h>
#include "common.h"

struct widget {
	uint16_t id;
	uint8_t visible;
	uint16_t w;
	uint16_t h;
	void (*paint)(struct widget *wid, uint16_t x, uint16_t y);
	int (*touch)(struct widget *wid, enum touch_type type);
};

extern void widget_init(struct widget *wid, uint16_t id, uint16_t w, uint16_t h);

extern void widget_get_size(struct widget *wid, uint16_t *w, uint16_t *h);

extern void widget_set_size(struct widget *wid, uint16_t w, uint16_t h);

extern uint8_t widget_get_visible(struct widget *wid);

extern void widget_set_visible(struct widget *wid, uint8_t v);

extern void widget_paint(struct widget *wid, uint16_t x, uint16_t y);

extern int widget_touch(struct widget *wid, enum touch_type type);

#endif
