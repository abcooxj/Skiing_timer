#include "key.h"

struct keys key[4]={0,0,0};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM3)			//判断中断信号是否来自TIM3
	{
		key[0].key_sta=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);		//按键PB0现在的状态，被按下则为0
		key[1].key_sta=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
		key[2].key_sta=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2);

		for(int i = 0;i < 4; i++ )		//确认是哪个键被按下
		{
			switch (key[i].judge_sta)
			{
				case 0:
				{
					if(key[i].key_sta==0) key[i].judge_sta = 1;	//第一次判断是否按下
				}
				break;
				case 1:
				{
					if(key[i].key_sta==0)	//进入下一次定时器扫描，按键还是按下的状态，则确认为按下，以此进行消抖
					{
						key[i].judge_sta = 2;
						key[i].single_flag = 1;
					}
					else		//否则就是抖动，本次不算按键被按下
						key[i].judge_sta = 0;
				}
				break;
				case 2:
				{
					if(key[i].key_sta==1)
					{	
					key[i].judge_sta = 0;	//判断是否松手，松手后按键状态重置
					}
				}
				break;
			}
		}
	}
}
