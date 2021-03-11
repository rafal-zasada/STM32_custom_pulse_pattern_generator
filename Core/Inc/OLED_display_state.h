/*
 * OLED_display_state.h
 *
 *  Created on: 1 Dec 2020
 *      Author: Raf
 */

#ifndef INC_OLED_DISPLAY_STATE_H_
#define INC_OLED_DISPLAY_STATE_H_


typedef enum 	{Leonardo_TC1, Leonardo_TC2, Leonardo_Case1, Leonardo_Case2, Leonardo_Case3, Leonardo_Case4, Leonardo_Case5, Leonardo_Case6, Leonardo_Case7,
				Leonardo_Case8, Leonardo_Case9,
				Leonardo_PRF1, Leonardo_PRF2, Leonardo_PRF3, Leonardo_PRF4, Leonardo_PRF5, Leonardo_PRF6, Leonardo_PRF7, Leonardo_PRF8, Leonardo_PRF9,
				Leonardo_Duty_12P, Leonardo_Duty_15P, Leonardo_Pattern_Q, Leonardo_Burst_18u_10kHz, Leonardo_Burst_20u_10kHz} OLEDStates_type;

extern OLEDStates_type OLEDDisplayState;

void OLED_Update_Display_Case(OLEDStates_type State);

#endif /* INC_OLED_DISPLAY_STATE_H_ */

