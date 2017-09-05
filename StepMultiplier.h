/*
 * StepMultiplier.h
 *
 *  Created on: Sep 4, 2014
 *      Author: bastl
 */

#ifndef STEPMULTIPLIER_H_
#define STEPMULTIPLIER_H_

#include "BastlStepper.h"

class StepMultiplier : public BastlStepper {
public:
	StepMultiplier(void (*stepCallback)(), StepSwinger * _swinger, unsigned int timeUnitsPerSecond);
	virtual void doStep(unsigned int elapsedTimeUnits);
	virtual void update(unsigned int elapsedTimeUnits);
	virtual void reset();
	void setMultiplication(unsigned char multiplication);
protected:
	unsigned int lastStepTimeUnits_;
	unsigned int lastSubStepTimeUnits_;
	unsigned char multiplication_;
	unsigned char stepsLeftToTrigger_;
	bool gotSyncStep_;
	bool anyStep_;
	bool gotStep_;
	unsigned char stepsReceived_;


};

inline void StepMultiplier::reset() {
	stepsReceived_ = 0;
}

inline void StepMultiplier::setMultiplication(unsigned char multiplication) {
	multiplication_ = multiplication;
}

#endif /* STEPMULTIPLIER_H_ */
