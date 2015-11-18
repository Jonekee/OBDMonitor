#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>

enum {
	WINDOW_ID_DEMO,
	WINDOW_ID_MAX
};

enum {
	BUTTON_ID_TEST1 = 0,
	BUTTON_ID_TEST2 = 1,
	BUTTON_ID_MAX,
	WIDGET_ID_MAX
};

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

