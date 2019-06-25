#pragma once

#include "CNE_GameObject.h"
#include "CNE_ResourceManager.h"

class CNE_SlashEffect : public CNE_GameObject 
{
	float delta;
public:
	CNE_SlashEffect(int, int, string, float, float, float, CNE_ResourceManager*);
	virtual int update(long);
	virtual ~CNE_SlashEffect();
};

