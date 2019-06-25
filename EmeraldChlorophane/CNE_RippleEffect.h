#pragma once

#include "CNE_GameObject.h"

class CNE_RippleEffect : public CNE_GameObject
{
	float speed;
public:
	CNE_RippleEffect(float, float, float, CNE_ResourceManager*);
	virtual int update(long);
	virtual ~CNE_RippleEffect();
};

