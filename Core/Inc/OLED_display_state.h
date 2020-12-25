/*
 * OLED_display_state.h
 *
 *  Created on: 1 Dec 2020
 *      Author: Raf
 */

#ifndef INC_OLED_DISPLAY_STATE_H_
#define INC_OLED_DISPLAY_STATE_H_


typedef enum 	{Leonardo_Case1, Leonardo_Case2, Leonardo_Case3, Leonardo_Case4, Leonardo_Case5, Leonardo_Case6, Leonardo_Case7,
				Leonardo_PRF1, Leonardo_PRF2, Leonardo_PRF3, Leonardo_PRF4, Leonardo_PRF5, Leonardo_PRF6, Leonardo_PRF7, Leonardo_PRF8, Leonardo_PRF9,
				Leonardo_Duty_12P, Leonardo_Duty_15P, Leonardo_Pattern_Q} OLEDStates_type;

void Update_OLED_Display_Frequency(OLEDStates_type State);
void DrawSplitLine(void);

#endif /* INC_OLED_DISPLAY_STATE_H_ */



//typedef enum
//{
//  GPIO_PIN_RESET = 0U,
//  GPIO_PIN_SET
//}GPIO_PinState;
