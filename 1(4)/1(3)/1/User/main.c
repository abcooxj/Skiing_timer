#include "stm32f10x.h"    // Device header
#include "drv_delay.h"
#include "drv_uart.h"
#include "drv_led.h"
#include "drv_AS62.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
#include "Serial.h"
#include "LED_Font.h"


#define __AS62_TX_MODE__									/**@@ ����ģʽ�� ���μ�Ϊ����ģʽ @@ **/


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
uint8_t flag=0;
int main(void)
{
	
	
	//���ڳ�ʼ��  ����ģ�鲨���ʱ仯
	drv_uart_init( 9600 );
	
	//ASxxģ�������ʼ�� ����ģʽ ��ַ 0x1234 �ź�0x17
	ASxx_param_init( );
	
	//��ʱ��ʼ��
	drv_delay_init( );
	  
	//LED��ʼ��
	drv_led_init( );
	
	Timer_Init();
	Serial_Init();
	 led_green_off();        
    led_red_off();          //��ʼ��LED��

	Key_Init();
	OLED_Init();
	
	
	
	while(1)              
	{
				KeyNum=Key_GetNum();
//						if(KeyNum==1)
//							{
								OLED_ShowString(2, 1, "ok");
								flag=0;
								KeyNum=0;
//							}
								if(flag==0)
								{
								OLED_ShowString(3, 1, "over");
								}
				Serial_SendArray(First_Data_Agreement,34);
				Timer0_Handle();
				ASCII_To_One_People();
				One_People_To_First_Data_Agreement();
				g_RxLength = ASxx_rx_packet( g_As62_rx_buffer );
					if(   0 != g_RxLength )
					{
					   flag=1;
						OLED_ShowString(1, 1, "Rx:");  // ��OLED����ʾ"Rx:"
						g_As62_rx_buffer[99]=0;
					}
					

	}
}
	

