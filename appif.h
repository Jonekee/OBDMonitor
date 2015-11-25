#ifndef _APPIF_H
#define _APPIF_H

#include "common.h"
#include <stdint.h>

extern void appif_touch_event(uint16_t widid, enum touch_type type);

extern int appif_idle_task(void);

#endif
