#pragma once

#include <string>

#include "CNE_GameObject.h"
#include "CNE_ResourceManager.h"

using namespace std;

class CNE_ParabolicEnemy : public CNE_GameObject
{
	float parabolaX, parabolaY, parabolaWidthScale, parabolaStartX, parabolaMoveDelta, parabolaCurrentX;
	bool pastParabolaApex;
public:
	CNE_ParabolicEnemy(string, string, float, CNE_ResourceManager*);
	void setParabola(float, float, float, float, float);
	CNE_ParabolicEnemy(int, int, string, float, float, float, float, float, CNE_ResourceManager*);
	virtual int update(long);
	virtual ~CNE_ParabolicEnemy();
};

