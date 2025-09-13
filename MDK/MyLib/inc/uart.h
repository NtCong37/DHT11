#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

void GPIO_Configure(void);
void USART_Configure(void);
void UART1_SendChar(char c);
void UART1_SendString(char *str);
void UART1_Send_Int_Number(int32_t number);
void USART1_Send_Int_Float(int32_t number);

#endif
