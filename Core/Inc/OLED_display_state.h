/*
 * OLED_display_state.h
 *
 *  Created on: 1 Dec 2020
 *      Author: Raf
 */

#ifndef INC_OLED_DISPLAY_STATE_H_
#define INC_OLED_DISPLAY_STATE_H_


typedef enum {Case1, Case2, Case3, Case4, Case5, Case6, Case7} OLEDStates_type;
void update_OLED_display(OLEDStates_type State);
void DrawSplitLine(void);

#endif /* INC_OLED_DISPLAY_STATE_H_ */



//typedef enum
//{
//  GPIO_PIN_RESET = 0U,
//  GPIO_PIN_SET
//}GPIO_PinState;
