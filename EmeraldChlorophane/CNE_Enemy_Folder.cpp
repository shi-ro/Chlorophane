#include "CNE_Enemy_Folder.h"

#include "CNE_Math.h"

CNE_Enemy_Folder::CNE_Enemy_Folder(CNE_BulletTranslator* t, string pattern, float speed, CNE_ResourceManager* m) : CNE_ParabolicEnemy(pattern, "e_paper2", speed, m) {
	preparingToFire = true;
	translator = t;
	readyToFire = false;
	shotTimer = new CNE_Time();
	shotTimer->start();
}

int CNE_Enemy_Folder::update(long ms) {
	CNE_ParabolicEnemy::update(ms);
	if (shotTimer->getTime().count() > 170000) {
		CNE_Point* ptr_p1 = new CNE_Point(x, y);
		CNE_Point* ptr_p2 = new CNE_Point(x, y + 300);
		CNE_Vector* vec = translator->createTimedPointToPointVector(ptr_p2, ptr_p1, 70000);
		delete ptr_p1;
		delete ptr_p2;
		translator->addBulletToTranslate(x, y, "e_bullet3", vec); // fire a bullet via the translator 
		shotTimer->stop();
		shotTimer->reset();
		shotTimer->start();
	}
	return 0;
}

CNE_Enemy_Folder::~CNE_Enemy_Folder() {
	delete shotTimer;
}
