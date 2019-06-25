#include "CNE_ID.h"
#include <string> 

using namespace std;

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

CNE_ID::CNE_ID() {
	id = alphanum[rand() % stringLength];;
}

bool CNE_ID::operator==(const CNE_ID* other) {
	return other->id == id;
}

CNE_ID::~CNE_ID() {
}
