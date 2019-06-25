#pragma once

#include "CNE_Time.h"
#include "CNE_ParabolicEnemy.h"
#include "CNE_BulletTranslator.h"

class CNE_Enemy_Folder : public CNE_ParabolicEnemy
{
	CNE_Time* shotTimer;
	CNE_BulletTranslator* translator;
	bool readyToFire, preparingToFire;
public:
	CNE_Enemy_Folder(CNE_BulletTranslator*, string, float, CNE_ResourceManager*);
	virtual int update(long);
	virtual ~CNE_Enemy_Folder();
};

