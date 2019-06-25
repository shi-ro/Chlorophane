#include "CNE_VectorBullet.h"

#include "CNE_Vector.h"
#include "CNE_GameObject.h"

CNE_VectorBullet::CNE_VectorBullet(int xPos, int yPos, CNE_Vector* ptr_vector, string aliasId, string imageId, CNE_ResourceManager* m) : CNE_GameObject(xPos, yPos, aliasId, imageId, m) {
	movementVector = ptr_vector;
	resourceId = "enemyBullet";
}

int CNE_VectorBullet::update(long delta) {
	x += movementVector->dx;
	y += movementVector->dy;
	return 0;
}

CNE_VectorBullet::~CNE_VectorBullet() {
	delete movementVector;
}
