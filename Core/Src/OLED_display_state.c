/*
 * OLED_state.c
 *
 *  Created on: 1 Dec 2020
 *      Author: Raf
 */


#include "OLED_display_state.h"
#include "ssd1306.h"
#include <stdbool.h>

OLEDStates_type OLEDDisplayState = Case1;
bool OLEDupToDate = false;


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
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(" Case 3", Font_16x26, White);
		ssd1306_SetCursor(0, 32);
		ssd1306_WriteString("f1(kHz)   f2(kHz)", Font_7x10, White);
		ssd1306_SetCursor(0, 45);
		ssd1306_WriteString("2.215 1.350", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;

	case Case4:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(" Case 4", Font_16x26, White);
		ssd1306_SetCursor(0, 32);
		ssd1306_WriteString("f1(kHz)   f2(kHz)", Font_7x10, White);
		ssd1306_SetCursor(0, 45);
		ssd1306_WriteString("0.725 1.800", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;

	case Case5:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(" Case 5", Font_16x26, White);
		ssd1306_SetCursor(0, 32);
		ssd1306_WriteString("f1(kHz)   f2(kHz)", Font_7x10, White);
		ssd1306_SetCursor(0, 45);
		ssd1306_WriteString("2.250 1.350", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;

	case Case6:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(" Case 6", Font_16x26, White);
		ssd1306_SetCursor(0, 32);
		ssd1306_WriteString("f1(kHz)   f2(kHz)", Font_7x10, White);
		ssd1306_SetCursor(0, 45);
		ssd1306_WriteString("1.420 3.930", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;

	case Case7:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString(" Case 7", Font_16x26, White);
		ssd1306_SetCursor(0, 32);
		ssd1306_WriteString("f1(kHz)   f2(kHz)", Font_7x10, White);
		ssd1306_SetCursor(0, 45);
		ssd1306_WriteString("0.850 6.000", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;

	default:
		break;
	}

	OLEDupToDate = true;

}



