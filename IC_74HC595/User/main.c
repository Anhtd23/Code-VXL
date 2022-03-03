#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "math.h"
#define SCK GPIO_Pin_0 //khai báo chân SDI là Pin0
#define RCK GPIO_Pin_1 //khai báo chân SCK là Pin1
#define SDI GPIO_Pin_2 //khai báo chân RCK là Pin2
GPIO_InitTypeDef GPIO_InitStructure; //tao Struct
void GPIO_Configure(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Cap clock cho PortA
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // che do Output
	GPIO_InitStructure.GPIO_Pin   = SDI | SCK | RCK;  //PIN
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // toc do
	GPIO_Init(GPIOA, &GPIO_InitStructure); //luu lai cac cau hinh
}

int output   = 0x00; //kq
int phep_or  = 0x01; //phep va
int phep_end = 0x01; // phep end

void delay (int time){
	for (int i = 0; i < time; i++){
		for (int j = 0; j < 0x2AFF; j++);
	}
}

// ham shiftout truyen nhan du lieu
void shiftout (int value){
	//duyet 8 LED
	for (int i = 0; i < 8; i++){
		if ((value & 0x80) == 0x80){ //Neu & 0x80 = 0x80 tuc la den LED o vi tri dau
			GPIO_SetBits(GPIOA, SDI); //dua SDI lên cao
		}
		else GPIO_ResetBits(GPIOA, SDI); // kéo SDI xuong
		delay(1);
		GPIO_SetBits(GPIOA, SCK); //Cap clock
		delay(1);
		GPIO_ResetBits(GPIOA, SCK);
		value <<=1; //moi lan lap dich di 1 bit
	}
}

//ham bat led
void setLed(int led, int state){
		if (state == 1) output |= (1 << led); //neu muon sang led o vi tri led thi dich led di 1
		else output &=~ (1 << led); // neu khong thi lay dao
		shiftout(output); //dua du lieu vao shifftout
		delay(1);
		GPIO_SetBits(GPIOA, RCK); //chot xung clock
		delay(1);
		GPIO_ResetBits(GPIOA, RCK);
}

//Ham tao hieu ung canh buom
void canh_buom(){
	for (int i = 3; i >= 0; i--){// duyet tu led 3 ve led 0
		for (int j = 4; j <= 7; j++){ //duyet tu led 4 ve led 7
			if ((i + j) == 7){ //vi tri i + j = 7 thì bat led
				setLed(i,1);
				setLed(j,1);
				delay(20);
			}
		}
	}
	for (int i = 3; i >= 0; i--){
		for (int j = 4; j <= 7; j++){
			if ((i + j) == 7){
				setLed(i,0);
				setLed(j,0);
				delay(20);
			}
		}
	}
}

// Ham tao hieu ung Snake
void snake(){
	int led = 1; //vi tri led dau tien
	while (led < 8){
		setLed(7,1); //bat led con moi
		for (int i = 0; i < 8; i++){ //duyet 8 led
			for (int j = i-led; j <= i; j++){
				setLed(j,1); // bat led vi tri i-led
				delay(20);
			}
			setLed(i-led,0); //tat led i-led
		}
		for (int i = 8 - led; i < 8; i++){
			setLed(i,0);
			delay(20);
		}
		delay(20);
		led++; //tang bien chay
	}
}

int main(){
	GPIO_Configure();
	while (1){
		int k = 2, m = 2; //so lan chay con buomm va snake
		while (k--){
			canh_buom();
		}
		while (m--){
			snake();
		}
	}
}
		
		