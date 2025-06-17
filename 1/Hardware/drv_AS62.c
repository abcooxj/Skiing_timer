#include "stm32f10x.h"                  // Device header
#include "drv_AS62.h"


//ģ�����ò�������
//�ı�ģ�������ֻ��ı��������ֵ��Ȼ���ʼ������
const uint8_t g_ASxx_Param_Config[ 6 ] = { 0xC0, 0x12, 0x34, 0x1A, 0x17, 0xC4 };			//����ģʽ
const uint8_t  g_ASxx_Config_Status_OK[ ] = { 0x4F, 0x4B, 0x0D, 0x0A };


/**
  * @brief :ASxxģ���ʼ��
  * @param :��
  * @note  :����Ĭ�ϲ�����ʼ�����޸�Ĭ�ϲ������ɸı�ģ���ʼ������
  * @retval:
  *        @ASxx_Write_OK д��ɹ�
  *        @ASxx_Write_ERROR д��ʧ��
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
		return ASxx_Write_OK;		//���óɹ�
	}
	else
	{
		return ASxx_Write_ERROR;	//����ʧ��
	}
	
}

/**
  * @brief :ASxxģ������ò���
  * @param :
  *         @pReadBuffer���������ص�ַ
  * @note  :��
  * @retval:��
  */
void ASxx_read_param( uint8_t *pReadBuffer )
{
	uint8_t Read_Cmd[ 3 ] = { 0xC1, 0xC1, 0xC1 };

	drv_uart_tx_bytes( Read_Cmd, 3 );
	drv_uart_rx_bytes( pReadBuffer );
	
}

/**
  * @brief :ASxxģ���ȡӲ���汾��
  * @param :
  *         @pReadBuffer��Ӳ���汾�ŷ��ص�ַ
  * @note  :��
  * @retval:��
  */
void ASxx_read_version( uint8_t *pReadBuffer )
{
	uint8_t Read_Cmd[ 3 ] = { 0xC3, 0xC3, 0xC3 };

	drv_uart_tx_bytes( Read_Cmd, 3 );
	drv_uart_rx_bytes( pReadBuffer );
}

/**
  * @brief :ASxxģ���ȡʵ�ʵ�ѹֵ
  * @param :
  *         @pReadBuffer����ѹֵ���ص�ַ
  * @note  :��
  * @retval:��
  */
void ASxx_read_voltage( uint8_t *pReadBuffer )
{
	uint8_t Read_Cmd[ 3 ] = { 0xC5, 0xC5, 0xC5 };

	drv_uart_tx_bytes( Read_Cmd, 3 );
	drv_uart_rx_bytes( pReadBuffer );
}

/**
  * @brief :ASxxģ�鸴λ
  * @param :��
  * @note  :��
  * @retval:��
  */
void ASxx_reset( void )
{
	uint8_t Read_Cmd[ 3 ] = { 0xC4, 0xC4, 0xC4 };

	drv_uart_tx_bytes( Read_Cmd, 3 );
}

/**
  * @brief :ASxxģ�鷢�����ݣ�����ģʽ��
  * @param :
  *        @Addr_H����ַ��λ
  *        @Addr_L����ַ��λ
  *        @Channel���ŵ�
  *        @pTxBuff���������ݵ�ַ
  *        @Length���������ݸ���
  * @note  :����ģʽ ���ݸ�����29��
  * @retval:��
  */
void ASxx_tx_packet( uint8_t Addr_H, uint8_t Addr_L, uint8_t Channel, uint8_t *pTxBuff, uint8_t Length )
{
	uint8_t Header[ 3 ] = { 0 };
	
	Header[ 0 ] = Addr_H;
	Header[ 1 ] = Addr_L;
	Header[ 2 ] = Channel;
	
	drv_uart_tx_bytes( Header, 3 );
	//��������
	drv_uart_tx_bytes( pTxBuff, Length );
}

/**
  * @brief :ASxxģ��������ݣ�����ģʽ��
  * @param :��
  * @note  :����ģʽ ���ݸ�����29��
  * @retval:��
  */
uint8_t ASxx_rx_packet( uint8_t *pRxBuff )
{
	uint8_t Length = 0;
	
	Length = drv_uart_rx_bytes( pRxBuff );
	
	return Length;
}


