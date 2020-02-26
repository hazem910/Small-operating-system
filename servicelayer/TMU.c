#include "TMU.h"


#define CLEAR 0
#define START 0
#define TCNT_INITIAL_VALUE 6
#define ONE 1
#define HIGH 1
static uint8_t g_res;
static uint8_t gs_arraycount;
static uint8_t gu8_multiple_init;
Task_BlockType gstr_arrayoftasks[BUFFER_SIZE]={CLEAR};


/************************************************************************/
/* TMU_Init
EnmTMUError_t TMU_Init (const TMU_ConfigType * ConfigPtr )
Synchronous
Non Reentrant
ConfigPtr Pointer to a selected configuration structure*/
/************************************************************************/
EnmTMUError_t TMU_Init (const TMU_ConfigType * ConfigPtr )
{
   EnmTMUError_t status =E_OK;
   if(ConfigPtr==NULL)
   {
      status =TMU_INIT_NULL_POINTER;
   }
   else
   {
      if(gu8_multiple_init==initialized)
      {
         status=TMU_MULTIPLE_INIT;
      }
       else
       {     gu8_multiple_init=initialized;
             g_res=ConfigPtr->RES;
            Timer_cfg_s instance={CLEAR};
            switch(ConfigPtr->TIMER_ID)
            {
              case TIMER_0:
                     instance.Timer_CH=TIMER_0;
                     instance.Timer_Mode=TIMER_MODE;
                     instance.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
                     instance.Timer_Prescaler=TIMER_PRESCALER_64;
                     Timer_Init(&instance);
                     break;
               case TIMER_1:
                     instance.Timer_CH=TIMER_1;
                     instance.Timer_Mode=TIMER_MODE;
                     instance.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
                     instance.Timer_Prescaler=TIMER_PRESCALER_64;
                     Timer_Init(&instance);
                     break;
               case TIMER_2:
                      instance.Timer_CH=TIMER_2;
                      instance.Timer_Mode=TIMER_MODE;
                      instance.Timer_Int_MODE=TIMER_INTERRUPT_MODE;
                      instance.Timer_Prescaler=TIMER_PRESCALER_64;
                      Timer_Init(&instance);
                      break;
               default:
                      status =E_NOK;
                      break;
            }
          }
      }
   return status;
}


/*
Function Name 	TMU_Start_Timer
Syntax:
Sync/Async:
Reentrancy:
Parameters (in):
Parameters (out):
Parameters (inOut):
Return:*/

EnmTMUError_t TMU_Start_Timer(uint16_t time,ptrtotask_CBK_FUNC ptrtofun,uint8_t periodicORoneshot)
{   EnmTMUError_t status=E_OK;
   if(gu8_multiple_init==not_init)
   {
      status=TMU_MODULE_NOT_INIT;
   }
else
{
         if(gs_arraycount<BUFFER_SIZE)
         {
            if((periodicORoneshot!=PERIODIC)&&(periodicORoneshot!=ONESHOT))
            {
               status=TMU_NOT_PERODICORONESHOT;
            }
            else
            {
              if(ptrtofun==NULL)
              {
                 status=TMU_FUN_NULL_POINTER;
              }
              else
              {
                    gstr_arrayoftasks[gs_arraycount].delay=time;
                    gstr_arrayoftasks[gs_arraycount].Ptrtotask=ptrtofun;
                    gstr_arrayoftasks[gs_arraycount].perodicity=periodicORoneshot;
                    gstr_arrayoftasks[gs_arraycount].delay_milistone=CLEAR;
  
                    if(gs_arraycount==CLEAR)
                    {
                       Timer_Start(TMU_TIMER_ID,TCNT_INITIAL_VALUE);
                    }

                  gs_arraycount++;
              }
            }
         }
         else
         {
            status=TMU_BUFFER_IS_FULL;
         }
}
return status;
}
/**
* @brief: TMU Stop
* @param: ptrFun: pointer to callback function
* @return: EnmTMUError_t status code with error code if one occurred
*/
EnmTMUError_t TMU_Stop_Timer(void (*ptrtofun)(void))
{
   EnmTMUError_t status=E_OK;
   uint8_t au8_counter=CLEAR;
   uint8_t Flag=CLEAR;
   if(gs_arraycount==CLEAR)
   {
      status=TMU_BUFFER_IS_EMPTY;
   }
   else
  {
         for(au8_counter=START;au8_counter<BUFFER_SIZE;au8_counter++)
         {

            if(gstr_arrayoftasks[au8_counter].Ptrtotask==ptrtofun)
            {   Flag=HIGH;
               if(au8_counter==BUFFER_SIZE-ONE)
               {
                  gstr_arrayoftasks[au8_counter].Ptrtotask=NULL;
                  gstr_arrayoftasks[au8_counter].delay_milistone=CLEAR;
                  gstr_arrayoftasks[au8_counter].delay=CLEAR;
                  gstr_arrayoftasks[au8_counter].perodicity=CLEAR;
               }
               else
               {
                  gstr_arrayoftasks[au8_counter].Ptrtotask=gstr_arrayoftasks[BUFFER_SIZE-ONE].Ptrtotask;
                  gstr_arrayoftasks[au8_counter].delay_milistone=gstr_arrayoftasks[BUFFER_SIZE-ONE].delay_milistone;
                  gstr_arrayoftasks[au8_counter].delay=gstr_arrayoftasks[BUFFER_SIZE-ONE].delay;
                  gstr_arrayoftasks[au8_counter].perodicity=gstr_arrayoftasks[BUFFER_SIZE-ONE].perodicity;

                  gstr_arrayoftasks[BUFFER_SIZE-ONE].Ptrtotask=NULL;
                  gstr_arrayoftasks[BUFFER_SIZE-ONE].delay_milistone=CLEAR;
                  gstr_arrayoftasks[BUFFER_SIZE-ONE].delay=CLEAR;
                  gstr_arrayoftasks[BUFFER_SIZE-ONE].perodicity=CLEAR;
               }
               gs_arraycount--;
            }

         }
         if(gs_arraycount==CLEAR)
         {
            Timer_Stop(TMU_TIMER_ID);
         }
        if(Flag==CLEAR)
        {
         status=TMU_MULTIPLE_STOP;
        }
 }
   return status;
}


