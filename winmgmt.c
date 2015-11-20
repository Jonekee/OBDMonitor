#include <stdint.h>
#include "winmgmt.h"
#include "window.h"

extern void topmenu_init(struct window *w);
extern void setting_init(struct window *w);

static struct window widget_map[WINDOW_ID_MAX];

static struct window *cur_widget = 0;

void winmgmt_init(uint16_t id)
{
	topmenu_init(&widget_map[WINDOW_ID_TOPMENU]);
	setting_init(&widget_map[WINDOW_ID_SETTING]);
	cur_widget = &widget_map[WINDOW_ID_TOPMENU];
	window_paint(cur_widget);
}

void winmgmt_paint(void)
{
	if (cur_widget) {
		window_paint(cur_widget);
	}
}

int winmgmt_touch(enum touch_type type, uint16_t x, uint16_t y, uint16_t *widid)
{
	if (cur_widget) {
		struct window_ctrl ctrl = window_touch(cur_widget, type, x, y);
		*widid = ctrl.widid;
		if (WINDOW_ID_MAX != ctrl.winid) {
			cur_widget = &widget_map[ctrl.winid];
			return 1;
		} else if (ctrl.update) {
			return 1;
		}
	}
	return 0;
}

