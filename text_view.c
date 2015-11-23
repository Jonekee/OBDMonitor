#include "text_view.h"
#include "unitext.h"
#include "lcd_driver.h"

static void text_view_paint(struct widget *b, uint16_t x, uint16_t y);
static int text_view_touch(struct widget *wid, enum touch_type type);

struct text_view_text {
	uint16_t id;
	wchar_t *text;
};

static struct text_view_text text_view_text_map[] = {
	{TEXT_VIEW_ID_SETTING_1,   L"RPM: "},
	{TEXT_VIEW_ID_SETTING_2,   L"SPD: "},
	{TEXT_VIEW_ID_SETTING_3,   L"MAF: "},
	{TEXT_VIEW_ID_SETTING_4,   L"TBD"},
	{TEXT_VIEW_ID_SETTING_5,   L"TBD"},
	{TEXT_VIEW_ID_SETTING_6,   L"TBD"},
	{TEXT_VIEW_ID_SETTING_7,   L"TBD"},
	{TEXT_VIEW_ID_SETTING_8,   L"BACK"},
};

extern uint32_t rpm_value;
extern uint32_t spd_value;
extern uint32_t maf_value;

void text_view_init(struct text_view *t, uint16_t id, uint16_t w, uint16_t h)
{
	uint16_t i;
	widget_init(&(t->base), id, w, h);
	t->base.paint = text_view_paint;
	t->base.touch = text_view_touch;
	for (i = 0; i < WIDGET_ID_MAX; i++) {
		if (text_view_text_map[i].id == t->base.id) {
			t->label = text_view_text_map[i].text;
		}
	}
}

void text_view_paint(struct widget *wid, uint16_t x, uint16_t y)
{
	uint32_t value = 0;
	struct text_view *view = (struct text_view *)wid;
	struct rectangle rect;
	wchar_t buf[20];
	rect.x = x;
	rect.y = y;
	rect.w = view->base.w;
	rect.h = view->base.h;
	lcd_driver_rectangle(&rect, 5, 0xFFFF);
	switch (wid->id) {
		case TEXT_VIEW_ID_SETTING_1:
		{
			value = rpm_value;
		}
		break;
		case TEXT_VIEW_ID_SETTING_2:
		{
			value = spd_value;
		}
		break;
		case TEXT_VIEW_ID_SETTING_3:
		{
			value = maf_value;
		}
		break;
		case TEXT_VIEW_ID_SETTING_4:
		{
		
		}
		break;
		case TEXT_VIEW_ID_SETTING_5:
		{
		
		}
		break;
		case TEXT_VIEW_ID_SETTING_6:
		{
		
		}
		break;
		case TEXT_VIEW_ID_SETTING_7:
		{
		
		}
		break;
		case TEXT_VIEW_ID_SETTING_8:
		{
		
		}
		break;
		default:
		break;
	}
	swprintf(buf, 20, L"%ls%d", view->label, value);
	unitext_print(buf, x + 5, y + 5);
}

int text_view_touch(struct widget *wid, enum touch_type type)
{
	return 0;
}
