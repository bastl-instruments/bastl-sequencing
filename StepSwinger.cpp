/*
 * StepSwinger.cpp
 *
 *  Created on: Aug 28, 2017
 *      Author: martin
 */

#include <StepSwinger.h>

unsigned int StepSwinger::getNextStepLength(unsigned int swinglessStep) {
	bool longStep = ((synchronizer->getCurrentStepNumber() / 4) % 2) == 0;
	if (longStep) {
		return ((swinglessStep / 4) * (100 + (swingValue * 5))) / 100;
	} else {
		return ((swinglessStep / 4) * (100 - (swingValue * 5))) / 100;
	}
}
