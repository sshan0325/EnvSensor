#ifndef _ENVSENSOR_H
#define _ENVSENSOR_H

/* Includes ---------------------------------------------------------------*/
#include "platform_config.h"
#include "stdio.h"
#include "usart.h"
#include "subfunction.h"

/* Private variables ------------------------------------------------------*/
#define CO2Addr                 (0x5A<<1) 
#define CO2DATALENGTH           9 

#define TEMPADDR                (0x44<<1) 
#define TEMPDATALENGTH          6


#define FAIL                    0
#define OK                      1

#define NOTREADY                2
#define ERROR                   3

#define SENSINGCYCLE            1              //sec

/* Private function prototypes --------------------------------------------*/
char ReadCO2();
char ReadTempCmd();
char ReadTemp();
char ReadpParticle();
#endif