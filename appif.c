#include "appif.h"

#include <string.h>

#include "canbus_driver.h"

uint32_t rpm_value = 0;
uint32_t spd_value = 0;
uint32_t maf_value = 0;

static uint8_t obd_status = 0;

static void update_basic_obd_data(void);

void appif_touch_event(uint16_t widid, enum touch_type type)
{
	if (TOUCH_TYPE_PRESS == type) {
		switch (widid) {
			case BUTTON_ID_RPM:
			case BUTTON_ID_SPD:
			case BUTTON_ID_MAF:
				update_basic_obd_data();
				break;
			default:
				break;
		}
	}
}

int appif_idle_task(void)
{
	if (obd_status) {
		update_basic_obd_data();
		return 1;
	}
	return 0;
}

void update_basic_obd_data(void)
{
	struct can_frame fout[3], fin[3];
	memset(fout, 0, 3 * sizeof(struct can_frame));
	memset(fin, 0, 3 * sizeof(struct can_frame));
	fout[0].id.bits.ide = 0;
	fout[0].id.bits.rtr = 0;
	fout[0].id.bits.exid = 0x7dfUL << 21;
	fout[0].lts.bits.ts = 0;
	fout[0].lts.bits.dlc = 8;
	fout[0].data[0] = 2;
	fout[0].data[1] = 1;
	memcpy(fout + 1, fout, sizeof(struct can_frame));
	memcpy(fout + 2, fout, sizeof(struct can_frame));
	fout[0].data[2] = 0x0C;
	fout[1].data[2] = 0x0D;
	fout[2].data[2] = 0x10;
	canbus_driver_write(fout, 3);
	canbus_driver_read(fin, 3);
	rpm_value = (fin[0].data[3] * 256UL + fin[0].data[4]) / 4;
	spd_value = fin[1].data[3];
	maf_value = (fin[2].data[3] * 256UL + fin[2].data[4]) / 100;
}
