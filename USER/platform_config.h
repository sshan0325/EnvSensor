/* Includes ------------------------------------------------------------------*/
#ifndef _PLATFORM_CONFIG_H
#define _PLATFORM_CONFIG_H
#include "stm32f0xx.h"
#include "stdio.h"
#endif 

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
           




/* Private function prototypes -----------------------------------------------*/
void TIM_Config(void);
void GPIO_Config(void);
void NVIC_Config(void);
void RCC_Configuration(void);
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void CMD(void);
void WatchDog_Init(void);
void WatchDog_Reset(void);
void SysInit(void);
char ReadCO2();
char ReadTempCmd();
char ReadTemp();
/***************************************************************END OF FILE****/
