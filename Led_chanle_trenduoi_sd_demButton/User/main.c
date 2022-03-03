#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include <stdbool.h>

void GPIO_Configure(){
	//H?c GPIOI Out Thanh ghi 
  //B1: Cap clock Cho port A
	RCC -> APB2ENR  |= 0x00000004;
	//B2: khai bao chan 
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
//ODR 
//Truyen 0 thi led PA5 sang hay tat ? : Sáng ??? : 
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
void Chan_Le(){
	GPIOA -> ODR   |= 0xAA;
	delay(20);
	GPIOA -> ODR   &= 0x55;
	delay(20);
	GPIOA -> ODR   |= 0xFF;
	GPIOA -> ODR   |= 0x55;
	delay(20);
	GPIOA -> ODR   &= 0xAA;
	delay(20);
	GPIOA -> ODR   |= 0xFF;

	if((GPIOB -> IDR & 0x01) != 0x01)
		return;
}
int duoi_len[] = {0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00};//sang dan duoi len
int t_x[] = {0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x00};

void S_duoi_len(){
	for(int i = 0; i<8; i++){
		GPIOA -> ODR |= duoi_len[i];
		delay(20);
		GPIOA -> ODR   &=~duoi_len[i];
		if((GPIOB -> IDR & 0x01) != 0x01)
			return;
	}
		
}
void S_tren_xuong(){
	for(int i = 0; i<8; i++){
		GPIOA -> ODR |= t_x[i];
		delay(20);
		GPIOA -> ODR &=~t_x[i];
		if((GPIOB -> IDR & 0x01) != 0x01)
			return;
	}
		
}
bool isStop = false;
int main(){
	GPIO_Configure();
	GPIO_ButtonConfigure();
	GPIOA -> ODR |= 0xFF;
	int cnt = 0;
	while(1){
		//S_tren_xuong();
		int lc = cnt % 3;
		if(isStop){
			switch(lc){
				case 0:
					S_tren_xuong();
					break;
				case 1:
					Chan_Le();
					break;
				case 2:
					S_duoi_len();
					break;
			}
		}

		if((GPIOB -> IDR & 0x01) != 0x01){
			isStop = true;
			cnt++;
		}
		else{
				GPIOA -> ODR |= 0xFFFF;
		}
			
	}
}