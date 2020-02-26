/*
 ============================================================================
 Name        : Testing.c
 Author      : Muhammed Gamal
 Description : this file test the ICU driver
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "TMU.h"


#define NONE_VALID_REPETITION_STATUS 3



extern TMU_ConfigType instans;


extern Task_BlockType gstr_arrayoftasks[BUFFER_SIZE];

void func_call(void)
{

}

void func_call2(void)
{

}

void func_call3(void)
{

}

void func_call4(void)
{

}

int main(void) {
	TMU_ConfigType *null_ptr=NULL;
	uint8_t u8_status1=0;
	uint8_t u8_status2=0;
	uint8_t u8_status3=0;
	uint8_t u8_status4=0;
	uint8_t u8_status5=0;
	uint8_t u8_status6=0;
	uint8_t u8_status7=0;
	uint8_t u8_status8=0;
	uint8_t u8_status9=0;
	uint8_t u8_status10=0;





	/************************************************************************************
	* Target Function: TMU_Init
	* Test Case: send NULL pointer to "TMU_Init"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status1 |=TMU_Init(null_ptr);
    u8_status1 |= TMU_DeInit();
	if(u8_status1==E_OK)
	{
		printf("NULL pointer (test case 1): PASSED\n");
	}
	else
	{
		printf("NULL pointer (test case 1): FAILED\n");
	}


	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: module not_initialized to "TMU_Start_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status2 |=TMU_Start_Timer(1000,func_call,PERIODIC);
    u8_status2 |= TMU_DeInit();
	if(u8_status2==E_OK)
	{
		printf("module not_initialized (test case 2): PASSED\n");
	}
	else
	{
		printf("module not_initialized (test case 2): FAILED\n");
	}

	/************************************************************************************
	* Target Function: TMU_Init
	* Test Case: multiple initialization to "TMU_Init"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status3 |=TMU_Init(&instans);
	u8_status3 |=TMU_Init(&instans);
    u8_status3 |= TMU_DeInit();
	if(u8_status3==E_OK)
	{
		printf("multiple initialization (test case 3): PASSED\n");
	}
	else
	{
		printf("multiple initialization (test case 3): FAILED\n");
	}




	/************************************************************************************
	* Target Function: TMU_Stop_Timer
	* Test Case: stop without start "TMU_Stop_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	TMU_Stop_Timer(func_call);
	if(u8_status4==E_OK)
	{
		printf("stop without start (test case 4): PASSED\n");
	}
	else
	{
		printf("stop without start (test case 4): FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: invalid parameter (repetition) "TMU_Start_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status5 |=TMU_Start_Timer(1000,func_call,NONE_VALID_REPETITION_STATUS);
	if(u8_status5==E_OK)
	{
		printf("invalid parameter (test case 5): PASSED\n");
	}
	else
	{
		printf("invalid parameter (test case 5): FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: invalid parameter (called function is null) "TMU_Start_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status6 |=TMU_Start_Timer(1000,NULL,PERIODIC);
	if(u8_status6==E_OK)
	{
		printf("invalid parameter (test case 6): PASSED\n");
	}
	else
	{
		printf("invalid parameter (test case 6): FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: multiple stop "TMU_Stop_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status7 |=TMU_Init(&instans);
	u8_status7 |=TMU_Stop_Timer(func_call);
	u8_status7 |=TMU_Stop_Timer(func_call);
	u8_status7 |= TMU_DeInit();
	if(u8_status7==E_OK)
	{
		printf("multiple stop (test case 7): PASSED\n");
	}
	else
	{
		printf("multiple stop (test case 7): FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: multiple start to the same called function "TMU_Start_Timer"
	* Expected OUTPUT: PASSED
	* Real OUTPUT: PASSED
	************************************************************************************/
	u8_status8 |=TMU_Init(&instans);
	u8_status8 |=TMU_Start_Timer(1000,func_call,PERIODIC);
	u8_status8 |=TMU_Start_Timer(1000,func_call,PERIODIC);
	u8_status8 |= TMU_DeInit();
	if(u8_status8==E_OK)
	{
		printf("multiple start (test case 8): PASSED\n");
	}
	else
	{
		printf("multiple start (test case 8): FAILED\n");
	}




	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: valid parameters"TMU_Start_Timer"
	* Expected OUTPUT: PASSED
	* Real OUTPUT: PASSED
	************************************************************************************/
	u8_status9 |=TMU_Init(&instans);
	u8_status9 |=TMU_Start_Timer(1000,func_call,PERIODIC);
	u8_status9 |= TMU_DeInit();
	if(u8_status9==E_OK)
	{
		printf("valid parameters (test case 9): PASSED\n");
	}
	else
	{
		printf("valid parameters (test case 9): FAILED\n");
	}



	/************************************************************************************
	* Target Function: TMU_Start_Timer
	* Test Case: full buffer (buffer is 3)"TMU_Start_Timer"
	* Expected OUTPUT: FAILED
	* Real OUTPUT: FAILED
	************************************************************************************/
	u8_status10 |=TMU_Init(&instans);
	u8_status10 |=TMU_Start_Timer(1000,func_call,PERIODIC);
	u8_status10 |=TMU_Start_Timer(500,func_call2,PERIODIC);
	u8_status10 |=TMU_Start_Timer(500,func_call3,PERIODIC);
	u8_status10 |=TMU_Start_Timer(900,func_call4,PERIODIC);
	//u8_status9 |= TMU_DeInit();
	if(u8_status10==E_OK)
	{
		printf("full buffer (test case 10): PASSED\n");
	}
	else
	{
		printf("full buffer (test case 10): FAILED\n");
	}

	return 0;
}




