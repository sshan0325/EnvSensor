#ifndef _PLATFORM_CONFIG_H
#define _PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"



/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void TIM_Config(void);
void GPIO_Config(void);
void NVIC_Config(void);
void RCC_Configuration(void);
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void WatchDog_Init(void);
void WatchDog_Reset(void);
void SysInit(void);
/***************************************************************END OF FILE****/

#endif 
