/**---------------------------------------------------------------------------
 * @file 		globals.c
 * @brief 	Short description for globals.c
 * @author  Gabriel Bastien  
 * @date   	03.12.2017
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "LPC17xx.H"
#include "PIN_LPC17xx.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_ADC.h"
#include "Board_LED.h"
#include "servocontrol.h"

int8_t polygon[] = {0,6,12,18,24,30,36,42,48,52,60,
										57,54,51,48,45,42,39,36,33,30,
										30,30,30,30,30,30,30,30,30,30,
										29,28,27,26,25,24,23,22,21,20,
										18,16,14,12,10,8,6,4,2,0,
										-12,-24,-36,-48,-60,-48,-36,-24,-12,0}; /*Array containing value in degree corresponding to the line */
enum stateservo servo = stopped;
uint8_t step = 0;

/** END OF FILE
*/
