#include "canbus_driver.h"

static uint32_t pid_spt = 0;

#define PID_SUPPORTED(n) ((pid_spt) & ((0x80000000UL) >> ((n) - (1))))

void monitor_init(void)
{
	struct can_frame fout, fin;
	fout.id.bits.ide = 0;
	fout.id.bits.rtr = 0;
	fout.id.bits.exid = 0x7dfUL << 21;
	fout.lts.bits.ts = 0;
	fout.lts.bits.dlc = 8;
	fout.data[0] = 2;
	fout.data[1] = 1;
	fout.data[2] = 0;
	canbus_driver_write(&fout, 1);
	while (!canbus_driver_read(&fin, 1));
	pid_spt = (fin.data[0] << 24) | (fin.data[1] << 16) | (fin.data[2] << 8) | (fin.data[3]);
	(void)pid_spt;
}
