/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "stdio.h"
#include "usart.h"
#include "platform_config.h"
#include "subfunction.h"
#include "EnvSensor.h"


/* Private define ------------------------------------------------------------*/
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)


PUTCHAR_PROTOTYPE
{
  USART_SendData(USART1, (uint8_t) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)    {}
  return ch;
}

/* Private variables ---------------------------------------------------------*/
/************************ ENV. SENSING ****************************/
unsigned int EnvSensingFlag = RESET;

/*************************** USART 1 ******************************/
uint8_t aRxBuffer[BUFFERSIZE];
unsigned char Rx_Compli_Flag = RESET;
unsigned char Rx_SensorData_Count = 0 ;

/*************************** USART 2 ******************************/
unsigned char U2_Rx_Count = 0 ;
unsigned char U2_Rx_DataSavePosition = 0;
unsigned char U2_Rx_DataPosition = 0;
unsigned char U2_Rx_Compli_Flag = RESET;
unsigned char U2_Rx_Buffer[U2_RX_BUFFER_SIZE] = {0};
extern unsigned char U2_Tx_Buffer[128] ;

/************************* Counter *******************************/
unsigned int SENSINGCOUNT = 0;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}



void TIM14_IRQHandler(void) //10ms
{
    if (TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET)
    {
      TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
      SENSINGCOUNT ++;
      
      if (SENSINGCOUNT>SENSINGCYCLE*100)
      {
        EnvSensingFlag=SET;
      }
    }
}

void USART2_IRQHandler(void)     
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        U2_Rx_Buffer[U2_Rx_DataSavePosition] = USART_ReceiveData(USART2);  
        U2_Rx_Count++;
        U2_Rx_DataSavePosition++;
        if (U2_Rx_DataSavePosition-U2_Rx_DataPosition > U2_Rx_Count)
        {
            U2_Rx_DataSavePosition=0;
            U2_Rx_DataPosition=0;
            U2_Rx_Count=0;
            #ifdef Consol_LOG   
            printf ("\r\n[System                ] U2 Beffer Error");     
            #endif
        }
    }
      
    if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
    {

    } // end of TX if
} 


void USART1_IRQHandler(void)     
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {    
    aRxBuffer[Rx_SensorData_Count] = USART_ReceiveData(USART1);	
    Rx_SensorData_Count++; 
    if (Rx_SensorData_Count>=18)
    {
      Rx_Compli_Flag = SET ; 
    }      
  }

  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {
  }
}


