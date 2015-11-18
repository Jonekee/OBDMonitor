#include <stdint.h>
#include <stdio.h>

#include "common.h"
#include "window.h"
#include "button.h"

static struct button btns[8];

extern void setting_init(struct window *w);

extern struct window_ctrl topmenu_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y);

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

struct widget_item *setting_item_ptr = setting_item_map;

void setting_init(struct window *w)
{
	uint16_t i;
	for (i = 0; i < w->item_cnt; i++) {
		if (WIDGET_TYPE_BUTTON == w->item_map[i].type) {
			struct unicode text;
			button_init((struct button *)(w->item_map[i].wid), w->item_map[i].id, w->item_map[i].w, w->item_map[i].h, text);
		}
	}
}

struct window_ctrl setting_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y)
{
	uint16_t i, j;
	struct window_ctrl ctrl;
	ctrl.update = 0;
	ctrl.winid = WINDOW_ID_MAX;
	ctrl.widid = WIDGET_ID_MAX;
	
	if (0 == ((struct button *)(w->item_map[BUTTON_ID_SETTING_8].wid))->visible) {
		if (TOUCH_TYPE_PRESS == type) {
			for (i = 0; i < w->item_cnt; i++) {
				button_set_visible((struct button *)(w->item_map[i].wid), 1);
			}
			ctrl.update = 1;
			printf("top menu is displayed\n");
		}
	} else {
		for (j = DEMO_WIDGET_MAX_LAYER; j > 0; j--) {
		for (i = 0; i < w->item_cnt; i++) {
			if ((j - 1) == w->item_map[i].layer) {
				if (((x > w->item_map[i].x) && (x < (w->item_map[i].x + w->item_map[i].w))) &&
					((y > w->item_map[i].y) && (y < (w->item_map[i].y + w->item_map[i].h)))) {
						ctrl.update = widget_touch(w->item_map[i].wid, type);
						ctrl.widid = w->item_map[i].id;
						switch (ctrl.widid) {
							case BUTTON_ID_SETTING_8:
							{
								ctrl.winid = WINDOW_ID_TOPMENU;
							}
								break;
							default:
								break;
						}
						if (WINDOW_ID_MAX != ctrl.winid) {
							ctrl.update = 1;
						}
						return ctrl;
				}
			}
		}
	}
}
	return ctrl;
}
