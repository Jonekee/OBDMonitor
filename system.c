#include <stm32f4xx.h>

#include "lcd_driver.h"

static void system_set_clock(void);

void system_set_clock(void)
{
	RCC->CR|=1<<16;				//HSE 开启 
	while(((RCC->CR&(1<<17))==0));//等待HSE RDY
	RCC->APB1ENR|=1<<28;	//电源接口时钟使能
	PWR->CR|=3<<14; 		//高性能模式,时钟可到168Mhz
	RCC->CFGR|=(0<<4)|(5<<10)|(4<<13);//HCLK 不分频;APB1 4分频;APB2 2分频. 
	RCC->CR&=~(1<<24);	//关闭主PLL
	RCC->PLLCFGR=8|(336<<6)|(((2>>1)-1)<<16)|(7<<24)|(1<<22);//配置主PLL,PLL时钟源来自HSE
	RCC->CR|=1<<24;			//打开主PLL
	while((RCC->CR&(1<<25))==0);//等待PLL准备好 
	FLASH->ACR|=1<<8;		//指令预取使能.
	FLASH->ACR|=1<<9;		//指令cache使能.
	FLASH->ACR|=1<<10;		//数据cache使能.
	FLASH->ACR|=5<<0;		//5个CPU等待周期. 
	RCC->CFGR&=~(3<<0);		//清零
	RCC->CFGR|=2<<0;		//选择主PLL作为系统时钟	 
	while((RCC->CFGR&(3<<2))!=(2<<2));//等待主PLL作为系统时钟成功. 
}

void system_boot(void)
{
	system_set_clock();
	lcd_driver_hw_init();
}
