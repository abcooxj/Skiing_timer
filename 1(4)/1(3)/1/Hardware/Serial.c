#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>


uint16_t res;

void Serial_Init(void)
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		USART_InitTypeDef USART_InitStructure;
		USART_InitStructure.USART_BaudRate=9600;//波特率
		USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//硬件流控制
		USART_InitStructure.USART_Mode=USART_Mode_Tx;//配置串口模式为发送
		USART_InitStructure.USART_Parity=USART_Parity_No;//配置校验位 无校验位
		USART_InitStructure.USART_StopBits=USART_StopBits_1;//配置停止位 
		USART_InitStructure.USART_WordLength=USART_WordLength_8b;//配置字长 8位
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

void Serial_SendByte(uint8_t Byte)//发送数据
{
		USART_SendData(USART3,Byte);
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
		
}

void Serial_SendArray(uint8_t *Array,uint16_t Length)//发送数组
{
	uint16_t i;
	for(i=0;i<Length;i++)//依次取出数组的每一位
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)	//发送字符串
{
	uint8_t i;
	for(i=0;String[i]!='\0';i++)//空字符0即为结束的标志位
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

void Serial_SendNumber(uint32_t Number,uint8_t Length)//发送数字
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Number/Serial_Pow(10,Length-i-1)%10+0x30);//0x30='0'
		
	}

}

int fputc(int ch, FILE *f)//重新定向到串口
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)//可变参数
{
	char String[100];
	va_list arg;
	va_start(arg, format);//接收参数表并放到arg里面
	vsprintf(String, format, arg);//格式化参数表
	va_end(arg);//释放参数
	Serial_SendString(String);
	
}

void USART1_IRQHandler(void)
{
	if (USART_GetFlagStatus(USART3,USART_IT_RXNE) == SET)//判断标志位
	{
		
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);//清零标志位
		
	}
}

