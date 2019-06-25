#include "CNE_TranslatedBullet.h"

#include <string>

using namespace std;

CNE_TranslatedBullet::CNE_TranslatedBullet(float xPos, float yPos, string a, CNE_Vector* vec) {
	x = xPos;
	y = yPos;
	id = a;
	vector = vec;
}


CNE_TranslatedBullet::~CNE_TranslatedBullet() {
}
