#ifndef	__DRV_LED_H__
#define __DRV_LED_H__


#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"



//LEDӲ������ 
#define LED_RED_GPIO_PORT			GPIOB								
#define LED_RED_GPIO_CLK			RCC_APB2Periph_GPIOB
#define LED_RED_GPIO_PIN			GPIO_Pin_10

#define LED_BLUE_GPIO_PORT			GPIOA								
#define LED_BLUE_GPIO_CLK			RCC_APB2Periph_GPIOA
#define LED_BLUE_GPIO_PIN			GPIO_Pin_5

//LED�˿ڶ���
#define LED_GPIO_PORT          GPIOC
#define LED_GPIO_PIN           GPIO_Pin_13

//D0,D1�˿ڶ���
#define D0_GPIO_PORT          GPIOA
#define D0_GPIO_PIN           GPIO_Pin_1

#define D1_GPIO_PORT          GPIOA
#define D1_GPIO_PIN           GPIO_Pin_2

/** LED���� */
typedef enum LedPort
{
	LED_RED = 0,		//��ɫLED
	LED_GREEN			//��ɫLED
}LedPortType;


void drv_led_init( void );
void drv_led_on( LedPortType LedPort );
void drv_led_off( LedPortType LedPort );
void drv_led_flashing( LedPortType LedPort );

//��ɫLED��������
#define led_red_on( )				drv_led_on( LED_RED )
#define led_red_off( )				drv_led_off( LED_RED )
#define led_red_flashing( )			drv_led_flashing( LED_RED )
//��ɫLED��������
#define led_green_on( )				drv_led_on( LED_GREEN )
#define led_green_off( )			drv_led_off( LED_GREEN )
#define led_green_flashing( )		drv_led_flashing( LED_GREEN )


#endif

