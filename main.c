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
      WatchDog_Reset();           // ��ġ�� �̺�Ʈ ���� �Լ�

      if (EnvSensingFlag==SET && Rx_Compli_Flag==SET)              // �� 1�ʸ��� ���� I/F ����
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

