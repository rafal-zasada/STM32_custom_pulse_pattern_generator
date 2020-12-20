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
#include <string.h>
#include <stdio.h>

int Freq_1;
int Freq_2;
int CurrentCase;
int CurrentFrequency;
float CalibrationFactor;
extern OLEDStates_type OLEDDisplayState;
extern bool OLEDupToDate;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;
#define NUMBER_OF_CASES 19


//typedef enum 	{Leonardo_Case1, Leonardo_Case2, Leonardo_Case3, Leonardo_Case4, Leonardo_Case5, Leonardo_Case6, Leonardo_Case7,
//				Leonardo_PRF1, Leonardo_PRF2, Leonardo_PRF3, Leonardo_PRF4, Leonardo_PRF5, Leonardo_PRF6, Leonardo_PRF7, Leonardo_PRF8, Leonardo_PRF9,
//				Leonardo_Duty_12P, Leonardo_Duty_15P, Leonardo_Pattern_Q} OLEDStates_type;

//C99 style initialisation - timer (TIM2) settings for required frequencies are valid for main clock = 80MHz and prescaler = 0 (actual x1)
CasesTypeDef UncalibratedCasesLeonardo[NUMBER_OF_CASES] = {
												 [Leonardo_Case1].Freq1 = 94117, [Leonardo_Case1].Freq2 = 41557,	// Leonardo_Case1 0.85kHz / 1.925kHz
												 [Leonardo_Case2].Freq1 = 59258, [Leonardo_Case2].Freq2 = 44443,		// Leonardo_Case2 1.35kHz / 1.8kHz
												 [Leonardo_Case3].Freq1 = 36116, [Leonardo_Case3].Freq2 = 59258,		// Leonardo_Case3 2.215kHz / 1.35kHz
												 [Leonardo_Case4].Freq1 = 110344, [Leonardo_Case4].Freq2 = 44443,		// Leonardo_Case4 0.725kHz / 1.8kHz
												 [Leonardo_Case5].Freq1 = 35555, [Leonardo_Case5].Freq2 = 59258,		// Leonardo_Case5 2.25kHz / 1.35kHz
												 [Leonardo_Case6].Freq1 = 56337, [Leonardo_Case6].Freq2 = 20355,		// Leonardo_Case6 1.42kHz / 3.93kHz
												 [Leonardo_Case7].Freq1 = 94117, [Leonardo_Case7].Freq2 = 13332,		// Leonardo_Case7 0.85kHz / 6kHz

												 [Leonardo_Case1].Pulse1 = 1600, [Leonardo_Case1].Pulse2 = 1600,		// 20us
												 [Leonardo_Case2].Pulse1 = 1600, [Leonardo_Case2].Pulse2 = 1600,
												 [Leonardo_Case3].Pulse1 = 1600, [Leonardo_Case3].Pulse2 = 1600,
												 [Leonardo_Case4].Pulse1 = 1600, [Leonardo_Case4].Pulse2 = 1600,
												 [Leonardo_Case5].Pulse1 = 1600, [Leonardo_Case5].Pulse2 = 1600,
												 [Leonardo_Case6].Pulse1 = 1600, [Leonardo_Case6].Pulse2 = 1600,
												 [Leonardo_Case7].Pulse1 = 1600, [Leonardo_Case7].Pulse2 = 1600,

												 [Leonardo_PRF1].Freq1 = 39999, [Leonardo_PRF1].Freq2 = 39999,		// Leonardo_PRF1
												 [Leonardo_PRF2].Freq1 = 7999, [Leonardo_PRF2].Freq2 = 7999,		// Leonardo_PRF2
												 [Leonardo_PRF3].Freq1 = 3999, [Leonardo_PRF3].Freq2 = 3999,		// Leonardo_PRF3
												 [Leonardo_PRF4].Freq1 = 2666, [Leonardo_PRF4].Freq2 = 2666,		// Leonardo_PRF4
												 [Leonardo_PRF5].Freq1 = 1999, [Leonardo_PRF5].Freq2 = 1999,		// Leonardo_PRF5
												 [Leonardo_PRF6].Freq1 = 1599, [Leonardo_PRF6].Freq2 = 1599,		// Leonardo_PRF6
												 [Leonardo_PRF7].Freq1 = 1332, [Leonardo_PRF7].Freq2 = 1332,		// Leonardo_PRF7
												 [Leonardo_PRF8].Freq1 = 1142, [Leonardo_PRF8].Freq2 = 1142,		// Leonardo_PRF8
												 [Leonardo_PRF9].Freq1 = 1142, [Leonardo_PRF9].Freq2 = 1142,		// Leonardo_PRF9

												 [Leonardo_Duty_12P].Freq1 = 33332, [Leonardo_Duty_12P].Freq2 = 33332,	// Leonardo_Duty_12P
												 [Leonardo_Duty_15P].Freq1 = 5332, [Leonardo_Duty_15P].Freq2 = 6913,		// Leonardo_Duty_15P
												 [Leonardo_Pattern_Q].Freq1 = 7999, [Leonardo_Pattern_Q].Freq2 = 7999,		// Leonardo_Pattern_Q


												 [Leonardo_PRF1].Pulse1 = 4000, [Leonardo_PRF1].Pulse2 = 4000,		// 50 us
												 [Leonardo_PRF2].Pulse1 = 960, [Leonardo_PRF2].Pulse2 = 960,		// 12 us
												 [Leonardo_PRF3].Pulse1 = 480, [Leonardo_PRF3].Pulse2 = 480,		// 6 us
												 [Leonardo_PRF4].Pulse1 = 320, [Leonardo_PRF4].Pulse2 = 320,		// 4 us
												 [Leonardo_PRF5].Pulse1 = 240, [Leonardo_PRF5].Pulse2 = 240,		// 3 us
												 [Leonardo_PRF6].Pulse1 = 192, [Leonardo_PRF6].Pulse2 = 192,		// 2.4 us
												 [Leonardo_PRF7].Pulse1 = 160, [Leonardo_PRF7].Pulse2 = 160,		// 2 us
												 [Leonardo_PRF8].Pulse1 = 136, [Leonardo_PRF8].Pulse2 = 136,		// 1.7 us
												 [Leonardo_PRF9].Pulse1 = 56, [Leonardo_PRF9].Pulse2 = 56,		// 0.7 us

												 [Leonardo_Duty_12P].Pulse1 = 4000, [Leonardo_Duty_12P].Pulse2 = 4000,		// 10 us
												 [Leonardo_Duty_15P].Pulse1 = 800, [Leonardo_Duty_15P].Pulse2 = 800,		// 10 us
												 [Leonardo_Pattern_Q].Pulse1 = 1600, [Leonardo_Pattern_Q].Pulse2 = 800,		// 20 us / 10 us (Pattern Q)

											};

