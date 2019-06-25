#pragma once
#include "CNE_ParabolicEnemy.h"

#include <string>

#include "CNE_Time.h"
#include "CNE_GameObject.h"
#include "CNE_ResourceManager.h"
#include "CNE_BulletTranslator.h"

using namespace std;

class CNE_Enemy_Paper : public CNE_ParabolicEnemy
{
	CNE_GameObject* trackedObject;
	CNE_Time* shotTimer;
	CNE_BulletTranslator* translator;
	bool readyToFire, preparingToFire;
public:
	CNE_Enemy_Paper(CNE_BulletTranslator*, CNE_GameObject*, string, float, CNE_ResourceManager*);
	virtual int update(long);
	virtual ~CNE_Enemy_Paper();
};

