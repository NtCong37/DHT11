#include "stm32f10x.h"
#include "dht11.h"
#include "timer.h"
#include "uart.h"

int main(void) {
		GPIO_InitTypeDef gpio;
		uint8_t hum_int, hum_dec, temp_int, temp_dec, checksum;
    //SystemInit();
		GPIO_Configure();
		USART_Configure();
		//SystemCoreClockUpdate();
    TIM_Configure();
    DHT11_Config();
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &gpio);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);

    while (1) {
        DHT11_Start();
				checksum = DHT11_Read_Data(&hum_int, &hum_dec, &temp_int, &temp_dec);
				if((hum_int + hum_dec + temp_int + temp_dec) == checksum){
					GPIO_ResetBits(GPIOC, GPIO_Pin_13);
					UART1_SendString("Do am: ");
					UART1_Send_Int_Number(hum_int);
					UART1_SendChar('.');
					if(hum_dec == 0){
						UART1_SendString("0");
					}
					else{
						UART1_Send_Int_Number(hum_dec);
					}
					UART1_SendString(", Nhiet do: ");
					UART1_Send_Int_Number(temp_int);
					UART1_SendChar('.');
					if(temp_dec == 0){
						UART1_SendString("0");
					}
					else{
						UART1_Send_Int_Number(temp_dec);
					}
					UART1_SendString("\\n");
					UART1_SendString("\\r");
				}
				else{
					UART1_SendString("Error!\r\n");
					GPIO_SetBits(GPIOC, GPIO_Pin_13);
				}
        delay_ms(2000);
    }
}
