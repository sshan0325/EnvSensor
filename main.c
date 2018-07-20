/* Includes ---------------------------------------------------------------*/
#include "platform_config.h"
#include "stdio.h"
#include "usart.h"
#include "subfunction.h"
#include "RF_KEY.h"    

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
        Delay(10);
        ReadCO2();
        Delay(10);
        ReadTemp();
      }       
      //RF_Key_Packet_handler();              // RF 모듈 패킷 핸들러
      //Packet_handler();                          // 월 패드 패킷 핸들러
      //Key_Polling();                               // 호출 버튼 감지 함수
  }
}





//////////////////////////////////////////////////////////////////////////////////////////////

