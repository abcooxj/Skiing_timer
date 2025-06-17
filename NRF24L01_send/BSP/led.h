#ifndef __LED_H
#define __LED_H

#include "main.h"

#define Buzzer_On        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
#define Buzzer_Off       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

void LED_Disp(uint8_t dsLED);
void LED_Chg(uint8_t num, uint8_t sta);

#endif