CasesTypeDef CalibratedCasesLeonardo[19] = {
												 [Leonardo_Case1].Freq1 = 94117, [Leonardo_Case1].Freq2 = 41557,	// Leonardo_Case1 0.85kHz / 1.925kHz
												 [Leonardo_Case2].Freq1 = 59258, [Leonardo_Case2].Freq2 = 44443,		// Leonardo_Case2 1.35kHz / 1.8kHz
												 [Leonardo_Case3].Freq1 = 36116, [Leonardo_Case3].Freq2 = 59258,		// Leonardo_Case3 2.215kHz / 1.35kHz
												 [Leonardo_Case4].Freq1 = 110344, [Leonardo_Case4].Freq2 = 44443,		// Leonardo_Case4 0.725kHz / 1.8kHz
												 [Leonardo_Case5].Freq1 = 35555, [Leonardo_Case5].Freq2 = 59258,		// Leonardo_Case5 2.25kHz / 1.35kHz
												 [Leonardo_Case6].Freq1 = 56337, [Leonardo_Case6].Freq2 = 20355,		// Leonardo_Case6 1.42kHz / 3.93kHz
												 [Leonardo_Case7].Freq1 = 94117, [Leonardo_Case7].Freq2 = 13332,		// Leonardo_Case7 0.85kHz / 6kHz

												 [Leonardo_Case1].Pulse1 = 1600, [Leonardo_Case1].Pulse2 = 1600,		// 20us
												 [Leonardo_Case2].Pulse1 = 1600, [Leonardo_Case2].Pulse2 = 1600,
												 [Leonardo_Case3].Pulse1 = 1600, [Leonardo_Case3].Pulse2 = 1600,
												 [Leonardo_Case4].Pulse1 = 1600, [Leonardo_Case4].Pulse2 = 1600,
												 [Leonardo_Case5].Pulse1 = 1600, [Leonardo_Case5].Pulse2 = 1600,
												 [Leonardo_Case6].Pulse1 = 1600, [Leonardo_Case6].Pulse2 = 1600,
												 [Leonardo_Case7].Pulse1 = 1600, [Leonardo_Case7].Pulse2 = 1600,

												 [Leonardo_PRF1].Freq1 = 33332, [Leonardo_PRF1].Freq2 = 33332,		// Leonardo_PRF1
												 [Leonardo_PRF2].Freq1 = 7999, [Leonardo_PRF2].Freq2 = 7999,		// Leonardo_PRF2
												 [Leonardo_PRF3].Freq1 = 3999, [Leonardo_PRF3].Freq2 = 3999,		// Leonardo_PRF3
												 [Leonardo_PRF4].Freq1 = 2666, [Leonardo_PRF4].Freq2 = 2666,		// Leonardo_PRF4
												 [Leonardo_PRF5].Freq1 = 1999, [Leonardo_PRF5].Freq2 = 1999,		// Leonardo_PRF5
												 [Leonardo_PRF6].Freq1 = 1599, [Leonardo_PRF6].Freq2 = 1599,		// Leonardo_PRF6
												 [Leonardo_PRF7].Freq1 = 1332, [Leonardo_PRF7].Freq2 = 1332,		// Leonardo_PRF7
												 [Leonardo_PRF8].Freq1 = 1142, [Leonardo_PRF8].Freq2 = 1142,		// Leonardo_PRF8
												 [Leonardo_PRF9].Freq1 = 1142, [Leonardo_PRF9].Freq2 = 1142,		// Leonardo_PRF9

												 [Leonardo_Duty_12P].Freq1 = 33332, [Leonardo_Duty_12P].Freq2 = 33332,	// Leonardo_Duty_12P
												 [Leonardo_Duty_15P].Freq1 = 5332, [Leonardo_Duty_15P].Freq2 = 6913,		// Leonardo_Duty_15P
												 [Leonardo_Pattern_Q].Freq1 = 7999, [Leonardo_Pattern_Q].Freq2 = 7999,		// Leonardo_Pattern_Q


												 [Leonardo_PRF1].Pulse1 = 4000, [Leonardo_PRF1].Pulse2 = 4000,		// 50 us
												 [Leonardo_PRF2].Pulse1 = 960, [Leonardo_PRF2].Pulse2 = 960,		// 12 us
												 [Leonardo_PRF3].Pulse1 = 480, [Leonardo_PRF3].Pulse2 = 480,		// 6 us
												 [Leonardo_PRF4].Pulse1 = 320, [Leonardo_PRF4].Pulse2 = 320,		// 4 us
												 [Leonardo_PRF5].Pulse1 = 240, [Leonardo_PRF5].Pulse2 = 240,		// 3 us
												 [Leonardo_PRF6].Pulse1 = 192, [Leonardo_PRF6].Pulse2 = 192,		// 2.4 us
												 [Leonardo_PRF7].Pulse1 = 160, [Leonardo_PRF7].Pulse2 = 160,		// 2 us
												 [Leonardo_PRF8].Pulse1 = 136, [Leonardo_PRF8].Pulse2 = 136,		// 1.7 us
												 [Leonardo_PRF9].Pulse1 = 56, [Leonardo_PRF9].Pulse2 = 56,		// 0.7 us

												 [Leonardo_Duty_12P].Pulse1 = 4000, [Leonardo_Duty_12P].Pulse2 = 4000,		// 10 us
												 [Leonardo_Duty_15P].Pulse1 = 800, [Leonardo_Duty_15P].Pulse2 = 800,		// 10 us
												 [Leonardo_Pattern_Q].Pulse1 = 1600, [Leonardo_Pattern_Q].Pulse2 = 800,		// 20 us / 10 us (Pattern Q)
											};

