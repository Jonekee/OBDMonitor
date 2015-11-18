#ifndef _WINMGMT_H
#define _WINMGMT_H

#include "common.h"

enum {
	TOP_WIDGET_ID_DEMO,
	TOP_WIDGET_ID_MAX
};

extern void winmgmt_init(uint16_t id);

extern int winmgmt_touch(enum touch_type type, uint16_t x, uint16_t y);

extern void winmgmt_paint(void);

#endif
