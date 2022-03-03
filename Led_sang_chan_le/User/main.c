#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
void GPIO_Configure(){
	//mac tu PA0 toi PA7
  //B1: Cap clock Cho port A
	RCC -> APB2ENR  |= 0x00000004;
	//B2: khai bao chan PC13 
	//CRL và CRH : 0 - 7 thanh CRL kiem soan . 8 - 15 thanh CRH kiem soat
	GPIOA -> CRL    |= 0x00000000; // sang tat
	//B3: Cau hinh cho Toc do mode output
	GPIOA -> CRL    |= 0x33333333;
}
//Tuong doi 
void delay(int time){
	for(int i = 0; i< time; i++){
		for(int j = 0; j< 0x2AFF; j++);//1ms
	}
} 

int main(){
	GPIO_Configure();
	GPIOA -> ODR |= 0xFF;
	while(1){
		GPIOA -> ODR |= 0xAA;
		delay(10);
		GPIOA -> ODR &=~(0xAA);
		GPIOA -> ODR  |= 0x55;
		delay(10);
		GPIOA -> ODR  &=~(0x55);
	}
}