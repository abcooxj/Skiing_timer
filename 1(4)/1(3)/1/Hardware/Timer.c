#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//配置通用定时器2
	
		TIM_InternalClockConfig(TIM2);//调用内部时钟（不写也可以，上电后默认就是内部时钟）
		//配置时基单元
		TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
		TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//设置分频模式：一分频
		TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//设置定时器模式：向上计数
		TimeBaseInitStructure.TIM_Period=10-1;   //ARR自动重装值
		TimeBaseInitStructure.TIM_Prescaler=720-1;  //PSC预分频器值
		TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器
	
		TIM_TimeBaseInit(TIM2,&TimeBaseInitStructure);//初始化
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);//手动清除中断标志位
		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能中断
		//配置NVIC
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断优先级分组
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;//配置中断通道
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使能
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//响应优先级
		NVIC_Init(&NVIC_InitStructure);
	
		TIM_Cmd(TIM2,ENABLE);//启动定时器
}

