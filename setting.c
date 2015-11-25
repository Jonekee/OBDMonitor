#include <stdint.h>
#include <stdio.h>

#include "common.h"
#include "window.h"

static uint16_t setting_touch(struct window *w, enum touch_type type, uint16_t widid);

static struct widget_item setting_item_map[1];

void setting_init(struct window *w)
{
	uint16_t i;
	window_init(w, setting_item_map, 0, setting_touch);
	for (i = 0; i < w->item_cnt; i++) {

	}
}

uint16_t setting_touch(struct window *w, enum touch_type type, uint16_t widid)
{
	if (TOUCH_TYPE_PRESS == type) {
		return WINDOW_ID_TOPMENU;
	} else {
		return WINDOW_ID_MAX;
	}
}
