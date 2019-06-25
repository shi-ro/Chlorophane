#include "CNE_ParabolicEnemy.h"

#include <math.h>

#include "CNE_GameObject.h"
#include "CNE_ResourceManager.h"

CNE_ParabolicEnemy::CNE_ParabolicEnemy(string pattern, string id, float speed, CNE_ResourceManager* m) : CNE_GameObject(0, 0, "parabolic_enemy", id, m) {
	resourceId = "enemy";
	if (pattern == "leftCenterTop-leftSide") {
		setParabola(0, 200, 100, 200, -speed);
	}
	else if (pattern == "rightCenterTop-rightSide") {
		setParabola(480, 200, 100, 280, speed);
	}
	else if (pattern == "leftCenterTop-leftSide-low") {
		setParabola(0, 300, 100, 200, -speed);
	}
	else if (pattern == "rightCenterTop-rightSide-low") {
		setParabola(480, 300, 100, 280, speed);
	}
	else if (pattern == "leftTop-rightSide-low") {
		setParabola(480, 300, 530, 19.5, speed);
	}
	else if (pattern == "rightTop-leftSide-low") {
		setParabola(0, 300, 530, 460.4, -speed);
	}
	else if (pattern == "leftSide-rightSide-high") {
		setParabola(240, 100, 2000, -403, speed);
	}
	else if (pattern == "rightSide-leftSide-high") {
		setParabola(240, 100, 2000, -883, -speed);
	}
	else if (pattern == "leftSide-rightSide-low") {
		setParabola(240, 100, -2000, -403, speed);
	}
	else if (pattern == "rightSide-leftSide-low") {
		setParabola(240, 100, -2000, -883, -speed);
	}
	else if (pattern == "leftCenter-rightCenter-high") {
		setParabola(240, 150, 1, 223, speed);
	}
	else if (pattern == "rightCenter-leftCenter-high") {
		setParabola(240, 150, 1, 256, -speed);
	}
	else if (pattern == "leftCenter-rightCenter-low") {
		setParabola(240, 300, 1, 220, speed);
	}
	else if (pattern == "rightCenter-leftCenter-low") {
		setParabola(240, 300, 1, 260, -speed);
	}
	else {
		cout << "pattern not set";
	}
}

void CNE_ParabolicEnemy::setParabola(float pX, float pY, float pXS, float sX, float pD) {
	parabolaX = pX;
	parabolaY = pY;
	parabolaWidthScale = pXS;
	parabolaStartX = sX;
	parabolaMoveDelta = pD;
	parabolaCurrentX = sX;
}

CNE_ParabolicEnemy::CNE_ParabolicEnemy(int xPos, int yPos, string imageId, float pX, float pY, float pXS, float sX, float pD, CNE_ResourceManager* m) : CNE_GameObject(xPos, yPos, "parabolic_enemy",imageId, m) {
	parabolaX = pX; 
	parabolaY = pY;
	parabolaWidthScale = pXS;
	parabolaStartX = sX;
	parabolaMoveDelta = pD;
	parabolaCurrentX = sX;
	resourceId = "enemy";
}

int CNE_ParabolicEnemy::update(long ms) {
	parabolaCurrentX += parabolaMoveDelta;
	float parabolaCurrentY = -1 / (parabolaWidthScale)*pow(x - parabolaX, 2) + parabolaY;
	x = parabolaCurrentX;
	y = parabolaCurrentY;
	if (parabolaStartX < parabolaX) {
		if (parabolaCurrentX > parabolaX) {
			pastParabolaApex = true;
			destoryOffScreen = true;
		}
	} else {
		if (parabolaCurrentX < parabolaX) {
			pastParabolaApex = true;
			destoryOffScreen = true;
		}
	}
	return 0;
}

CNE_ParabolicEnemy::~CNE_ParabolicEnemy() {
}
