#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>


uint16_t res;

void Serial_Init(void)
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		USART_InitTypeDef USART_InitStructure;
		USART_InitStructure.USART_BaudRate=9600;//������
		USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//Ӳ��������
		USART_InitStructure.USART_Mode=USART_Mode_Tx;//���ô���ģʽΪ����
		USART_InitStructure.USART_Parity=USART_Parity_No;//����У��λ ��У��λ
		USART_InitStructure.USART_StopBits=USART_StopBits_1;//����ֹͣλ 
		USART_InitStructure.USART_WordLength=USART_WordLength_8b;//�����ֳ� 8λ
		USART_Init(USART3,&USART_InitStructure);

		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		NVIC_InitTypeDef NVIC_InitStruct;
		NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; // 1
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;        // 1
	
		USART_Cmd(USART3,ENABLE);
}

void Serial_SendByte(uint8_t Byte)//��������
{
		USART_SendData(USART3,Byte);
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
		
}

void Serial_SendArray(uint8_t *Array,uint16_t Length)//��������
{
	uint16_t i;
	for(i=0;i<Length;i++)//����ȡ�������ÿһλ
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)	//�����ַ���
{
	uint8_t i;
	for(i=0;String[i]!='\0';i++)//���ַ�0��Ϊ�����ı�־λ
	{
		Serial_SendByte(String[i]);
	}

}

uint32_t Serial_Pow(uint32_t x,uint32_t Y)
{
		uint32_t Result=1;
	while(Y--)
	{
	
	Result *=x;
	}
		return Result;
}

void Serial_SendNumber(uint32_t Number,uint8_t Length)//��������
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Number/Serial_Pow(10,Length-i-1)%10+0x30);//0x30='0'
		
	}

}

int fputc(int ch, FILE *f)//���¶��򵽴���
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)//�ɱ����
{
	char String[100];
	va_list arg;
	va_start(arg, format);//���ղ������ŵ�arg����
	vsprintf(String, format, arg);//��ʽ��������
	va_end(arg);//�ͷŲ���
	Serial_SendString(String);
	
}

void USART1_IRQHandler(void)
{
	if (USART_GetFlagStatus(USART3,USART_IT_RXNE) == SET)//�жϱ�־λ
	{
		
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);//�����־λ
		
	}
}

