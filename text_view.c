#include "text_view.h"
#include "unitext.h"
#include "lcd_driver.h"

static void text_view_paint(struct widget *b, uint16_t x, uint16_t y);
static int text_view_touch(struct widget *wid, enum touch_type type);

void text_view_init(struct text_view *t, uint16_t id, uint16_t w, uint16_t h)
{
	widget_init(&(t->base), id, w, h);
	t->base.paint = text_view_paint;
	t->base.touch = text_view_touch;
	t->label = 0;
	t->value = 0;
}

void text_view_paint(struct widget *wid, uint16_t x, uint16_t y)
{
	struct text_view *view = (struct text_view *)wid;
	struct rectangle rect;
	rect.x = x;
	rect.y = y;
	rect.w = view->base.w;
	rect.h = view->base.h;
	lcd_driver_rectangle(&rect, 5, 0xFFFF);
	if (view->label) {
		wchar_t buf[20];
		swprintf(buf, 20, L"%ls: %ld", view->label, *(view->value));
		unitext_print(buf, x + 5, y + 5);
	}
}

void text_view_bind(struct text_view *t, wchar_t *text, uint32_t *data)
{
	t->label = text;
	t->value = data;
}

int text_view_touch(struct widget *wid, enum touch_type type)
{
	return 0;
}
