#include "CNE_Enemy_Urchin.h"

#include <math.h>

#include "CNE_Math.h"

CNE_Enemy_Urchin::CNE_Enemy_Urchin(CNE_BulletTranslator* t, string pattern, int pie , float speed, CNE_ResourceManager* m) : CNE_ParabolicEnemy(pattern, "e_paper3", speed, m)
{
	pieces = pie;
	preparingToFire = true;
	translator = t;
	readyToFire = false;
	shotTimer = new CNE_Time();
	shotTimer->start();
}

int CNE_Enemy_Urchin::update(long ms) {
	CNE_ParabolicEnemy::update(ms);
	if (shotTimer->getTime().count() > 1000000) {
		CNE_Math* math = new CNE_Math();
		CNE_Point* ptr_p1 = new CNE_Point(x, y);
		CNE_Point* ptr_p2 = new CNE_Point(x, y + 300);
		for (float i = 0; i < M_PI * 2; i += M_PI * 2.0 / pieces) {
			CNE_Point* ptr_rot = math->dotRotate(ptr_p2, ptr_p1, i);
			CNE_Vector* vec = translator->createTimedPointToPointVector(  ptr_rot, ptr_p1, 200000);
			translator->addBulletToTranslate(x, y, "e_bullet1", vec);
			delete ptr_rot;
		}
		delete ptr_p1;
		delete ptr_p2;
		delete math;
		shotTimer->stop();
		shotTimer->reset();
		shotTimer->start();
	}
	return 0;
}

CNE_Enemy_Urchin::~CNE_Enemy_Urchin() {
	delete shotTimer;
}
