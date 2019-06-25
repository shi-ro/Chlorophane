
#include <map>
#include <string>
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "CNE_ResourceManager.h"

using namespace std;

CNE_ResourceManager::CNE_ResourceManager(SDL_Window* ptr_window, SDL_Renderer* ptr_renderer) {
	screenSurface = SDL_GetWindowSurface(ptr_window);
	window = ptr_window;
	renderer = ptr_renderer;
}

CNE_ResourceManager::~CNE_ResourceManager() {
	map<string, SDL_Surface*>::iterator it;
	for (it = _surfaces.begin(); it != _surfaces.end(); it++) {
		SDL_FreeSurface(it->second);
	}
	_surfaces.clear();
}

void CNE_ResourceManager::setWindowSurface(SDL_Window* ptr_window) {
	screenSurface = SDL_GetWindowSurface(ptr_window);
}


SDL_Surface* CNE_ResourceManager::loadSurface(string id, string path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	_surfaces.insert(make_pair(id, loadedSurface));
	string msg = string("Loaded surface [ ") + id + string(" ] from [ ") + path + string(" ].");
	cout << msg << '\n';
	return loadedSurface;
}

SDL_Surface* CNE_ResourceManager::getSurface(string id) {
	return _surfaces.find(id)->second;
}

bool CNE_ResourceManager::surfaceExists(string id) {
	map<string, SDL_Surface*>::iterator it;
	for (it = _surfaces.begin(); it != _surfaces.end(); it++) {
		if (it->first == id) {
			return true;
		}
	}
	return false;
}

