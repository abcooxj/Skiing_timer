#include "stm32f10x.h"                  // Device header
#include "drv_AS62.h"

//模块配置参数数组
//改变模块参数，只需改变参数数组值，然后初始化即可
const uint8_t g_ASxx_Param_Config[ 6 ] = { 0xC0, 0x12, 0x34, 0x1A, 0x17, 0xC4 };			//定点模式
const uint8_t  g_ASxx_Config_Status_OK[ ] = { 0x4F, 0x4B, 0x0D, 0x0A };


/**
  * @brief :ASxx模块初始化
  * @param :无
  * @note  :按照默认参数初始化，修改默认参数表即可改变模块初始化参数
  * @retval:
  *        @ASxx_Write_OK 写入成功
  *        @ASxx_Write_ERROR 写入失败
  */
ASxxWriteStatusType ASxx_param_init( void )
{
	uint8_t i = 0;
	uint8_t Read_Buff[ 5 ] = { 0 };
	
	drv_uart_tx_bytes((uint8_t *)g_ASxx_Param_Config, 6 );
	drv_uart_rx_bytes( Read_Buff );
	
	for( i = 0; i < 4; i++ )
	{
		if( Read_Buff[ i ] != g_ASxx_Config_Status_OK[ i ] )
		{
			break;
		}
	}
	
	if( 4 == i )
	{
		return ASxx_Write_OK;		//配置成功
	}
	else
	{
		return ASxx_Write_ERROR;	//配置失败
	}
	
}

/**
  * @brief :ASxx模块读配置参数
  * @param :
  *         @pReadBuffer：参数返回地址
  * @note  :无
  * @retval:无
  */
void ASxx_read_param( uint8_t *pReadBuffer )
{
	uint8_t Read_Cmd[ 3 ] = { 0xC1, 0xC1, 0xC1 };

	drv_uart_tx_bytes( Read_Cmd, 3 );
	drv_uart_rx_bytes( pReadBuffer );
	
}

/**
  * @brief :ASxx模块读取硬件版本号
  * @param :
  *         @pReadBuffer：硬件版本号返回地址
  * @note  :无
  * @retval:无
  */
void ASxx_read_version( uint8_t *pReadBuffer )
{
	uint8_t Read_Cmd[ 3 ] = { 0xC3, 0xC3, 0xC3 };

	drv_uart_tx_bytes( Read_Cmd, 3 );
	drv_uart_rx_bytes( pReadBuffer );
}

/**
  * @brief :ASxx模块读取实际电压值
  * @param :
  *         @pReadBuffer：电压值返回地址
  * @note  :无
  * @retval:无
  */
void ASxx_read_voltage( uint8_t *pReadBuffer )
{
	uint8_t Read_Cmd[ 3 ] = { 0xC5, 0xC5, 0xC5 };

	drv_uart_tx_bytes( Read_Cmd, 3 );
	drv_uart_rx_bytes( pReadBuffer );
}

/**
  * @brief :ASxx模块复位
  * @param :无
  * @note  :无
  * @retval:无
  */
void ASxx_reset( void )
{
	uint8_t Read_Cmd[ 3 ] = { 0xC4, 0xC4, 0xC4 };

	drv_uart_tx_bytes( Read_Cmd, 3 );
}

/**
  * @brief :ASxx模块发送数据（定点模式）
  * @param :
  *        @Addr_H：地址高位
  *        @Addr_L：地址低位
  *        @Channel：信道
  *        @pTxBuff：发送数据地址
  *        @Length：发送数据个数
  * @note  :定点模式 数据个数最29个
  * @retval:无
  */
void ASxx_tx_packet( uint8_t Addr_H, uint8_t Addr_L, uint8_t Channel, uint8_t *pTxBuff, uint8_t Length )
{
	uint8_t Header[ 3 ] = { 0 };
	
	Header[ 0 ] = Addr_H;
	Header[ 1 ] = Addr_L;
	Header[ 2 ] = Channel;
	
	drv_uart_tx_bytes( Header, 3 );
	//发送数据
	drv_uart_tx_bytes( pTxBuff, Length );
}

/**
  * @brief :ASxx模块接收数据（定点模式）
  * @param :无
  * @note  :定点模式 数据个数最29个
  * @retval:无
  */
uint8_t ASxx_rx_packet( uint8_t *pRxBuff )
{
	uint8_t Length = 0;
	
	Length = drv_uart_rx_bytes( pRxBuff );
	
	return Length;
}

/**
  * @brief :ASxx模块在山上进行发送,并且
  * @param :无
  * @note  :定点模式 数据个数最29个
  * @retval:无
  */
//void ASxx_rx_actions(void)
//{
//   //串口初始化  根据模块波特率变化
//	drv_uart_init( 9600 );
//	//延时初始化
//	drv_delay_init( );
//	  
//	//LED初始化
//	drv_led_init( );
//	
//	Key_Init();
////	Buzzer_Init();
//	 led_green_off();        
//    led_red_off();          //初始化LED灭

//	
//	OLED_Init();
//	//ASxx模块参数初始化 定点模式 地址 0x1234 信号0x17
//	ASxx_param_init( );
//	
//    OLED_Init();
//    if(KeyNum==1)
//		{
//			
//	
//		
//		    ASxx_tx_packet( 0x12, 0x35, 0x17, (uint8_t *)pAshining, 8 );	//向地址为0x1235 信道为0x17的模块 发送固定字符串 ashining 字符串
//					
//		OLED_ShowString(1, 1, "Tx:");  // 在OLED上显示"Tx:"
//			OLED_ShowString(2, 1, (uint8_t*)pAshining);  // 在OLED上显示发送的数据
//			
//			led_red_flashing( );
//			drv_delay_500Ms( 3 );
//			GPIO_SetBits(GPIOB,GPIO_Pin_12);//开启有源蜂鸣器
//		}
//		if(KeyNum==2)
//		{
//			OLED_ShowString(1, 1, "0:");
//		}
//}

