
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
	RCC->APB1ENR|=1<<25;//ʹ��CAN1ʱ�� CAN1ʹ�õ���APB1��ʱ��(max:42M)
	CAN1->MCR=0x0000;	//�˳�˯��ģʽ(ͬʱ��������λΪ0)
	CAN1->MCR|=1<<0;		//����CAN�����ʼ��ģʽ
	while((CAN1->MSR&1<<0)==0);
	CAN1->MCR|=0<<7;		//��ʱ�䴥��ͨ��ģʽ
	CAN1->MCR|=0<<6;		//����Զ����߹���
	CAN1->MCR|=0<<5;		//˯��ģʽͨ���������(���CAN1->MCR��SLEEPλ)
	CAN1->MCR|=1<<4;		//��ֹ�����Զ�����
	CAN1->MCR|=0<<3;		//���Ĳ�����,�µĸ��Ǿɵ�
	CAN1->MCR|=0<<2;		//���ȼ��ɱ��ı�ʶ������
	CAN1->BTR=0x00000000;	//���ԭ��������.
	CAN1->BTR|=0<<30;	//ģʽ���� 0,��ͨģʽ;1,�ػ�ģʽ;
	CAN1->BTR|=0<<24; 	//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ
	CAN1->BTR|=5<<20; 	//Tbs2=tbs2+1��ʱ�䵥λ
	CAN1->BTR|=6<<16;	//Tbs1=tbs1+1��ʱ�䵥λ
	CAN1->BTR|=5<<0;  	//��Ƶϵ��(Fdiv)Ϊbrp+1
							//������:Fpclk1/((Tbs1+Tbs2+1)*Fdiv)
	CAN1->MCR&=~(1<<0);		//����CAN�˳���ʼ��ģʽ
	while((CAN1->MSR&1<<0)==1);
	//��������ʼ��
	CAN1->FMR|=1<<0;		//�������鹤���ڳ�ʼ��ģʽ
	CAN1->FA1R&=~(1<<0);	//������0������
	CAN1->FS1R|=1<<0; 		//������λ��Ϊ32λ.
	CAN1->FM1R|=0<<0;		//������0�����ڱ�ʶ������λģʽ
	CAN1->FFA1R|=0<<0;		//������0������FIFO0
	CAN1->sFilterRegister[0].FR1=0X00000000;//32λID
	CAN1->sFilterRegister[0].FR2=0X00000000;//32λMASK
	CAN1->FA1R|=1<<0;		//���������0
	CAN1->FMR&=0<<0;		//���������������ģʽ
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
