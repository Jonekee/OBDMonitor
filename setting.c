#include <stdint.h>
#include <stdio.h>

#include "common.h"
#include "window.h"
#include "button.h"

static struct button btns[8];

static uint16_t setting_touch(struct window *w, enum touch_type type, uint16_t widid);

static struct widget_item setting_item_map[] = {
	{1, 120, 10, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_SETTING_1, (struct widget *)&btns[0]},
	{1, 120, 60, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_SETTING_2, (struct widget *)&btns[1]},
	{1, 120, 110, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_SETTING_3, (struct widget *)&btns[2]},
	{1, 120, 160, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_SETTING_4, (struct widget *)&btns[3]},
	{1, 120, 210, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_SETTING_5, (struct widget *)&btns[4]},
	{1, 120, 260, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_SETTING_6, (struct widget *)&btns[5]},
	{1, 120, 310, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_SETTING_7, (struct widget *)&btns[6]},
	{1, 120, 360, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_SETTING_8, (struct widget *)&btns[7]}
};

void setting_init(struct window *w)
{
	uint16_t i;
	window_init(w, setting_item_map, 8, setting_touch);
	for (i = 0; i < w->item_cnt; i++) {
		if (WIDGET_TYPE_BUTTON == w->item_map[i].type) {
			button_init((struct button *)(w->item_map[i].wid), w->item_map[i].id, w->item_map[i].w, w->item_map[i].h);
		}
	}
}

uint16_t setting_touch(struct window *w, enum touch_type type, uint16_t widid)
{
	switch (widid) {
		case BUTTON_ID_SETTING_8:
				if (TOUCH_TYPE_PRESS == type) {
					return WINDOW_ID_TOPMENU;
				}
			default:
				break;
	}
	return WINDOW_ID_MAX;
}
