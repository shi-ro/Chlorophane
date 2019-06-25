#include "CNE_BulletTranslator.h"

#include <stack>
#include <string>
#include <iostream>

#include "CNE_Point.h"
#include "CNE_Vector.h"
#include "CNE_TranslatedBullet.h";

using namespace std;

CNE_BulletTranslator::CNE_BulletTranslator() { }

void CNE_BulletTranslator::addBulletToTranslate(float x, float y, string id, CNE_Vector* v) {
	CNE_TranslatedBullet* ptr_tb = new CNE_TranslatedBullet(x, y, id, v);
	bullets.push(ptr_tb);
}

CNE_TranslatedBullet* CNE_BulletTranslator::getNextBullet() {
	CNE_TranslatedBullet* ptr_tb = bullets.top();
	bullets.pop();
	return ptr_tb;
}

CNE_Vector* CNE_BulletTranslator::createTimedPointToPointVector(CNE_Point* p1, CNE_Point* p2, long ms) {
	float distance = p1->distanceTo(p2);
	float updatesForMovement = ms / 1000;
	float dx = p1->x - p2->x;
	float dy = p1->y - p2->y;
	return new CNE_Vector(dx / updatesForMovement, dy / updatesForMovement);
}

bool CNE_BulletTranslator::hasNextBullet() {
	return !bullets.empty();
}

CNE_BulletTranslator::~CNE_BulletTranslator() {
}
