#ifndef __OLED_H
#define __OLED_H

#include "main.h"

#define Hardware_IIC_No hi2c1 /*ѡ���Լ�ʹ�õ�IIC����*/


void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);//��ʾ�ַ�
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);//�ַ���
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//����
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);//����
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//16������
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);//��������
void OLED_ShowChinese(uint8_t Line, uint8_t Column, uint8_t CHN);
void OLED_ShowPicture(uint8_t Pic);//����Ļ��ʾ��Ƭ
void OLED_FastShowPicture(uint8_t Pic);
void OLED_FastShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_FastShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_FastShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void Refresh(void);
void DMA_Refresh(void);
void TeamName(void);
uint32_t OLED_Pow(uint32_t X, uint32_t Y);

uint32_t oled_pow(uint8_t m,uint8_t n);
void OLED_Showdecimal(uint8_t x,uint8_t y,float num,uint8_t z_len,uint8_t f_len,uint8_t size2);


#endif
