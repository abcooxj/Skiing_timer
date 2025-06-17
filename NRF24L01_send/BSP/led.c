#include "led.h"

uint8_t led_sta = 0x00;

void LED_Disp(uint8_t dsLED)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, dsLED << 8, GPIO_PIN_RESET);
}

void LED_Chg(uint8_t num, uint8_t sta)
{
    uint8_t pos = 0x01 << (num - 1);
    led_sta = (led_sta & (~pos)) | (pos * sta);
    LED_Disp(led_sta);
}
