#ifndef _DEMO_WIDGET_H
#define _DEMO_WIDGET_H

#include "window.h"

extern void topmenu_init(struct window *w);

extern struct window_ctrl topmenu_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y);

extern struct widget_item *topmenu_item_map;

#endif
