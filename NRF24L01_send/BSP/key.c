#include "key.h"

struct keys key[4]={0,0,0};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM3)			//�ж��ж��ź��Ƿ�����TIM3
	{
		key[0].key_sta=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);		//����PB0���ڵ�״̬����������Ϊ0
		key[1].key_sta=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
		key[2].key_sta=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2);

		for(int i = 0;i < 4; i++ )		//ȷ�����ĸ���������
		{
			switch (key[i].judge_sta)
			{
				case 0:
				{
					if(key[i].key_sta==0) key[i].judge_sta = 1;	//��һ���ж��Ƿ���
				}
				break;
				case 1:
				{
					if(key[i].key_sta==0)	//������һ�ζ�ʱ��ɨ�裬�������ǰ��µ�״̬����ȷ��Ϊ���£��Դ˽�������
					{
						key[i].judge_sta = 2;
						key[i].single_flag = 1;
					}
					else		//������Ƕ��������β��㰴��������
						key[i].judge_sta = 0;
				}
				break;
				case 2:
				{
					if(key[i].key_sta==1)
					{	
					key[i].judge_sta = 0;	//�ж��Ƿ����֣����ֺ󰴼�״̬����
					}
				}
				break;
			}
		}
	}
}
