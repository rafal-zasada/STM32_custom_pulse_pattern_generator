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


extern char GUI_message[200];
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern float CalibrationFactor;
extern UART_HandleTypeDef huart2;


	uint32_t PAGEError = 0;	// error will be saved here
	static FLASH_EraseInitTypeDef EraseInitStruct;
	static uint32_t Address = 0x080FF800;	// use last sector of STM32L476RG for EEPROM emulation
//	uint64_t Data = 0; // type?

void InitCalibrationEEPROM(void)	// needed only for erase before write to EEPROM
{
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Banks       = FLASH_BANK_2;
	EraseInitStruct.Page        = 511;
	EraseInitStruct.NbPages     = 1;
}

void SaveCalibrationInEEPROM(uint64_t Data)
{
	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);
	HAL_FLASH_Program (FLASH_TYPEPROGRAM_DOUBLEWORD, Address, Data);
	HAL_FLASH_Lock();
}

void CalibrationModeFromISR(void)
{
	bool Previous_Pin6_State = 1;
	bool Previous_Pin8_State = 1;

	HAL_TIM_Base_Stop_IT(&htim3);
	//	  __HAL_TIM_DISABLE_IT(&htim3, TIM_IT_UPDATE); //using this sometimes "disables" TIM2 for 53 seconds like it has missed restart point and is overflowing. Why?
	TIM2->CNT = 0;		// reset TIM2 otherwise it will miss set point and will be off until overflow.
	TIM2->ARR = 7999 * CalibrationFactor;	//Set timer2 period to 100us --> 10 kHz (calibration frequency)

	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0)
	{
		Previous_Pin6_State = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);
		Previous_Pin8_State = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);

		for(int i = 0; i < 100000; i++); // wait between consecutive pin reads to avoid bouncing (about 14 ms)

		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == 0 && Previous_Pin6_State == 1)
		{
			CalibrationFactor += 0.1;
			Previous_Pin6_State = 0;
			TIM2->CNT = 0;
			TIM2->ARR = 7999 * CalibrationFactor;
		}

		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8) == 0 && Previous_Pin8_State == 1)
		{
			CalibrationFactor -= 0.1;		// later make sure it doesn't go below 0 !
			Previous_Pin8_State = 0;
			TIM2->CNT = 0;
			TIM2->ARR = 7999 * CalibrationFactor;
		}
	}

	ApplyCalFactor();
	HAL_TIM_Base_Start_IT(&htim3);
	//	  __HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);

}


/*
if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    HAL_Delay(100);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    HAL_Delay(100);

    SaveCalibrationInEEPROM(0x1111222233334444);
}

*/
