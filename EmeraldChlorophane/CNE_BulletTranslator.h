#pragma once

#include <stack>
#include <string>

#include "CNE_Point.h"
#include "CNE_Vector.h"
#include "CNE_TranslatedBullet.h";

using namespace std;

class CNE_BulletTranslator
{
	stack<CNE_TranslatedBullet*> bullets;
public:
	CNE_BulletTranslator();
	void addBulletToTranslate(float, float, string, CNE_Vector*);
	CNE_TranslatedBullet* getNextBullet();
	CNE_Vector* createTimedPointToPointVector(CNE_Point*, CNE_Point*, long);
	bool hasNextBullet();
	~CNE_BulletTranslator();
};

