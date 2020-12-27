/*
 * calibration.h
 *
 *  Created on: Dec 5, 2020
 *      Author: Raf
 */


#ifndef INC_CALIBRATION_H_
#define INC_CALIBRATION_H_

void InitDataInFlashSettings(void);
void SaveCalibrationFactorInFlash(void);
void Freq_Calibration_Mode(void);
void Pulse_Adjustment_Mode(void);
float ReadFrequencyCalibrationFactorFromFlash(void);
float ReadPulseWidthOffsetFromFlash(void);


#endif /* INC_CALIBRATION_H_ */
