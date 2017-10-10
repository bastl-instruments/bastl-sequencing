/*
 * StepGenerator.cpp
 *
 *  Created on: Sep 5, 2014
 *      Author: bastl
 */

#include "StepGenerator.h"

//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

StepGenerator::StepGenerator(void (*_stepCallback)(), StepSwinger * _swinger) :
BastlStepper(_stepCallback, _swinger),
lastStepTimeUnits_(0), started_(false)
{
}

void StepGenerator::doStep(unsigned int elapsedTimeUnits) {

	//This is kind of sync method
	#ifdef DEBUG
	printf("StepGenerator::doStep - timeElapsedFromLast: %d , timeUnitsPerStep,: %d\n",
			(elapsedTimeUnits - lastStepTimeUnits_),
			timeUnitsPerStep_);
	#endif
	if (elapsedTimeUnits - lastStepTimeUnits_  < (timeUnitsPerStep_ / 3)) {
		lastStepTimeUnits_ = elapsedTimeUnits;
		#ifdef DEBUG
		printf("StepGenerator::doStep - Move this little forward! to: %d\n", lastStepTimeUnits_);
		#endif
	} else {
		lastStepTimeUnits_ = (elapsedTimeUnits - timeUnitsPerStep_) - 1;
		#ifdef DEBUG
		printf("StepGenerator::doStep - Move this little backward! to: %d\n", lastStepTimeUnits_);
		#endif
	}
	update(elapsedTimeUnits);
}

void StepGenerator::update(unsigned int elapsedTimeUnits) {
	if (!started_) {
		started_ = true;
		stepCallback_();
		nextStepInTimeUnits_ = swinger_->getNextStepLength(timeUnitsPerStep_ * 4);
		lastStepTimeUnits_ = elapsedTimeUnits;
	} else {
		if (elapsedTimeUnits - lastStepTimeUnits_  > nextStepInTimeUnits_) {
			lastStepTimeUnits_ += nextStepInTimeUnits_;
			leftovers_ += timeUnitsPerStepLeftovers_;
			lastStepTimeUnits_ += leftovers_ / 1000;
			leftovers_ = leftovers_ % 1000;
			nextStepInTimeUnits_ = swinger_->getNextStepLength(timeUnitsPerStep_ * 4);
			#ifdef DEBUG
			printf("StepGenerator::update - TRIGGER! elapsed: %d, timeUnitsPerStep: %d, currentStep %d\n", elapsedTimeUnits, timeUnitsPerStep_, lastStepTimeUnits_);
			#endif
			stepCallback_();
		}
		closerToNextStep_ = (elapsedTimeUnits - lastStepTimeUnits_) > (nextStepInTimeUnits_ / 2);
	}
}
