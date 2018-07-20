/* Includes ------------------------------------------------------------------*/
#include "subfunction.h"
#include "stm32f0xx_tim.h"
#include "platform_config.h"
#include "usart.h"
#include <stdio.h>

/* Global variables ---------------------------------------------------------*/
static __IO uint32_t               TimingDelay;


/*************************** Flag ********************************/



void SysInit(void)
{
  RCC_Configuration();
  GPIO_Config();
  NVIC_Config();
  USART_Configuration();
  TIM_Config();  
  WatchDog_Init(); 

  if (SysTick_Config(SystemCoreClock / 1000))                   while (1);

  printf ("\r\n[System                ] Power On");     
  printf ("\r\n[System                ] System Init Done.\r\n");            
}


void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}


void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
