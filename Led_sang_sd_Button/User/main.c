// LED PA5 sang, ket hop Button PB0
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
void GPIO_Configure(){
  //B1: Cap clock Cho port A
	RCC -> APB2ENR  |= 0x00000004;
	//B2: khai bao chan PA5 
	//CRL và CRH : 0 - 7 thanh CRL kiem soan . 8 - 15 thanh CRH kiem soat
	GPIOA -> CRL    |= 0xFF0FFFFF;
	//B3: Cau hinh cho Toc do mode output
	GPIOA -> CRL    |= 0x00300000;
}
//Tuong doi 
void delay(int time){
	for(int i = 0; i< time; i++){
		for(int j = 0; j< 0x2AFF; j++);//1ms
	}
}

//cau hinh port B0 doc gia tri button 
void GPIO_ButtonConfigure(){
	//B1 : cap clock cho port B 
	RCC -> APB2ENR  |= 0x00000008;
	//Khai bao chan sd PB0 
	GPIOB -> CRL    |= 0xFFFFFFF0;
  //Cau hinh mode va cau toc do 
  GPIOB -> CRL    |= 0x00000008;//10 : Push up . push down 
  GPIOB -> ODR    &=~(0x01);	//push down;
}
int main(){
	GPIO_Configure();
	GPIO_ButtonConfigure();
	GPIOA -> ODR |= 0xFF;
	while(1){		
		if(GPIOB -> IDR & 0x01){
			GPIOA -> ODR |= 0x20;
		}
		else GPIOA -> ODR &=~(0x20);
	}
}