#include "servicelayer\TMU.h"
#include "MCAL\DIO.h"

void func_call(void);
void func_call1(void);
void func_call2(void);
void func_call3(void);
extern TMU_ConfigType instans;


extern Task_BlockType gstr_arrayoftasks[BUFFER_SIZE];



int main(void)
{
	sei();
   DIO_Cfg_s instanse={GPIOA,LOWER_NIBBLE | UPPER_NIBBLE,OUTPUT};
   DIO_init(&instanse);

   /*test case1 (BUFFER_SIZE is 3) */
   /*
   TMU_Init(&instans);
   TMU_Start_Timer(1000,func_call,PERIODIC);
   TMU_Start_Timer(500,func_call1,PERIODIC);
   TMU_Start_Timer(300,func_call2,PERIODIC);
   TMU_Start_Timer(600,func_call3,PERIODIC);
   */

   /*test case2 (BUFFER_SIZE is 3)*/

   TMU_Init(&instans);
   TMU_Start_Timer(1000,func_call,PERIODIC);
   TMU_Start_Timer(500,func_call1,PERIODIC);
   TMU_Start_Timer(300,func_call2,PERIODIC);
   TMU_Stop_Timer(func_call);
   //TMU_Stop_Timer(func_call3);


   /*test case1 (BUFFER_SIZE is 3)*/
   /*
   TMU_Init(&instans);
   TMU_Start_Timer(1000,func_call,PERIODIC);
   TMU_Start_Timer(500,func_call1,PERIODIC);
   TMU_Start_Timer(300,func_call2,PERIODIC);
   TMU_Stop_Timer(func_call2);
   TMU_Start_Timer(300,func_call3,PERIODIC);
   */

 
   while(1)
   {
      TMU_Dispatch();
      
   }
   
   
}
void func_call(void)
{
   DIO_Toggle(GPIOA,PIN0);
}

void func_call1(void)
{
   DIO_Toggle(GPIOA,PIN1);
}

void func_call2(void)
{
   DIO_Toggle(GPIOA,PIN2);
}

void func_call3(void)
{
   DIO_Toggle(GPIOA,PIN3);
}
