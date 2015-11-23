#include <stdio.h>
#include "system.h"
#include "mainloop.h"
#include "canbus_driver.h"

uint32_t rpm_value;
uint32_t spd_value;
uint32_t maf_value;

int main(void)
{
	
	struct can_frame fout, fin;
	system_boot();
	fout.id.bits.ide = 0;
	fout.id.bits.rtr = 0;
	fout.id.bits.exid = 0x7dfUL << 21;
	fout.lts.bits.ts = 0;
	fout.lts.bits.dlc = 8;
	fout.data[0] = 2;
	fout.data[1] = 1;
	fout.data[2] = 0x0D;
	while (!canbus_driver_write(&fout, 1));
	while (!canbus_driver_read(&fin, 1));
	spd_value = fin.data[3];
	fout.data[2] = 0x0C;
	while (!canbus_driver_write(&fout, 1));
	while (!canbus_driver_read(&fin, 1));
	rpm_value = (fin.data[3] * 256UL + fin.data[4]) / 4;
	fout.data[2] = 0x10;
	while (!canbus_driver_write(&fout, 1));
	while (!canbus_driver_read(&fin, 1));
	maf_value = (fin.data[3] * 256UL + fin.data[4]) / 100;
	printf("system boot successfully.\n");
	return mainloop();
}
