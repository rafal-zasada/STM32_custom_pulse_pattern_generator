/*
 * calibration.h
 *
 *  Created on: Dec 5, 2020
 *      Author: Raf
 */


#ifndef INC_CALIBRATION_H_
#define INC_CALIBRATION_H_

void InitCalibrationDataInFlash(void);
void SaveCalibrationFactorInFlash(void);
void Freq_Calibration_Mode(void);
void Pulse_Adjustment_Mode(void);
float Read_Frequency_Calibration_Factor_From_Flash(void);
float ReadPulseWidthOffsetFromFlash(void);


#endif /* INC_CALIBRATION_H_ */
