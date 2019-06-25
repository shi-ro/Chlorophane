#include "CNE_Enemy_Paper.h"

#include "CNE_Time.h"
#include "CNE_Math.h"
#include "CNE_Point.h"
#include "CNE_GameObject.h"
#include "CNE_ResourceManager.h"
#include "CNE_BulletTranslator.h"

CNE_Enemy_Paper::CNE_Enemy_Paper(CNE_BulletTranslator* t, CNE_GameObject* track, string pattern, float speed, CNE_ResourceManager* m) : CNE_ParabolicEnemy(pattern, "e_paper1", speed, m) {
	preparingToFire = true;
	translator = t;
	trackedObject = track;
	readyToFire = false;
	shotTimer = new CNE_Time();
	shotTimer->start();
}

int CNE_Enemy_Paper::update(long ms) {
	CNE_ParabolicEnemy::update(ms);
	if (shotTimer->getTime().count() > 3000000) {
		CNE_Point* ptr_p1 = new CNE_Point(x, y);
		CNE_Math* math = new CNE_Math();
		CNE_Point* ptr_p2 = new CNE_Point(trackedObject->x + math->random(-40, 40), trackedObject->y + math->random(-40, 40));
		CNE_Vector* vec = translator->createTimedPointToPointVector(ptr_p2, ptr_p1, 200000);
		delete ptr_p1;
		delete ptr_p2;
		delete math;
		translator->addBulletToTranslate(x, y, "e_bullet2", vec); // fire a bullet via the translator 
		shotTimer->stop();
		shotTimer->reset();
	}
	return 0;
}

CNE_Enemy_Paper::~CNE_Enemy_Paper() {
	delete shotTimer;
}
