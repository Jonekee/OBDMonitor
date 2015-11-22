#include "button.h"
#include "unitext.h"
#include "lcd_driver.h"

struct button_text {
	uint16_t id;
	wchar_t *text;
};

static struct button_text text_map[] = {
	{BUTTON_ID_PATTERN,   L"PATTERN"},
	{BUTTON_ID_ITEM,      L"ITEM"},
	{BUTTON_ID_SETTING,   L"SETTING"},
	{BUTTON_ID_BACK_1,    L"BACK"},
	{BUTTON_ID_SETTING_1, L"SETTING_1"},
	{BUTTON_ID_SETTING_2, L"SETTING_2"},
	{BUTTON_ID_SETTING_3, L"SETTING_3"},
	{BUTTON_ID_SETTING_4, L"SETTING_4"},
	{BUTTON_ID_SETTING_5, L"SETTING_5"},
	{BUTTON_ID_SETTING_6, L"SETTING_6"},
	{BUTTON_ID_SETTING_7, L"SETTING_7"},
};

static void button_paint(struct widget *b, uint16_t x, uint16_t y);
static int button_touch(struct widget *wid, enum touch_type type);

void button_init(struct button *b, uint16_t id, uint16_t w, uint16_t h)
{
	widget_init(&(b->base), id, w, h);
	b->base.paint = button_paint;
	b->base.touch = button_touch;
	b->pressed = 0;
}

void button_paint(struct widget *wid, uint16_t x, uint16_t y)
{
	uint16_t i;
	struct button *btn = (struct button *)wid;
	struct rectangle rect;
	rect.x = x;
	rect.y = y;
	rect.w = btn->base.w;
	rect.h = btn->base.h;
	lcd_driver_rectangle(&rect, 5, 0xFFFF);
	for (i = 0; i < WIDGET_ID_MAX; i++) {
		if (text_map[i].id == wid->id) {
			unitext_print(text_map[i].text, x + 5, y + 5);
			return;
		}
	}
}

int button_touch(struct widget *wid, enum touch_type type)
{
	struct button *btn = (struct button *)wid;
	if (TOUCH_TYPE_PRESS == type) {
		if (0 == btn->pressed) {
			btn->pressed = 1;
			return 1;
		}
	} else if (TOUCH_TYPE_RELEASE == type) {
		if (1 == btn->pressed) {
			btn->pressed = 0;
			return 1;
		}
	}
	return 0;
}
