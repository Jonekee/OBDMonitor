#include <stdio.h>
#include "system.h"
#include "mainloop.h"
#include "canbus_driver.h"

int main(void)
{
	system_boot();
	printf("system boot successfully.\n");
	return mainloop();
}
