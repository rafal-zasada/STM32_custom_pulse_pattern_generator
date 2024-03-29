/*
 * OLED_state.c
 *
 *  Created on: 1 Dec 2020
 *      Author: Raf
 */

#include <stdbool.h>
#include <stdio.h>
#include "OLED_display_state.h"
#include "ssd1306.h"
#include "generator_control.h"

OLEDStates_type OLEDDisplayState = Leonardo_Case1;
extern int CurrentCase;
extern int OutputState;
extern int NumberOfPulses;

// not used
//static void DrawSplitLine(void)
//{
//	for(int i = 0; i < 30; i++)
//	{
//		ssd1306_DrawPixel(60, 32 + i, White);
//	}
//}

// writes number to buffer only
static void OLED_WriteCaseNumber(void)
{
	char StringBuffer[10] = {0};

	snprintf(StringBuffer, 10, "%2d", CurrentCase + 1);
	ssd1306_SetCursor(110, 52);
	ssd1306_WriteString(StringBuffer, Font_7x10, White);

}

void OLED_Update_Display_Case(OLEDStates_type State)
{
	char StringBuffer[20] = {0};

	ssd1306_Fill(Black);
	ssd1306_SetCursor(93, 3);

	if(CurrentCase == Leonardo_Burst_18u_10kHz || CurrentCase == Leonardo_Burst_20u_10kHz || CurrentCase == Leonardo_TC_1_Single_Shot)
	{
		ssd1306_WriteString("TRG", Font_11x18, White);
	}

	else
	{
		if(OutputState == OutputON)
		{
			ssd1306_WriteString("ON", Font_11x18, White);
		}
		if(OutputState == OutputOFF)
		{
			ssd1306_WriteString("OFF", Font_11x18, White);
		}
	}


	ssd1306_SetCursor(0, 0);

	switch(State)
	{
	case Leonardo_TC1:
		ssd1306_WriteString("TC 1", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 10 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 10 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("Duty= 10 %", Font_7x10, White);
		break;

	case Leonardo_TC2:
		ssd1306_WriteString("TC 2", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 12 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 10 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("Duty= 12 %", Font_7x10, White);
		break;

	case Leonardo_Case1:
		ssd1306_WriteString("PH 1", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 0.850 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 1.925 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		break;

	case Leonardo_Case2:
		ssd1306_WriteString("PH 2", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 1.350 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 1.800 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		break;

	case Leonardo_Case3:
		ssd1306_WriteString("PH 3", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 2.215 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 1.350 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		break;

	case Leonardo_Case4:
		ssd1306_WriteString("PH 4", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 0.725 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 1.800 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		break;

	case Leonardo_Case5:
		ssd1306_WriteString("PH 5", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 2.250 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 1.350 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		break;

	case Leonardo_Case6:
		ssd1306_WriteString("PH 6", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 1.420 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 3.930 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		break;

	case Leonardo_Case7:
		ssd1306_WriteString("PH 7", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 0.850 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 6.000 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 20 us", Font_7x10, White);
		break;

	case Leonardo_Case8_switching:
		ssd1306_WriteString("PH 8", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 3.250 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 5.880 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 25/3 us", Font_7x10, White);
		break;

	case Leonardo_Case9_switching:
		ssd1306_WriteString("PH 9", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 3.250 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 0.900 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 25/45 us", Font_7x10, White);
		break;


	case Leonardo_PRF1:
		ssd1306_WriteString("PRF 1", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 2 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 50 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 10 %", Font_7x10, White);
		break;

	case Leonardo_PRF2:
		ssd1306_WriteString("PRF 2", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 10 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 12 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		break;

	case Leonardo_PRF3:
		ssd1306_WriteString("PRF 3", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 20 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 6 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		break;

	case Leonardo_PRF4:
		ssd1306_WriteString("PRF 4", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 30 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 4 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		break;

	case Leonardo_PRF5:
		ssd1306_WriteString("PRF 5", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 40 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 3 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		break;

	case Leonardo_PRF6:
		ssd1306_WriteString("PRF 6", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 50 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 2.4 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		break;

	case Leonardo_PRF7:
		ssd1306_WriteString("PRF 7", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 60 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 2 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		break;

	case Leonardo_PRF8:
		ssd1306_WriteString("PRF 8", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 70 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 1.7 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 12 %", Font_7x10, White);
		break;

	case Leonardo_PRF9:
		ssd1306_WriteString("PRF 9", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 70 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 0.7 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("DUTY= 4.9 %", Font_7x10, White);
		break;

	case Leonardo_Duty_12P:
		ssd1306_WriteString("Dy12", Font_16x26, White);
		ssd1306_SetCursor(65, 3);
		ssd1306_WriteString("%", Font_11x18, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 2.4 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW= 50 us", Font_7x10, White);
		break;

	case Leonardo_Duty_15P:
		ssd1306_WriteString("Dy15", Font_16x26, White);
		ssd1306_SetCursor(65, 3);
		ssd1306_WriteString("%", Font_11x18, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF1= 15 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PRF2= 11.57 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW= 10 us", Font_7x10, White);
		break;

	case Leonardo_Pattern_Q:
		ssd1306_WriteString("PRN Q", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("PRF= 10 kHz", Font_7x10, White);
		ssd1306_SetCursor(0, 41);
		ssd1306_WriteString("PW1= 20 us", Font_7x10, White);
		ssd1306_SetCursor(0, 53);
		ssd1306_WriteString("PW2= 10 us", Font_7x10, White);
		break;

	case Leonardo_Burst_18u_10kHz:
		ssd1306_WriteString("B 18u", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		snprintf(StringBuffer, sizeof(StringBuffer), "count= %d", NumberOfPulses);
		ssd1306_WriteString(StringBuffer, Font_11x18, White);
		ssd1306_SetCursor(0, 52);
		ssd1306_WriteString("PRF= 10 kHz", Font_7x10, White);
		break;

	case Leonardo_Burst_20u_10kHz:
		ssd1306_WriteString("B 20u", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		snprintf(StringBuffer, sizeof(StringBuffer), "count= %d", NumberOfPulses);
		ssd1306_WriteString(StringBuffer, Font_11x18, White);
		ssd1306_SetCursor(0, 52);
		ssd1306_WriteString("PRF= 10 kHz", Font_7x10, White);
		break;

	case Leonardo_TC_1_Single_Shot:
		ssd1306_WriteString("S 10u", Font_16x26, White);
		ssd1306_SetCursor(0, 29);
		ssd1306_WriteString("one shot", Font_11x18, White);
		ssd1306_SetCursor(0, 52);
		ssd1306_WriteString("PW= 10 us", Font_7x10, White);
		break;

	default:
		break;
	}

	OLED_WriteCaseNumber();
	ssd1306_UpdateScreen();
}

