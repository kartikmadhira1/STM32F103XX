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
GPIO_InitTypeDef gpio;
EXTI_InitTypeDef EXTI_struct;
NVIC_InitTypeDef nvic;
int main(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//setting enable A, inputs 1 & 2 configurations
gpio.GPIO_Pin=(1<<GPIO_Pin_3 | 1<<GPIO_Pin_4 | ~(1<<GPIO_Pin_5));
gpio.GPIO_Mode=GPIO_Mode_Out_PP;
gpio.GPIO_Speed=GPIO_Speed_2MHz;


RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//First updating the external interrupt lines.
//The lines enable the interrupt in all the GPIOx.9 pins.
EXTI_struct.EXTI_Line=EXTI_Line9;
//Mode are of two types- event and interrupt.
EXTI_struct.EXTI_Mode=EXTI_Mode_Interrupt;
//capturing the rising edge from the encoder ticks
EXTI_struct.EXTI_Trigger=EXTI_Trigger_Rising;
//specifing the states of pins.
EXTI_struct.EXTI_LineCmd=ENABLE;
//firing the struct
EXTI_Init(&EXTI_struct);

//enabling the gpio pin no PA8 for external interrupt and then
//connecting it to the line8 for EXTI8
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//capsulating all the values in the gpio struct
gpio.GPIO_Pin=GPIO_Pin_9 ;
//the pin PA8 has to be externally pulled low or high.
gpio.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//setting the speed on the input.
gpio.GPIO_Speed=GPIO_Speed_2MHz;

//Fusing both EXTI line 8 and pin PA8.
GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource9);

//Setting up the vector handler functions
//capsulating all the values for the interrupt controller.
nvic.NVIC_IRQChannel=EXTI9_5_IRQn;
nvic.NVIC_IRQChannelPreemptionPriority=0x00;
nvic.NVIC_IRQChannelSubPriority=0x00;
nvic.NVIC_IRQChannelCmd=ENABLE;

	}


//creating a sub-routine for the NVIC handler or the interrupt vector table.

void EXTI9_5_IRQHandler(void)
{
	//getting the status of the interrupts
	if(EXTI_GetITStatus(EXTI_Line9))
	{	 //getting the value in the data register of GPIOA
		 //and ANDING with the pin number 8
		 if((GPIOA->IDR & GPIO_Pin_9))
		 {
			 count++;
		 }
		 else
		 {
			count--;
		}
		 if (count==100)
		 	{   //if counts become 100, we need to set the PC13 led number
		 		GPIO_InitTypeDef gpio;
		 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		 		gpio.GPIO_Pin=GPIO_Pin_13;
		 		gpio.GPIO_Mode=GPIO_Mode_Out_PP;
		 		gpio.GPIO_Speed=GPIO_Speed_2MHz;
		 		//setting the pin high for the led
		 		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		 	}

		 EXTI_ClearITPendingBit(EXTI_Line9);
	}
}
