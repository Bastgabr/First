/**---------------------------------------------------------------------------
 * @file 		isr.c
 * @brief 	Short description for isr.c
 * @author  Gabriel Bastien  
 * @date   	03.12.2017
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "LPC17xx.H"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_LED.h"
#include "Board_Buttons.h"
#include "PIN_LPC17xx.h"
#include "servocontrol.h" 

void TIMER1_IRQHandler (void)
{
	static uint32_t ticks = 0;
	static uint32_t lasttick_1 = 0; 
	
	if (LPC_TIM1->IR & (1 << 0))				/* Check if the interrupt flag is high 							*/  
		 LPC_TIM1->IR |= (1 << 0); 				/* Reset Interrup Flag to 0													*/
	
	if(Buttons_GetState() == 1)					/*Test if Button INT0 is pressed										*/
	{
		if((ticks - lasttick_1)>9)				/*Debouncing the information coming from the button */
		{
			switch (servo)									/* switch to determine the state of the programm 		*/
			{
				case stopped : 
					servo = running;
					break;
				case running : 
					break;
			}
		}
		lasttick_1 = ticks;
	}
	
	if (servo == running)
	{
	 ES1_AppBoard_SetPWM1(polygon[step]);	/* Executing Appboard to set MR2 to the right value depending on the values in the Array*/
	 step++;															/* Incrementing the value to go to the next value in array															*/
	 if (step == 61)
	 {
		 servo = stopped;										/*Switch to case stop if loop is done 																									*/
		 step = 0;													/* Reset the value to 0 if every 61 values of the array have been treated 							*/
	 }
	} 

	ticks ++;
}




void WDT_IRQHandler (void)
{
	
} 
