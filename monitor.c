#include "canbus_driver.h"

static uint32_t pid_spt = 0;

#define PID_SUPPORTED(n) ((pid_spt) & ((0x80000000UL) >> ((n) - (1))))

void monitor_init(void)
{
	(void)pid_spt;
}
