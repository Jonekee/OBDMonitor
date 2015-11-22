#ifndef _CANBUS_DRIVER_H
#define _CANBUS_DRIVER_H

#include <stdint.h>

union can_identity {
	struct {
		uint32_t :1; /* reserved */
		uint32_t rtr:1; /* remote transmition req */
		uint32_t ide:1; /* whether extended message */
		uint32_t exid:28; /* id or exid */
	} bits;
	uint32_t word;
};

union can_lents {
	struct {
		uint32_t dlc:4;
		uint32_t :12;
	  uint32_t ts:16;
	} bits;
	uint32_t word;
};

struct can_frame {
	union can_identity id;
	union can_lents lts;
	uint8_t data[8];
};

extern void canbus_driver_open(void);
extern int canbus_driver_read(struct can_frame *frame, uint8_t count);
extern int canbus_driver_write(struct can_frame *frame, uint8_t count);
extern void canbus_driver_close(void);

#endif
