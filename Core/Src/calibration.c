/*
 * frequency_calibration.c
 *
 *  Created on: Dec 5, 2020
 *      Author: Raf
 */
#include<stdint.h>  // for uint64_t
#include <calibration.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "stm32l4xx_hal.h"
#include "tim.h"
#include "freq_selection.h"
#include "ssd1306.h"
#include "OLED_display_state.h"


uint32_t PAGEError = 0;		// error will be saved here
static FLASH_EraseInitTypeDef EraseInitStruct;
static uint32_t FrequencyCalibrationFactorFlashAddress = 0x080FF800;	// use start of last sector of STM32L476RG flash for storing frequency calibration data
static uint32_t PulseWitdhOffsetFlashAddress = 0x080FF808; 				// use start of last sector + 8 of STM32L476RG flash for storing pulse width offset data
static uint32_t *ptrCalibrationFactorInFlashAddress = (uint32_t*)0x080FF800;
static uint32_t *ptrPulseWidthOffsetInFlashAddress = (uint32_t*)0x080FF808;
char string_buffer[20] = {0};
extern char PC_GUI_message[200];
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern float FrequencyCalibrationFactor;
//extern UART_HandleTypeDef huart2; // for debug only
extern OLEDStates_type OLEDDisplayState;
extern float PulseWidthOffset;
bool FrequencyCalibrationModeFlag;
bool PulseOffsetAdjustmentModeFlag;

#define FREQUENCY_CF_UPPER_LIMIT  1.01	// 1%
#define FREQUENCY_CF_LOWER_LIMIT  0.99	// 1%
#define PW_OFFSET_UPPER_LIMIT  50			// 50 * 12.5ns = 625 ns
#define PW_OFFSET_LOWER_LIMIT  -10			// 125 ns

void InitDataInFlashSettings(void)	// initialisation needed only for erase function before write to EEPROM
{
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Banks       = FLASH_BANK_2;
	EraseInitStruct.Page        = 511;
	EraseInitStruct.NbPages     = 1;
}

void SaveCalibrationFactorInFlash()
{
	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);
	HAL_FLASH_Program (FLASH_TYPEPROGRAM_DOUBLEWORD, FrequencyCalibrationFactorFlashAddress, FrequencyCalibrationFactor * 1000000);
	HAL_FLASH_Program (FLASH_TYPEPROGRAM_DOUBLEWORD, PulseWitdhOffsetFlashAddress, PulseWidthOffset * 1000);
	HAL_FLASH_Lock();
}

float ReadFrequencyCalibrationFactorFromFlash(void)
{
	uint32_t raw_value_calibration_factor = *(ptrCalibrationFactorInFlashAddress);
	if(raw_value_calibration_factor == 0xFFFFFFFF)
		raw_value_calibration_factor = 1000000; // if not programmed/saved yet then set to 1000000
	return ((float)raw_value_calibration_factor / 1000000);
}

float ReadPulseWidthOffsetFromFlash(void)
{
	uint32_t raw_value_PW_offset_factor = *(ptrPulseWidthOffsetInFlashAddress);
	if(raw_value_PW_offset_factor == 0xFFFFFFFF)
		raw_value_PW_offset_factor = 0; // if not programmed/saved yet then set to 0
	return ((float)raw_value_PW_offset_factor / 1000);
}

static void UpdateFrequencyCalibrationDisplay(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("FREQ. CALIBRATION:", Font_7x10, White);
	ssd1306_SetCursor(0, 14);
	ssd1306_WriteString("ADJUST FREQ. TO", Font_7x10, White);
	ssd1306_SetCursor(0, 28);
	ssd1306_WriteString("10kHz WITH TOGGLE", Font_7x10, White);
	ssd1306_SetCursor(0, 44);
	snprintf(string_buffer, 20, "CF= %.4f", FrequencyCalibrationFactor);
	ssd1306_WriteString(string_buffer, Font_11x18, White);
	ssd1306_UpdateScreen();
}

static void UpdatePulseAdjustmentDisplay(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("PULSE ADJUSTMENT:", Font_7x10, White);
	ssd1306_SetCursor(0, 14);
	ssd1306_WriteString("ADJUST OFFSET WITH", Font_7x10, White);
	ssd1306_SetCursor(0, 28);
	ssd1306_WriteString("TOGGLE FOR PW 0.2u", Font_7x10, White);
	ssd1306_SetCursor(0, 44);
	snprintf(string_buffer, 20, "%+7.1f ns", PulseWidthOffset * 12.5);
	ssd1306_WriteString(string_buffer, Font_11x18, White);
	ssd1306_UpdateScreen();
}

