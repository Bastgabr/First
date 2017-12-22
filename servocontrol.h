#ifndef __SERVOCONTROL_H
#define __SERVOCONTROL_H
/* Inhalt der Headerdatei stopwatch.h*/

#include <stdio.h>

/*---------------------------------------------------------------------------*/
/* defines                                                                   */
/*---------------------------------------------------------------------------*/
#define FONT_HEIGHT_BIG    24       /* Big Fontsize see GLCD_Fonts.c */
#define FONT_WIDTH_BIG     16       /* Big Fontsize see GLCD_Fonts.c */
#define LED_2_2						 3				/*Assosiation between LED name and location*/

/*---------------------------------------------------------------------------*/
/* function declarations                                                     */
/*---------------------------------------------------------------------------*/
/**--------------------------------------------------------------------------
 * @fn 			void init(void);
 * @brief 	call others initialisation fonctions 
 * @return	nothing
 * @param		nothing 
 * @author	Gabriel Bastien
 * @date		03.12.17
 ----------------------------------------------------------------------------*/
void init(void);

/**--------------------------------------------------------------------------
 * @fn 			void ES1_AppBoard_InitPWM1 (void);
 * @brief 	Initialise the PWM 
 * @return	nothing
 * @param		nothing 
 * @author	Gabriel Bastien
 * @date		03.12.17
 ----------------------------------------------------------------------------*/
void ES1_AppBoard_InitPWM1 (void);

/**--------------------------------------------------------------------------
 * @fn 			int8_t ES1_AppBoard_SetPWM1 (int8_t degree);
 * @brief 	give a value to MR2 depending on the given value
 * @return	0 if given parameters are between -60 and 60 (else return 1)
 * @param		int8_t degree 
 * @author	Gabriel Bastien
 * @date		03.12.17
 ----------------------------------------------------------------------------*/
int8_t ES1_AppBoard_SetPWM1 (int8_t degree);

/**--------------------------------------------------------------------------
 * @fn 			void GLCDPrint(uint8_t txt_l1[10],uint8_t txt_l2[10],uint8_t txt_statevalue[10],uint8_t txt_step[10]);
 * @brief 	Printing state step and sentences on the LCD screen
 * @return	nothing
 * @param		uint8_t txt_l1[10],uint8_t txt_l2[10],uint8_t txt_statevalue[10],uint8_t txt_step[10] 
 * @author	Gabriel Bastien
 * @date		03.12.17
 ----------------------------------------------------------------------------*/
void GLCDPrint(uint8_t txt_l1[10],uint8_t txt_l2[10],uint8_t txt_statevalue[10],uint8_t txt_step[10]);

/**--------------------------------------------------------------------------
 * @fn 			void initwatchdog(void);
 * @brief 	Initialise the Watchdog Timer
 * @return	nothing 
 * @param		nothing
 * @author	Gabriel Bastien
 * @date		03.12.17
 ----------------------------------------------------------------------------*/
void initwatchdog(void);


/*---------------------------------------------------------------------------*/
/* externals                                                                 */
/*---------------------------------------------------------------------------*/
extern GLCD_FONT GLCD_Font_16x24;					 /* GLCD Font from GLCD_Fonts.c    */
extern GLCD_FONT GLCD_Font_6x8;
extern enum stateservo servo;
extern uint8_t step;
extern int8_t polygon[]; 

/*---------------------------------------------------------------------------*/
/* structs, unions, enums, bitfields, typedefs                               */
/*---------------------------------------------------------------------------*/
enum stateservo
{
	stopped = 0,
	running = 1,
};
#endif /* __SERVOCONTROL_H */
