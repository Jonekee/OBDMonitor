#include "button.h"
#include "unitext.h"
#include "lcd_driver.h"

struct btn_text_item {
	uint16_t id;
	wchar_t *text;
};

static struct btn_text_item btn_text_map[] = {
	{BUTTON_ID_PATTERN, L"PATTERN"},
	{BUTTON_ID_ITEM, L"ITEM"},
	{BUTTON_ID_SETTING, L"SETTING"},
	{BUTTON_ID_RPM, L"RPM"},
	{BUTTON_ID_SPD, L"SPD"},
	{BUTTON_ID_MAF, L"MAF"},
	{BUTTON_ID_LANG, L"LANGUAGE"},
  {BUTTON_ID_VEHICLE, L"VEHICLE"},
	{BUTTON_ID_UNIT, L"UNIT"},
  {BUTTON_ID_PERCENT, L"PERCENT"},
  {BUTTON_ID_DISPLAY, L"DISPLAY"},
  {BUTTON_ID_BUZZER, L"BUZZER"},
  {BUTTON_ID_FONT, L"FONT"},
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
	for (i = 0; i < sizeof(btn_text_map) / sizeof(struct btn_text_item); i++) {
		if (wid->id == btn_text_map[i].id) {
			unitext_print(btn_text_map[i].text, x + 5, y + 5);
			break;
		}
	}
}

int button_touch(struct widget *wid, enum touch_type type)
{
	return 0;
}
