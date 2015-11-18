#include "widget.h"

void widget_init(struct widget *wid, uint16_t id, uint16_t w, uint16_t h)
{
	wid->id = id;
	wid->w = w;
	wid->h = h;
}
void widget_paint(struct widget *wid, uint16_t x, uint16_t y)
{
	wid->paint(wid, x, y);
}

int widget_touch(struct widget *wid, enum touch_type type)
{
	return wid->touch(wid, type);
}
