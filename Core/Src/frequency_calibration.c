/*
 * frequency_calibration.c
 *
 *  Created on: Dec 5, 2020
 *      Author: Raf
 */
#include <stdio.h>
#include <stdbool.h>
#include "frequency_calibration.h"
#include "stm32l4xx_hal.h"
#include "tim.h"
#include "freq_selection.h"
#include "stdio.h"
#include <stdbool.h>
#include <string.h>
#include "ssd1306.h"
#include "OLED_display_state.h"

uint32_t PAGEError = 0;					// error will be saved here
static FLASH_EraseInitTypeDef EraseInitStruct;
static uint32_t CalibrationFactorInFlashAddress = 0x080FF800;	// use last sector of STM32L476RG for EEPROM emulation
static uint32_t *ptrCalibrationFactorInFlashAddress = (uint32_t*)0x080FF800;
char string_buffer[20] = {0};
extern char PC_GUI_message[200];
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern float CalibrationFactor;
//extern UART_HandleTypeDef huart2;
extern bool OLEDupToDate;
extern OLEDStates_type OLEDDisplayState;
bool CalibrationModeFlag;

void InitCalibrationDataInFlash(void)	// initialisation needed only for erase function before write to EEPROM
{
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Banks       = FLASH_BANK_2;
	EraseInitStruct.Page        = 511;
	EraseInitStruct.NbPages     = 1;
}

void SaveCalibrationFactorInFlash(uint64_t Data)
{
	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);
	HAL_FLASH_Program (FLASH_TYPEPROGRAM_DOUBLEWORD, CalibrationFactorInFlashAddress, Data);
	HAL_FLASH_Lock();
}

static void UpdateCalibrationDisplay(void)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("CALIBRATION MODE:", Font_7x10, White);
	ssd1306_SetCursor(0, 14);
	ssd1306_WriteString("ADJUST OUTPUT TO", Font_7x10, White);
	ssd1306_SetCursor(0, 28);
	ssd1306_WriteString("10 KHZ WITH TOGGLE", Font_7x10, White);
	ssd1306_SetCursor(0, 44);
	snprintf(string_buffer, 12, "CF= %.4f", CalibrationFactor);
	ssd1306_WriteString(string_buffer, Font_11x18, White);
	ssd1306_UpdateScreen();
}

void CalibrationMode(void)
{
	float InitialCalibrationFactor = CalibrationFactor;
	bool Previous_Pin6_State = 1;
	bool Previous_Pin8_State = 1;

	for(int i = 0; i < 1000000; i++); // about 140 ms
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);	// disable switch function implemented in ISR to use this switch here for calibration
	UpdateCalibrationDisplay();

	HAL_TIM_Base_Stop_IT(&htim3);	// stop frequency switching
	// __HAL_TIM_DISABLE_IT(&htim3, TIM_IT_UPDATE); //using this sometimes "disables" TIM2 for 53 seconds like it has missed restart point and is overflowing. Why?
	TIM2->CNT = 0;		// reset TIM2 otherwise it will miss set point and will be off until overflow.
	TIM2->ARR = 7999 * CalibrationFactor;	//Set timer2 period to 100us --> 10 kHz (calibration frequency)

	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0)
	{
		Previous_Pin6_State = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);
		Previous_Pin8_State = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);

		for(int i = 0; i < 100000; i++); // wait between consecutive pin reads to avoid bouncing around threshold (about 14 ms)

		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == 0 && Previous_Pin6_State == 1)
		{
			CalibrationFactor += 0.0001;
			if(CalibrationFactor > 1.01) CalibrationFactor = 1.01; // limit Calibration factor to + 2%
			Previous_Pin6_State = 0;
			TIM2->CNT = 0;
			TIM2->ARR = 7999 * CalibrationFactor;
			UpdateCalibrationDisplay();
		}

		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8) == 0 && Previous_Pin8_State == 1)
		{
			CalibrationFactor -= 0.0001;		// later make sure it doesn't go below 0 !
			if(CalibrationFactor < 0.98) CalibrationFactor = 0.98; // limit Calibration factor to - 2%
			Previous_Pin8_State = 0;
			TIM2->CNT = 0;
			TIM2->ARR = 7999 * CalibrationFactor;
			UpdateCalibrationDisplay();
		}
	}

	for(int i = 0; i < 1000000; i++); // about 140 ms
	OLEDupToDate = false;
	CalibrationModeFlag = false;
	ApplyCalFactor();
	SaveCalibrationFactorInFlash(CalibrationFactor * 1000000);

	if(InitialCalibrationFactor != CalibrationFactor)
	{
		// Calibration saved message on Display
		ssd1306_Fill(Black);
		ssd1306_SetCursor(0, 10);
		ssd1306_WriteString("CALIBRATION:", Font_11x18, White);
		ssd1306_SetCursor(0, 30);
		ssd1306_WriteString("   SAVED", Font_11x18, White);
		ssd1306_UpdateScreen();
		HAL_Delay(2000);
	}

	Update_OLED_DisplayCase(OLEDDisplayState);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);	// buttons used here are used somewhere else as EXTI so it has to be cleared
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	HAL_TIM_Base_Start_IT(&htim3); // start frequency switching
	//	  __HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);
}

void ReadCalibrationDataFromFlash(float *CalibrationFactor)
{
	uint32_t raw_value_calibration_factor = *(ptrCalibrationFactorInFlashAddress);
	if(raw_value_calibration_factor == 0xFFFFFFFF)
		raw_value_calibration_factor = 1000000; // if not programmed/saved yet then set to 1000000
	*CalibrationFactor = (float)raw_value_calibration_factor / 1000000;
}

