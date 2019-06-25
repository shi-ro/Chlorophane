#include "CNE_SlashEffect.h"



CNE_SlashEffect::CNE_SlashEffect(int xPos, int yPos, string imageId, float minAngle, float maxAngle, float speed, CNE_ResourceManager* m ) : CNE_GameObject(xPos, yPos, "slash_effect", imageId, m) {
	angle = minAngle + (rand() % static_cast<int>(maxAngle - minAngle + 1));
	delta = speed;
}

int CNE_SlashEffect::update(long ms) {
	w -= 0.5;
	h += 5/delta;
	if (w <= 0) {
		garbage = true;
		w = 0;
	}
	if (h <= 0) {
		garbage = true;
		h = 0;
	}
	return 0;
}

CNE_SlashEffect::~CNE_SlashEffect() {
}
