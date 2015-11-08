#include <stm32f4xx.h>

#include "lcd_driver.h"

static void system_set_clock(void);

void system_set_clock(void)
{
	RCC->CR|=1<<16;				//HSE ���� 
	while(((RCC->CR&(1<<17))==0));//�ȴ�HSE RDY
	RCC->APB1ENR|=1<<28;	//��Դ�ӿ�ʱ��ʹ��
	PWR->CR|=3<<14; 		//������ģʽ,ʱ�ӿɵ�168Mhz
	RCC->CFGR|=(0<<4)|(5<<10)|(4<<13);//HCLK ����Ƶ;APB1 4��Ƶ;APB2 2��Ƶ. 
	RCC->CR&=~(1<<24);	//�ر���PLL
	RCC->PLLCFGR=8|(336<<6)|(((2>>1)-1)<<16)|(7<<24)|(1<<22);//������PLL,PLLʱ��Դ����HSE
	RCC->CR|=1<<24;			//����PLL
	while((RCC->CR&(1<<25))==0);//�ȴ�PLL׼���� 
	FLASH->ACR|=1<<8;		//ָ��Ԥȡʹ��.
	FLASH->ACR|=1<<9;		//ָ��cacheʹ��.
	FLASH->ACR|=1<<10;		//����cacheʹ��.
	FLASH->ACR|=5<<0;		//5��CPU�ȴ�����. 
	RCC->CFGR&=~(3<<0);		//����
	RCC->CFGR|=2<<0;		//ѡ����PLL��Ϊϵͳʱ��	 
	while((RCC->CFGR&(3<<2))!=(2<<2));//�ȴ���PLL��Ϊϵͳʱ�ӳɹ�. 
}

void system_boot(void)
{
	system_set_clock();
	lcd_driver_hw_init();
}
