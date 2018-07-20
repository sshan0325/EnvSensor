/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0XX_IT_H
#define __STM32F0XX_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/* Exported functions ------------------------------------------------------- */
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USART2_IRQHandler(void);
void USART1_IRQHandler(void);
void TIM14_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_IT_H */


