#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

void GPIO_Configure(){
	RCC -> APB2ENR |= 0x10;
	GPIOC -> CRL   |= 0x00000000;
	GPIOC -> CRL   |= 0x33333333;
	GPIOC -> CRH 	 |= 0x00000000;
	GPIOC -> CRH 	 |= 0x33333333;
}

void GPIO_ButtonConfigure(){
	RCC -> APB2ENR |= 0x08;
	GPIOB -> CRL |= 0xFFFFF000;
	GPIOB -> CRL |= 0x00000888;
} 

uint32_t lastbut = 0x00, nowbut = 0x00, but =0x00;
int checkbut(){
	nowbut = GPIOB -> IDR & 0x07;
		if(nowbut!=lastbut && nowbut!= 0x00){
			but = nowbut;
			return 1;
		}
		lastbut = nowbut;
		return 0;
}

void delay (int time ){
	for (int i = 0; i < time; i++){
		for (int j = 0 ; j < 0x2AFF; j++);
	}
}

void canhbuom(){
	GPIOC -> ODR |= 0xFFFF;
	delay(10);
	for(int i = 0; i <= 8; i++){
		GPIOC -> ODR &= ~((1<<8)>>i);
		GPIOC -> ODR &= ~((1<<7)<<i);
		if (checkbut()){
			break;
		}
		delay(10);
	}
}

void giotnuoc(){
	GPIOC -> ODR |= 0xFFFF;
	delay(10);
	for(int i = 15; i>= 0; i--){
		for(int j = 0; j <= i; j++){
			GPIOC -> ODR |= (1 << (j - 1));
			GPIOC -> ODR &= ~(1 << j);
			if (checkbut()){
				break;
			}
			delay(10);
		}
	}
}
void sangdan(){
	GPIOC -> ODR |= 0xFFFF;
	delay(10);
	for(int i = 0; i <= 15; i++){
		GPIOC -> ODR &= ~(1<<i);
		if (checkbut()){
			break;
		}
		delay(10);
	}
}

void EXT0_Configure(){
	RCC -> APB2ENR    |= 0x01;
	//Chonj port B0 
	AFIO -> EXTICR[0] = 0x01;
	EXTI -> PR        |= 0x01;
	EXTI -> RTSR     |= 0x00;
	EXTI -> FTSR     |= 0x01;
	EXTI -> SWIER     = 0x00;
	EXTI -> IMR      |= 0x01;
	EXTI -> EMR      = 0x00;
	//Cau hinh trong NVIC 
	NVIC -> ISER[0]  = 0x40;
}

void EXTI0_IRQHandler(){
	if(((EXTI -> PR) == 1)  && (EXTI -> IMR == 1)){
		EXTI -> PR   |= 0x01;
		GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)1^(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_0)));
	}
}

void EXT1_Configure(){
	RCC -> APB2ENR    |= 0x01;
	//Chonj port B1
	AFIO -> EXTICR[0] = 0x10;
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
	NVIC -> ISER[0]  = 0x80;
}

void EXTI1_IRQHandler(){
	if(((EXTI -> PR) == 1)  && (EXTI -> IMR == 1)){
		EXTI -> PR   |= 0x01;
		GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)1^(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_1)));
	}
}

void EXT2_Configure(){
	RCC -> APB2ENR    |= 0x01;
	//Chon port B2
	AFIO -> EXTICR[0] = 0x100;
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
	NVIC -> ISER[0]  = 0x100;
}

void EXTI2_IRQHandler(){
	if(((EXTI -> PR) == 1)  && (EXTI -> IMR == 1)){
		EXTI -> PR   |= 0x01;
		GPIO_WriteBit(GPIOB, GPIO_Pin_2, (BitAction)1^(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_2)));
	}
}

int main (){
	GPIO_Configure();
	GPIO_ButtonConfigure();
	EXT0_Configure();
	EXT1_Configure();
	EXT2_Configure();
	while (1){
		GPIOC -> ODR |= 0xFFFF;
		but = GPIOB -> IDR & 0x07;
		switch(but){
			case 0x01:{
				canhbuom();
				break;
				}
			case 0x02:{
				sangdan();
				break;
			}
			case 0x04:{
				giotnuoc();
				break;
			}
			default:{
				break;
			}
		}
	}
}
			
		
	
	





	