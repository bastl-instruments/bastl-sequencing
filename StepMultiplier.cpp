/*
 * StepMultiplier.cpp
 *
 *  Created on: Sep 4, 2014
 *      Author: bastl
 */

#include "StepMultiplier.h"

//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

StepMultiplier::StepMultiplier(void (*stepCallback)(), StepSwinger * _swinger, unsigned int timeUnitsPerSecond) : BastlStepper(stepCallback, _swinger) {
	timeUnitsPerStep_ = (timeUnitsPerSecond * 60) / 120;
	anyStep_ = false;
	gotStep_ = false;
	gotSyncStep_ = false;
	stepsReceived_ = 0;
	#ifdef DEBUG
	printf("StepMultiplier::init - Setting timeUnitsPerStep %d\n", timeUnitsPerStep_);
	#endif
}

void StepMultiplier::doStep(unsigned int elapsedTimeUnits) {

	// We just make sure main loop thread knows something has happened
	// and can process forced step
	anyStep_ = true;
	gotStep_ = true;
}

void StepMultiplier::update(unsigned int elapsedTimeUnits) {

	if (gotStep_) {
		gotStep_ = false;
		if (anyStep_) {
			timeUnitsPerStep_ = (elapsedTimeUnits - lastStepTimeUnits_) / multiplication_;
		}
		lastStepTimeUnits_ = elapsedTimeUnits;
		bool sync = (stepsReceived_ * multiplication_) % 8 == 0;
		stepsReceived_++;
		if (sync) {
			for (unsigned char stepNumber = 0; stepNumber <= stepsLeftToTrigger_; stepNumber++) {
				stepCallback_();
			}
			stepsLeftToTrigger_ = 0;
			lastSubStepTimeUnits_ = lastStepTimeUnits_;
		}
		stepsLeftToTrigger_ += multiplication_;
		if (sync)
			stepsLeftToTrigger_--;
	}
	unsigned int nextStepTime = swinger_->getNextStepLength(timeUnitsPerStep_ * 4);
	if ((stepsLeftToTrigger_ != 0) &&
		(elapsedTimeUnits - lastSubStepTimeUnits_ > nextStepTime)) {
		stepCallback_();
		stepsLeftToTrigger_--;
		lastSubStepTimeUnits_ += nextStepTime;
	}
	//Need to do something with this one
	closerToNextStep_ = (elapsedTimeUnits - lastSubStepTimeUnits_) > (nextStepTime / 2);
}
