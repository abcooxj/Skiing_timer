#include "stm32f10x.h"                  // Device header

/**
   *@brief    ��ʼ����ʱ��
   *@param    ��
   *@retval   ��
   *@note     ��
  */
void Timer_Init(void)
{
    /*��һ��������RCC--����Ӧ�����ʱ��*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//����TIM2��ʱ��
    
    /*�ڶ�����ѡ��ʱ����Ԫ��ʱ��*/
    TIM_InternalClockConfig(TIM2);//ѡ��ʱ����Ԫ��ʱ��--�ڲ�ʱ�ӣ����д���ɲ�д--��ʱ���ϵ��Ĭ�Ͼ���ʹ���ڲ�ʱ�ӣ���
    
    /*������������ʱ����Ԫ*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//����ṹ��TIM_TimeBaseInitStructure
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ָ��ʱ�ӷ�Ƶ--��Ϊһ��Ƶ������Ƶ
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//ѡ�������ģʽ�����ϼ��������¼���������������������
    TIM_TimeBaseInitStructure.TIM_Period = 72 - 1;//����--ARR�Զ���װ����ֵ����1����Ϊ��������һ������ƫ�
    TIM_TimeBaseInitStructure.TIM_Prescaler = 10000 - 1;//PSCԤ��Ƶ����ֵ����1����ΪԤ��Ƶ����һ������ƫ�
    /*�����д��룺Ԥ��Ƶ��72M����7200��Ƶ��10K�ļ���Ƶ�ʣ�����10K��Ƶ���¼�10000������Ϊ1s*/
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//�ظ���������ֵ
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��ʱ����Ԫ
    /*
        ���䣺1�����������Ƶ�ʣ�CK_CNT_OV = CK_CNT / (ARR + 1) = CK_PSC / (PSC + 1) / (ARR + 1)����ʱ��Ƶ��=72M/��PSC+1��/��ARR+1��
            2��ARR��PSC��ȡֵӦ��0~65535֮��
            3����PSC��С��ARR�ϴ�ʱ������һ���Ƚϸߵ�Ƶ�ʼǽ϶��������֮��Ϊ��һ���Ƚϵ͵�Ƶ�ʼƱȽ��ٵ���
    */
    
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);//�ֶ��������жϱ�־λ���--����ճ�ʼ���ͽ����ж�--������ϵ���1��ʼ����
    /*���Ĳ���ʹ�ܸ����ж�*/
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//������TIM2�ĸ����жϵ�NVIC��ͨ·
    
    /*���岽������NVIC--���ж�ѡ����ʵ����ȼ���ͨ��NVIC�ж��źż��ɽ���CPU��*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ָ���жϵķ���--�������ȼ����飨��ռ���ȼ���pre-emption priority��--��ռ���ȼ��ʹ�ռ���ȼ���subpriority��--��Ӧ���ȼ������������жϷ���ķ�ʽ�����鷽ʽ����оƬֻ����һ�ַ�ʽ--���������ģ���У���ͬ�����̣�ÿ��ģ�������ͬһ�ַ��鷽ʽ�����ǽ������ס�������е��ʼ��ģ���оͲ����ڷ����ˣ���
    
    NVIC_InitTypeDef NVIC_InitStructure;//����ṹ��NVIC_InitStructrue
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//ָ����ʹ�õ��ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ָ����ʹ�õ��ж�ͨ����״̬����ENABLE��DISABLE����--ʹ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//ָ����ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//ָ����Ӧ���ȼ�
    NVIC_Init(&NVIC_InitStructure);//��ʼ��NVIC
    
    TIM_Cmd(TIM2,ENABLE);//������ʱ��
}

/**
   *@brief    �ⲿ�жϺ���ģ��
   *@param    ��
   *@retval   ��
   *@note     ��
  */
/*
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)//�Ƚ����жϱ�־λ���ж�--�ж�TIM2�ĸ����жϵı�־λ�Ƿ�Ϊ1
    {
        
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//����жϱ�־λ����������жϱ�־λ������һֱ�����жϣ��������һֱ��Ӧ�ж϶�ִ���жϺ��������³��������жϺ����У�
    }
}
*/
