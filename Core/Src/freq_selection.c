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

int Freq_1;
int Freq_2;
int CurrentCase;
int CurrentFrequency;
float CalibrationFactor;
extern OLEDStates_type OLEDDisplayState;
extern bool OLEDupToDate;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;

//C99 style initialisation - timer (TIM2) settings for required frequencies are valid for main clock = 80MHz and prescaler = 0 (actual x1)

CasesTypeDef UncalibratedCasesSet1[7] = {	 [0].Freq_1 = 94117, [0].Freq_2 = 41557,	// 0.85kHz / 1.925kHz
								 [1].Freq_1 = 59258, [1].Freq_2 = 44443,	// 1.35kHz / 1.8kHz
								 [2].Freq_1 = 36116, [2].Freq_2 = 59258,	// 2.215kHz / 1.35kHz
								 [3].Freq_1 = 110344, [3].Freq_2 = 44443,	// 0.725kHz / 1.8kHz
								 [4].Freq_1 = 35555, [4].Freq_2 = 59258,	// 2.25kHz / 1.35kHz
								 [5].Freq_1 = 56337, [5].Freq_2 = 20355,	// 1.42kHz / 3.93kHz
								 [6].Freq_1 = 94117, [6].Freq_2 = 13332,	// 0.85kHz / 6kHz
							};

CasesTypeDef CalibratedCasesSet1[7] = {	 [0].Freq_1 = 94117, [0].Freq_2 = 41557,	// 0.85kHz / 1.925kHz
								 [1].Freq_1 = 59258, [1].Freq_2 = 44443,	// 1.35kHz / 1.8kHz
								 [2].Freq_1 = 36116, [2].Freq_2 = 59258,	// 2.215kHz / 1.35kHz
								 [3].Freq_1 = 110344, [3].Freq_2 = 44443,	// 0.725kHz / 1.8kHz
								 [4].Freq_1 = 35555, [4].Freq_2 = 59258,	// 2.25kHz / 1.35kHz
								 [5].Freq_1 = 56337, [5].Freq_2 = 20355,	// 1.42kHz / 3.93kHz
								 [6].Freq_1 = 94117, [6].Freq_2 = 13332,	// 0.85kHz / 6kHz
							};

void ApplyCalFactor(void)
{
	// adjust values with calibration factor
	for(int i = 0;i < (  (sizeof(UncalibratedCasesSet1)) / sizeof(UncalibratedCasesSet1[0])  ); i++)
	{
		CalibratedCasesSet1[i].Freq_1 = UncalibratedCasesSet1[i].Freq_1 * CalibrationFactor;
		CalibratedCasesSet1[i].Freq_2 = UncalibratedCasesSet1[i].Freq_2 * CalibrationFactor;
	}
}

void InitFrequency(void)
{
	ApplyCalFactor();
	//Initialise to Case1 and Freq1
	CurrentCase = 0; // array index, actual Case is + 1
	CurrentFrequency = CalibratedCasesSet1[CurrentCase].Freq_1;
}

// interrupt handler not using HAL to fix pin toggle jitter
void TIM3_IRQHandler(void)
{
	if(TIM2->ARR == CalibratedCasesSet1[CurrentCase].Freq_1)
	{
		GPIOC->BSRR = 0b10000; // set pin 4
	}
	else
	{
		GPIOC->BSRR = 0b100000000000000000000; // reset pin 4
	}



//	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);

	if(TIM2->ARR == CalibratedCasesSet1[CurrentCase].Freq_1)	// writing directly to registers to avoid delays
	{
		TIM2->ARR = CalibratedCasesSet1[CurrentCase].Freq_2;
	}
	else
	{
		TIM2->ARR = CalibratedCasesSet1[CurrentCase].Freq_1;
	}

	//	TIM2->CNT = 0xFFFF; // r
//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

	__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE); // not using HAL callback so it has to be done manually
}

/*
// need reenabling this Callback in stm32l4xx_it.c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim3)		// which timer triggered this function? At the moment there is only one anyway
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_4);	// for scope trigger

		//  GPIOC->BSRR = 0b10000;
		//  GPIOC->BSRR = 0b100000000000000000000;

		if(TIM2->ARR == CalibratedCasesSet1[CurrentCase].Freq_1)	// writing directly to registers to avoid delays
		{
			TIM2->ARR = CalibratedCasesSet1[CurrentCase].Freq_2;
		}
		else
		{
			TIM2->ARR = CalibratedCasesSet1[CurrentCase].Freq_1;
		}
	}
}
*/

void FreqCaseUpFromISR(void)
{
	CurrentCase++;
	if(CurrentCase > 6)
		CurrentCase = 6;

	OLEDDisplayState = CurrentCase;
	OLEDupToDate = false;
	update_OLED_display(OLEDDisplayState);
}

void FreqCaseDownFromISR(void)
{
	CurrentCase--;
	if(CurrentCase < 0)
		CurrentCase = 0;

	OLEDDisplayState = CurrentCase;
	OLEDupToDate = false;
	update_OLED_display(OLEDDisplayState);
}


