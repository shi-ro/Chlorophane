#include "CNE_RippleEffect.h"

CNE_RippleEffect::CNE_RippleEffect(float xPos, float yPos, float spd, CNE_ResourceManager* m) : CNE_GameObject(xPos, yPos, "ripple_effect", "d_ping", m) {
	speed = spd;
	w = 10;
	h = 10;
}

int CNE_RippleEffect::update(long ms) {
	opacity -= speed * 5;
	w += speed * 3;
	h += speed * 3;
	if (opacity < 0) {
		opacity = 0;
		garbage = true;
	}
	return 0;
}

CNE_RippleEffect::~CNE_RippleEffect() {
}
