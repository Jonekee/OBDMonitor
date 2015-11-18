#ifndef _WINDOW_H
#define _WINDOW_H

#include "common.h"

#define DEMO_WIDGET_MAX_LAYER 5

enum {
	WIDGET_TYPE_BUTTON
};

struct widget_item {
	uint8_t layer;
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	uint8_t type;
	uint8_t id;
	struct widget *wid;
};

struct window;
typedef struct window_ctrl (*touch_cb)(struct window *w, enum touch_type type, uint16_t x, uint16_t y);


struct window_opt {
	void (*init)(struct window *w);
	touch_cb touch;
};

struct window {
	struct widget_item *item_map;
	uint16_t item_cnt;
	touch_cb touch;
};

extern void window_init(struct window *w, struct widget_item *item, uint16_t cnt, struct window_opt opts);

extern void window_paint(struct window *w);

extern struct window_ctrl window_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y);

#endif
