
#include <SDL.h>

#include <list>
#include <stack>
#include <string>
#include <iostream>

#include "CNE_ID.h"
#include "CNE_Math.h"
#include "CNE_Time.h"
#include "CNE_GameObject.h"
#include "CNE_ResourceManager.h"

using namespace std;

CNE_GameObject::CNE_GameObject(int xPos, int yPos, string aliasId, string imageId, CNE_ResourceManager* m) {
	x = xPos;
	y = yPos;
	alias = aliasId; 
	angle = 0;
	resourceId = "GameObject";
	id = new CNE_ID();
	manager = m;
	// now that manager is received and id is set time to try and load the object's surface
	changeSurface(imageId);
}

int CNE_GameObject::draw(long ms) {
	if (visible) {
		SDL_Rect* dr = new SDL_Rect();
		SDL_Point* center = new SDL_Point();
		center->x = w / 2;
		center->y = h / 2;
		dr->x = x - w / 2;
		dr->y = y - h / 2;
		dr->w = w;
		dr->h = h;
		SDL_SetTextureAlphaMod(currentTexture, opacity);
		SDL_RenderCopyEx(manager->renderer, currentTexture, NULL, dr, angle, center, SDL_FLIP_NONE);
		delete dr;
		delete center;
	}
	return 0;
}

void CNE_GameObject::changeSurface(string imageId) {
	if (manager->surfaceExists(imageId)) {
		SDL_Surface* surface = manager->getSurface(imageId);
		currentSurface = surface;
		w = currentSurface->w;
		h = currentSurface->h;
		currentTexture = SDL_CreateTextureFromSurface(manager->renderer, currentSurface);
	}
	else {
		// surface does not exist in manager, throw error
		string msg = string("Failed to create game object: surface with id [ ") + imageId + string(" ] does not exist.");
		throw invalid_argument(msg);
	}
}

// update method to be overriden
int CNE_GameObject::update(long delta) {
	return 0;
}

bool CNE_GameObject::operator==(const CNE_GameObject* other) {
	return this->id == other->id;
}

CNE_GameObject::~CNE_GameObject() {
	SDL_DestroyTexture(currentTexture);
	delete id;
}
