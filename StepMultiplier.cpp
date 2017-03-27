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


StepMultiplier::StepMultiplier() : lastSubStepTimeUnits_(0), multiplication_(2), stepsLeftToTrigger_(0), stepBufferCount_(0) , minTriggerTimeUnits_(0), anyStep_(false), doStepTriggered_(false){
}

void StepMultiplier::init(unsigned char multiplication, unsigned int minTriggerTime, unsigned int timeUnitsPerSecond) {
	multiplication_ = multiplication;
	minTriggerTimeUnits_ = minTriggerTime;
	timeUnitsPerStep_ = (timeUnitsPerSecond * 60) / 120;
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
	doStepTriggered_ = true;
}

void StepMultiplier::update(unsigned int elapsedTimeUnits) {

	// If we have some forced trigger we need to process it here
	if (doStepTriggered_) {
		doStepTriggered_ = false;
		// If we get step that shall play we need to add this step
		stepsLeftToTrigger_ ++;
		// And also all that are left to be do
		stepBufferCount_ += stepsLeftToTrigger_;
		// And we need to mark that we shall play some more steps
		stepsLeftToTrigger_ = (multiplication_ - 1);
		//And we mark the time we played this step
		lastSubStepTimeUnits_ = elapsedTimeUnits;
	}
	// Otherwise we check if we should add some more steps to the buffer
	// using standard procedure
	else if (stepsLeftToTrigger_ != 0) {

		if ((elapsedTimeUnits - lastSubStepTimeUnits_) > (timeUnitsPerStep_ / multiplication_)) {

			stepBufferCount_++;
			unsigned char subStepsFromLastStep = (multiplication_ - stepsLeftToTrigger_); // this might happen to be negative !!!

			//Next line is handling problems with rounding so instead of increasing the last triggered
			//To the current time we increase it by division of the step multiplied by number of current step
			//That should have little better precision
			lastSubStepTimeUnits_ = lastStepTimeUnits_ + ((timeUnitsPerStep_ * subStepsFromLastStep) / multiplication_);
			stepsLeftToTrigger_--;

		}
	}

	//And here we trigger steps if there are some and the time from last step is lower then
	//Minimum distance in between steps that could be set by public setter
	if ((stepBufferCount_ > 0) &&
		((elapsedTimeUnits - lastTriggeredStepTime_) > minTriggerTimeUnits_)) {
		if (stepCallback_ != 0) {
			stepCallback_();
		}
		lastTriggeredStepTime_ = elapsedTimeUnits;
		stepBufferCount_--;
	}
	closerToNextStep_ = (elapsedTimeUnits - lastTriggeredStepTime_) > (minTriggerTimeUnits_ / 2);
}
