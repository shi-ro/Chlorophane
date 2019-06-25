
#include "CNE_Math.h"
#include "CNE_Rectangle.h"

CNE_Rectangle::CNE_Rectangle(int xPos, int yPos, int w, int h, float t) {
	x = xPos;
	y = yPos;
	width = w;
	height = h;
	if (t != 0.0f) {
		CNE_Point* ptr_p1 = &CNE_Point(x, y);
		CNE_Point* ptr_p2 = &CNE_Point(x, y);
		CNE_Point* ptr_p3 = CNE_Math().dotRotate(ptr_p1, ptr_p2, t);
		delete ptr_p1;
		delete ptr_p2;
		rx = ptr_p3->x;
		ry = ptr_p3->y;
		rotated = true;
		delete ptr_p3;
	}
}

bool CNE_Rectangle::intersects(CNE_Rectangle* other) {
	return true;
}

CNE_Rectangle::~CNE_Rectangle() {

}
