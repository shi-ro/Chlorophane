#include "CNE_Enemy_Boss1.h"

#include "CNE_Math.h";

CNE_Enemy_Boss1::CNE_Enemy_Boss1(CNE_BulletTranslator* t, CNE_ResourceManager* m) : CNE_GameObject(240, -100, "boss1", "e_boss1", m) {
	translator = t; 
	health = 5000;
	resourceId = "enemy";
	shotTimer = new CNE_Time();
}

int CNE_Enemy_Boss1::update(long ms) {
	if (state == 0) {
		y += 1;
		if (y > 120) {
			state = 1;
			shotTimer->start();
		}
	} else if (state == 1 && shotTimer->getTime().count() > 1000000) {
		CNE_Math* math = new CNE_Math();
		CNE_Point* ptr_p1 = new CNE_Point(x, y);
		CNE_Point* ptr_p2 = new CNE_Point(x, y + 50);
		for (float i = 0; i < M_PI * 2; i += M_PI * 2.0 / math->random(10, 30)) {
			CNE_Point* ptr_rot = math->dotRotate(ptr_p2, ptr_p1, i);
			CNE_Vector* vec = translator->createTimedPointToPointVector(ptr_rot, ptr_p1, 50000);
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
	else if (state == 1 && health < 2500 && health > 1000 && shotTimer->getTime().count() > 500000) {
		CNE_Math* math = new CNE_Math();
		CNE_Point* ptr_p1 = new CNE_Point(x, y);
		CNE_Point* ptr_p2 = new CNE_Point(x, y + 50);
		alt = !alt;
		float randomNum = math->random(10, 30);
		for (float i = 0; i < M_PI * 2; i += M_PI * 2.0 / randomNum) {
			CNE_Point* ptr_rot = math->dotRotate(ptr_p2, ptr_p1, i + (alt ? M_PI / randomNum : M_PI * 2.0 / randomNum));
			CNE_Vector* vec = translator->createTimedPointToPointVector(ptr_rot, ptr_p1, 50000);
			translator->addBulletToTranslate(x, y, math->random(1, 10)>5 ? "e_bullet1" : "e_bullet2", vec);
			delete ptr_rot;
		}
		delete ptr_p1;
		delete ptr_p2;
		delete math;
		shotTimer->stop();
		shotTimer->reset();
		shotTimer->start();
	}
	else if (state == 1 && health < 1000 && shotTimer->getTime().count() > 700000) {
		CNE_Math* math = new CNE_Math();
		CNE_Point* ptr_p1 = new CNE_Point(x, y);
		CNE_Point* ptr_p2 = new CNE_Point(x, y + 50);
		float randomNum = math->random(10, 30);
		alt = !alt;
		for (float i = 0; i < M_PI * 2; i += M_PI * 2.0 / randomNum) {
			CNE_Point* ptr_rot = math->dotRotate(ptr_p2, ptr_p1, i + (alt ? M_PI/ randomNum : M_PI*2.0/randomNum));
			CNE_Vector* vec = translator->createTimedPointToPointVector(ptr_rot, ptr_p1, 50000);
			translator->addBulletToTranslate(x, y, "e_bullet2", vec);
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

CNE_Enemy_Boss1::~CNE_Enemy_Boss1()
{
}
