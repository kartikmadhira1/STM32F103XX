/**
  *****************************************************************************
  * @project encoder_counts
  * @author  Kartik Madhira <kartikmadhira1@gmail.com>
  * @date    8 Nov 2016
  * @brief   Simple code to get 100 counts from encoder and blink PC13 LED thereafter.
  */

#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "misc.h"

/* The APB2 peripheral's clock needs to be enabled so that the GPIO are
 * input enabled
 * Nested Vector Interrupt Controller is the one that controls all the interrupts
 */
int count; //contains the count from encoder
//defining a InitStruct for external EXTI,GPIO, NVIC to capsulate all the features we need to set

GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_struct;
NVIC_InitTypeDef nvic;



void EXTI9_5_IRQHandler(void)

{ 	static int8_t   count;
	static const    int8_t states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0} ;
	static uint16_t  current_encoder_pos,enc_count;
	static uint8_t  prev_encoder_pos=0;
	//first reading the current encoder values and storing in the form of AB.
	prev_encoder_pos<<=2;
	current_encoder_pos=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)<<1| GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
	//adding the previous state also and appending it to the prev_encoder_pos;
	prev_encoder_pos|=(current_encoder_pos & 0x03);
	//now anding with 0xff and it will give one of the states given in the statetable;
	count= states[(prev_encoder_pos & 0x0f)];
	if (count==1)
	{
		enc_count++;
	}

	if (enc_count==1200)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
		GPIO_Init(GPIOC,&GPIO_InitStructure);
		//setting the pin high for the led
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	}
	EXTI_ClearITPendingBit(EXTI_Line5);  //Clear Channel B
	EXTI_ClearITPendingBit(EXTI_Line6);  //Clear Channel A
}


int main()
{
	while(1)
	{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//setting enable A, inputs 1 & 2 configurations
GPIO_InitStructure.GPIO_Pin=(GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5);
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
GPIO_Init(GPIOB,&GPIO_InitStructure);
GPIO_ResetBits(GPIOB,(GPIO_Pin_3 | GPIO_Pin_5));
GPIO_SetBits(GPIOB,GPIO_Pin_4);

//connecting it to the line8 for EXTI8
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//capsulating all the values in the gpio struct
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_5;
//the pin PA8 has to be externally pulled low or high.
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
//setting the speed on the input.
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);


GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);

//First updating the external interrupt lines.
//The lines enable the interrupt in all the GPIOx.8 pins.
EXTI_struct.EXTI_Line=EXTI_Line6|EXTI_Line5;
//Mode are of two types- event and interrupt.
EXTI_struct.EXTI_Mode=EXTI_Mode_Interrupt;
//capturing the rising edge from the encoder ticks
EXTI_struct.EXTI_Trigger=EXTI_Trigger_Rising;
//specifing the states of pins.
EXTI_struct.EXTI_LineCmd=ENABLE;
//firing the struct
EXTI_Init(&EXTI_struct);

//enabling the gpio pin no PA8 for external interrupt and then

//Fusing both EXTI line 8 and pin PA8.

//Setting up the vector handler functions
//capsulating all the values for the interrupt controller.
nvic.NVIC_IRQChannel=EXTI9_5_IRQn;
nvic.NVIC_IRQChannelPreemptionPriority=0x00;
nvic.NVIC_IRQChannelSubPriority=0x00;
nvic.NVIC_IRQChannelCmd=ENABLE;
NVIC_Init(&nvic);
	}
}
//creating a sub-routine for the NVIC handler or the interrupt vector table.



