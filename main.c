#include <stdio.h>
#include "system.h"
#include "demo_widget.h"

int main(void)
{
	system_boot();
	printf("system boot successfully.\n");
	demo_widget_init(demo_widget_ptr);
	return 0;
}
