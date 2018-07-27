/* Includes ---------------------------------------------------------------*/
#include "EnvSensor.h"

/*************************** USART 1 ******************************/
extern uint8_t aRxBuffer[BUFFERSIZE];
extern unsigned char Rx_Compli_Flag;
extern unsigned char Rx_SensorData_Count;

char ReadTemp()
{
  float         temp_val, Rhum_val;
  int           timeout;
  uint8_t       received_data[6], Datacount, Dummy1;

  // Check I2C1 State
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET)  {
     if((timeout--) == 0)        return FAIL;
  } 

  //Start I2C Communication
  I2C_TransferHandling(I2C1, TEMPADDR, 2, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXIS) == RESET)  {
     if((timeout--) == 0)        return FAIL;
  } 

  //Send DataRead Command  [E0 00]
  I2C_SendData(I2C1, 0xE0);  
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXIS) == RESET)  {
     if((timeout--) == 0)        return FAIL;
  } 
  I2C_SendData(I2C1, 0x00);  
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXE) == RESET)  {
     if((timeout--) == 0)        return FAIL;
  } 

  //Stop I2C Command
  I2C_GenerateSTOP(I2C1, ENABLE);
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))  {
     if((timeout--) == 0)        return FAIL;
  } 

  // Check I2C1 State
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET)  {
     if((timeout--) == 0)        return FAIL;
  } 

  //Start I2C Communication
  I2C_TransferHandling(I2C1, TEMPADDR, 6, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

  //Read Data
  for (Datacount=0 ; Datacount<TEMPDATALENGTH ; Datacount++)
  {
    timeout=2000;
    while (!I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE))  {
     if((timeout--) == 0)        return FAIL;
    } 
    received_data[Datacount] = I2C_ReceiveData(I2C1); // read one byte and request another byte
  }

  //Stop I2C Communication
  I2C_GenerateSTOP(I2C1, ENABLE);
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))  {
     if((timeout--) == 0)        return FAIL;
  } 
  
  //Calcuration Temp & Humi
  temp_val = (175*(received_data[0]*256+received_data[1]));
  temp_val = (temp_val/65535)-45;
  Rhum_val = 100*(received_data[3]*256+received_data[4]);
  Rhum_val = Rhum_val/65535;
  printf ("\r\nTemp : %.1f \r\nHumi : %.1f \r\n\r\n",temp_val, Rhum_val);            
  
  return OK;
}

char ReadTempCmd()
{
  int timeout;

  //Check I2C State
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET)  {
      if((timeout--) == 0)       return FAIL;
  }  

  //Start I2C Communication
  I2C_TransferHandling(I2C1, TEMPADDR, 2, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXIS) == RESET)  {
     if((timeout--) == 0)        return FAIL;
  }      
  
  //Send DataRead Command for Measure Temnp & Humi  [20 32]
  I2C_SendData(I2C1, 0x20);  
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXIS) == RESET)  {
      if((timeout--) == 0)       return FAIL;
  }    
  I2C_SendData(I2C1, 0x32);  
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1,I2C_FLAG_TXE) == RESET)  {
      if((timeout--) == 0)        return FAIL;
  }      

  //Stop I2C Communication
  I2C_GenerateSTOP(I2C1, ENABLE);
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))  {
      if((timeout--) == 0)        return FAIL;
  }
  
  return OK;
}


char ReadCO2()
{
  uint8_t received_data[9], Datacount, Dummy1, Dummy2;
  unsigned int Co2_val, timeout;

  //Check I2C State
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET);  {
      if((timeout--) == 0)        return FAIL;
  }
  
  //Start I2C Communication
  I2C_TransferHandling(I2C1, CO2Addr, 9, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

  for (Datacount=0 ; Datacount<CO2DATALENGTH ; Datacount++)
  {
    timeout=2000;
    while (!I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE));  {
      if((timeout--) == 0)        return FAIL;
    }  
    received_data[Datacount] = I2C_ReceiveData(I2C1); // read one byte and request another byte
  }

  I2C_GenerateSTOP(I2C1, ENABLE);
  timeout=2000;
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));   {
      if((timeout--) == 0)        return FAIL;
    }         

  if (0 == received_data[2])
  {
    Co2_val = received_data[0]*256 + received_data[1];
    printf ("\r\nCo2 Value : %d",Co2_val);
  }
  else
  {
    printf ("\r\nCo2 Value : Not Ready");
  }
    
  
  return OK;
}

char ReadpParticle()
{
  int PM25Value, PM10Value;
  
  if(aRxBuffer[0]==0xAA && aRxBuffer[1]==0xAA         // 정상 데이터 여부 확인
     && aRxBuffer[2]==0x53 && aRxBuffer[3]==0x52)
  {
      PM25Value = (aRxBuffer[12]*256) + aRxBuffer[13];              //PM2.5 센싱 데이터
      PM10Value = (aRxBuffer[14]*256) + aRxBuffer[15];              //PM10 센싱 데이터
  }
  else
  {
  }
  
  Rx_Compli_Flag=RESET;
  Rx_SensorData_Count=0;
  
  //printf ("\r\n%d %d %d %d %d %d %d %d",aRxBuffer[0],aRxBuffer[1],aRxBuffer[2],aRxBuffer[3],aRxBuffer[12],aRxBuffer[13],aRxBuffer[14],aRxBuffer[15]);
  printf ("\r\nPM2.5 Value : %d",PM25Value);
  printf ("\r\nPM10  Value : %d",PM10Value);
  
  return OK;
}