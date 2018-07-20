/* Includes ---------------------------------------------------------------*/
#include "platform_config.h"
#include "subfunction.h"
#include "EnvSensor.h"

//////////////////////////////////////////////////////////////////////////////////////////////
/***************************** Main Function *********************************/
//////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{  
  int temp=0;
  
  SysInit();
 

  while (1)
  {
      WatchDog_Reset();                        // 왓치독 이베트 셋팅 함수
      temp++;

      if (temp>200000)
      {
        temp=0;
        
        ReadTempCmd();
        ReadCO2();
        ReadTemp();
      }       
  }
}





//////////////////////////////////////////////////////////////////////////////////////////////

