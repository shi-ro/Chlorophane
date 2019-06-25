#include "CNE_Oscillation.h"

CNE_Oscillation::CNE_Oscillation(float minVal, float maxVal, float start, float delta, bool pos) {
	min = minVal;
	max = maxVal;
	step = delta;
	current = start;
	positive = pos;
}

void CNE_Oscillation::update() {
	if (positive) {
		current += step;
	} else {
		current -= step;
	}
	if (current > max) {
		positive = false;
	}
	if (current < min) {
		positive = true;
	}
}

CNE_Oscillation::~CNE_Oscillation() {}
