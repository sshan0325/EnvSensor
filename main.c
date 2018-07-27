/* Includes -----------------------------------------------------------------*/
#include "subfunction.h"
#include "EnvSensor.h"

/* Private variables --------------------------------------------------------*/
extern unsigned char Rx_Compli_Flag;
extern unsigned int EnvSensingFlag;

///////////////////////////////////////////////////////////////////////////////
/***************************** Main Function *********************************/
///////////////////////////////////////////////////////////////////////////////
int main(void)
{  
  SysInit();

  while (1)
  {
      WatchDog_Reset();           // 왓치독 이베트 셋팅 함수

      if (EnvSensingFlag==SET && Rx_Compli_Flag==SET)              // 매 1초마다 센서 I/F 수행
      {
        EnvSensingFlag=RESET;
        
        ReadpParticle();
        ReadTempCmd();
        ReadCO2();
        ReadTemp();
      }       
  }
}





//////////////////////////////////////////////////////////////////////////////////////////////

