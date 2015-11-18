#ifndef _SETTING_H
#define _SETTING_H

#include "window.h"

extern void setting_init(struct window *w);

extern struct window_ctrl setting_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y);

extern struct widget_item *setting_item_ptr;

#endif
