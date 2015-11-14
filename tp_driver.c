#include "tp_driver_if.h"
#include "tp_driver.h"

struct tp_driver {
	struct tp_device dev;
	struct tp_opts *opt;
};

extern struct tp_opts gt9147_opts;

static struct tp_driver tp_drv = {
	{800, 480}, &gt9147_opts
};

static struct tp_driver *driver = &tp_drv;

void tp_driver_open(void)
{
	driver->opt->open(&(driver->dev));
}

int tp_driver_read(struct pointer *p, int cnt)
{
	return 0;
}
