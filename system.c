#include <stm32f4xx.h>

#include "lcd_driver.h"
#include "tp_driver.h"

static void system_set_clock(void);
static void system_hw_setup(void);

void system_set_clock(void)
{
	RCC->CR|=1<<16;
	while(((RCC->CR&(1<<17))==0));
	RCC->APB1ENR|=1<<28;
	PWR->CR|=3<<14;
	RCC->CFGR|=(0<<4)|(5<<10)|(4<<13);
	RCC->CR&=~(1<<24);
	RCC->PLLCFGR=25|(336<<6)|(((2>>1)-1)<<16)|(7<<24)|(1<<22);
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

void system_hw_setup(void)
{
	RCC->AHB3ENR |= RCC_AHB3ENR_FSMCEN;

	FSMC_Bank1->BTCR[7]|=0XF;
	FSMC_Bank1->BTCR[7]|=60<<8;

	FSMC_Bank1E->BWTR[6]&=~0XF;
	FSMC_Bank1E->BWTR[6]&=~(0XF<<8);
	FSMC_Bank1E->BWTR[6]|=3<<0;
	FSMC_Bank1E->BWTR[6]|=2<<8;

	FSMC_Bank1->BTCR[6] &= ~(FSMC_BCR4_WAITEN | FSMC_BCR4_MUXEN);
	FSMC_Bank1->BTCR[6] |= (FSMC_BCR4_EXTMOD | FSMC_BCR4_WREN | FSMC_BCR4_MBKEN);

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= 0xAAAA0A0A;
	GPIOD->PUPDR |= 0x55550505;
	GPIOD->OSPEEDR |= 0xFFFF0F0F;
	GPIOD->AFR[0] |= 0x00CC00CC;
	GPIOD->AFR[1] |= 0xCCCCCCCC;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	GPIOE->MODER |= 0xAAAA8000;
	GPIOE->PUPDR |= 0x55554000;
	GPIOE->OSPEEDR |= 0xFFFFC000;
	GPIOE->AFR[0] |= 0xC0000000;
	GPIOE->AFR[1] |= 0xCCCCCCCC;

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
	GPIOF->MODER |= 0x02000000;
	GPIOF->PUPDR |= 0x01000000;
	GPIOF->OSPEEDR |= 0x03000000;
	GPIOF->AFR[1] |= 0x000C0000;

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	GPIOG->MODER |= 0x02000000;
	GPIOG->PUPDR |= 0x01000000;
	GPIOG->OSPEEDR |= 0x03000000;
	GPIOG->AFR[1] |= 0x000C0000;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER15_0;
}

void system_boot(void)
{
	system_set_clock();
	system_hw_setup();
	lcd_driver_open();
	tp_driver_open();
}
