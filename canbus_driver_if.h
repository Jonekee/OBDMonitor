#ifndef CANBUS_DRIVER_IF_H
#define CANBUS_DRIVER_IF_H

#include <stdint.h>

#include <stm32f4xx.h>

struct can_device {
	CAN_TypeDef *pcan;
	GPIO_TypeDef *pio;
};

struct can_device;
struct can_frame;

struct canbus_opt {
	void (*open)(struct can_device *dev);
	int (*read)(struct can_device *device, struct can_frame *frame, uint8_t count);
	int (*write)(struct can_device *device, struct can_frame *frame, uint8_t count);
	void (*close)(struct can_device *dev);
};

#endif
