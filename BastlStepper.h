/*
 * BastlStepper.h
 *
 *  Created on: Sep 4, 2014
 *      Author: bastl
 */

#ifndef BASTLSTEPPER_H_
#define BASTLSTEPPER_H_

#include "StepSwinger.h"

class BastlStepper {
public:
	BastlStepper (void (*stepCallback)(), StepSwinger * _swinger);
	unsigned int getTimeUnitsPerStep();
	bool isCloserToNextStep();
	virtual void doStep(unsigned int elapsedTimeUnits) = 0;
	virtual void update(unsigned int elapsedTimeUnits) = 0;
protected:
	unsigned int timeUnitsPerStep_;
	bool closerToNextStep_;
	void (*stepCallback_)();
	StepSwinger * swinger_;
};

inline unsigned int BastlStepper::getTimeUnitsPerStep() {
	return timeUnitsPerStep_;
}

inline bool BastlStepper::isCloserToNextStep() {
	return closerToNextStep_;
}

#endif /* BASTLSTEPPER_H_ */
