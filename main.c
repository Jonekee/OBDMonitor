#include <stdio.h>
#include "system.h"
#include "event.h"
#include "button.h"

int main(void)
{
	struct button b;
	struct unicode text;
	uint8_t pressed = 1;
	system_boot();
	button_init(&b, 0, 100, 200, text);
	button_set_visible(&b, 1);
	printf("system boot successfully.\n");
	while (1) {
		button_set_pressed(&b, pressed);
		b.base.paint((struct widget *)&b, 10, 20);
		pressed = !pressed;
	}
	return 0;
}
