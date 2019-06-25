#pragma once

#include "CNE_Time.h"
#include "CNE_Point.h"
#include "CNE_Vector.h"
#include "CNE_VectorBullet.h";
#include "CNE_TranslatedBullet.h"
#include "CNE_BulletTranslator.h"

class CNE_BulletEmittor : public CNE_GameObject
{
	CNE_BulletTranslator* translator;
	CNE_Time* mainTimer;
	CNE_Vector* fireVector;
	CNE_GameObject* focusObject; 
	bool readyingNextShot, shotReady;
	bool trackFocusObject, singleShot, burstShot, firstUpdate, executedStartDelay, burstFinished;
	int burstNumber;
	int currentBurstCount;
	float startDelay, burstDelay, repeatDelay, fireSpeed, randomization, timeToFocus;

public:
	CNE_BulletEmittor(CNE_BulletTranslator*, float, float, CNE_GameObject*, float, CNE_Vector* , bool, bool, bool, int, float, float, float, float, float, CNE_ResourceManager*);
	virtual int update(long ms);
	CNE_Vector* createTimedPointToPointVector(CNE_Point*, CNE_Point*, long);
	virtual ~CNE_BulletEmittor();
};