void ApplyCalFactor(void)
{
	// adjust values with calibration factor
	for(int i = 0;i < (  (sizeof(UncalibratedCasesLeonardo)) / sizeof(UncalibratedCasesLeonardo[0])  ); i++)
	{
		CalibratedCasesLeonardo[i].Freq1 = UncalibratedCasesLeonardo[i].Freq1 * CalibrationFactor;
		CalibratedCasesLeonardo[i].Freq2 = UncalibratedCasesLeonardo[i].Freq2 * CalibrationFactor;
		CalibratedCasesLeonardo[i].Pulse1 = UncalibratedCasesLeonardo[i].Pulse1 * CalibrationFactor;
		CalibratedCasesLeonardo[i].Pulse2 = UncalibratedCasesLeonardo[i].Pulse2 * CalibrationFactor;
	}
}

void InitFrequency(void)
{
	ApplyCalFactor();
	//Initialise to Case1 and Freq1
	CurrentCase = Leonardo_Case1;     // array index, actual Case is + 1
	CurrentFrequency = 1;
}

// interrupt handler without HAL to fix pin toggle jitter
void TIM3_IRQHandler(void)
{
//	char PC_GUI_message[200] = {0};
//	extern UART_HandleTypeDef huart2;



	// update period and pulse for TIM2



	if(CurrentCase >= Leonardo_Case1 && CurrentCase <= Leonardo_Case7)
	{
		ScopeTriggerFromISR();

		if(TIM2->ARR == CalibratedCasesLeonardo[CurrentCase].Freq1)
		{
			TIM2->ARR = CalibratedCasesLeonardo[CurrentCase].Freq2;
		}
		else
		{
			TIM2->ARR = CalibratedCasesLeonardo[CurrentCase].Freq1;
		}
		TIM3->ARR = 14;
	}

	if(CurrentCase >= Leonardo_PRF1 && CurrentCase <= Leonardo_PRF9)
	{
		ScopeTriggerFromISR();

		TIM2->ARR = CalibratedCasesLeonardo[CurrentCase].Freq1;
		TIM2->CCR1 = CalibratedCasesLeonardo[CurrentCase].Pulse1;  // capture/compare register used for pulse length
		TIM3->ARR = 14;	// arbitrary number
	}


	if(CurrentCase == Leonardo_Duty_12P)
	{
		ScopeTriggerFromISR();

		TIM2->ARR = CalibratedCasesLeonardo[CurrentCase].Freq1;
		TIM2->CCR1 = CalibratedCasesLeonardo[CurrentCase].Pulse1;  // capture/compare register used for pulse length
		TIM3->ARR = 14;	// arbitrary number
	}

	if(CurrentCase == Leonardo_Duty_15P)
	{
		ScopeTriggerFromISR();
		TIM2->CCR1 = CalibratedCasesLeonardo[CurrentCase].Pulse1;

		if(TIM2->ARR == CalibratedCasesLeonardo[CurrentCase].Freq1)
		{
			TIM2->ARR = CalibratedCasesLeonardo[CurrentCase].Freq2;
			TIM3->ARR = 2;
		}
		else
		{
			TIM2->ARR = CalibratedCasesLeonardo[CurrentCase].Freq1;
			TIM3->ARR = 23;
		}
	}

	// update TIM3 "pulse counter" interrupt (for this ISR) and pulse width
	if(CurrentCase == Leonardo_Pattern_Q)
	{
		//scope trigger
		GPIOC->BSRR |= (1u << 4); // set pin 4
		for(int i = 0; i < 25; i++); // about 3 us
		GPIOC->BSRR |= (1u << 20); // reset pin 4

		TIM2->ARR = CalibratedCasesLeonardo[CurrentCase].Freq1;
		TIM3->ARR = 23; // set to trigger this ISR

		TIM2->CCR1 = CalibratedCasesLeonardo[CurrentCase].Pulse1;
		for(int i = 0; i < 1250; i++); // about 150 us (allow one pulse - dirty trick)
		TIM2->CCR1 = CalibratedCasesLeonardo[CurrentCase].Pulse2;
	}

//	  snprintf(PC_GUI_message, 200, " TIM2->CCR1 = %lu\n TIM3->ARR = %lu\n", TIM2->CCR1, TIM3->ARR);
//	  HAL_UART_Transmit(&huart2, (unsigned char*)PC_GUI_message, strlen(PC_GUI_message), 100);

	__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE); // not using HAL callback so it has to be done manually
}

