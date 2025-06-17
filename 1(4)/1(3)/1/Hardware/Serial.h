#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdarg.h>
#include "stm32f10x.h"                  // Device header

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array,uint16_t Length);
void Serial_SendString(char *String);
uint32_t Serial_Pow(uint32_t x,uint32_t Y);
void Serial_SendNumber(uint32_t Number,uint8_t Length);
void Serial_Printf(char *format, ...);
#endif
