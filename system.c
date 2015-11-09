#include <stm32f4xx.h>

#include "lcd_driver.h"

static void system_set_clock(void);

void system_set_clock(void)
{
	RCC->CR|=1<<16;
	while(((RCC->CR&(1<<17))==0));
	RCC->APB1ENR|=1<<28;
	PWR->CR|=3<<14;
	RCC->CFGR|=(0<<4)|(5<<10)|(4<<13);
	RCC->CR&=~(1<<24);
	RCC->PLLCFGR=8|(336<<6)|(((2>>1)-1)<<16)|(7<<24)|(1<<22);
	RCC->CR|=1<<24;
	while((RCC->CR&(1<<25))==0);
	FLASH->ACR|=1<<8;
	FLASH->ACR|=1<<9;
	FLASH->ACR|=1<<10;
	FLASH->ACR|=5<<0; 
	RCC->CFGR&=~(3<<0);
	RCC->CFGR|=2<<0; 
	while((RCC->CFGR&(3<<2))!=(2<<2));
}

void system_boot(void)
{
	system_set_clock();
	lcd_driver_hw_init();
}
