#include "window.h"
#include "widget.h"
#include "lcd_driver.h"

void window_init(struct window *w, struct widget_item *item, uint16_t cnt, touch_cb touch)
{
	w->item_map = item;
	w->item_cnt = cnt;
	w->touch = touch;
}

void window_paint(struct window *w)
{
	uint16_t i;
	uint16_t j;
	lcd_driver_clear();
	for (j = 0; j < DEMO_WIDGET_MAX_LAYER; j++) {
		for (i = 0; i < w->item_cnt; i++) {
			if (j == w->item_map[i].layer) {
				widget_paint(w->item_map[i].wid, w->item_map[i].x, w->item_map[i].y);
			}
		}
	}
}

struct window_ctrl window_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y)
{
	uint16_t i, j;
	struct window_ctrl ctrl;
	ctrl.update = 0;
	ctrl.winid = WINDOW_ID_MAX;
	ctrl.widid = WIDGET_ID_MAX;
	
	for (j = DEMO_WIDGET_MAX_LAYER; j > 0; j--) {
		for (i = 0; i < w->item_cnt; i++) {
			if ((j - 1) == w->item_map[i].layer) {
				if (widget_get_visible(w->item_map[i].wid)) {
					uint16_t ww, hh;
					widget_get_size(w->item_map[i].wid, &ww, &hh);
					if (((x > w->item_map[i].x) && (x < (w->item_map[i].x + ww))) &&
					((y > w->item_map[i].y) && (y < (w->item_map[i].y + hh)))) {
						ctrl.update = widget_touch(w->item_map[i].wid, type);
						ctrl.widid = w->item_map[i].id;
						ctrl.winid = w->touch(w, type, ctrl.widid);
						if (WINDOW_ID_MAX != ctrl.winid) {
							ctrl.update = 1;
						}
						return ctrl;
					}
				}
			}
		}
	}
	ctrl.winid = w->touch(w, type, ctrl.widid);
	if (WINDOW_ID_MAX != ctrl.winid) {
		ctrl.update = 1;
	}
	return ctrl;
}
