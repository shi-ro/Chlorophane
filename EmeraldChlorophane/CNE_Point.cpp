#include "CNE_Point.h"
#include <math.h>

CNE_Point::CNE_Point(float xPos, float yPos) {
	x = xPos;
	y = yPos;
}

float CNE_Point::distanceTo(CNE_Point* ptr_other) {
	float dx = ptr_other->x - this->x;
	float dy = ptr_other->y - this->y;
	return sqrt(pow(dx, 2) + pow(dy, 2));
}