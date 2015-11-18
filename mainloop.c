#include <stdio.h>
#include "winmgmt.h"
#include "touch.h"
#include "appif.h"

int mainloop(void)
{
	uint8_t c = 1;
	winmgmt_init(WINDOW_ID_DEMO);
	if (c) {
	while (1) {
			struct pointer p;
			enum touch_type type = touch_detect(&p);
			if (TOUCH_TYPE_NONE != type) {
				uint16_t widid;
				if (winmgmt_touch(type, p.x, p.y, &widid)) {
					winmgmt_paint();
				}
				if (WIDGET_ID_MAX != widid) {
					appif_touch_event(widid, type);
				}
				printf("pointer event (%d, %d)\n", p.x, p.y);
			}
		}
	}
	return 0;
}
