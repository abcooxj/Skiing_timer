#include "stm32f10x.h"    // Device header
#include "drv_delay.h"
#include "drv_uart.h"
#include "drv_led.h"
#include "drv_AS62.h"
#include "OLED.h"
#include "Key.h"
#include "Buzzer.h"
#include "Delay.h"
#include "stdio.h"
#include "Timer.h"

void oled_disp(void);
void timer_disp(void);
void key_proc(void);

#define __AS62_TX_MODE__									/**@@ ����ģʽ�� ���μ�Ϊ����ģʽ @@ **/


#ifdef __AS62_TX_MODE__
//	char *pAshining = "1";
	char *pAshining = "ashining";

#else
//     uint8_t g_ashining[ 8 ] ={ '1', '0', 'h', '0', '0', '0', '0', '0' };

     uint8_t g_ashining[ 8 ] ={ 'a', 's', 'h', 'i', 'n', 'i', 'n', 'g' };
	uint8_t g_As62_rx_buffer[ 100 ] = { 0 };
	uint8_t g_RxLength = 0;
#endif
    
int view = 0;   
uint8_t timer_flag;    

int main(void)	
{
	
	//���ڳ�ʼ��  ����ģ�鲨���ʱ仯
	drv_uart_init( 9600 );
	
	//ASxxģ�������ʼ�� ����ģʽ ��ַ 0x1234 �ź�0x17
	ASxx_param_init( );
	  
	Key_Init();
	Buzzer_Init();
    Timer_Init();//��ʼ����ʱ��
	OLED_Init();
ASxx_reset();
    OLED_Clear();
	while(1)
	{
       key_proc();
        oled_disp();
        timer_disp();	
	}
}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)//�Ƚ����жϱ�־λ���ж�--�ж�TIM2�ĸ����жϵı�־λ�Ƿ�Ϊ1
    {
        key_serv();
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//����жϱ�־λ����������жϱ�־λ������һֱ�����жϣ��������һֱ��Ӧ
    }
}

void key_proc(void)
{
    if (key[1].short_flag  == 1)
        {           
            view=0;
            timer_flag=1;
            key[1].short_flag  = 0;
        }
        else if (key[2].short_flag  == 1)
        {     
            view=1;
            ASxx_tx_packet(0x00, 0x00, 0x17, (uint8_t *)pAshining, 8);  // ���ַΪ 0x0000 �ŵ�Ϊ 0x17 ��ģ�鷢�͹̶��ַ���			
           key[2].short_flag  = 0;
            ASxx_reset();
        }
        else if (key[3].short_flag  == 1)
        {  
            view=2;
            ASxx_tx_packet(0x00, 0x00, 0x17, (uint8_t *)pAshining, 8);  // ���ַΪ 0x0000 �ŵ�Ϊ 0x17 ��ģ�鷢�͹̶��ַ���		   
            key[3].short_flag  = 0;
            ASxx_reset();
        }
      else
      {
          
      }
}


void oled_disp(void)
{
    if(view==0)
    {
       OLED_ShowNum(3,5,1,2);
    }
    if(view==1)
    {
        OLED_ShowNum(3,5,2,2);
        OLED_ShowString(1, 1, "Tx:");  // �� OLED ����ʾ "Tx:"
		OLED_ShowString(2, 1, pAshining);  // �� OLED ����ʾ���͵�����
    }
     if(view==2)
    {
        OLED_ShowNum(3,5,3,2);
        OLED_ShowString(1, 1, "Tx:");  // �� OLED ����ʾ "Tx:"
		OLED_ShowString(2, 1, pAshining);  // �� OLED ����ʾ���͵�����
    }
    if(view==3)
    {
        OLED_ShowNum(3,5,0,2);
    }
}

void timer_disp(void)
{
    int i=0;
    if(timer_flag==1)
    {
        for(i=0;i<100;i++)
        {
            Buzzer_ON();
            timer_flag=0;
        }      
            Buzzer_OFF();
    }
    else
        {
            Buzzer_OFF();
        }
}
