#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

void TIM_Configure(void);
void delay_us(uint16_t time);
void delay_ms(uint16_t time);

#endif
