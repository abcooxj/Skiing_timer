#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"                  // Device header
#include "stdbool.h"

struct keys
{
    uint8_t judge_sta;
    bool key_sta;
    bool short_flag;
};
extern struct keys key[4];

void Key_Init(void);
void key_serv(void);


#endif
