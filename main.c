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
      WatchDog_Reset();                        // ��ġ�� �̺�Ʈ ���� �Լ�
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
      //RF_Key_Packet_handler();              // RF ��� ��Ŷ �ڵ鷯
      //Packet_handler();                          // �� �е� ��Ŷ �ڵ鷯
      //Key_Polling();                               // ȣ�� ��ư ���� �Լ�
  }
}





//////////////////////////////////////////////////////////////////////////////////////////////