/*
// disabled here and in stm32l4xx_it.c due to scope trigger jitter - basic ISR work fine
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


void ScopeTriggerFromISR(void)
{
	// scope trigger for dual frequency cases
	if(CalibratedCasesLeonardo[CurrentCase].Freq1 != CalibratedCasesLeonardo[CurrentCase].Freq2)
	{
		if(TIM2->ARR == CalibratedCasesLeonardo[CurrentCase].Freq1)
		{
			GPIOC->BSRR |= (1u << 4); // set pin 4
		}
		else
		{
			GPIOC->BSRR |= (1u << 20); // reset pin 4
		}
	}


	// scope trigger for single frequency cases (unnecessary but added for convenience to avoid need for switching trigger source in the scope)
	if(CalibratedCasesLeonardo[CurrentCase].Freq1 == CalibratedCasesLeonardo[CurrentCase].Freq2)
	{
		if(CurrentFrequency == 1)
		{
			GPIOC->BSRR |= (1u << 4); // set pin 4
			CurrentFrequency = 2;
		}
		else
		{
			GPIOC->BSRR |= (1u << 20); // reset pin 4
			CurrentFrequency = 1;
		}
	}
}

void FreqCaseUpFromISR(void)
{
	CurrentCase++;
	if(CurrentCase > NUMBER_OF_CASES - 1)
		CurrentCase = NUMBER_OF_CASES - 1;

	OLEDDisplayState = CurrentCase;
	OLEDupToDate = false;
	Update_OLED_DisplayCase(OLEDDisplayState);
}

void FreqCaseDownFromISR(void)
{
	CurrentCase--;
	if(CurrentCase < 0)
		CurrentCase = 0;

	OLEDDisplayState = CurrentCase;
	OLEDupToDate = false;
	Update_OLED_DisplayCase(OLEDDisplayState);
}


