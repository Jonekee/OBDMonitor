#include <stdio.h>
#include "system.h"
#include "sysevent_if.h"

int main(void)
{
	system_boot();
	printf("system boot successfully.\n");
	return 0;
}
