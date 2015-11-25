#include <stdint.h>
#include <stdio.h>

#include "common.h"
#include "window.h"

#include "button.h"

static struct button btns[7];
static uint16_t setting_touch(struct window *w, enum touch_type type, uint16_t widid);

static struct widget_item setting_item_map[] = {
{1, 120, 10, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_LANG, (struct widget *)&btns[0]},
{1, 120, 60, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_VEHICLE, (struct widget *)&btns[1]},
{1, 120, 110, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_UNIT, (struct widget *)&btns[2]},
{1, 120, 160, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_PERCENT, (struct widget *)&btns[3]},
{1, 120, 210, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_DISPLAY, (struct widget *)&btns[4]},
{1, 120, 260, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_BUZZER, (struct widget *)&btns[5]},
{1, 120, 310, 240, 40, WIDGET_TYPE_BUTTON, BUTTON_ID_FONT, (struct widget *)&btns[6]},
};

void setting_init(struct window *w)
{
	uint16_t i;
	window_init(w, setting_item_map, sizeof(setting_item_map) / sizeof(struct widget_item), setting_touch);
	for (i = 0; i < w->item_cnt; i++) {
		switch (w->item_map[i].type) {
			case WIDGET_TYPE_BUTTON:
				button_init((struct button *)(w->item_map[i].wid), w->item_map[i].id, w->item_map[i].w, w->item_map[i].h);
				break;
			default:
				break;
		}
	}
}

uint16_t setting_touch(struct window *w, enum touch_type type, uint16_t widid)
{
	if (TOUCH_TYPE_PRESS == type) {
		switch (widid) {
			case WIDGET_ID_MAX:
				return WINDOW_ID_TOPMENU;
			default:
				break;
		}
	}
	return WINDOW_ID_MAX;
}
