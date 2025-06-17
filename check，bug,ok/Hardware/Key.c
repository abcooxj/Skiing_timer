#include "key.h"

struct keys key[4];

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void key_serv(void)
{
    key[1].key_sta = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
    key[2].key_sta = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
    key[3].key_sta = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
    
    for (int i = 0; i < 4; i++)
    {
        switch (key[i].judge_sta)
        {
            case 0:
            {
                if (key[i].key_sta == 0)
                    key[i].judge_sta = 1;
            }break;
            
            case 1:
            {
                if (key[i].key_sta == 0)
                {
                    key[i].judge_sta = 2;
                    key[i].short_flag = 1;
                }
                else
                    key[i].judge_sta = 0;
            }break;
            
            case 2:
            {
                if (key[i].key_sta == 1)
                    key[i].judge_sta = 0;
            }break;
        }
    }
}
