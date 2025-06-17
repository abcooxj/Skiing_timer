#include "stm32f10x.h"                  // Device header

/**
   *@brief    初始化定时器
   *@param    无
   *@retval   无
   *@note     无
  */
void Timer_Init(void)
{
    /*第一步：配置RCC--打开相应外设的时钟*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启TIM2的时钟
    
    /*第二步：选择时基单元的时钟*/
    TIM_InternalClockConfig(TIM2);//选择时基单元的时钟--内部时钟（此行代码可不写--定时器上电后默认就是使用内部时钟））
    
    /*第三步：配置时基单元*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//定义结构体TIM_TimeBaseInitStructure
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//指定时钟分频--此为一分频即不分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//选择计数器模式（向上计数、向下计数和三种中央对齐计数）
    TIM_TimeBaseInitStructure.TIM_Period = 72 - 1;//周期--ARR自动重装器的值（减1是因为计数器有一个数的偏差）
    TIM_TimeBaseInitStructure.TIM_Prescaler = 10000 - 1;//PSC预分频器的值（减1是因为预分频器有一个数的偏差）
    /*上两行代码：预分频对72M进行7200分频即10K的计数频率，则在10K的频率下计10000个数即为1s*/
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//重复计数器的值
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化时基单元
    /*
        补充：1、计数器溢出频率：CK_CNT_OV = CK_CNT / (ARR + 1) = CK_PSC / (PSC + 1) / (ARR + 1)即定时器频率=72M/（PSC+1）/（ARR+1）
            2、ARR和PSC的取值应在0~65535之间
            3、当PSC较小，ARR较大时，即以一个比较高的频率记较多的数；反之即为以一个比较低的频率计比较少的数
    */
    
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);//手动将更新中断标志位清除--避免刚初始化就进入中断--解除了上电后从1开始增加
    /*第四步：使能更新中断*/
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//开启了TIM2的更新中断到NVIC的通路
    
    /*第五步：配置NVIC--给中断选择合适的优先级（通过NVIC中断信号即可进入CPU）*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//指定中断的分组--配置优先级分组（先占优先级（pre-emption priority）--抢占优先级和从占优先级（subpriority）--响应优先级）；参数是中断分组的方式（分组方式整个芯片只能用一种方式--若将其放在模块中（如同本工程）每个模块必须是同一种分组方式，如是将其放在住主函数中的最开始，模块中就不必在分组了））
    
    NVIC_InitTypeDef NVIC_InitStructure;//定义结构体NVIC_InitStructrue
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//指定所使用的中断通道
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//指定所使用的中断通道的状态（（ENABLE和DISABLE））--使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//指定抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//指定响应优先级
    NVIC_Init(&NVIC_InitStructure);//初始化NVIC
    
    TIM_Cmd(TIM2,ENABLE);//启动定时器
}

/**
   *@brief    外部中断函数模板
   *@param    无
   *@retval   无
   *@note     无
  */
/*
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)//先进行中断标志位的判断--判断TIM2的更新中断的标志位是否为1
    {
        
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志位（若不清除中断标志位，他将一直申请中断，程序则会一直响应中断而执行中断函数，导致程序卡死在中断函数中）
    }
}
*/
