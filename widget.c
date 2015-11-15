#include "widget.h"

void widget_paint(struct widget *wid, uint16_t x, uint16_t y)
{
	wid->paint(wid, x, y);
}
