#include "stm32f10x.h"                  // Device header
#include "drv_led.h"

void drv_led_init( void )
{
	
	GPIO_InitTypeDef	GpioInitStructer;
	
	//ʹ�ܿ���ʱ��
	RCC_APB2PeriphClockCmd( LED_RED_GPIO_CLK | LED_BLUE_GPIO_CLK | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC , ENABLE );	//�򿪶˿�ʱ�� PA��PC
	
	GpioInitStructer.GPIO_Mode = GPIO_Mode_Out_PP;						
	GpioInitStructer.GPIO_Speed = GPIO_Speed_2MHz;		
	
	GpioInitStructer.GPIO_Pin = LED_RED_GPIO_PIN;		
	GPIO_Init( LED_RED_GPIO_PORT, &GpioInitStructer );			//��ʼ����ɫLED����
	GPIO_SetBits( LED_RED_GPIO_PORT, LED_RED_GPIO_PIN );		//��ʼ״̬�øߣ���ɫLED��ʼ��״̬Ĭ��Ϊ��
	
	GpioInitStructer.GPIO_Pin = LED_BLUE_GPIO_PIN;		
	GPIO_Init( LED_BLUE_GPIO_PORT, &GpioInitStructer );			//��ʼ����ɫLED����
	GPIO_SetBits( LED_BLUE_GPIO_PORT, LED_BLUE_GPIO_PIN );		//��ʼ״̬�øߣ���ɫLED��ʼ��״̬Ĭ��Ϊ��
  //��ʼ��LED����PC13
	GpioInitStructer.GPIO_Pin = LED_GPIO_PIN;		
	GPIO_Init( LED_GPIO_PORT, &GpioInitStructer );			//��ʼ��LED����
	GPIO_SetBits( LED_GPIO_PORT, LED_GPIO_PIN );		//��ʼ״̬�ø�
	//��ʼ����������D0��D1
	GpioInitStructer.GPIO_Pin = D0_GPIO_PIN;		
	GPIO_Init( D0_GPIO_PORT, &GpioInitStructer );			//��ʼ��LED����
	GPIO_SetBits( D0_GPIO_PORT, D0_GPIO_PIN );		//��ʼ״̬�ø�
	
	GpioInitStructer.GPIO_Pin = D1_GPIO_PIN;		
	GPIO_Init( D1_GPIO_PORT, &GpioInitStructer );			//��ʼ��LED����
	GPIO_SetBits( D1_GPIO_PORT, D1_GPIO_PIN );		//��ʼ״̬�ø�
	
}


void drv_led_on( LedPortType LedPort )
{
	if( LED_RED == LedPort )	//LED_RED
	{
		GPIO_ResetBits( LED_RED_GPIO_PORT, LED_RED_GPIO_PIN );		//��ɫLED�����õͣ���ɫLED��
	}
	else						//LED_BLUE
	{
		GPIO_ResetBits( LED_BLUE_GPIO_PORT, LED_BLUE_GPIO_PIN );	//��ɫLED�����õͣ���ɫLED��
	}
	
}


void drv_led_off( LedPortType LedPort )
{
	if( LED_RED == LedPort )	//LED_RED
	{
		GPIO_SetBits( LED_RED_GPIO_PORT, LED_RED_GPIO_PIN );		//��ɫLED�����øߣ���ɫLED��
	}
	else						//LED_BLUE
	{
		GPIO_SetBits( LED_BLUE_GPIO_PORT, LED_BLUE_GPIO_PIN );		//��ɫLED�����øߣ���ɫLED��
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
