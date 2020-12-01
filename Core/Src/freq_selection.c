/*
 * freq_selection.c
 *
 *  Created on: Nov 29, 2020
 *      Author: Raf
 */


#include "freq_selection.h"
#include "stm32l4xx_hal.h"
#include <stdbool.h>
#include "OLED_display_state.h"


//C99 style initialisation - timer (TIM2) settings for required frequencies are valid for main clock = 80MHz and prescaler = 0 (actual x1)
CasesTypeDef CasesSet1[7] = {	 [0].Freq_1 = 94117, [0].Freq_2 = 41557,	// 0.85kHz / 1.925kHz
								 [1].Freq_1 = 59258, [1].Freq_2 = 44443,	// 1.35kHz / 1.8kHz
								 [2].Freq_1 = 36116, [2].Freq_2 = 59258,	// 2.215kHz / 1.35kHz
								 [3].Freq_1 = 110344, [3].Freq_2 = 44443,	// 0.725kHz / 1.8kHz
								 [4].Freq_1 = 35555, [4].Freq_2 = 59258,	// 2.25kHz / 1.35kHz
								 [5].Freq_1 = 56337, [5].Freq_2 = 20355,	// 1.42kHz / 3.93kHz
								 [6].Freq_1 = 94117, [6].Freq_2 = 13332,	// 0.85kHz / 6kHz

};

int Freq_1;
int Freq_2;
int CurrentCase;
int CurrentFrequency;

extern OLEDStates_type OLEDDisplayState;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);				// just for debugging with scope

	  if(TIM2->ARR == CasesSet1[CurrentCase].Freq_1)	// writing directly to registers to avoid delays
	  {
		  TIM2->ARR = CasesSet1[CurrentCase].Freq_2;
	  }
	  else
	  {
		  TIM2->ARR = CasesSet1[CurrentCase].Freq_1;
	  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_2)	// case up button pressed
	{
		CurrentCase++;
		if(CurrentCase > 6)
			CurrentCase = 6;
	}

	if(GPIO_Pin == GPIO_PIN_3)	//case down button pressed
	{
		CurrentCase--;
		if(CurrentCase < 0)
			CurrentCase = 0;
	}

	OLEDDisplayState = CurrentCase++; // 0 = Case1

}




