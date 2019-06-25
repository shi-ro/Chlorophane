#pragma once
#include <SDL.h>

#include <list>
#include <string>
#include <iostream>

#include "CNE_Time.h"
#include "CNE_ID.h"
#include "CNE_ResourceManager.h"

using namespace std;

class CNE_GameObject
{
	int updates;
	SDL_Texture* currentTexture;
	SDL_Surface* currentSurface;
	CNE_ResourceManager* manager;
public:
	float x, y, w, h;
	float opacity = 255;
	float health = 100;
	CNE_ID* id;
	bool visible = true;
	float angle;
	string alias;
	string resourceId;
	int drawLayer;
	bool destoryOffScreen;
	bool garbage;
	CNE_GameObject(int, int, string, string, CNE_ResourceManager*);
	int draw(long);
	virtual int update(long);
	void changeSurface(string);
	bool operator==(const CNE_GameObject*);
	virtual ~CNE_GameObject();
};

