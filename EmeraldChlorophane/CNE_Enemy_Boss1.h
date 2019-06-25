#pragma once

#include "CNE_Time.h"
#include "CNE_GameObject.h"
#include "CNE_BulletTranslator.h"

class CNE_Enemy_Boss1 : public CNE_GameObject
{
	CNE_Time* shotTimer;
	CNE_BulletTranslator* translator;
	bool readyToFire, preparingToFire;
	int state = 0;
	bool alt = true;
public:
	CNE_Enemy_Boss1(CNE_BulletTranslator*, CNE_ResourceManager*);
	virtual int update(long);
	virtual ~CNE_Enemy_Boss1();
};

