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

void ApplyCalFactor(void);
void InitFrequency(void);
void FreqCaseUpFromISR(void);
void FreqCaseDownFromISR(void);


#endif /* INC_FREQ_SELECTION_H_ */
