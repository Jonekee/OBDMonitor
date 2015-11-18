#include <stdint.h>
#include <stdio.h>

#include "common.h"
#include "window.h"
#include "button.h"

static struct button btns[BUTTON_ID_MAX];

extern void topmenu_init(struct window *w);

extern struct window_ctrl topmenu_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y);

struct widget_item topmenu_item_map[] = {
	{1, 15, 330, 140, 140, WIDGET_TYPE_BUTTON, BUTTON_ID_PATTERN, (struct widget *)&btns[0]},
	{1, 170, 330, 140, 140, WIDGET_TYPE_BUTTON, BUTTON_ID_ITEM, (struct widget *)&btns[1]},
	{1, 325, 330, 140, 140, WIDGET_TYPE_BUTTON, BUTTON_ID_SETTING, (struct widget *)&btns[2]},
	{1, 15, 500, 60, 60, WIDGET_TYPE_BUTTON, BUTTON_ID_BACK_1, (struct widget *)&btns[3]}
};

void topmenu_init(struct window *w)
{
	uint16_t i;
	for (i = 0; i < w->item_cnt; i++) {
		if (WIDGET_TYPE_BUTTON == w->item_map[i].type) {
			struct unicode text;
			button_init((struct button *)(w->item_map[i].wid), w->item_map[i].id, w->item_map[i].w, w->item_map[i].h, text);
		}
	}
}

struct window_ctrl topmenu_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y)
{
	uint16_t i, j;
	struct window_ctrl ctrl;
	ctrl.update = 0;
	ctrl.winid = WINDOW_ID_MAX;
	ctrl.widid = WIDGET_ID_MAX;
	
	
	if (0 == ((struct button *)(w->item_map[BUTTON_ID_BACK_1].wid))->visible) {
		if (TOUCH_TYPE_PRESS == type) {
			for (i = 0; i < BUTTON_ID_MAX; i++) {
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
							case BUTTON_ID_PATTERN:
							{
							}
								break;
							case BUTTON_ID_ITEM:
								break;
							case BUTTON_ID_SETTING:
								break;
							case BUTTON_ID_BACK_1:
							{
								for (i = 0; i < BUTTON_ID_MAX; i++) {
									button_set_visible((struct button *)(w->item_map[i].wid), 0);
								}
								ctrl.update = 1;
								printf("back is pressed\n");
							}
								/* all button visible false */
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
