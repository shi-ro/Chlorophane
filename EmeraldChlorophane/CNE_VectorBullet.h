#pragma once

#include <string>
#include <iostream>

#include "CNE_Vector.h"
#include "CNE_GameObject.h"
#include "CNE_ResourceManager.h"

using namespace std;

class CNE_VectorBullet: public CNE_GameObject
{
	CNE_Vector* movementVector;
public:
	CNE_VectorBullet(int, int, CNE_Vector* , string, string, CNE_ResourceManager*);
	virtual int update(long);
	virtual ~CNE_VectorBullet();
};

