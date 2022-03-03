#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
void GPIO_Configure(){
	RCC -> APB2ENR |= 0x10;
	GPIOC -> CRH   |= 0xFF0FFFFF;
	GPIOC -> CRH   |= 0x00300000;
}

void EXT0_Configure(){
	//Cap clock cho Bit AFIO thanh ghi RCC_APB2ENR 
	RCC -> APB2ENR    |= 0x01;
	//Chonj port C 
	AFIO -> EXTICR[0] = 0x02;
	//Thanh ghi reset qua trinh dem 
	EXTI -> PR        |= 0x01;
	//Cau hinh cho Trigger theo suon xuong ! Suon len cho = 0 
	EXTI -> RTSR     |= 0x00;
	EXTI -> FTSR     |= 0x01;
	//Cho thanh ghi SWIER
	EXTI -> SWIER     = 0x00;
	//Cqau hinhf IMR = 1 
	EXTI -> IMR      |= 0x01;
	//EMR = 0
	EXTI -> EMR      = 0x00;
	//Cau hinh trong NVIC 
	NVIC -> ISER[0]  = 0x40;
}

void EXTI0_IRQHandler(){
	if(((EXTI -> PR) == 1)  && (EXTI -> IMR == 1)){
		EXTI -> PR   |= 0x01;
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)1^(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)));
	}
}

int main(){
	GPIO_Configure();
	EXT0_Configure();
	while(1){
	}
}
