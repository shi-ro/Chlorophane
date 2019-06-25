#pragma once
#include <string>

using namespace std;

class CNE_ID
{
	string id;
public:
	CNE_ID();
	bool operator==(const CNE_ID*);
	~CNE_ID();
};

