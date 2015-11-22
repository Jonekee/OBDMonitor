#ifndef _TEXT_VIEW_H
#define _TEXT_VIEW_H

#include <wchar.h>
#include <stdint.h>
#include "widget.h"

struct text_view {
	struct widget base;
	wchar_t *label;
	uint16_t w;
	uint16_t h;
	uint32_t *value;
};

extern void text_view_init(struct text_view *t, uint16_t id, uint16_t w, uint16_t h);

#endif
