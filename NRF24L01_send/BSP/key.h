#ifndef __KEY_H_
#define __KEY_H_

#include "main.h"
#include "stdbool.h"

struct keys
{
	unsigned char judge_sta;//判断进行到哪一步
	bool  key_sta;//识别硬件按键按下，按下为0
	bool single_flag;//如果确认按键按下，为1
};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);


#endif
