#include <stdint.h>
#include "button.h"

enum {
	WIDGET_TYPE_BUTTON
};

enum {
	BUTTON_ID_TEST1,
	BUTTON_ID_TEST2,
	BUTTON_ID_MAX
};

struct widget_item {
	uint8_t layer;
	uint16_t x;
	uint16_t y;
	uint8_t type;
	uint8_t id;
	struct widget *w;
};

struct demo_widget {
	struct widget wid;
	struct widget_item *item_map;
	uint16_t item_cnt;
};

static void demo_widget_paint(struct widget *wid, uint16_t x, uint16_t y);
static void demo_widget_button_init(struct button *b, uint16_t id);

static struct button btns[BUTTON_ID_MAX];

static struct widget_item widget_item_map[] = {
	{3, 100, 200, WIDGET_TYPE_BUTTON, BUTTON_ID_TEST1, (struct widget *)&btns[0]},
	{2, 110, 210, WIDGET_TYPE_BUTTON, BUTTON_ID_TEST2, (struct widget *)&btns[1]}
};

static struct demo_widget widget_inst = {
	{demo_widget_paint}, widget_item_map, 2
};

struct demo_widget *demo_widget_ptr = &widget_inst;

void demo_widget_init(struct demo_widget *w)
{
	uint16_t i;
	for (i = 0; i < w->item_cnt; i++) {
		if (WIDGET_TYPE_BUTTON == w->item_map[i].type) {
			demo_widget_button_init((struct button *)(w->item_map[i].w), w->item_map[i].id);
		}
	}
}

void demo_widget_paint(struct widget *wid, uint16_t x, uint16_t y)
{
	uint16_t i;
	uint16_t j;
	uint16_t k = 0;
	struct demo_widget *dw = (struct demo_widget *)wid;
	for (j = 0; k < dw->item_cnt; j++) {
		for (i = 0; i < dw->item_cnt; i++) {
			if (j == dw->item_map[i].layer) {
				widget_paint(dw->item_map[i].w, x + dw->item_map[i].x, y + dw->item_map[i].y);
				k++;
			}
		}
	}
}

void demo_widget_button_init(struct button *b, uint16_t id)
{
	struct unicode text;
	uint16_t w;
	uint16_t h;
	switch (id) {
		case BUTTON_ID_TEST1:
			w = 50;
			h = 100;
			break;
		case BUTTON_ID_TEST2:
			w = 100;
			h = 50;
			break;
		default:
			return;
	}
	button_init(b, 0, w, h, text);
}
