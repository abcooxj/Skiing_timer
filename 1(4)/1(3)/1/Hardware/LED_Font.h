
#include "stm32f10x.h"                  // Device header
#include "Timer.h"
uint8_t flag;
uint8_t Second,Second_Two,Minute,Minute_Two,Hour,Hour_Two,Milliseconds,Milliseconds_Two,Milliseconds_Three;

#define 		Zero       	 		  	(0x30)
#define 		One       			  	(0x31)
#define 		Two       			  	(0x32)
#define 		Three     		    	(0x33)
#define 		Four      			 	(0x34)
#define 		Five     			    (0x35)
#define 		Six          			(0x36)
#define 		Seven       			(0x37)
#define 		Eight       			(0x38)
#define 		Nine        			(0x39)
#define 		Aline_length      		(34)

//LED显示格式
/*
包头格式固定：0xFE,0x5C,0x4B,0x89
包尾格式固定：0XFF,0xFF

*/
uint8_t LEDShowing_Format[]={0xFE,0x5C,0x4B,0x89,0x4F,0x00,0x00,0x00,0x65,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,
	0x29,0x00,0xFF,0xFF,0x0A,One,0x2A,Zero,Zero,0x22,Zero,Zero,0x27,Zero,Zero,
	0x2A,0x00,0xFF,0xFF,0x0A,Two,0x2A,Zero,Zero,0x22,Zero,Zero,0x27,Zero,Zero,
	0x2B,0x00,0xFF,0xFF,0x0A,0xFF,0xFF};//54个数据

//定义秒表的每一位数据				
uint8_t Stopwatch_Data[7]={Zero,Zero,Zero,Zero,Zero,Zero,Zero};

uint8_t ASCII_code[10]={Zero,One,Two,Three,Four,Five,Six,Seven,Eight,Nine};  //0~9的ASCII码值数组

uint8_t One_People[7]={One,Zero,Zero,Zero,Zero,Zero,Zero};//第一人的数据：时分秒
uint8_t Two_People[7]={One,Zero,Zero,Zero,Zero,Zero,Zero};//第二人的数据：时分秒

//计时时间显示格式  34个数据 0*00"00'00
uint8_t First_Data_Agreement[Aline_length]={0xFE,0x5C,0x4B,0x89,0x22,0x00,0x00,0x00,0x65,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,
	0x29,0x00,0xFF,0xFF,0x0A,Zero,0x2A,Zero,Zero,0x22,Zero,Zero,0x27,Zero,Zero,0xFF,0xFF};
uint8_t  Second_Data_Agreement[Aline_length]={0xFE,0x5C,0x4B,0x89,0x22,0x00,0x00,0x00,0x65,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,
	0x2A,0x00,0xFF,0xFF,0x0A,Zero,0x2A,Zero,Zero,0x22,Zero,Zero,0x27,Zero,Zero,0xFF,0xFF};


 
void All_Cleaning(void)//把显示屏上的数字清零
{
	uint8_t i;
	
	for(i=1;i<7;i++)//用for循环依次把每一位清零
	{
		One_People[i]=Zero;
		Two_People[i]=Zero;
	}

}



void Timer0_Handle(void) //时间处理
{
	uint8_t i;
	Stopwatch_Data[1]=Minute_Two;
	Stopwatch_Data[2]=Minute;
	Stopwatch_Data[3]=Second_Two;
	Stopwatch_Data[4]=Second;
	Stopwatch_Data[5]=Milliseconds_Two;
	Stopwatch_Data[6]=Milliseconds;
	for(i=0;i<10;i++)
	{
		if(Stopwatch_Data[1]==i)Stopwatch_Data[1]=ASCII_code[i];
		if(Stopwatch_Data[2]==i)Stopwatch_Data[2]=ASCII_code[i];
		if(Stopwatch_Data[3]==i)Stopwatch_Data[3]=ASCII_code[i];
		if(Stopwatch_Data[4]==i)Stopwatch_Data[4]=ASCII_code[i];
		if(Stopwatch_Data[5]==i)Stopwatch_Data[5]=ASCII_code[i];
		if(Stopwatch_Data[6]==i)Stopwatch_Data[6]=ASCII_code[i];
	}
	
}

void ASCII_To_One_People()  //时间从ASCII码赋给第一个人，再给发送数组  
{
	One_People[1]=Stopwatch_Data[1];
	One_People[2]=Stopwatch_Data[2];
	One_People[3]=Stopwatch_Data[3];
	One_People[4]=Stopwatch_Data[4];
	One_People[5]=Stopwatch_Data[5];
	One_People[6]=Stopwatch_Data[6];
	First_Data_Agreement[22]=One_People[0];
	First_Data_Agreement[24]=One_People[1];
	First_Data_Agreement[25]=One_People[2];
	First_Data_Agreement[27]=One_People[3];
	First_Data_Agreement[28]=One_People[4];
	First_Data_Agreement[30]=One_People[5];
	First_Data_Agreement[31]=One_People[6];
	
}

void One_People_To_First_Data_Agreement()   //第1个人成绩给发送数组
{
	First_Data_Agreement[22]=One_People[0];//1
	
	First_Data_Agreement[24]=One_People[1];//时
	First_Data_Agreement[25]=One_People[2];
	
	First_Data_Agreement[27]=One_People[3];//分
	First_Data_Agreement[28]=One_People[4];
	
	First_Data_Agreement[30]=One_People[5];//秒
	First_Data_Agreement[31]=One_People[6];
}	

void Two_People_To_Second_Data_Agreement()   //第2个人成绩给发送数组
{
	Second_Data_Agreement[22]=Two_People[0];
	
	Second_Data_Agreement[24]=Two_People[1];
	Second_Data_Agreement[25]=Two_People[2];
	
	Second_Data_Agreement[27]=Two_People[3];
	Second_Data_Agreement[28]=Two_People[4];
	
	Second_Data_Agreement[30]=Two_People[5];
	Second_Data_Agreement[31]=Two_People[6];
}


void TIM2_IRQHandler(void)//中断
{
		if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
		{	
		if(flag==1)//判断按键是否按下标志位
			Milliseconds_Three++;
		else Milliseconds_Three=0;
		if(Milliseconds_Three>=100)
		{
			Milliseconds_Three=0;
			Milliseconds++;
			if(Milliseconds>=10)
			{
				Milliseconds=0;
				Milliseconds_Two++;
				if(Milliseconds_Two>=10)
				{
			Milliseconds_Two=0;
			Second++;
			if(Second>=10)           //个位
		{
			Second=0;
			Second_Two++; 
				if(Second_Two>=6)   //十位
					{
						Second_Two=0;
						Minute++;
							if(Minute>10)
							{
								Minute=0;
								Minute_Two++;
								
										}
									}
								}
							}
					}
		}
	}
			TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志位
		
}

