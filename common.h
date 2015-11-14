#ifndef _COMMON_H
#define _COMMON_H

#include <stdint.h>

struct rect {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
};

struct unicode {
	uint8_t *code;
	uint8_t len;
};

#endif
