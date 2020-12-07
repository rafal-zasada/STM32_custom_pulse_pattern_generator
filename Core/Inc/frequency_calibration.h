/*
 * frequency_calibration.h
 *
 *  Created on: Dec 5, 2020
 *      Author: Raf
 */

#ifndef INC_FREQUENCY_CALIBRATION_H_
#define INC_FREQUENCY_CALIBRATION_H_

void InitCalibrationDataInFlash(void);
void SaveCalibrationFactorInFlash(uint64_t Data);
void CalibrationMode(void);
void ReadCalibrationDataFromFlash(float *CalibrationFactor);

#endif /* INC_FREQUENCY_CALIBRATION_H_ */
