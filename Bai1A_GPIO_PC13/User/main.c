#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
void GPIO_Configure(){ 
  //B1: Cap clock Cho port C
	RCC -> APB2ENR  |= 0x00000010;
	//B2: khai bao chan PC13 
	//CRL và CRH : 0 - 7 thanh CRL kiem soan . 8 - 15 thanh CRH kiem soat
	GPIOC -> CRH    |= 0xFF0FFFFF;
	//B3: Cau hinh cho Toc do mode output
	GPIOC -> CRH    |= 0x00300000;
}

//Tuong doi 
void delay(int time){
	for(int i = 0; i< time; i++){
		for(int j = 0; j< 0x2AFF; j++);//1ms
	}
}

//ODR 
int main(){
	GPIO_Configure();
	while(1){
		GPIOC -> ODR |= 0x2000;
		delay(10);
		GPIOC -> ODR &=~(0x2000);
		delay(10);
	}
}