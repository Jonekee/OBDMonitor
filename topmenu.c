#include <stdint.h>
#include <stdio.h>

#include "common.h"
#include "window.h"
#include "button.h"

static struct button btns[4];

static uint16_t topmenu_touch(struct window *w, enum touch_type type, uint16_t widid);

static struct widget_item topmenu_item_map[] = {
	{1, 15, 330, 140, 140, WIDGET_TYPE_BUTTON, BUTTON_ID_PATTERN, (struct widget *)&btns[0]},
	{1, 170, 330, 140, 140, WIDGET_TYPE_BUTTON, BUTTON_ID_ITEM, (struct widget *)&btns[1]},
	{1, 325, 330, 140, 140, WIDGET_TYPE_BUTTON, BUTTON_ID_SETTING, (struct widget *)&btns[2]},
	{1, 15, 500, 60, 60, WIDGET_TYPE_BUTTON, BUTTON_ID_BACK_1, (struct widget *)&btns[3]}
};

void topmenu_init(struct window *w)
{
	uint16_t i;
	window_init(w, topmenu_item_map, 4, topmenu_touch);
	for (i = 0; i < w->item_cnt; i++) {
		if (WIDGET_TYPE_BUTTON == w->item_map[i].type) {
			button_init((struct button *)(w->item_map[i].wid), w->item_map[i].id, w->item_map[i].w, w->item_map[i].h);
		}
	}
}

uint16_t topmenu_touch(struct window *w, enum touch_type type, uint16_t widid)
{
	uint16_t i;
	switch (widid) {
		case WIDGET_ID_MAX:
			if (TOUCH_TYPE_PRESS == type) {
				for (i = 0; i < w->item_cnt; i++) {
					widget_set_visible(w->item_map[i].wid, 1);
				}
				printf("top menu is displayed\n");
				return WINDOW_ID_TOPMENU;
			}
			break;
		case BUTTON_ID_SETTING:
			if (TOUCH_TYPE_PRESS == type) {
				return WINDOW_ID_SETTING;
			}
		case BUTTON_ID_BACK_1:
		{
			if (TOUCH_TYPE_PRESS == type) {
				for (i = 0; i < w->item_cnt; i++) {
					widget_set_visible(w->item_map[i].wid, 0);
				}
				printf("back is pressed\n");
				return WINDOW_ID_TOPMENU;
			}
		}
		default:
			break;
	}
	return WINDOW_ID_MAX;
}
