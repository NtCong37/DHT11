#include "dht11.h"
#include "timer.h"

void DHT11_Config(void){
	  GPIO_InitTypeDef gpio;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		gpio.GPIO_Mode = GPIO_Mode_Out_OD;
		gpio.GPIO_Pin = GPIO_Pin_12;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &gpio);
}

void DHT11_Start(void){
		GPIO_InitTypeDef gpio;
		gpio.GPIO_Mode = GPIO_Mode_Out_OD;
		gpio.GPIO_Pin = GPIO_Pin_12;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &gpio);
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
		delay_ms(20);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		delay_us(30);
		gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB, &gpio);
}

uint8_t DHT11_ReadByte(void){
    uint8_t i;
		uint8_t byte = 0;
    for (i = 0; i < 8; i++){
			while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0){};
			TIM_SetCounter(TIM4, 0);
			while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1){};
			if(TIM_GetCounter(TIM4) > 45){
				byte = (byte << 1) | 1;
			}
			else{
				byte = (byte << 1);
			}
    }
    return byte;
}

uint8_t DHT11_Read_Data(uint8_t* hum_int, uint8_t* hum_dec, uint8_t* temp_int, uint8_t* temp_dec){
    
		uint8_t byte[5];
		uint8_t i;
		uint32_t timeout = 0;
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1){
			delay_us(1);
			timeout++;
			if(timeout > 100){
				return 0;
			}
		}
		timeout = 0;
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0){
			delay_us(1);
			timeout++;
			if(timeout > 100){
				return 0;
			}
		}
		timeout = 0;
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1){
			delay_us(1);
			timeout++;
			if(timeout > 100){
				return 0;
			}
		}
		for(i = 0; i < 5; i++){
			byte[i] = DHT11_ReadByte();
		}
		*hum_int = byte[0];
		*hum_dec = byte[1];
		*temp_int = byte[2];
		*temp_dec = byte[3];
		
		return byte[4];
}
