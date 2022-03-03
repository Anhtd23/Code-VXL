#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
void GPIO_Configure(){
	RCC -> APB2ENR |= 0x10;
	GPIOC -> CRH   |= 0xFF0FFFFF;
	GPIOC -> CRH   |= 0x00300000;
}

void TIM3_Configure(){
	//cap clock Cho TIM3
	RCC -> APB1ENR |= 0x02;
	/*LOAD gia tri thanh ghi ban dau*/
	TIM3 -> ARR     = 0xFFFF;//cau hinh cho no o gia tri nay truoc
	/*bo chia tan so*/
	TIM3 -> PSC     = 72 - 1;
	/*cau hinh cho bien dem len */
	TIM3 -> CR1    |= 0x01;
	//Cau hinh cho su kien reload UG
	TIM3 -> EGR    |= 0x01;
}

void TIM2_Configure(){
	//cap clock Cho TIM3
	RCC -> APB1ENR |= 0x01;
	/*LOAD gia tri thanh ghi ban dau*/
	TIM2 -> ARR     = 0xFFFF;//cau hinh cho no o gia tri nay truoc
	/*bo chia tan so*/
	TIM2 -> PSC     = 72 - 1;
	/*cau hinh cho bien dem len */
	TIM2 -> CR1    |= 0x01;
	//Cau hinh cho su kien reload UG
	TIM2 -> EGR    |= 0x01;
}


void delay(int time){
	while(time){
		TIM2 -> CNT = 0;
		while(TIM2 -> CNT < 1000){
		}
		time--;
	}
}
int main(){
	TIM2_Configure();
	GPIO_Configure();
	while(1){
		GPIOC -> ODR  |= 0x2000;
		delay(10);
		GPIOC -> ODR &=~(0x2000);
		delay(10);
	}
}
