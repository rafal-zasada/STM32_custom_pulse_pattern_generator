/*
 * freq_selection.h
 *
 *  Created on: Nov 29, 2020
 *      Author: Raf
 */

#ifndef INC_FREQ_SELECTION_H_
#define INC_FREQ_SELECTION_H_

typedef struct
{
	unsigned int Freq1;
	unsigned int Freq2;
	unsigned int Pulse1;
	unsigned int Pulse2;
}CasesTypeDef;

#define OutputON 1
#define OutputOFF 0

void InitPatternGenerator(void);
void NextFrequency(void);
void PreviousFrequency(void);
void ScopeTriggerFromISR(void);
void UpdateCalibratedCasesArray(void);

#endif /* INC_FREQ_SELECTION_H_ */