/**
* @brief: TMU Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: EnmTMUError_t status code with error code if one occurred
*/


EnmTMUError_t TMU_Dispatch(void)
{
   EnmTMUError_t status=E_OK;
   uint8_t u8_preloadtimer=TCNT_INITIAL_VALUE;
   
   if(gu_timer_count1>=RESOLUTION)
   { 
      gu_timer_count1=CLEAR;
      
      Timer_SetValue(TMU_TIMER_ID,&u8_preloadtimer);
      	/*Loop through Tasks in the array and increment milestones*/
      uint8_t u8_counter=CLEAR;
      for(u8_counter=START;u8_counter<BUFFER_SIZE;u8_counter++)
      {
         if(gstr_arrayoftasks[u8_counter].Ptrtotask==NULL)
         {
            
         }
         else
         {
            gstr_arrayoftasks[u8_counter].delay_milistone++;
         }
      }
      /* Loop through  array of structure and handle each one */
      for(u8_counter=START;u8_counter<BUFFER_SIZE;u8_counter++)
      {
         if(gstr_arrayoftasks[u8_counter].Ptrtotask==NULL)
         {
            
         }
         else
         {
            if(gstr_arrayoftasks[u8_counter].delay_milistone>=gstr_arrayoftasks[u8_counter].delay)
             {
                gstr_arrayoftasks[u8_counter].delay_milistone=CLEAR;
                gstr_arrayoftasks[u8_counter].Ptrtotask();
                if(gstr_arrayoftasks[u8_counter].perodicity==ONESHOT)
                {
                   TMU_Stop_Timer(gstr_arrayoftasks[u8_counter].Ptrtotask);
                }
             }  
             else
             {
                
             }      
         }
      }
   }
   else
   {
      
   }
   return status;
}

/**
* @brief: TMU DeInitialization
* @param: void
* Input : void
* Output: None
* @return: EnmTMUError_t status code with error code if one occurred
*/
EnmTMUError_t TMU_DeInit(void)
{
   EnmTMUError_t u8_status=E_OK;
   uint8_t u8_counter=CLEAR;
   if(gu8_multiple_init==initialized)
   {
         for(u8_counter=START;u8_counter<BUFFER_SIZE;u8_counter++)
         {
             gstr_arrayoftasks[u8_counter].Ptrtotask=NULL;
             gstr_arrayoftasks[u8_counter].delay_milistone=CLEAR;
             gstr_arrayoftasks[u8_counter].delay=CLEAR;
             gstr_arrayoftasks[u8_counter].perodicity=CLEAR;
      
         }
         Timer_Stop(TMU_TIMER_ID);
   }
   else
   {
      u8_status=TMU_MODULE_NOT_INIT;
   }
   gu8_multiple_init = not_init;
   return u8_status;
}
