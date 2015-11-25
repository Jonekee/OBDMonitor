
/* Controller Area Network (bxCAN) */

#define hw_setbits(status, mask) status |= (mask)
#define hw_clrbits(status, mask) status &= ~(mask)
#define hw_waitset(status, mask) while (((status) & (mask)) != (mask))
#define hw_waitclr(status, mask) while (!((status) & (mask)))

#include <stdint.h>
#include "canbus_driver_if.h"
#include "canbus_driver.h"

static void can_open(struct can_device *device);
static int can_read(struct can_device *device, struct can_frame *frame, uint8_t count);
static int can_write(struct can_device *device, struct can_frame *frame, uint8_t count);
static void can_close(struct can_device *device);

void can_open(struct can_device *device)
{
	#if 0
	/* leave sleep mode */
	hw_clrbits(device->pcan->MCR, CAN_MCR_SLEEP);
	hw_waitclr(device->pcan->MSR, CAN_MSR_SLAK);
	/* enter initialization mode */
	hw_setbits(device->pcan->MCR, CAN_MCR_INRQ);
	hw_waitset(device->pcan->MSR, CAN_MSR_INAK);

	/* set CAN_BTR and CAN_MCR */

	/* returun to normal mode */
	hw_clrbits(device->pcan->MCR, CAN_MCR_INRQ);
	hw_waitclr(device->pcan->MSR, CAN_MSR_INAK);
	#else
	RCC->APB1ENR|=1<<25;//使能CAN1时钟 CAN1使用的是APB1的时钟(max:42M)
	CAN1->MCR=0x0000;	//退出睡眠模式(同时设置所有位为0)
	CAN1->MCR|=1<<0;		//请求CAN进入初始化模式
	while((CAN1->MSR&1<<0)==0);
	CAN1->MCR|=0<<7;		//非时间触发通信模式
	CAN1->MCR|=0<<6;		//软件自动离线管理
	CAN1->MCR|=0<<5;		//睡眠模式通过软件唤醒(清除CAN1->MCR的SLEEP位)
	CAN1->MCR|=1<<4;		//禁止报文自动传送
	CAN1->MCR|=0<<3;		//报文不锁定,新的覆盖旧的
	CAN1->MCR|=0<<2;		//优先级由报文标识符决定
	CAN1->BTR=0x00000000;	//清除原来的设置.
	CAN1->BTR|=0<<30;	//模式设置 0,普通模式;1,回环模式;
	CAN1->BTR|=0<<24; 	//重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位
	CAN1->BTR|=5<<20; 	//Tbs2=tbs2+1个时间单位
	CAN1->BTR|=6<<16;	//Tbs1=tbs1+1个时间单位
	CAN1->BTR|=5<<0;  	//分频系数(Fdiv)为brp+1
							//波特率:Fpclk1/((Tbs1+Tbs2+1)*Fdiv)
	CAN1->MCR&=~(1<<0);		//请求CAN退出初始化模式
	while((CAN1->MSR&1<<0)==1);
	//过滤器初始化
	CAN1->FMR|=1<<0;		//过滤器组工作在初始化模式
	CAN1->FA1R&=~(1<<0);	//过滤器0不激活
	CAN1->FS1R|=1<<0; 		//过滤器位宽为32位.
	CAN1->FM1R|=0<<0;		//过滤器0工作在标识符屏蔽位模式
	CAN1->FFA1R|=0<<0;		//过滤器0关联到FIFO0
	CAN1->sFilterRegister[0].FR1=0X00000000;//32位ID
	CAN1->sFilterRegister[0].FR2=0X00000000;//32位MASK
	CAN1->FA1R|=1<<0;		//激活过滤器0
	CAN1->FMR&=0<<0;		//过滤器组进入正常模式
	#endif
}

int can_read(struct can_device *device, struct can_frame *frame, uint8_t count)
{
	uint8_t cnt0 = device->pcan->RF0R & CAN_RF0R_FMP0;
	uint8_t cnt1 = device->pcan->RF1R & CAN_RF1R_FMP1;
	uint8_t i, j;
	if (count > cnt1 + cnt0) {
		count = cnt1 + cnt0;
	}
	for (i = 0; i < count; i++) {
		if (i < cnt0) {
			frame[i].id.word = device->pcan->sFIFOMailBox[0].RIR;
			frame[i].lts.word = device->pcan->sFIFOMailBox[0].RDTR;
			for (j = 0; j < frame[i].lts.bits.dlc; j++) {
				if (j < 4) {
					frame[i].data[j] = device->pcan->sFIFOMailBox[0].RDLR >> ((j % 4) << 3);
				} else {
					frame[i].data[j] = device->pcan->sFIFOMailBox[0].RDHR >> ((j % 4) << 3);
				}
			}
			device->pcan->RF0R |= CAN_RF0R_RFOM0;
		} else {
			frame[i].id.word = device->pcan->sFIFOMailBox[1].RIR;
			frame[i].lts.word = device->pcan->sFIFOMailBox[1].RDTR;
			for (j = 0; j < frame[i].lts.bits.dlc; j++) {
				if (j < 4) {
					frame[i].data[j] = device->pcan->sFIFOMailBox[1].RDLR >> ((j % 4) << 3);
				} else {
					frame[i].data[j] = device->pcan->sFIFOMailBox[1].RDHR >> ((j % 4) << 3);
				}
			}
			device->pcan->RF1R |= CAN_RF1R_RFOM1;
		}
	}
	if (cnt0) {
		device->pcan->RF0R |= 0x20;
	}
	if (cnt1) {
		device->pcan->RF1R |= 0x20;
	}
	return count;
}

int can_write(struct can_device *device, struct can_frame *frame, uint8_t count)
{
	uint32_t tsr = device->pcan->TSR;
	int ret = 0;
	int cur = 0;
	uint8_t mask[3] = {0};
	uint8_t i;
	if (CAN_TSR_TME0 & tsr) {
		if (ret < count) {
			mask[0] = 1;
			ret++;
		}
	}
	if (CAN_TSR_TME1 & tsr) {
		if (ret < count) {
			mask[1] = 1;
			ret++;
		}
	}
	if (CAN_TSR_TME2 & tsr) {
		if (ret < count) {
			mask[2] = 1;
			ret++;
		}
	}
	for (i = 0; i < 3; i++) {
		if (mask[i]) {
			uint32_t j;
			device->pcan->sTxMailBox[i].TIR = frame[cur].id.word;
			device->pcan->sTxMailBox[i].TDTR = frame[cur].lts.word;
			device->pcan->sTxMailBox[i].TDLR = 0;
			device->pcan->sTxMailBox[i].TDHR = 0;
			for (j = 0; j < frame[cur].lts.bits.dlc; j++) {
				if (j < 4) {
					device->pcan->sTxMailBox[i].TDLR |= ((uint32_t)(frame[cur].data[j])) << ((j % 4) << 3);
				} else {
					device->pcan->sTxMailBox[i].TDHR |= ((uint32_t)(frame[cur].data[j])) << ((j % 4) << 3);
				}
			}
			device->pcan->sTxMailBox[i].TIR |= CAN_TI0R_TXRQ;
			cur++;
		}
	}
	return ret;
}

void can_close(struct can_device *device)
{

}

struct canbus_opt can_opt = {
	can_open,
	can_read,
	can_write,
	can_close
};
