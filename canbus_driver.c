#include "canbus_driver.h"
#include "canbus_driver_if.h"

extern struct canbus_opt can_opt;

struct canbus_driver {
	struct can_device dev;
	struct canbus_opt *opt;
};

static struct canbus_driver can_dev = {{CAN1, 0}, &can_opt};

static struct canbus_driver *driver = &can_dev;

void canbus_driver_open(void)
{
	driver->opt->open(&(driver->dev));
}

int canbus_driver_read(struct can_frame *frame, uint8_t count)
{
	return driver->opt->read(&(driver->dev), frame, count);
}

int canbus_driver_write(struct can_frame *frame, uint8_t count)
{
	return driver->opt->write(&(driver->dev), frame, count);
}

void monitor_close(void)
{
	driver->opt->close(&(driver->dev));
}
