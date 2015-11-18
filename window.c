#include "window.h"

void window_init(struct window *w)
{
	w->init(w);
}

void window_paint(struct window *w)
{
	w->paint(w);
}

struct window_ctrl window_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y)
{
	return w->touch(w, type, x, y);
}
