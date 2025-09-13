#ifndef __DHT11_H__
#define __DHT11_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "timer.h"

void DHT11_Config(void);
void DHT11_Start(void);
uint8_t DHT11_ReadByte(void);
uint8_t DHT11_Read_Data(uint8_t* hum_int, uint8_t* hum_dec, uint8_t* temp_int, uint8_t* temp_dec);


#endif