void Freq_Calibration_Mode(void)
{
	bool FrequencyCalibrationUpdated = false;
	bool Previous_Pin6_State = 1;
	bool Previous_Pin8_State = 1;
	uint32_t CalibrationFrequency_ARR = 7999;

	for(int i = 0; i < 1000000; i++); // about 140 ms delay for de-bouncing
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);	// disable switch function implemented in ISR to use this switch here for calibration
	UpdateFrequencyCalibrationDisplay();
	HAL_TIM_Base_Stop_IT(&htim3);	// stop frequency switching
	TIM3->CNT = 0;
	TIM2->CNT = 0;
	TIM2->ARR = round(CalibrationFrequency_ARR * FrequencyCalibrationFactor);	//Set timer2 period to 100us --> 10 kHz (calibration frequency)
	TIM2->CCR1 = round(80 * FrequencyCalibrationFactor + PulseWidthOffset);  	//  1us nominal pulse width for frequency calibration

	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0)
	{
		//just for scope trigger output
		GPIOC->BSRR |= (1u << 4); // set pin 4
		for(int i = 0; i < 25; i++); // about 3 us
		GPIOC->BSRR |= (1u << 20); // reset pin 4

		Previous_Pin6_State = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);
		Previous_Pin8_State = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);
		for(int i = 0; i < 100000; i++); // wait between consecutive pin reads (above) to avoid bouncing around threshold (about 14 ms)

		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == 0 && Previous_Pin6_State == 1)
		{
			FrequencyCalibrationFactor += 0.0001;
			if(FrequencyCalibrationFactor > FREQUENCY_CF_UPPER_LIMIT) FrequencyCalibrationFactor = FREQUENCY_CF_UPPER_LIMIT;
			Previous_Pin6_State = 0;
			TIM2->CNT = 0;
			TIM2->ARR = round(CalibrationFrequency_ARR * FrequencyCalibrationFactor);
			UpdateFrequencyCalibrationDisplay();
			FrequencyCalibrationUpdated = true;
		}

		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8) == 0 && Previous_Pin8_State == 1)
		{
			FrequencyCalibrationFactor -= 0.0001;
			if(FrequencyCalibrationFactor < FREQUENCY_CF_LOWER_LIMIT) FrequencyCalibrationFactor = FREQUENCY_CF_LOWER_LIMIT;
			Previous_Pin8_State = 0;
			TIM2->CNT = 0;
			TIM2->ARR = round(CalibrationFrequency_ARR * FrequencyCalibrationFactor);
			UpdateFrequencyCalibrationDisplay();
			FrequencyCalibrationUpdated = true;
		}
	}

	for(int i = 0; i < 1000000; i++); // about 140 ms
	FrequencyCalibrationModeFlag = false;


	if(FrequencyCalibrationUpdated)
	{
		ApplyFrequencyCalFactor();
		SaveCalibrationFactorInFlash();

		// Calibration saved message on Display
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 10);
		ssd1306_WriteString("CALIBRATION:", Font_11x18, White);
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString("   SAVED", Font_11x18, White);
		ssd1306_UpdateScreen();
		HAL_Delay(2000);
	}

	OLED_Update_Display_Case(OLEDDisplayState);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);	// buttons used here are used somewhere else as EXTI so any flags has to be cleared
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	HAL_TIM_Base_Start_IT(&htim3); // start frequency switching
}


void Pulse_Adjustment_Mode(void)
{
	bool PW_OffsetUpdated = false;
	bool Previous_Pin6_State = 1;
	bool Previous_Pin8_State = 1;
	uint32_t CalibrationPulseWidth_CCR1 = 16; // nominal pulse width = 0.2u

	for(int i = 0; i < 1000000; i++); // about 140 ms
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);	// disable switch function implemented in ISR to use this switch here for calibration
	UpdatePulseAdjustmentDisplay();

	HAL_TIM_Base_Stop_IT(&htim3);	// stop frequency switching
	TIM3->CNT = 0;
	TIM2->CNT = 0;
	TIM2->ARR = round(7999 * FrequencyCalibrationFactor);	// frequency = 10 kHz (arbitrary number for pulse calibration)
	TIM2->CCR1 = round(CalibrationPulseWidth_CCR1 * FrequencyCalibrationFactor + PulseWidthOffset);  // set pulse width

	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == 0)
	{
		//just for scope trigger output
		GPIOC->BSRR |= (1u << 4); // set pin 4
		for(int i = 0; i < 25; i++); // about 3 us
		GPIOC->BSRR |= (1u << 20); // reset pin 4

		Previous_Pin6_State = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);
		Previous_Pin8_State = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);

		for(int i = 0; i < 100000; i++); // de-bouncing (about 14 ms)

        if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == 0 && Previous_Pin6_State == 1)
		{
			PulseWidthOffset += 1;
			if(PulseWidthOffset > PW_OFFSET_UPPER_LIMIT) PulseWidthOffset = PW_OFFSET_UPPER_LIMIT;
			Previous_Pin6_State = 0;
			TIM2->CNT = 0;
			TIM2->CCR1 = round(CalibrationPulseWidth_CCR1 * FrequencyCalibrationFactor + PulseWidthOffset);
			UpdatePulseAdjustmentDisplay();
			PW_OffsetUpdated = true;
		}

		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8) == 0 && Previous_Pin8_State == 1)
		{
			PulseWidthOffset -= 1;
			if(PulseWidthOffset < PW_OFFSET_LOWER_LIMIT) PulseWidthOffset = PW_OFFSET_LOWER_LIMIT; // limit offset
			Previous_Pin8_State = 0;
			TIM2->CNT = 0;
			TIM2->CCR1 = round(CalibrationPulseWidth_CCR1 - PulseWidthOffset);
			UpdatePulseAdjustmentDisplay();
			PW_OffsetUpdated = true;
		}
	}

	for(int i = 0; i < 1000000; i++); // about 140 ms
	PulseOffsetAdjustmentModeFlag = false;


	if(PW_OffsetUpdated)
	{
		Apply_PW_Offsets();
		SaveCalibrationFactorInFlash();

		// Calibration saved message on Display
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 10);
		ssd1306_WriteString(" PW OFFSET", Font_11x18, White);
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString("   SAVED", Font_11x18, White);
		ssd1306_UpdateScreen();
		HAL_Delay(2000);
	}

	OLED_Update_Display_Case(OLEDDisplayState);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);	// buttons used here are used somewhere else as EXTI so it has to be cleared
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	HAL_TIM_Base_Start_IT(&htim3); // start frequency switching
}




