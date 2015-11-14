#ifndef _SYSEVENT_IF_H
#define _SYSEVENT_IF_H

#include <stdint.h>

enum touch_type {
	TOUCH_TYPE_PRESS,
	TOUCH_TYPE_RELEASE
};

struct touch_event_if {
	void (*touch_event)(enum touch_type type, uint16_t x, uint16_t y);
};

#endif
