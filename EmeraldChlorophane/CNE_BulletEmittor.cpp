#include "CNE_BulletEmittor.h"

#include "CNE_Time.h"
#include "CNE_Point.h"
#include "CNE_Vector.h"
#include "Chlorophane.h"
#include "CNE_GameObject.h"
#include "CNE_TranslatedBullet.h"
#include "CNE_BulletTranslator.h"

CNE_BulletEmittor::CNE_BulletEmittor(CNE_BulletTranslator* t, float xPos, float yPos, CNE_GameObject* focus, float toFocus, CNE_Vector* fVector, bool track, bool single, bool burst, int burstAmt, float sDelay, float bDelay, float rDelay, float speed, float rand, CNE_ResourceManager* m) : CNE_GameObject(xPos, yPos, "emitter", "empty", m) {
	translator = t;
	if (focus != NULL) {
		focusObject = focus;
		trackFocusObject = track;
		timeToFocus = toFocus;
		CNE_Point* ptr_p1 = new CNE_Point(xPos, yPos);
		CNE_Point* ptr_p2 = new CNE_Point(focus->x, focus->y);
		fireVector = createTimedPointToPointVector(ptr_p1, ptr_p2, timeToFocus);
		delete ptr_p1;
		delete ptr_p2;
	}
	if (fVector != NULL) {
		fireVector = fVector;
	}
	singleShot = single;
	burstShot = burst;
	if (burstShot) {
		burstNumber = burstAmt;
		burstDelay = bDelay;
	}
	startDelay = sDelay;
	if (!singleShot) {
		repeatDelay = rDelay;
	}
	fireSpeed = speed;
	randomization = rand;
	mainTimer = new CNE_Time();
}

CNE_Vector* CNE_BulletEmittor::createTimedPointToPointVector(CNE_Point* p1, CNE_Point* p2, long ms) {
	float distance = p1->distanceTo(p2);
	float updatesForMovement = ms / 1000;
	float dx = p1->x - p2->x;
	float dy = p1->y - p2->y;
	return new CNE_Vector(dx / updatesForMovement, dy / updatesForMovement);
}

int CNE_BulletEmittor::update(long ms) {
	if (readyingNextShot && !burstFinished && mainTimer->getTime().count() > burstDelay) {
		shotReady = true;
	}
	else {
		if (readyingNextShot && mainTimer->getTime().count() > repeatDelay) {
			shotReady = true;
		}
	}
	if (firstUpdate) {
		mainTimer->start();
		firstUpdate = false;
	}
	if (!executedStartDelay && mainTimer->getTime().count() > startDelay) {
		executedStartDelay = true;
	}
	if (executedStartDelay && shotReady) {
		if (trackFocusObject) {
			CNE_Point* ptr_p1 = new CNE_Point(x, y);
			CNE_Point* ptr_p2 = new CNE_Point(focusObject->x, focusObject->y);
			fireVector = createTimedPointToPointVector(ptr_p1, ptr_p2, timeToFocus);
			delete ptr_p1;
			delete ptr_p2;
		}
		cout << "firing bullet ... \n";
		translator->addBulletToTranslate(x, y, "e_bullet1", new CNE_Vector(fireVector->dx, fireVector->dy));
		if (burstShot) {
			currentBurstCount++;
			if (currentBurstCount >= burstNumber) {
				burstFinished = true;
			}
			mainTimer->stop();
			mainTimer->reset();
			mainTimer->start();
			readyingNextShot = true;
			shotReady = true;
		} else if (singleShot) {
			garbage = true;
		} else {
			mainTimer->stop();
			mainTimer->reset();
			mainTimer->start();
			readyingNextShot = true;
			shotReady = false;
		}
	}
	return 0;
}

CNE_BulletEmittor::~CNE_BulletEmittor() {
	delete mainTimer;
}