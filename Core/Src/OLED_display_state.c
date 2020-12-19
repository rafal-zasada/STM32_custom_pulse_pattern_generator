/*
 * OLED_state.c
 *
 *  Created on: 1 Dec 2020
 *      Author: Raf
 */


#include "OLED_display_state.h"
#include "ssd1306.h"
#include <stdbool.h>

OLEDStates_type OLEDDisplayState = Leonardo_Case1;
bool OLEDupToDate = false;

void DrawSplitLine(void)
{
//	void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color)
	for(int i = 0; i < 30; i++)
	{
		ssd1306_DrawPixel(60, 32 + i, White);
	}
}

void Update_OLED_DisplayCase(OLEDStates_type State)
{
	switch(State)
	{
	case Leonardo_Case1:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Case 1", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 0.850 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 1.925 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_Case2:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Case 2", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 1.350 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 1.800 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_Case3:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Case 3", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 2.215 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 1.350 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_Case4:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Case 4", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 0.725 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 1.800 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_Case5:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Case 5", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 2.250 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 1.350 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_Case6:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Case 6", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 1.420 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 3.930 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_Case7:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("Case 7", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 0.850 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 6.000 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_PRF1:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("PRF 1", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 2 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 50 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 10 %", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_PRF2:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("PRF 2", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 10 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 12 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_PRF3:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("PRF 3", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 20 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 6 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_PRF4:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("PRF 4", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 30 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 4 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_PRF5:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("PRF 5", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 40 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 3 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_PRF6:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("PRF 6", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 50 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 2.4 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_PRF7:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("PRF 7", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 60 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 2 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_PRF8:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("PRF 8", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 70 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 1.7 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_PRF9:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("PRF 9", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 70 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 0.7 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 4.9 %", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_Duty_12P:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("D= 12%", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 2.4 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 50 us", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_Duty_15P:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("D= 15%", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 15 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 11.57 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 10 us", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;

	case Leonardo_Pattern_Q:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("P-RN Q", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 10 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW1= 20 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW2= 10 us", Font_7x10, White);
		ssd1306_UpdateScreen();
		break;



	default:
		break;
	}

	OLEDupToDate = true;
}



