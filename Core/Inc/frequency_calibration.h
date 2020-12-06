/*
 * frequency_calibration.h
 *
 *  Created on: Dec 5, 2020
 *      Author: Raf
 */

#ifndef INC_FREQUENCY_CALIBRATION_H_
#define INC_FREQUENCY_CALIBRATION_H_

void InitCalibrationEEPROM(void);
void SaveCalibrationInEEPROM(uint64_t Data);
void CalibrationModeFromISR(void);

#endif /* INC_FREQUENCY_CALIBRATION_H_ */
