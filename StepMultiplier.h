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
	StepMultiplier(void (*stepCallback)(), StepSwinger * _swinger, unsigned char minTriggerTime, unsigned int timeUnitsPerSecond);
	virtual void doStep(unsigned int elapsedTimeUnits);
	virtual void update(unsigned int elapsedTimeUnits);
	void setMultiplication(unsigned char multiplication);
protected:
	unsigned int lastStepTimeUnits_;
	unsigned int lastSubStepTimeUnits_;
	unsigned int lastTriggeredStepTime_;
	unsigned char multiplication_;
	unsigned char stepsLeftToTrigger_;
	unsigned char stepBufferCount_;
	unsigned char minTriggerTimeUnits_;
	bool doStepTriggered_;
	bool anyStep_;

};

inline void StepMultiplier::setMultiplication(unsigned char multiplication) {
	multiplication_ = multiplication;
}

#endif /* STEPMULTIPLIER_H_ */
