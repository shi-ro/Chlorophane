#pragma once
class CNE_Circle
{
	int x, y, r;
public:
	CNE_Circle(int, int, int);
	bool intersects(CNE_Circle*);
};

