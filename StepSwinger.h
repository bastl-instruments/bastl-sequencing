/*
 * StepSwinger.h
 *
 *  Created on: Aug 28, 2017
 *      Author: Martin Baar
 */

#ifndef STEPSWINGER_H_
#define STEPSWINGER_H_

#include "../bastl/StepSynchronizer.h"

/*
 * Computes length of the step when swing functionality is used
 */
class StepSwinger {
public:
	void init(StepSynchronizer * synchronizer_);
	void setSwing(unsigned char value);
	unsigned int getNextStepLength(unsigned int swinglessStepLength);
	bool swingUsed();

private:
	unsigned char swingValue;
	StepSynchronizer * synchronizer;
};

inline void StepSwinger::setSwing(unsigned char value) {
	swingValue = value;
}

inline void StepSwinger::init(StepSynchronizer * synchronizer_) {
	synchronizer = synchronizer_;
}
inline bool StepSwinger::swingUsed() {
	return swingValue != 0;
}

#endif /* STEPSWINGER_H_ */
