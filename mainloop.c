#include <stdio.h>
#include "tp_driver.h"
#include "demo_widget.h"

int mainloop(void)
{
	uint16_t x = 0;
	uint8_t c = 1;
	demo_widget_init(demo_widget_ptr);
	widget_paint((struct widget *)demo_widget_ptr, x, x);
	if (c) {
		while (1) {
			struct pointer p;
			p.x = p.y = 0;
			tp_driver_read(&p, 1);
			if (p.x && p.y) {
				widget_paint((struct widget *)demo_widget_ptr, x, x);
				x++;
				printf("pointer event (%d, %d)\n", p.x, p.y);
			}
		}
	}
	return 0;
}
