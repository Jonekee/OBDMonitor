#include <stm32f4xx.h>

#include "canbus_driver.h"
#include "lcd_driver.h"
#include "tp_driver.h"

static void system_hw_setup(void);

//时钟设置函数
//Fvco=Fs*(plln/pllm);
//Fsys=Fvco/pllp=Fs*(plln/(pllm*pllp));
//Fusb=Fvco/pllq=Fs*(plln/(pllm*pllq));

//Fvco:VCO频率
//Fsys:系统时钟频率
//Fusb:USB,SDIO,RNG等的时钟频率
//Fs:PLL输入时钟频率,可以是HSI,HSE等. 
//plln:主PLL倍频系数(PLL倍频),取值范围:64~432.
//pllm:主PLL和音频PLL分频系数(PLL之前的分频),取值范围:2~63.
//pllp:系统时钟的主PLL分频系数(PLL之后的分频),取值范围:2,4,6,8.(仅限这4个值!)
//pllq:USB/SDIO/随机数产生器等的主PLL分频系数(PLL之后的分频),取值范围:2~15.

//外部晶振为8M的时候,推荐值:plln=336,pllm=8,pllp=2,pllq=7.
//得到:Fvco=8*(336/8)=336Mhz
//     Fsys=336/2=168Mhz
//     Fusb=336/7=48Mhz
//返回值:0,成功;1,失败。
uint8_t Sys_Clock_Set(uint32_t plln,uint32_t pllm,uint32_t pllp,uint32_t pllq)
{ 
	uint16_t retry=0;
	uint8_t status=0;
	RCC->CR|=1<<16;				//HSE 开启 
	while(((RCC->CR&(1<<17))==0)&&(retry<0X1FFF))retry++;//等待HSE RDY
	if(retry==0X1FFF)status=1;	//HSE无法就绪
	else   
	{
		RCC->APB1ENR|=1<<28;	//电源接口时钟使能
		PWR->CR|=3<<14; 		//高性能模式,时钟可到168Mhz
		RCC->CFGR|=(0<<4)|(5<<10)|(4<<13);//HCLK 不分频;APB1 4分频;APB2 2分频. 
		RCC->CR&=~(1<<24);	//关闭主PLL
		RCC->PLLCFGR=pllm|(plln<<6)|(((pllp>>1)-1)<<16)|(pllq<<24)|(1<<22);//配置主PLL,PLL时钟源来自HSE
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
	return status;
}  

//系统时钟初始化函数
//plln:主PLL倍频系数(PLL倍频),取值范围:64~432.
//pllm:主PLL和音频PLL分频系数(PLL之前的分频),取值范围:2~63.
//pllp:系统时钟的主PLL分频系数(PLL之后的分频),取值范围:2,4,6,8.(仅限这4个值!)
//pllq:USB/SDIO/随机数产生器等的主PLL分频系数(PLL之后的分频),取值范围:2~15.
void Stm32_Clock_Init(uint32_t plln,uint32_t pllm,uint32_t pllp,uint32_t pllq)
{  
	RCC->CR|=0x00000001;		//设置HISON,开启内部高速RC振荡
	RCC->CFGR=0x00000000;		//CFGR清零 
	RCC->CR&=0xFEF6FFFF;		//HSEON,CSSON,PLLON清零 
	RCC->PLLCFGR=0x24003010;	//PLLCFGR恢复复位值 
	RCC->CR&=~(1<<18);			//HSEBYP清零,外部晶振不旁路
	RCC->CIR=0x00000000;		//禁止RCC时钟中断 
	Sys_Clock_Set(plln,pllm,pllp,pllq);//设置时钟 
	//配置向量表				  
	SCB->VTOR=0|(0&(uint32_t)0xFFFFFE00);//设置NVIC的向量表偏移寄存器,VTOR低9位保留,即[8:0]保留。
}

//GPIO设置专用宏定义
#define GPIO_MODE_IN    	0		//普通输入模式
#define GPIO_MODE_OUT		1		//普通输出模式
#define GPIO_MODE_AF		2		//AF功能模式
#define GPIO_MODE_AIN		3		//模拟输入模式

#define GPIO_SPEED_2M		0		//GPIO速度2Mhz
#define GPIO_SPEED_25M		1		//GPIO速度25Mhz
#define GPIO_SPEED_50M		2		//GPIO速度50Mhz
#define GPIO_SPEED_100M		3		//GPIO速度100Mhz

#define GPIO_PUPD_NONE		0		//不带上下拉
#define GPIO_PUPD_PU		1		//上拉
#define GPIO_PUPD_PD		2		//下拉
#define GPIO_PUPD_RES		3		//保留 

#define GPIO_OTYPE_PP		0		//推挽输出
#define GPIO_OTYPE_OD		1		//开漏输出 

//GPIO引脚编号定义
#define PIN0				1<<0
#define PIN1				1<<1
#define PIN2				1<<2
#define PIN3				1<<3
#define PIN4				1<<4
#define PIN5				1<<5
#define PIN6				1<<6
#define PIN7				1<<7
#define PIN8				1<<8
#define PIN9				1<<9
#define PIN10				1<<10
#define PIN11				1<<11
#define PIN12				1<<12
#define PIN13				1<<13
#define PIN14				1<<14
#define PIN15				1<<15 

//GPIO通用设置 
//GPIOx:GPIOA~GPIOI.
//BITx:0X0000~0XFFFF,位设置,每个位代表一个IO,第0位代表Px0,第1位代表Px1,依次类推.比如0X0101,代表同时设置Px0和Px8.
//MODE:0~3;模式选择,0,输入(系统复位默认状态);1,普通输出;2,复用功能;3,模拟输入.
//OTYPE:0/1;输出类型选择,0,推挽输出;1,开漏输出.
//OSPEED:0~3;输出速度设置,0,2Mhz;1,25Mhz;2,50Mhz;3,100Mh. 
//PUPD:0~3:上下拉设置,0,不带上下拉;1,上拉;2,下拉;3,保留.
//注意:在输入模式(普通输入/模拟输入)下,OTYPE和OSPEED参数无效!!
void GPIO_Set(GPIO_TypeDef* GPIOx,uint32_t BITx,uint32_t MODE,uint32_t OTYPE,uint32_t OSPEED,uint32_t PUPD)
{  
	uint32_t pinpos=0,pos=0,curpin=0;
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	//一个个位检查 
		curpin=BITx&pos;//检查引脚是否要设置
		if(curpin==pos)	//需要设置
		{
			GPIOx->MODER&=~(3<<(pinpos*2));	//先清除原来的设置
			GPIOx->MODER|=MODE<<(pinpos*2);	//设置新的模式 
			if((MODE==0X01)||(MODE==0X02))	//如果是输出模式/复用功能模式
			{  
				GPIOx->OSPEEDR&=~(3<<(pinpos*2));	//清除原来的设置
				GPIOx->OSPEEDR|=(OSPEED<<(pinpos*2));//设置新的速度值  
				GPIOx->OTYPER&=~(1<<pinpos) ;		//清除原来的设置
				GPIOx->OTYPER|=OTYPE<<pinpos;		//设置新的输出模式
			}  
			GPIOx->PUPDR&=~(3<<(pinpos*2));	//先清除原来的设置
			GPIOx->PUPDR|=PUPD<<(pinpos*2);	//设置新的上下拉
		}
	}
} 

