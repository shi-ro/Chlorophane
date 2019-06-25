#pragma once
class CNE_Point
{
public:
	float x, y;
	CNE_Point(float x, float y);
	float distanceTo(CNE_Point*);
};

