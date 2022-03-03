// Cho sang tu PA0 toi PA7 su dung Button
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
void GPIO_Configure(){
	RCC -> APB2ENR |= 0x00000004;
	GPIOA -> CRL   |= 0x00000000;
	GPIOA -> CRL   |= 0x33333333;
}
void delay(int time){
	for (int i = 0; i< time; i++){
		for (int j = 0; j < 0x2AFF; j++);
	}
}
// Su dung Button PB0
void GPIO_ButtonConfigure(){
	RCC -> APB2ENR  |= 0x00000008;
	GPIOB -> CRL    |= 0xFFFFFFF0;
	GPIOB -> CRL    |= 0x00000008;
	GPIOB ->ODR     &=~(0x01);
}

void chan_le(){
	GPIOA -> ODR  |= 0xAA;
	delay(10);
	GPIOA -> ODR  &=~(0xAA);
	GPIOA -> ODR  |= 0x55;
	delay(10);
	GPIOA -> ODR  &=~ (0x55);
}

int main(){
	GPIO_Configure();
	GPIO_ButtonConfigure();
	GPIOA-> ODR  |= 0xFF;
	while (1){
		if((GPIOB -> IDR & 0x01) != 0x01){
		chan_le();
		}
		else GPIOA -> ODR |= 0xFFFF;
	}
}