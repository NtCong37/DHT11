#include "stm32f10x.h"
#include "uart.h"

void GPIO_Configure(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//A9: TX
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//A10 : RX INPUTFLOASTING
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void USART_Configure(){
	USART_InitTypeDef  USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_InitStructure.USART_BaudRate           = 9600;
	USART_InitStructure.USART_Mode               = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Parity             = USART_Parity_No;
	USART_InitStructure.USART_StopBits           = USART_StopBits_1;
	USART_InitStructure.USART_WordLength         = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}

void UART1_SendChar(char c){
	USART_SendData(USART1, c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){};
}

void UART1_SendString(char *str){
	while(*str){
		UART1_SendChar(*str++);
	}
}

void UART1_Send_Int_Number(int32_t number){
	uint8_t count_element = 0;
	int32_t tmp_number = number;
	uint8_t string_number[10];
	if(number < 0){
		tmp_number = -tmp_number;
	}
	while(tmp_number){
		string_number[count_element] = (uint8_t)(tmp_number%10)+ '0';
		count_element++;
		tmp_number /= 10;
	}
	if(number < 0){
		string_number[count_element] = '-';
		count_element++;
	}
	string_number[count_element] = '\0';
	while(count_element--){
		UART1_SendChar(string_number[count_element]);
	}
}

void USART1_Send_Int_Float(int32_t number){
	uint8_t count_element = 0;
	int32_t tmp_number = number*10000;
	uint8_t string_number[10];
	if(tmp_number < 0){
		tmp_number = -tmp_number;
	}
	if(number % 10 >= 5){
		tmp_number = (tmp_number/10) + 1;
	}
	else{
		tmp_number = tmp_number / 10;
	}
	while(tmp_number){
		string_number[count_element] = (uint8_t)(tmp_number % 10) + 48;
		if(count_element == 3){
			string_number[count_element] = '.';
			count_element++;
			string_number[count_element] = (uint8_t)(tmp_number % 10) + 48;
		}
		count_element++;
		tmp_number /= 10;
	}
	if(tmp_number < 0){
		string_number[count_element] = '-';
		count_element++;
	}
	string_number[count_element] = '\0';
	while(count_element--){
		UART1_SendChar(string_number[count_element]);
	}
}
