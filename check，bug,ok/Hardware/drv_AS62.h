#ifndef __DRV_AS62_H__
#define __DRV_AS62_H__


#include "drv_uart.h"


typedef enum 
{
	ASxx_Write_OK = 0,		//写入成功
	ASxx_Write_ERROR		//写入失败
}ASxxWriteStatusType;



ASxxWriteStatusType ASxx_param_init( void );
void ASxx_read_param( uint8_t *pReadBuffer );
void ASxx_read_version( uint8_t *pReadBuffer );
void ASxx_read_voltage( uint8_t *pReadBuffer );
void ASxx_reset( void );
void ASxx_tx_packet( uint8_t Addr_H, uint8_t Addr_L, uint8_t Channel, uint8_t *pTxBuff, uint8_t Length );
uint8_t ASxx_rx_packet( uint8_t *pRxBuff );

//void ASxx_rx_actions(void);

#endif
