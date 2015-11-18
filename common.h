#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>

enum touch_type {
	TOUCH_TYPE_PRESS,
	TOUCH_TYPE_RELEASE
};

struct unicode {
	uint8_t *code;
	uint8_t len;
};

#endif

