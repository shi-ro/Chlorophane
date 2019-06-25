#pragma once

#include "CNE_Time.h"
#include "CNE_ParabolicEnemy.h"
#include "CNE_BulletTranslator.h"

class CNE_Enemy_Urchin : public CNE_ParabolicEnemy
{
	CNE_Time* shotTimer;
	CNE_BulletTranslator* translator;
	bool readyToFire, preparingToFire;
	int pieces;
public:
	CNE_Enemy_Urchin(CNE_BulletTranslator*, string, int, float, CNE_ResourceManager*);
	virtual int update(long);
	virtual ~CNE_Enemy_Urchin();
};

