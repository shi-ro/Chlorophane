
#include "CNE_Circle.h"
#include "CNE_Point.h"

CNE_Circle::CNE_Circle(int xPos, int yPos, int radius) {
	x = xPos;
	y = yPos;
	r = radius;
}

bool CNE_Circle::intersects(CNE_Circle* ptr_other) {
	CNE_Point* ptr_p1 = &CNE_Point(this->x, this->y);
	CNE_Point* ptr_p2 = &CNE_Point(ptr_other->x, ptr_other->y);
	float dist = ptr_p1->distanceTo(ptr_p2);
	delete ptr_p1;
	delete ptr_p2;
	return dist < this->r + ptr_other->r;
}
