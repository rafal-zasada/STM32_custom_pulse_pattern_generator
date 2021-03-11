/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include<stdint.h>  // for uint64_t
#include <stdbool.h>
#include <calibration.h>
#include <generator_control.h>
#include "gpio.h"
#include "OLED_display_state.h"

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
  extern bool FrequencyCalibrationModeFlag;
  extern bool PulseOffsetAdjustmentModeFlag;
  extern int OutputState;
  extern TIM_HandleTypeDef htim2;
  extern int CurrentCase;
/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_7
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8
                          |GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC2 PC3 PC4 PC9
                           PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4
                           PA5 PA6 PA7 PA8
                           PA9 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC5 PC6 PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB15 PB4 PB5 PB8
                           PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	for(int i = 0; i < 30000; i++);			// about 3.7 ms delay

	for(int i = 0; i < 100; i++)			// if none of EXTI are stable (continuously low) then return
	{
		if(HAL_GPIO_ReadPin( GPIOC, GPIO_PIN_5) && HAL_GPIO_ReadPin( GPIOC, GPIO_PIN_6) && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)
				&& HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) != 0)
		{
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);
			return;
		}
	}

	if(GPIO_Pin == GPIO_PIN_10)	// output ON/OFF button pressed
	{
		if(OutputState == OutputON)
		{
			TIM2->CNT = 0xFFFFFFFF - 10000;	// set TIM2 PWM to "safe" pulseOFF area
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
			OutputState = OutputOFF;
		}
		else if(OutputState == OutputOFF)
		{
			TIM2->CNT = 0xFFFFFFFF - 10000;	// set TIM2 PWM to "safe" pulseOFF area
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			OutputState = OutputON;
		}

		TIM3->CNT = 0; 	// reset switching counter


		HAL_NVIC_SetPendingIRQ(TIM3_IRQn); 			// force TIM3 interrupt to update TIM2 PWM settings
		OLED_Update_Display_Case(OLEDDisplayState);	// this also works as a debouncing delay
	}

	if(GPIO_Pin == GPIO_PIN_6)	// next case button pressed (PC6)
	{
		TIM2->CNT = 0xFFFFFFFF - 10000;	// avoid missing timer set point and extra pulse generation by setting CNT just before overflow (outside PWM high area and close to overflow for short delay - about 125 us)
		TIM3->CNT = 0;						// avoid missing timer set point (and overflow) when ARR register is changed
		NextFrequency();
		for(int i = 0; i < 100000; i++); 	// about 14 ms debounce
	}

	if(GPIO_Pin == GPIO_PIN_8)				// previous case down button pressed (PC8)
	{
		TIM2->CNT = 0xFFFFFFFF - 10000;	// avoid missing timer set point and extra pulse generation by setting CNT just before overflow (outside PWM high area and close to overflow for short delay - about 125 us)
		TIM3->CNT = 0;							// avoid timer overflow when ARR register is changed
		PreviousFrequency();
		for(int i = 0; i < 100000; i++); 	// about 14 ms debounce
	}

	if(GPIO_Pin == GPIO_PIN_13)	// Frequency calibration button (PC13)
	{
		FrequencyCalibrationModeFlag = true;
	}


	if(GPIO_Pin == GPIO_PIN_11)	// Pulse adjustment button (PA11)
	{
		PulseOffsetAdjustmentModeFlag = true;
	}

	if(GPIO_Pin == GPIO_PIN_5)	// Encoder button  (PC5)
	{
		if(CurrentCase == Leonardo_Burst_18u_10kHz || CurrentCase == Leonardo_Burst_20u_10kHz)
		{
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		}
	}

	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin); // clear interrupt manually again (it is done already in library function before this callback function (and here in some cases) but interrupt can occur again when this function is running).
}

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
