#include "widget.h"

void widget_init(struct widget *wid, uint16_t id, uint16_t w, uint16_t h)
{
	wid->visible = 1;
	wid->id = id;
	wid->w = w;
	wid->h = h;
}

void widget_get_size(struct widget *wid, uint16_t *w, uint16_t *h)
{
	*w = wid->w;
	*h = wid->h;
}

void widget_set_size(struct widget *wid, uint16_t w, uint16_t h)
{
	wid->w = w;
	wid->h = h;
}

uint8_t widget_get_visible(struct widget *wid)
{
	return wid->visible;
}

extern void widget_set_visible(struct widget *wid, uint8_t v)
{
	wid->visible = v;
}

void widget_paint(struct widget *wid, uint16_t x, uint16_t y)
{
	if (wid->visible) {
		wid->paint(wid, x, y);
	}
}

int widget_touch(struct widget *wid, enum touch_type type)
{
	if (wid->visible) {
		return wid->touch(wid, type);
	} else {
		return 0;
	}
}
