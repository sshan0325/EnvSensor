
/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"

/* Private variables ---------------------------------------------------------*/

void RCC_Configuration(void)
{
    /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */ 
  /* GPIOA, GPIOB  Clocks enable */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);
  
   /* Timer2, Timer14  Clocks enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_TIM14 | RCC_APB1Periph_TIM3 , ENABLE ) ;
  
  /* Enable SYSCFG clock, RS 485 to UART  */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 , ENABLE);
  
  /* enable APB1 peripheral clock for I2C1 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  
  /* enable clock for SCL and SDA pins  */
  //RCC_AHB1PeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);  
  
  
}


void GPIO_Config(void)
{
  GPIO_InitTypeDef                      GPIO_InitStructure;
  I2C_InitTypeDef I2C_InitStruct;
  // LED
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  // BUTTON
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP  ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // BUZZER 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP  ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_1);
  
 /* Configure pins as AF pushpull (USART2) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  /* Connect pin to Periph */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);    
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1); 
  
   
  /* USART2 Direction pin : PB 0 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
  
  /* Configure pins as AF pushpull (USART1) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  /* Connect pin to Periph */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);    
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
  
  /* Configure pins as AF pushpull (I2C) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;                        // we are going to use PB6 and PB7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		  // set pins to alternate function
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  // set GPIO speed
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;		  // set output to open drain --> the line has to be only pulled low, not driven high
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		  // enable pull up resistors
  GPIO_Init(GPIOB, &GPIO_InitStructure);			          // init GPIOB
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                        // we are going to use PB6 and PB7
  GPIO_Init(GPIOB, &GPIO_InitStructure);			          // init GPIOB
  // Connect I2C2 pins to AF  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_1);	// SCL
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_1);      // SDA

  I2C_Cmd(I2C1, DISABLE);
  I2C_SoftwareResetCmd(I2C1, ENABLE);
  I2C_SoftwareResetCmd(I2C1, DISABLE);
        
  // configure I2C1
  I2C_InitStruct.I2C_Timing = 0xB0420F13; //0x10805E89;
  I2C_InitStruct.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  I2C_InitStruct.I2C_DigitalFilter = 0;  
  I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStruct.I2C_OwnAddress1 = 0xAB;
  I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_Init(I2C1, &I2C_InitStruct);
  I2C_Cmd(I2C1, ENABLE);
}

//////////////////////////////////// TIMMER//////////////////////////////////////////////////
void TIM_Config(void)
{
  TIM_TimeBaseInitTypeDef         TIM_TimeBaseStructure;
  
  /* Timer 14 Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 480;     // 48000000 / 480 =100000 Hz = 10us
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 1000; //   10 ms == 1000us
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
  
    /* TIM Interrupts enable */
  TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);

  /* TIM14 enable counter */
  TIM_Cmd(TIM14, ENABLE);
}

void NVIC_Config(void)
{
  NVIC_InitTypeDef                      NVIC_InitStructure;
  
  //Enable the TIM14 gloabal Interrupt 
  NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 2 ;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable the USART2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

