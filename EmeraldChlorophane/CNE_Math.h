#pragma once
#include "CNE_Point.h"

static class CNE_Math
{
public:
	CNE_Math();
	static int random(int, int);
	static CNE_Point* dotRotate(CNE_Point*, CNE_Point*, float);
	static bool rectOverlap(float, float, float, float, float, float, float, float);
	static bool valueInRange(float, float, float);
	~CNE_Math();
};