//GPIO复用设置
//GPIOx:GPIOA~GPIOI.
//BITx:0~15,代表IO引脚编号.
//AFx:0~15,代表AF0~AF15.
//AF0~15设置情况(这里仅是列出常用的,详细的请见407数据手册,56页Table 7):
//AF0:MCO/SWD/SWCLK/RTC   AF1:TIM1/TIM2;            AF2:TIM3~5;               AF3:TIM8~11
//AF4:I2C1~I2C3;          AF5:SPI1/SPI2;            AF6:SPI3;                 AF7:USART1~3;
//AF8:USART4~6;           AF9;CAN1/CAN2/TIM12~14    AF10:USB_OTG/USB_HS       AF11:ETH
//AF12:FSMC/SDIO/OTG/HS   AF13:DCIM                 AF14:                     AF15:EVENTOUT
void GPIO_AF_Set(GPIO_TypeDef* GPIOx,uint8_t BITx,uint8_t AFx)
{  
	GPIOx->AFR[BITx>>3]&=~(0X0F<<((BITx&0X07)*4));
	GPIOx->AFR[BITx>>3]|=(uint32_t)AFx<<((BITx&0X07)*4);
}   

void system_hw_setup(void)
{
	RCC->AHB1ENR|=1<<0;  	//使能PORTA口时钟 
	GPIO_Set(GPIOA,PIN11|PIN12,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA11,PA12,复用功能,上拉输出
 	GPIO_AF_Set(GPIOA,11,9);//PA11,AF9
	GPIO_AF_Set(GPIOA,12,9);//PA12,AF9 	   
	
	RCC->AHB1ENR|=0XF<<3;    	//使能PD,PE,PF,PG时钟  
	RCC->AHB1ENR|=1<<1;     	//使能PB时钟  
	RCC->AHB3ENR|=1<<0;     	//使能FSMC时钟  
	GPIO_Set(GPIOB,PIN15,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);							//PB15 推挽输出,控制背光
	GPIO_Set(GPIOD,(3<<0)|(3<<4)|(7<<8)|(3<<14),GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);	//PD0,1,4,5,8,9,10,14,15 AF OUT
	GPIO_Set(GPIOE,(0X1FF<<7),GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);						//PE7~15,AF OUT
	GPIO_Set(GPIOF,PIN12,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);							//PF12,FSMC_A6
	GPIO_Set(GPIOG,PIN12,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);							//PG12,FSMC_NE4
 	GPIO_AF_Set(GPIOD,0,12);	//PD0,AF12
 	GPIO_AF_Set(GPIOD,1,12);	//PD1,AF12
 	GPIO_AF_Set(GPIOD,4,12);	//PD4,AF12
 	GPIO_AF_Set(GPIOD,5,12);	//PD5,AF12 
 	GPIO_AF_Set(GPIOD,8,12);	//PD8,AF12
 	GPIO_AF_Set(GPIOD,9,12);	//PD9,AF12
 	GPIO_AF_Set(GPIOD,10,12);	//PD10,AF12 
 	GPIO_AF_Set(GPIOD,14,12);	//PD14,AF12
 	GPIO_AF_Set(GPIOD,15,12);	//PD15,AF12
	
 	GPIO_AF_Set(GPIOE,7,12);	//PE7,AF12
 	GPIO_AF_Set(GPIOE,8,12);	//PE8,AF12
 	GPIO_AF_Set(GPIOE,9,12);	//PE9,AF12
 	GPIO_AF_Set(GPIOE,10,12);	//PE10,AF12
 	GPIO_AF_Set(GPIOE,11,12);	//PE11,AF12
 	GPIO_AF_Set(GPIOE,12,12);	//PE12,AF12
 	GPIO_AF_Set(GPIOE,13,12);	//PE13,AF12
 	GPIO_AF_Set(GPIOE,14,12);	//PE14,AF12
 	GPIO_AF_Set(GPIOE,15,12);	//PE15,AF12
	
 	GPIO_AF_Set(GPIOF,12,12);	//PF12,AF12
 	GPIO_AF_Set(GPIOG,12,12);	//PG12,AF12
	 
	//寄存器清零
	//bank1有NE1~4,每一个有一个BCR+TCR，所以总共八个寄存器。
	//这里我们使用NE1 ，也就对应BTCR[0],[1]。				    
	FSMC_Bank1->BTCR[6]=0X00000000;
	FSMC_Bank1->BTCR[7]=0X00000000;
	FSMC_Bank1E->BWTR[6]=0X00000000;
	//操作BCR寄存器	使用异步模式
	FSMC_Bank1->BTCR[6]|=1<<12;		//存储器写使能
	FSMC_Bank1->BTCR[6]|=1<<14;		//读写使用不同的时序
	FSMC_Bank1->BTCR[6]|=1<<4; 		//存储器数据宽度为16bit 	    
	//操作BTR寄存器	
	//读时序控制寄存器 							    
	FSMC_Bank1->BTCR[7]|=0<<28;		//模式A 	 						  	 
	FSMC_Bank1->BTCR[7]|=0XF<<0; 	//地址建立时间(ADDSET)为15个HCLK 1/168M=6ns*15=90ns	
	//因为液晶驱动IC的读数据的时候，速度不能太快,尤其是个别奇葩芯片。
	FSMC_Bank1->BTCR[7]|=60<<8;  	//数据保存时间(DATAST)为60个HCLK	=6*60=360ns
	//写时序控制寄存器  
	FSMC_Bank1E->BWTR[6]|=0<<28; 	//模式A 	 							    
	FSMC_Bank1E->BWTR[6]|=9<<0;		//地址建立时间(ADDSET)为9个HCLK=54ns
 	//9个HCLK（HCLK=168M）,某些液晶驱动IC的写信号脉宽，最少也得50ns。  	 
	FSMC_Bank1E->BWTR[6]|=8<<8; 	//数据保存时间(DATAST)为6ns*9个HCLK=54ns
	//使能BANK1,区域4
	FSMC_Bank1->BTCR[6]|=1<<0;		//使能BANK1，区域1	    
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER15_0;
}
extern void delay_init(uint8_t SYSCLK);
void system_boot(void)
{
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);
	system_hw_setup();
	canbus_driver_open();
	lcd_driver_open();
	tp_driver_open();
}
