#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>

enum {
	WINDOW_ID_TOPMENU,
	WINDOW_ID_MAX
};

#define BUTTON_ID_PATTERN 0
#define BUTTON_ID_ITEM    1
#define BUTTON_ID_SETTING 2
#define BUTTON_ID_BACK_1  3
#define BUTTON_ID_MAX     4

#define WIDGET_ID_MAX 2

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

struct unicode {
	uint8_t *code;
	uint8_t len;
};

#endif

