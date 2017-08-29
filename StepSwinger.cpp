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
		return ((swinglessStep * (10 + swingValue)) / 10) / 4;
	} else {
		return ((swinglessStep * (10 - swingValue)) / 10) / 4;
	}
}
