#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>

#define WINDOW_ID_TOPMENU 0
#define WINDOW_ID_SETTING 1
#define	WINDOW_ID_MAX     2

#define TEXT_VIEW_ID_1     0
#define TEXT_VIEW_ID_2     1
#define BUTTON_ID_PATTERN  2
#define BUTTON_ID_ITEM     3
#define BUTTON_ID_SETTING  4
#define BUTTON_ID_BACK_1   5
#define BUTTON_ID_RPM      6
#define BUTTON_ID_SPD      7
#define BUTTON_ID_MAF      8
#define BUTTON_ID_LANG     9
#define BUTTON_ID_VEHICLE  10
#define BUTTON_ID_UNIT     11
#define BUTTON_ID_PERCENT  12
#define BUTTON_ID_DISPLAY  13
#define BUTTON_ID_BUZZER   14
#define BUTTON_ID_FONT     15
#define WIDGET_ID_MAX      16

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

