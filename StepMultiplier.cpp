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
	if (anyStep_) {
		timeUnitsPerStep_ = elapsedTimeUnits - lastStepTimeUnits_;
	}
	lastStepTimeUnits_ = elapsedTimeUnits;
	anyStep_ = true;
	gotStep_ = true;
	gotSyncStep_ = (stepsReceived_ * multiplication_) % 8 == 0;
	stepsReceived_ = (stepsReceived_ + 1) % 8;
}

void StepMultiplier::update(unsigned int elapsedTimeUnits) {

	if (gotSyncStep_) {
		for (unsigned char stepNumber = 0; stepNumber <= stepsLeftToTrigger_; stepNumber++) {
			stepCallback_();
		}
		stepsLeftToTrigger_ = 0;
		lastSubStepTimeUnits_ = lastStepTimeUnits_;
	}
	if (gotStep_) {
		stepsLeftToTrigger_ += multiplication_;
		if (gotSyncStep_)
			stepsLeftToTrigger_--;
		gotStep_ = false;
	}
	gotSyncStep_ = false;

	//unsigned int timeFromLastStep = elapsedTimeUnits - lastSubStepTimeUnits_;
	unsigned int nextStepTime = swinger_->getNextStepLength((timeUnitsPerStep_ * 4) / (unsigned int)multiplication_);
	if ((stepsLeftToTrigger_ != 0) &&
		(elapsedTimeUnits - lastSubStepTimeUnits_ > nextStepTime)) {
		stepCallback_();
		stepsLeftToTrigger_--;
		lastSubStepTimeUnits_ += nextStepTime;
	}
	//Need to do something with this one
	//closerToNextStep_ = (elapsedTimeUnits - lastTriggeredStepTime_) > (minTriggerTimeUnits_ / 2);
}
