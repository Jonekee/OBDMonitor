#include "tp_driver_if.h"

static void gt9147_open(struct tp_device *dev);
static int gt9147_read(struct tp_device *dev, uint16_t *x, uint16_t *y);
static void gt9147_close(struct tp_device *dev);

void gt9147_open(struct tp_device *dev)
{

}

int gt9147_read(struct tp_device *dev, uint16_t *x, uint16_t *y)
{
	return 0;
}

void gt9147_close(struct tp_device *dev)
{

}

struct tp_opts gt9147_opts = {
	gt9147_open,
	gt9147_read,
	gt9147_close
};
