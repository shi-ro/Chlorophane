#include "CNE_Math.h"

#include <math.h>
#include <iostream>

#include "CNE_Point.h"

#define PI 3.14159265

using namespace std;

CNE_Math::CNE_Math() {
}

int CNE_Math::random(int min, int max) {
	return min + (rand() % static_cast<int>(max - min + 1));
}

CNE_Point* CNE_Math::dotRotate(CNE_Point * ptr_r, CNE_Point * ptr_c, float t) {
	float xval = (ptr_r->x - ptr_c->x) * cos(t) - (ptr_r->y - ptr_c->y) * sin(t) + (ptr_c->x);
	float yval = (ptr_r->y - ptr_c->y) * cos(t) + (ptr_r->x - ptr_c->x) * sin(t) + (ptr_c->y);
	return new CNE_Point(xval, yval);
}

bool CNE_Math::valueInRange(float value, float min, float max) {
	return (value >= min) && (value <= max);
}

bool CNE_Math::rectOverlap(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) {
	bool xOverlap = valueInRange(Ax, Bx, Bx + Bw) ||
		valueInRange(Bx, Ax, Ax + Aw);
	bool yOverlap = valueInRange(Ay, By, By + Bh) ||
		valueInRange(By, Ay, Ay + Ah);
	return xOverlap && yOverlap;
}

CNE_Math::~CNE_Math() {
	
}
