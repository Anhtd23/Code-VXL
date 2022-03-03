#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
void GPIO_Configure(){ 
  //B1: Cap clock Cho port A
	RCC -> APB2ENR  |= 0x00000004;
	//B2: khai bao chan PC13 
	//CRL và CRH : 0 - 7 thanh CRL kiem soan . 8 - 15 thanh CRH kiem soat
	GPIOA -> CRL    |= 0x00000000;
	//B3: Cau hinh cho Toc do mode output
	GPIOA -> CRL    |= 0x33333333;
}
//Tuong doi 
void delay(int time){
	for(int i = 0; i< time; i++){
		for(int j = 0; j< 0x2AFF; j++);//1ms
	}
}
void GPIO_ButtonConfigure(){
	//B1 : cap clock cho port B 
	RCC -> APB2ENR  |= 0x00000008;
	//Khai bao chan sd PB0 
	GPIOB -> CRL    |= 0xFFFFFFF0;
  //Cau hinh mode va cau toc do 
  GPIOB -> CRL    |= 0x00000008;//10 : Push up . push down 
  GPIOB -> ODR    &=~(0x01);	//push down;
}
void Chan_Le(){
	GPIOA -> ODR   |= 0xAA;
	delay(10);
	GPIOA -> ODR   &=~(0xAA);
	GPIOA -> ODR   |= 0x55;
	delay(10);
	GPIOA -> ODR   &=~(0x55);
}
int mang[] ={0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00};
void Sang_dan_Duoi_Len(){
	for(int i = 0; i< 8; i++){
		GPIOA -> ODR |= mang[i];
		delay(10);
		GPIOA -> ODR &=~mang[i];
	}
}
int main(){
	GPIO_Configure();
	GPIO_ButtonConfigure();
	while(1){
		Sang_dan_Duoi_Len();
	}
}