/*---------------------------------------------------------------------------
 * @file 		servocontrol.c 
 * @brief 	Main file
 * @author  Gabriel Bastien  
 * @date   	03.12.2017
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "LPC17xx.H"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_ADC.h"
#include "Board_LED.h"
#include "Board_Buttons.h"
#include "PIN_LPC17xx.h"
#include "servocontrol.h"

#include <string.h>

int main(void)
{
	init();
	uint8_t txt_l1[10];
	uint8_t txt_l2[10];
	uint8_t txt_statevalue[10];
	uint8_t txt_step[10];
	
	while(1)
	{
		GLCDPrint(txt_l1,txt_l2,txt_statevalue,txt_step);
	} 	
}



/*-----------------------------------------------------------------------------
	init FONCTION

	init initialise boards, componants and timers
 *----------------------------------------------------------------------------*/
void init(void)
{
	LED_Initialize();													  /* Initialisation of the board LED		*/
	GLCD_Initialize();													/* Initialisation of the board GLCD		*/
	ADC_Initialize();
	
	GLCD_SetBackgroundColor(GLCD_COLOR_WHITE);	/* Set backgroud screen Color to White*/
	GLCD_ClearScreen();												  /* Clear GLCD													*/
	GLCD_SetFont(&GLCD_Font_16x24);					  	/* Set printing Font to Big						*/
	ES1_AppBoard_InitPWM1();										/* Initialisation of the PWM 					*/
/*----- Initialization Timer Interrupt 1 -------------------------------------*/       
   LPC_SC->PCLKSEL0 |= 1 << 4;            		/* Timer 1 - turn power on						*/ 
   
   LPC_TIM1->MR0 = 10000000-1;								/*Interrupt every 100ms								*/
   LPC_TIM1->MCR = (3 << 0);

   NVIC_SetPriority(TIMER1_IRQn,5);						/* Set Timer priority									*/
   NVIC_EnableIRQ(TIMER1_IRQn);								/* Enable the interrupts on timer 1		*/

   LPC_TIM1->TCR = (1 << 0);
	
		initwatchdog();														/* Initialise the watchdog timer			*/
}
/*-----------------------------------------------------------------------------
	initwatchdog FONCTION

	initwatchdog initialise Watchdog timer (here in chip reset mode)
 *----------------------------------------------------------------------------*/
void initwatchdog(void)
{
 NVIC_EnableIRQ(WDT_IRQn); 			// Enable WDT at NVIC
 LPC_WDT->WDCLKSEL = 0; 				// Select Internal RC Oszillator 4 MHz
 // Default Prescaler of 4
 LPC_WDT->WDTC = 200000; 				// Watch Feed after 200 ms;
 LPC_WDT->WDMOD = 1<<0; 				// Set Enable Bit, Watchdog is now running
 LPC_WDT->WDMOD = 1<<1;		   		// Reset mode : the watchdog reset the chip if not feed
 LPC_WDT->WDFEED = 0xAA;				// Feeding Watchdog
 LPC_WDT->WDFEED = 0x55; 				// Feeding Watchdog
} 

/*-----------------------------------------------------------------------------
	ES1_AppBoard_InitPWM1 FONCTION

	ES1_AppBoard_InitPWM1 initialise PMW
 *----------------------------------------------------------------------------*/
void ES1_AppBoard_InitPWM1 (void) 
{    LPC_SC->PCONP    |=  (1<<6);   // Tab. 46 - PWM Power on     
		 LPC_SC->PCLKSEL0 |=  (1<<12);  // Tab. 40 - CCLK for PWM 
 
   // Configure Pin 25, Port 3 as PWM-Channel 2    
	PIN_Configure(  3,                         // Port                 
									25,                         // Pin                     
									3,                         // Pin function (0-3)                  
									PIN_PINMODE_PULLDOWN,
									PIN_PINMODE_NORMAL);   
 
 
   LPC_PWM1->MR0 =  2000000; // Tab. 446 - Set PWM Period to 20ms    
	 LPC_PWM1->MCR |= (1<<1); // Tab. 450 - Enable TC Reset on PWMMR0    
	 LPC_PWM1->MR2 =  150000; // Tab. 446 - Set falling edge to 1,5 ms    
	 LPC_PWM1->LER |= (1<<2); // Tab. 453 - Enable PWM Match 2 Latch  
 
   LPC_PWM1->PCR |= (1<<1); // Tab. 452 - Single edge mode for PWM-Channel 2     
	 LPC_PWM1->PCR |= (1<<10); // Tab. 452 - Enable Output PWM2    
   LPC_PWM1->TCR |= (1<<0); // Tab. 448 - Counter Reset to Clear reset     
	 LPC_PWM1->TCR |= (1<<3); // Tab. 448 - Enable PWM  
}

/*-----------------------------------------------------------------------------
	GLCDPrint FONCTION

	GLCDPrint manage the printing on LCD
 *----------------------------------------------------------------------------*/
void GLCDPrint(uint8_t txt_l1[10],uint8_t txt_l2[10],uint8_t txt_statevalue[10],uint8_t txt_step[10])
{		
	sprintf((char*)txt_l1,"Servo-Control");
	GLCD_DrawString(0*FONT_WIDTH_BIG, 0*FONT_HEIGHT_BIG, (char*)txt_l1);
	
	sprintf((char*)txt_l2,"Labor Embedded");
	GLCD_DrawString(0*FONT_WIDTH_BIG, 1*FONT_HEIGHT_BIG, (char*)txt_l2);
	
	LPC_WDT->WDFEED = 0xAA; // Feeding Watchdog
	LPC_WDT->WDFEED = 0x55; // Feeding Watchdog
	if(servo == 1)
	{
		sprintf((char*)txt_statevalue, "State : running");
		GLCD_DrawString(0*FONT_WIDTH_BIG, 8*FONT_HEIGHT_BIG, (char*)txt_statevalue);
	}
	else
	{
		sprintf((char*)txt_statevalue, "State : stopped");
		GLCD_DrawString(0*FONT_WIDTH_BIG, 8*FONT_HEIGHT_BIG, (char*)txt_statevalue);	
	}
		
	sprintf((char*)txt_step, "step :%02d", step);
	GLCD_DrawString(0*FONT_WIDTH_BIG, 9*FONT_HEIGHT_BIG, (char*)txt_step);
	
	/*Need to feed a second time the watchdog beaucause GLCD draw inctruction are during 50ms each */
	
	LPC_WDT->WDFEED = 0xAA; // Feeding Watchdog 
	LPC_WDT->WDFEED = 0x55; // Feeding Watchdog
}
