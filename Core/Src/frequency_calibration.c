/*
 * frequency_calibration.c
 *
 *  Created on: Dec 5, 2020
 *      Author: Raf
 */
#include <stdio.h>
#include "frequency_calibration.h"
#include "stm32l4xx_hal.h"

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
