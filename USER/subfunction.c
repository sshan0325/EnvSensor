/* Includes ------------------------------------------------------------------*/
#include "subfunction.h"
#include "stm32f0xx_tim.h"
#include "platform_config.h"
#include "usart.h"

/* Private variables ---------------------------------------------------------*/
unsigned char                   Key_Polling_Count=0;
unsigned char                   Key_State=KEY_RELEASED;
unsigned char                   KeyActiveState=KEY_INACTIVE;
static __IO uint32_t               TimingDelay;
extern unsigned char        U2_Tx_Buffer[128];
extern unsigned char U2_Rx_DataPosition;

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

///////////////////////////////////////////////////////////////////////////
/******************** 체크섬 만드는 함수 *******************/
//////////////////////////////////////////////////////////////////////////
unsigned char Make_Checksum(void)                       //  
{
      unsigned char Checksum = 0x02;
      for(unsigned int i = 1 ; i< (Tx_LENGTH - 1) ; i++)
      {
         Checksum ^= U2_Tx_Buffer[i];
         Checksum ++;
      }
      return Checksum;
}
//////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
/******************** 체크섬 검사 함수 *******************/
//////////////////////////////////////////////////////////////////////////
unsigned char Check_Checksum(void)                      // 
{
      unsigned char Checksum = 0x02;
      unsigned char Rx_Length = 0;
      unsigned int     TempDataPosition;
      TempDataPosition= U2_Rx_DataPosition+2;
      if (TempDataPosition > 255)             TempDataPosition-=256;
      Rx_Length = U2_Rx_Buffer[TempDataPosition];
      
      for(unsigned char i = 1 ; i< (Rx_Length -1) ; i++)
      {        
        TempDataPosition = U2_Rx_DataPosition+i;
        if (TempDataPosition > 255)             TempDataPosition-=256;
        Checksum ^= U2_Rx_Buffer[TempDataPosition];
        Checksum ++;
      }
      return Checksum;
}
//////////////////////////////////////////////////////////////////////////