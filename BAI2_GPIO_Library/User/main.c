#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
//Chung ta co 2 cai thai DISABLE , ENABLE
void GPIO_Configure(){
	//B1: Cap clock cho port C
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//B2: Cau hinh chan Pin 
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void delay(int time){
	for(int i = 0; i< time; i++){
		for(int j = 0; j< 0x2AFF; j++);
	}
}
/// Chu y:Led PC13 chung ta tat led: SetBit . Bat Led ResetBit 
//Cac led chan con lai: SetBit la Bat led . ResetBits(TatLed)
int main(){
	GPIO_Configure();
	while(1){
		GPIO_SetBits(GPIOC, GPIO_Pin_13);//tat led truoc 
		delay(10);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);//bat 
		delay(10);
	}
}
