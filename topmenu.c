#include <stdint.h>
#include <stdio.h>

#include "window.h"

#include "text_view.h"
#include "button.h"


extern uint32_t rpm_value;
extern uint32_t spd_value;
extern uint32_t maf_value;

static struct text_view views[2];
static struct button btns[7];

static int status = 0;
static uint16_t cur_text_view_id = WIDGET_ID_MAX;

static uint16_t topmenu_touch(struct window *w, enum touch_type type, uint16_t widid);
static void topmenu_set_position(struct window *w, uint16_t id, uint16_t x, uint16_t y);

static struct widget_item topmenu_item_map[9] = {
	{1, 20, 20, 200, 60, WIDGET_TYPE_TEXT_VIEW, TEXT_VIEW_ID_1, (struct widget *)&views[0]},
	{1, 260, 20, 200, 60, WIDGET_TYPE_TEXT_VIEW, TEXT_VIEW_ID_2, (struct widget *)&views[1]},
	
	{2, 15, 330, 140, 140, WIDGET_TYPE_BUTTON, BUTTON_ID_PATTERN, (struct widget *)&btns[0]},
	{2, 170, 330, 140, 140, WIDGET_TYPE_BUTTON, BUTTON_ID_ITEM, (struct widget *)&btns[1]},
	{2, 325, 330, 140, 140, WIDGET_TYPE_BUTTON, BUTTON_ID_SETTING, (struct widget *)&btns[2]},
	{2, 15, 500, 60, 60, WIDGET_TYPE_BUTTON, BUTTON_ID_BACK_1, (struct widget *)&btns[3]},
	
	{2, 0, 100, 200, 60, WIDGET_TYPE_BUTTON, BUTTON_ID_RPM, (struct widget *)&btns[4]},
	{2, 0, 180, 200, 60, WIDGET_TYPE_BUTTON, BUTTON_ID_SPD, (struct widget *)&btns[5]},
	{2, 0, 260, 200, 60, WIDGET_TYPE_BUTTON, BUTTON_ID_MAF, (struct widget *)&btns[6]},
};

void topmenu_init(struct window *w)
{
	uint16_t i;
	window_init(w, topmenu_item_map, sizeof(topmenu_item_map) / sizeof(struct widget_item), topmenu_touch);
	for (i = 0; i < w->item_cnt; i++) {
		switch (w->item_map[i].type) {
			case WIDGET_TYPE_TEXT_VIEW:
			{
				text_view_init((struct text_view *)(w->item_map[i].wid), w->item_map[i].id, w->item_map[i].w, w->item_map[i].h);
			}
				break;
			case WIDGET_TYPE_BUTTON:
			{
				button_init((struct button *)(w->item_map[i].wid), w->item_map[i].id, w->item_map[i].w, w->item_map[i].h);
				widget_set_visible(w->item_map[i].wid, 0);
			}
				break;
			default:
				break;
		}
	}
	status = 0;
}

uint16_t topmenu_touch(struct window *w, enum touch_type type, uint16_t widid)
{
	if (TOUCH_TYPE_PRESS == type) {
		switch (widid) {
			case WIDGET_ID_MAX:
			{
				if (0 == status) {
					uint16_t i;
					for (i = 0; i < w->item_cnt; i++) {
						switch (w->item_map[i].id) {
							case BUTTON_ID_PATTERN:
							case BUTTON_ID_ITEM:
							case BUTTON_ID_SETTING:
							case BUTTON_ID_BACK_1:
								widget_set_visible(w->item_map[i].wid, 1);
								break;
							default:
								break;
						}
					}
					status = 1;
					return WINDOW_ID_TOPMENU;
				} else if (2 == status) {
					uint16_t i;
					for (i = 0; i < w->item_cnt; i++) {
						switch (w->item_map[i].id) {
							case BUTTON_ID_RPM:
							case BUTTON_ID_SPD:
							case BUTTON_ID_MAF:
								widget_set_visible(w->item_map[i].wid, 0);
								break;
							case TEXT_VIEW_ID_1:
							case TEXT_VIEW_ID_2:
								widget_set_visible(w->item_map[i].wid, 1);
								break;
							default:
								break;
						}
					}
					status = 0;
					return WINDOW_ID_TOPMENU;
				}
			}
				break;
			case BUTTON_ID_BACK_1:
			{
				uint16_t i;
				for (i = 0; i < w->item_cnt; i++) {
					switch (w->item_map[i].id) {
							case BUTTON_ID_PATTERN:
							case BUTTON_ID_ITEM:
							case BUTTON_ID_SETTING:
							case BUTTON_ID_BACK_1:
								widget_set_visible(w->item_map[i].wid, 0);
								break;
							default:
								break;
						}
				}
				status = 0;
				return WINDOW_ID_TOPMENU;
			}
			case TEXT_VIEW_ID_1:
			case TEXT_VIEW_ID_2:
			{
				if (0 == status) {
					uint16_t i;
					for (i = 0; i < w->item_cnt; i++) {
						switch (w->item_map[i].id) {
							case TEXT_VIEW_ID_1:
							case TEXT_VIEW_ID_2:
							{
								widget_set_visible(w->item_map[i].wid, 0);
							}
								break;
							case BUTTON_ID_RPM:
							case BUTTON_ID_SPD:
							case BUTTON_ID_MAF:
							{
								if (TEXT_VIEW_ID_1 == widid) {
									topmenu_set_position(w, w->item_map[i].id, 20, w->item_map[i].y);
								} else {
									topmenu_set_position(w, w->item_map[i].id, 260, w->item_map[i].y);
								}
								cur_text_view_id = widid;
								widget_set_visible(w->item_map[i].wid, 1);
							}
								break;
						}
					}
					status = 2;
					return WINDOW_ID_TOPMENU;
				}
			}
				break;
			case BUTTON_ID_RPM:
			case BUTTON_ID_SPD:
			case BUTTON_ID_MAF:
			{
				uint16_t i;
					for (i = 0; i < w->item_cnt; i++) {
						switch (w->item_map[i].id) {
							case BUTTON_ID_RPM:
							case BUTTON_ID_SPD:
							case BUTTON_ID_MAF:
								widget_set_visible(w->item_map[i].wid, 0);
								break;
							case TEXT_VIEW_ID_1:
							case TEXT_VIEW_ID_2:
								if (w->item_map[i].id == cur_text_view_id) {
									switch (widid) {
										case BUTTON_ID_RPM:
											text_view_bind((struct text_view *)w->item_map[i].wid, L"RPM", &rpm_value);
											break;
										case BUTTON_ID_SPD:
											text_view_bind((struct text_view *)w->item_map[i].wid, L"SPD", &spd_value);
											break;
										case BUTTON_ID_MAF:
											text_view_bind((struct text_view *)w->item_map[i].wid, L"MAF", &maf_value);
											break;
										default:
											break;
									}
								}
								widget_set_visible(w->item_map[i].wid, 1);
								break;
							default:
								break;
						}
					}
					status = 0;
					return WINDOW_ID_TOPMENU;
			}
			case BUTTON_ID_SETTING:
				return WINDOW_ID_SETTING;
			default:
				break;
		}
	}
	return WINDOW_ID_MAX;
}

void topmenu_set_position(struct window *w, uint16_t id, uint16_t x, uint16_t y)
{
	uint16_t i;
	for (i = 0; i < w->item_cnt; i++) {
		if (w->item_map[i].id == id) {
			if (x) {
				w->item_map[i].x = x;
			}
			if (y) {
				w->item_map[i].y = y;
			}
			break;
		}
	}
}
