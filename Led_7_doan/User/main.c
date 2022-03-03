#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

int led7Seg[] ={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

void GPIO_Led7SegConfigure(){
	//cap clock port C
	RCC -> APB2ENR |= 0x10;
	//Cau hinh cho chan 
	GPIOC -> CRL   |= 0xF0000000;  //do chi tu chan 0-6 duoc noi
	//Cau hinh toc do speed , cau hinh mode output 
	GPIOC -> CRL   |= 0x03333333;
}
void delay(int time){
	for(int i = 0; i< time ; i++){
		for(int j = 0; j< 0x2AFF; j++);//1 ms
	}
}
int main(){
	GPIO_Led7SegConfigure();
	while(1){
		for(int i = 0; i < 10; i++){
			GPIOC -> ODR  = led7Seg[i];
			delay(10);
		}
	}
}