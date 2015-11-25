#ifndef _TEXT_VIEW_H
#define _TEXT_VIEW_H

#include <wchar.h>
#include <stdint.h>
#include "widget.h"

struct text_view {
	struct widget base;
	wchar_t *label;
	uint32_t *value;
	uint16_t w;
	uint16_t h;
};

extern void text_view_init(struct text_view *t, uint16_t id, uint16_t w, uint16_t h);

extern void text_view_bind(struct text_view *t, wchar_t *label, uint32_t *value);

#endif
