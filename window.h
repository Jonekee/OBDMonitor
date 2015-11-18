#ifndef _WINDOW_H
#define _WINDOW_H

#include "common.h"

struct window {
	void (*init)(struct window *w);
	void (*paint)(struct window *w);
	struct window_ctrl (*touch)(struct window *w, enum touch_type type, uint16_t x, uint16_t y);
};

extern void window_init(struct window *w);

extern void window_paint(struct window *w);

extern struct window_ctrl window_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y);

#endif
