#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>

#define WINDOW_ID_TOPMENU 0
#define WINDOW_ID_SETTING 1
#define	WINDOW_ID_MAX     2


#define BUTTON_ID_PATTERN   0
#define BUTTON_ID_ITEM      1
#define BUTTON_ID_SETTING   2
#define BUTTON_ID_BACK_1    3
#define TEXT_VIEW_ID_SETTING_1 4
#define TEXT_VIEW_ID_SETTING_2 5
#define TEXT_VIEW_ID_SETTING_3 6
#define TEXT_VIEW_ID_SETTING_4 7
#define TEXT_VIEW_ID_SETTING_5 8
#define TEXT_VIEW_ID_SETTING_6 9
#define TEXT_VIEW_ID_SETTING_7 10
#define TEXT_VIEW_ID_SETTING_8 11

#define WIDGET_ID_MAX       12

struct window_ctrl {
	int update;
	uint16_t widid;
	uint16_t winid;
};

struct pointer {
	uint16_t x;
	uint16_t y;
};

enum touch_type {
	TOUCH_TYPE_PRESS,
	TOUCH_TYPE_RELEASE,
	TOUCH_TYPE_NONE
};

#endif

