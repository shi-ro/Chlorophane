#pragma once

#include <string>

#include "CNE_Vector.h"

using namespace std;

class CNE_TranslatedBullet
{
public:
	float x, y;
	string id;
	CNE_Vector* vector;
	CNE_TranslatedBullet(float, float, string, CNE_Vector*);
	~CNE_TranslatedBullet();
};

