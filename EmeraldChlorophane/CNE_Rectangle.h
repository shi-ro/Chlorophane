#pragma once
class CNE_Rectangle
{
	int x, y, width, height;
	float rx, ry, theta;
	bool rotated;
public:
	CNE_Rectangle(int, int, int, int, float);
	bool intersects(CNE_Rectangle*);
	~CNE_Rectangle();
};