#include "timer.h"
#include "stm32f10x.h"

void TIM_Configure(){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseStruct.TIM_Prescaler = 71;			//Chia clock xuong
	TIM_TimeBaseStruct.TIM_Period = 0xFFFF;						//Gia tri ARR
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStruct);
	TIM_Cmd(TIM4, ENABLE);
}

void delay_us(uint16_t time){
	//TIM_SetCounter(TIM4, time);
	TIM_SetCounter(TIM4, 0);
	//TIM_Cmd(TIM4, ENABLE);
	//while(TIM_GetCounter(TIM4) > 0){};
	while(TIM_GetCounter(TIM4) < time){};
	//TIM_Cmd(TIM4, DISABLE);
}

void delay_ms(uint16_t time){
	while(time--){
		delay_us(1000);
	}
}
