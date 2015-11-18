#include <stdint.h>
#include "lcd_driver.h"
#include "common.h"
#include "window.h"
#include "button.h"

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

struct demo_window {
	struct window w;
	struct widget_item *item_map;
	uint16_t item_cnt;
};

static void demo_window_init(struct window *w);

static void demo_window_paint(struct window *wid);

static struct window_ctrl demo_window_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y);

static struct button btns[BUTTON_ID_MAX];

static struct widget_item widget_item_map[] = {
	{3, 0, 0, 50, 100, WIDGET_TYPE_BUTTON, BUTTON_ID_TEST1, (struct widget *)&btns[0]},
	{2, 110, 210, 100, 50, WIDGET_TYPE_BUTTON, BUTTON_ID_TEST2, (struct widget *)&btns[1]}
};

static struct demo_window window_inst = {
	{demo_window_init, demo_window_paint, demo_window_touch}, widget_item_map, 2
};

struct window *demo_window_ptr = (struct window *)&window_inst;

void demo_window_init(struct window *w)
{
	uint16_t i;
	struct demo_window *dw = (struct demo_window *)w;
	for (i = 0; i < dw->item_cnt; i++) {
		if (WIDGET_TYPE_BUTTON == dw->item_map[i].type) {
			struct unicode text;
			button_init((struct button *)(dw->item_map[i].wid), dw->item_map[i].id, dw->item_map[i].w, dw->item_map[i].h, text);
		}
	}
}

void demo_window_paint(struct window *wid)
{
	uint16_t i;
	uint16_t j;
	struct demo_window *dw = (struct demo_window *)wid;
	lcd_driver_clear();
	for (j = 0; j < DEMO_WIDGET_MAX_LAYER; j++) {
		for (i = 0; i < dw->item_cnt; i++) {
			if (j == dw->item_map[i].layer) {
				widget_paint(dw->item_map[i].wid, dw->item_map[i].x, dw->item_map[i].y);
			}
		}
	}
}

struct window_ctrl demo_window_touch(struct window *w, enum touch_type type, uint16_t x, uint16_t y)
{
	uint16_t i, j;
	struct window_ctrl ctrl;
	struct demo_window *dw = (struct demo_window *)w;
	ctrl.update = 0;
	ctrl.winid = WINDOW_ID_MAX;
	ctrl.widid = WIDGET_ID_MAX;
	
	for (j = DEMO_WIDGET_MAX_LAYER; j > 0; j--) {
		for (i = 0; i < dw->item_cnt; i++) {
			if ((j - 1) == dw->item_map[i].layer) {
				if (((x > dw->item_map[i].x) && (x < (dw->item_map[i].x + dw->item_map[i].w))) &&
					((y > dw->item_map[i].y) && (y < (dw->item_map[i].y + dw->item_map[i].h)))) {
						ctrl.update = widget_touch(dw->item_map[i].wid, type);
						ctrl.widid = dw->item_map[i].id;
						switch (ctrl.widid) {
							case BUTTON_ID_TEST1:
								break;
							case BUTTON_ID_TEST2:
								break;
							default:
								break;
						}
						return ctrl;
				}
			}
		}
	}
	return ctrl;
}
