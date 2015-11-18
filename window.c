#include "window.h"
#include "widget.h"
#include "lcd_driver.h"

void window_init(struct window *w, struct widget_item *item, uint16_t cnt, struct window_opt opts)
{
	w->item_map = item;
	w->item_cnt = cnt;
	w->touch = opts.touch;
	opts.init(w);
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
	return w->touch(w, type, x, y);
}
