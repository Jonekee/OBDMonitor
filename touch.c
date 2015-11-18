#include "tp_driver.h"

struct pointer last_point = {0, 0};

enum touch_type touch_detect(struct pointer *pt)
{
	struct pointer p;
	p.x = p.y = 0;
	tp_driver_read(&p, 1);
	if (p.x && p.y) {
		last_point = p;
		*pt = p;
		return TOUCH_TYPE_PRESS;
	} else if (last_point.x && last_point.y) {
		*pt = last_point;
		last_point.x = last_point.y = 0;
		return TOUCH_TYPE_RELEASE;
	} else {
		return TOUCH_TYPE_NONE;
	}
}
