/*
 * StepGenerator.h
 *
 *  Created on: Sep 5, 2014
 *      Author: bastl
 */

#ifndef STEPGENERATOR_H_
#define STEPGENERATOR_H_

#include "BastlStepper.h"

class StepGenerator : public BastlStepper {
public:
	StepGenerator(void (*_stepCallback)(), StepSwinger * _swinger);
	virtual void doStep(unsigned int elapsedTimeUnits);
	virtual void update(unsigned int elapsedTimeUnits);
	void setTimeUnitsPerStep(unsigned int timeUnits, unsigned int timeUnitsPerStepLeftovers);
private:
	unsigned int lastStepTimeUnits_;
	unsigned int nextStepInTimeUnits_;
	unsigned int timeUnitsPerStepLeftovers_;
	unsigned int leftovers_;
	bool started_;
};

inline void StepGenerator::setTimeUnitsPerStep(unsigned int timeUnits, unsigned int timeUnitsPerStepLeftovers) {
	timeUnitsPerStep_ = timeUnits;
	timeUnitsPerStepLeftovers_ = timeUnitsPerStepLeftovers;
}

#endif /* STEPGENERATOR_H_ */
