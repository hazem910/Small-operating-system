#include "servicelayer\TMU.h"
#include "MCAL\DIO.h"

void func_call(void);
extern TMU_ConfigType instans;


extern Task_BlockType gstr_arrayoftasks[BUFFER_SIZE];
int main(void)
{
   DIO_Cfg_s instanse={GPIOA,PIN0,OUTPUT};
   DIO_init(&instanse);
   
   TMU_Init(&instans);
     sei();
   TMU_Start_Timer(1000,func_call,PERIODIC);
 
   while(1)
   {
      TMU_Dispatch();
      
   }
   
   
}
void func_call(void)
{
   DIO_Toggle(GPIOA,PIN0);
}
