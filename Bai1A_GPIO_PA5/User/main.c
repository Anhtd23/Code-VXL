#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
void GPIO_Configure(){
	RCC -> APB2ENR    |=  0x00000004;
	GPIOA -> CRL      |=  0xFF0FFFFF;
	GPIOA -> CRL      |=  0x00300000;
}
void delay(int time){
	for (int i = 0; i < time; i++){
		for (int j = 0; j < 0x2AFF; j++);
	}
}
int main(){
	while(1){
		GPIO_Configure();
		
		GPIOA -> ODR  |= 0x20;
		delay(10);
		
		GPIOA ->ODR   &=~(0x20);
		delay(10);
	}
}