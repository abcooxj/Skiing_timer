#ifndef __KEY_H_
#define __KEY_H_

#include "main.h"
#include "stdbool.h"

struct keys
{
	unsigned char judge_sta;//�жϽ��е���һ��
	bool  key_sta;//ʶ��Ӳ���������£�����Ϊ0
	bool single_flag;//���ȷ�ϰ������£�Ϊ1
};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);


#endif
