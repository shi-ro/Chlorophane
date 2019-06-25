#pragma once
class CNE_Oscillation
{
	float min, max, step;
	bool positive;
public:
	float current;
	CNE_Oscillation(float, float, float, float, bool);
	void update();
	~CNE_Oscillation();
};

