

/**
  *****************************************************************************
  * @project stepper control using a4998 microstepping driver with DMA usart
  * @author  Kartik Madhira <kartikmadhira1@gmail.com>
  * @date    26th Nov 2016
  * @brief
  */

// ----------------------------------------------------------------------------
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"
#include <stdio.h>

//defining the ports and pins
#define CIRCUM		6.28				//radius of the pulley
#define USART_TX  	GPIO_Pin_9
#define USART_RX  	GPIO_Pin_10

#define GPIO_BLINK  GPIO_Pin_13
GPIO_InitTypeDef	 gpio;
USART_InitTypeDef	 usart;
DMA_InitTypeDef		 dma;
int rec_data();

//timer function taken from example.
static void
Delay(__IO uint32_t nTime);
static void
TimingDelay_Decrement(void);
void
SysTick_Handler(void);
int i, steps;
unsigned int count;
char k[3];
static uint16_t a;
uint32_t  buffer = 0x0000;
// ----------------------------------------------------------------------------
int main ()
{ /*
	//setting up the pins for the control
	gpio.GPIO_Pin=(1<<MS1 | 1<<MS2 | 1<<MS3 | 1<<DIR);
	gpio.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio.GPIO_Speed=GPIO_Speed_10MHz;
	//sTince gpio is a struct, it is passed by reference.
	GPIO_Init(GPIOA, &gpio); */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//setting USART Tx and Rx pins
	gpio.GPIO_Pin=(USART_TX);
	gpio.GPIO_Mode=GPIO_Mode_AF_PP;
	gpio.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin=USART_RX;
	gpio.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);
	//now the question is that do i intialize the USART individually or should I
	//do that via a DMA- the answer is that USART is my peripeheral and DMA is the mode
	//through which i want to access my data blocks
	//instead of getting an integer value from DMA array
	usart.USART_Mode=USART_Mode_Rx | USART_Mode_Tx ;
	usart.USART_BaudRate=9600;
	usart.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usart.USART_StopBits=USART_StopBits_1;
	usart.USART_Parity=USART_Parity_No;
	usart.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1, &usart);
	USART_Cmd(USART1,ENABLE);
	//enabling the clock for DMA,
		/*setting the USART input data register as the base address and disabling the
		the mem location increment since same location is to be used to transfer data.
		DMA.*/
	//iterating through each count to get the data block in array and converting to integer
	//the k buffer will contain the three inputs from a bash script on the host pc
	//sending values using the pySerial library on python.
	/*
	 * The three inputs are mainly the distance to be travelled by the stepper's pulley,
	 * the step size of the stepper and direction
	 */
	for(i=0;i<3;i++){
		USART_Init(USART1, &usart);
		USART_Cmd(USART1,ENABLE);
		rec_data();
		k[i]=buffer;
	}
	//putting a switch case to get the values
	switch(k[2]){
	case '1':
		a=0x00;//this will be the for ms1, ms2, ms3=0;
		//now given the distance, what will be the number of steps to travel
		steps=k[1]/CIRCUM;
		break;
	case '2':
		a=0x08;
		steps=k[1]*2/CIRCUM;
		break;
	case '4':
		a=0x10;
		steps=k[1]*4/CIRCUM;
		break;
	case '8':
		a=0x18;
		steps=k[1]*8/CIRCUM;
		break;
	case '16':
		a=0x38;
		steps=k[1]*16/CIRCUM;
		break;
	}
//since a pulse has to be given for every step,
	set_bits();

/*	char k=buffer;
	if(k=='1')
	{	GPIO_InitTypeDef gpio;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

		gpio.GPIO_Pin=GPIO_Pin_13;
		gpio.GPIO_Mode=GPIO_Mode_Out_PP;
		gpio.GPIO_Speed=GPIO_Speed_50MHz;
		//sTince gpio is a struct, it is passed by reference.
		GPIO_Init(GPIOC, &gpio);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	}
	*/


}

//subroutine to get the recieved data

int rec_data(){
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	dma.DMA_PeripheralBaseAddr=(&(USART1->DR));
	dma.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	//essentially, the USART uses 8 bit serial transfer
	dma.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	dma.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	//we are doing periph->DMA data block transfer, so disabling M2M
	dma.DMA_M2M=DMA_M2M_Disable;
	//enabling circular buffer, as it it meant for continuous data flow
	dma.DMA_Mode=DMA_Mode_Normal;
	//I dont know what this means lol, can be the iterations for the buffer
	dma.DMA_BufferSize=1;
	dma.DMA_Priority=DMA_Priority_VeryHigh;
	//recieving the data in memory location pointing to the buffer.
	//buffer=recieved data
	dma.DMA_MemoryBaseAddr=&buffer;
	dma.DMA_MemoryInc=DMA_MemoryInc_Enable;
	//the peripheral is the source of the data block transfer
	dma.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_Init(DMA1_Channel5, &dma);
	/*now that all the properties are assigned and the DMA1 channel5 assigned,
	we now start the DMA transfer and wait for the DMA flag to reset.
	*/
	DMA_Cmd(DMA1_Channel5,ENABLE);
	 /*enabling the Rx request for DMA*/
	//since the DMA's is now enabled, we poll the transfer complete bit
	while((DMA_GetFlagStatus(DMA1_FLAG_TC5)==RESET));
	//disable the DMA
	DMA_ClearFlag(DMA1_FLAG_TC5);
	DMA_Cmd(DMA1_Channel5,DISABLE);
	//disabling the UART also
	USART_DMACmd(USART1,USART_DMAReq_Rx,DISABLE);
	USART_Cmd(USART1,DISABLE);
	USART_DeInit(USART1);
	return buffer;
}


void set_bits()
{
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	gpio.GPIO_Pin=GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 ;
	gpio.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio);
	GPIOB->ODR&=0;
	GPIOB->ODR|=a;

}

static __IO uint32_t uwTimingDelay;

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in SysTick ticks.
 * @retval None
 */
void
Delay(__IO uint32_t nTime)
{
  uwTimingDelay = nTime;

  while (uwTimingDelay != 0)
    ;
}

void
TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
    {
      uwTimingDelay--;
    }
}

void
SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

