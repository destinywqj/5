#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "time.h"
#include "usart.h"
#include "pwm.h"

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif
void My_USART1_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef  NVIC_InitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	USART_InitStrue.USART_BaudRate=115200;
  USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None ;
	USART_InitStrue.USART_Mode=USART_Mode_Tx |USART_Mode_Rx ;
	USART_InitStrue.USART_Parity=USART_Parity_No;
	USART_InitStrue.USART_StopBits=USART_StopBits_1;
	USART_InitStrue.USART_WordLength=USART_WordLength_8b;
  USART_Init(USART1,&USART_InitStrue); 
	
	USART_Cmd(USART1,ENABLE);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);
	
	
}

void USART1_IRQHandler(void)
{
	u8 res;
if(USART_GetITStatus(USART1,USART_IT_RXNE))
{
 res= USART_ReceiveData(USART1);
	USART_SendData(USART1,res);
}

}
int main(void)
 {		char a = 'a';
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	My_USART1_Init(); 
	 while(1)
	 {printf("%c \r\n",a);
	 }
	 
 }



//#include "led.h"
//#include "delay.h"
//#include "sys.h"
//#include "key.h"
//#include "time.h"
//#include "usart.h"
//#include "pwm.h"
//void My_USART1_Init(void)
//{
// GPIO_InitTypeDef  GPIO_InitStrue;
//	USART_InitTypeDef USART_InitStrue;
//	NVIC_InitTypeDef  NVIC_InitStrue;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
// RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
//	
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);
//	
//	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
//	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStrue);
//	
//	USART_InitStrue.USART_BaudRate=115200;
//  USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None ;
//	USART_InitStrue.USART_Mode=USART_Mode_Tx |USART_Mode_Rx ;
//	USART_InitStrue.USART_Parity=USART_Parity_No;
//	USART_InitStrue.USART_StopBits=USART_StopBits_1;
//	USART_InitStrue.USART_WordLength=USART_WordLength_8b;
//  USART_Init(USART1,&USART_InitStrue); 
//	
//	USART_Cmd(USART1,ENABLE);
//	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//	
//	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
//	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
//	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
//	NVIC_Init(&NVIC_InitStrue);
//	
//	
//}

//void USART1_IRQHandler(void)
//{
//	u8 res;
//if(USART_GetITStatus(USART1,USART_IT_RXNE))
//{
// res= USART_ReceiveData(USART1);
//	USART_SendData(USART1,res);
//}

//}
//int main(void)
// {		
// NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	My_USART1_Init(); 
//	 while(1);
//	 
// } 
