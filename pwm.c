/**---------------------------------------------------------------------------
 * @file 		pwm.c
 * @brief 	pwm fonctions
 * @author  Gabriel Bastien  
 * @date   	03.12.2017
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "LPC17xx.H"
#include "PIN_LPC17xx.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_LED.h"
#include "servocontrol.h" 

/*-----------------------------------------------------------------------------
	ES1_AppBoard_SetPWM1 FONCTION

	ES1_AppBoard_SetPWM1 Convert value of rotation (degree) in ms for the PWM 
 *----------------------------------------------------------------------------*/

int8_t ES1_AppBoard_SetPWM1 (int8_t degree)
{
	if ((degree >= -60)&&(degree <= 60))
	{
		LPC_PWM1->MR2 = ((degree * 100000)/120) + 150000;
		LPC_PWM1->LER |= (1<<2);
		return 0;
	}
		else 
		return 1;
}
