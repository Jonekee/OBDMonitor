#include <stdio.h>
#include "tp_driver.h"
#include "winmgmt.h"

int mainloop(void)
{
	uint8_t c = 1;
	winmgmt_init(TOP_WIDGET_ID_DEMO);
	if (c) {
		while (1) {
			struct pointer p;
			p.x = p.y = 0;
			tp_driver_read(&p, 1);
			if (p.x && p.y) {
				if (winmgmt_touch(TOUCH_TYPE_PRESS, p.x, p.y)) {
					winmgmt_paint();
				}
				printf("pointer event (%d, %d)\n", p.x, p.y);
			}
		}
	}
	return 0;
}
