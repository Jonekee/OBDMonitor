#include <stdio.h>
#include "system.h"
#include "demo_widget.h"

int main(void)
{
	uint8_t i;
	system_boot();
	printf("system boot successfully.\n");
	demo_widget_init(demo_widget_ptr);
	for (i = 0; i < 100; i++) {
		widget_paint((struct widget *)demo_widget_ptr, i, i);
	}
	return 0;
}
