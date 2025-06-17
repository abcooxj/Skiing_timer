#include "stm32f10x.h"    // Device header
#include "drv_delay.h"
#include "drv_uart.h"
#include "drv_led.h"
#include "drv_AS62.h"
#include "OLED.h"
#include "Key.h"

#define __AS62_TX_MODE__									/**@@ 发送模式， 屏蔽即为接收模式 @@ **/


#ifdef __AS62_TX_MODE__
	char *pAshining = "ashining";
#else
    uint8_t g_ashining[ 8 ] ={ 'a', 's', 'h', 'i', 'n', 'i', 'n', 'g' };
	uint8_t g_As62_rx_buffer[ 100 ] = { 0 };
	uint8_t g_RxLength = 0;
#endif

uint8_t g_As62_rx_buffer[ 100 ] = { 1 };
uint8_t g_RxLength = 0;
uint8_t KeyNum;
uint8_t oledDisplayNum = 0;
int main(void)
{
	
	
	//串口初始化  根据模块波特率变化
	drv_uart_init( 9600 );
	
	//ASxx模块参数初始化 定点模式 地址 0x1234 信号0x17
	ASxx_param_init( );
	
	//延时初始化
	drv_delay_init( );
	  
	//LED初始化
	drv_led_init( );
	
	Key_Init();
	
	 led_green_off();        
    led_red_off();          //初始化LED灭

	
	OLED_Init();
	
	
	 
	while(1)              
	{
       OLED_ShowString(4, 1, "OK:");  // 在OLED上显示"Rx:"
			g_RxLength = ASxx_rx_packet( g_As62_rx_buffer );
			if(   0 != g_RxLength )
			{
               
				led_green_flashing( );
//                 OLED_ShowString(3, 2, "Oggff:");
				OLED_ShowString(1, 1, "Rx:");  // 在OLED上显示"Rx:"
//                OLED_ShowString(1, 1, "sainging");  // 在OLED上显示"Rx:"
                g_As62_rx_buffer[99]=0;
		 OLED_ShowString(2, 1, (char*)g_As62_rx_buffer);  // 在OLED上显示接收的数据
                
			}

	}
}
	

