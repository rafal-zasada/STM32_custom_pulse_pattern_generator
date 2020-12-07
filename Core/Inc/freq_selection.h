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
	unsigned int Freq_1;
	unsigned int Freq_2;
}CasesTypeDef;

void ApplyCalFactor(void);
void InitFrequency(void);
void FreqCaseUpFromISR(void);
void FreqCaseDownFromISR(void);


#endif /* INC_FREQ_SELECTION_H_ */
