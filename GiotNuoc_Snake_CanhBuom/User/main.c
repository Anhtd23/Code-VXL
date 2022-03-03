#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stdlib.h"
// Su dung Port C tu chan 0 toi 15
void GPIO_Configure(){
	RCC   -> APB2ENR  |= 0x10;
	GPIOC -> CRL      |= 0x00000000;
	GPIOC -> CRL      |= 0x33333333;
	GPIOC -> CRH      |= 0x00000000;
	GPIOC -> CRH      |= 0x33333333;
}

//Cau hinh cho button B0, B1, B2
void GPIO_ButtonConfigure(){
	RCC    -> APB2ENR |= 0x08;
	GPIOB  -> CRL   |= 0xFFFFF000;
	GPIOB  -> CRL   |= 0x00000888;
}

uint32_t lastbut = 0x00, nowbut = 0x00, but = 0x00;
int checkbut(){
	nowbut = GPIOB -> IDR & 0x07;
	if (nowbut != lastbut && nowbut != 0x00){
		but = nowbut;
		return 1;
	}
	lastbut = nowbut;
	return 0;
}

void delay (int time){
	for (int i = 0; i < time; i++){
		for (int j = 0; j < 0x2AFF; j++);
	}
}

void canh_buom(){
	GPIOC -> ODR |= 0xFFFF;
	delay(10);
	for (int i = 0; i <= 8; i++){
		GPIOC -> ODR &=~ ((1 << 8) >> i);
		GPIOC -> ODR &=~ ((1 << 7) << i);
		if(checkbut()){
			break;
		}
		delay(10);
	}
}

void giot_nuoc (){
	GPIOC -> ODR |= 0xFFFF;
	delay (10);
	for (int i = 15; i >= 0; i--){
		for (int j = 0; j <= i; j++){
			GPIOC -> ODR |= (1 << (j-1));
			GPIOC -> ODR &=~ (1 << j);
			if (checkbut()){
				break;
			}
			delay(10);
		}
	}
}

void snake(){
	GPIOC -> ODR |= 0xFFFF;
	delay(10);
	int len = 3;
	while (len < 16){
		GPIOC -> ODR |= 0xFFFF;
		int victim = 0 + (int)( rand() * (15 - 0 + 1.0) / (1.0 + RAND_MAX) );
		GPIOC -> ODR &= ~(1 << victim);
		for(int i = 0; i < 16; i++){
			GPIOC -> ODR &= ~(1 << i);
			if(i == victim){ len ++;}
			GPIOC -> ODR |= ((1 << i) >> len);
			if (checkbut()){
				break;
			}
			delay(10);
		}
	}
}

int main (){
	GPIO_Configure();
	GPIO_ButtonConfigure();
	while (1){
		GPIOC -> ODR |= 0xFFFF;
		but = GPIOB -> IDR & 0x07;
		switch(but){
			case 0x01:{
				canh_buom();
				break;
				}
			case 0x02:{
				snake();
				break;
			}
			default:{
				giot_nuoc();
				break;
			}
		}
	}
}
				
			
	

