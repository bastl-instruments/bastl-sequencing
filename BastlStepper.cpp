/*
 * BastlStepper.cpp
 *
 *  Created on: Sep 4, 2014
 *      Author: bastl
 */

#include "BastlStepper.h"

BastlStepper:: BastlStepper(void (*stepCallback)(), StepSwinger * _swinger) {
	stepCallback_ = stepCallback;
	swinger_ = _swinger;
}
