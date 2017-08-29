/*
 * StepDevider.h
 *
 *  Created on: Sep 4, 2014
 *      Author: bastl
 */

#ifndef STEPDEVIDER_H_
#define STEPDEVIDER_H_

#include "BastlStepper.h"

class StepDivider : public BastlStepper {
public:
	virtual void doStep(unsigned int elapsedTimeUnits);
	virtual void update(unsigned int elapsedTimeUnits){}
	void setDivision(unsigned char division);
	unsigned int getTimeSinceLastStep(unsigned int elapsedTimeUnits);
protected:
	unsigned char numberOfStepsToIgnore_;
	unsigned int lastStepTimeUnits_;
	unsigned char division_;
};

inline void StepDivider::setDivision(unsigned char division) {
	division_ = division;
}
#endif /* STEPDEVIDER_H_ */
