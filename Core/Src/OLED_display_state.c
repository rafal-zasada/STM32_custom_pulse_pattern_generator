/*
 * OLED_state.c
 *
 *  Created on: 1 Dec 2020
 *      Author: Raf
 */


#include "OLED_display_state.h"
#include "ssd1306.h"

OLEDStates_type OLEDDisplayState = Case1;


void update_OLED_display(OLEDStates_type State)
{
	switch(State)
	{
	case Case1:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(" Case 1", Font_16x26, White);
		ssd1306_SetCursor(0, 32);
		ssd1306_WriteString("f1(kHz)   f2(kHz)", Font_7x10, White);
		ssd1306_SetCursor(0, 45);
		ssd1306_WriteString("0.850 1.925", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;

	case Case2:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(" Case 2", Font_16x26, White);
		ssd1306_SetCursor(0, 32);
		ssd1306_WriteString("f1(kHz)   f2(kHz)", Font_7x10, White);
		ssd1306_SetCursor(0, 45);
		ssd1306_WriteString("1.350 1.800", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;

	case Case3:
		break;

	case Case4:
		break;

	case Case5:
		break;

	case Case6:
		break;

	case Case7:
		break;

	default:
		break;
	}


}



