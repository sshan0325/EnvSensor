/* Includes -----------------------------------------------------------------*/
#include "subfunction.h"
#include "EnvSensor.h"

/* Private variables --------------------------------------------------------*/
extern unsigned int SENSINGCYCLE;  //Every 10ms, SENSINGCYCLE Value is Increased

///////////////////////////////////////////////////////////////////////////////
/***************************** Main Function *********************************/
///////////////////////////////////////////////////////////////////////////////
int main(void)
{  
  SysInit();

  while (1)
  {
      WatchDog_Reset();           // 왓치독 이베트 셋팅 함수

      if (SENSINGCYCLE > 100)              // 매 1초마다 센서 I/F 수행
      {
        SENSINGCYCLE=0;
        
        ReadTempCmd();
        ReadCO2();
        ReadTemp();
      }       
  }
}





//////////////////////////////////////////////////////////////////////////////////////////////

