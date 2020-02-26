#ifndef TMU_H_
#define TMU_H_
/********************************************************************/
/**************************INCLUDES**********************************/
/********************************************************************/                                            
#include "TMU_confg.h"
#include "Timer.h"
#include "Error_Handling.h"
/********************************************************************/
/**************************DEFINES***********************************/
/*******************************************************************/
#define ONESHOT 0
#define PERIODIC 1
#define initialized 1
#define not_init   0


typedef  sint8_t EnmTMUError_t;
/********************************************************************/
/**************************EXTERN***********************************/
/*******************************************************************/
typedef struct TMU_ConfigType
{
   uint8_t RES;
   uint8_t TIMER_ID;
}TMU_ConfigType;

typedef void(*ptrtotask_CBK_FUNC)(void);

typedef struct Task_BlockType
{
   uint8_t perodicity;
   uint16_t delay;
   ptrtotask_CBK_FUNC Ptrtotask;
   uint16_t delay_milistone;
}Task_BlockType;


/************************************************************************/
/* TMU_Init
EnmTMUError_t TMU_Init (const TMU_ConfigType * ConfigPtr )
Synchronous
Non Reentrant
ConfigPtr Pointer to a selected configuration structure*/                                                         
/************************************************************************/
extern EnmTMUError_t TMU_Init (const TMU_ConfigType * ConfigPtr );
/*
Function Name 	TMU_Start_Timer
Syntax:
Sync/Async:
Reentrancy:
Parameters (in):
Parameters (out):
Parameters (inOut):
Return:*/

extern EnmTMUError_t TMU_Start_Timer(uint16_t time,ptrtotask_CBK_FUNC ptrtofun,uint8_t periodicORoneshot);
/**
* @brief: TMU Stop
* @param: ptrFun: pointer to callback function
* @return: EnmTMUError_t status code with error code if one occurred
*/

extern EnmTMUError_t TMU_Stop_Timer(void (*ptrtofun)(void));

/**
* @brief: TMU Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: EnmTMUError_t status code with error code if one occurred
*/
extern EnmTMUError_t TMU_Dispatch(void);

/**
* @brief: TMU DeInitialization
* @param: void
* Input : void
* Output: None
* @return: EnmTMUError_t status code with error code if one occurred
*/
extern EnmTMUError_t TMU_DeInit(void);





#endif /* TMU_H_ */
