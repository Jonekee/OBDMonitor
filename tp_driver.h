#ifndef _TP_DRIVER_H
#define _TP_DRIVER_H

#include <stdint.h>

struct pointer {
	uint32_t x;
	uint32_t y;
};

extern void tp_driver_open(void);

extern void tp_driver_close(void);

extern int tp_driver_read(struct pointer *p, int cnt);

#endif
