#ifndef _TP_DRIVER_IF_H
#define _TP_DRIVER_IF_H

#include <stdint.h>

struct tp_device {
	uint16_t height;
	uint16_t width;
};

struct tp_opts {
	void (*open)(struct tp_device *dev);
	int (*read)(struct tp_device *dev, uint16_t *x, uint16_t *y);
	void (*close)(struct tp_device *dev);
};

#endif
