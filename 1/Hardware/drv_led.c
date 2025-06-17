#include "stm32f10x.h"                  // Device header
#include "drv_led.h"

void drv_led_init( void )
{
	
	GPIO_InitTypeDef	GpioInitStructer;
	
	//使能口线时钟
	RCC_APB2PeriphClockCmd( LED_RED_GPIO_CLK | LED_BLUE_GPIO_CLK | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC , ENABLE );	//打开端口时钟 PA和PC
	
	GpioInitStructer.GPIO_Mode = GPIO_Mode_Out_PP;						
	GpioInitStructer.GPIO_Speed = GPIO_Speed_2MHz;		
	
	GpioInitStructer.GPIO_Pin = LED_RED_GPIO_PIN;		
	GPIO_Init( LED_RED_GPIO_PORT, &GpioInitStructer );			//初始化红色LED引脚
	GPIO_SetBits( LED_RED_GPIO_PORT, LED_RED_GPIO_PIN );		//初始状态置高，红色LED初始化状态默认为灭
	
	GpioInitStructer.GPIO_Pin = LED_BLUE_GPIO_PIN;		
	GPIO_Init( LED_BLUE_GPIO_PORT, &GpioInitStructer );			//初始化蓝色LED引脚
	GPIO_SetBits( LED_BLUE_GPIO_PORT, LED_BLUE_GPIO_PIN );		//初始状态置高，蓝色LED初始化状态默认为灭
  //初始化LED引脚PC13
	GpioInitStructer.GPIO_Pin = LED_GPIO_PIN;		
	GPIO_Init( LED_GPIO_PORT, &GpioInitStructer );			//初始化LED引脚
	GPIO_SetBits( LED_GPIO_PORT, LED_GPIO_PIN );		//初始状态置高
	//初始化控制引脚D0、D1
	GpioInitStructer.GPIO_Pin = D0_GPIO_PIN;		
	GPIO_Init( D0_GPIO_PORT, &GpioInitStructer );			//初始化LED引脚
	GPIO_SetBits( D0_GPIO_PORT, D0_GPIO_PIN );		//初始状态置高
	
	GpioInitStructer.GPIO_Pin = D1_GPIO_PIN;		
	GPIO_Init( D1_GPIO_PORT, &GpioInitStructer );			//初始化LED引脚
	GPIO_SetBits( D1_GPIO_PORT, D1_GPIO_PIN );		//初始状态置高
	
}


void drv_led_on( LedPortType LedPort )
{
	if( LED_RED == LedPort )	//LED_RED
	{
		GPIO_ResetBits( LED_RED_GPIO_PORT, LED_RED_GPIO_PIN );		//红色LED引脚置低，红色LED亮
	}
	else						//LED_BLUE
	{
		GPIO_ResetBits( LED_BLUE_GPIO_PORT, LED_BLUE_GPIO_PIN );	//蓝色LED引脚置低，蓝色LED亮
	}
	
}


void drv_led_off( LedPortType LedPort )
{
	if( LED_RED == LedPort )	//LED_RED
	{
		GPIO_SetBits( LED_RED_GPIO_PORT, LED_RED_GPIO_PIN );		//红色LED引脚置高，红色LED灭
	}
	else						//LED_BLUE
	{
		GPIO_SetBits( LED_BLUE_GPIO_PORT, LED_BLUE_GPIO_PIN );		//蓝色LED引脚置高，蓝色LED灭
	}
	
}


void drv_led_flashing( LedPortType LedPort )
{
	
	if( LED_RED == LedPort )
	{
		LED_RED_GPIO_PORT->ODR ^= ( uint32_t)LED_RED_GPIO_PIN;
	}
	else
	{
		LED_BLUE_GPIO_PORT->ODR ^= ( uint32_t)LED_BLUE_GPIO_PIN;
	}
}
