#pragma once
#include <SDL.h>
#include <map>
#include <string>

using namespace std;

class CNE_ResourceManager
{
private:
	map<string, SDL_Texture*> _textures;
	map<string, SDL_Surface*> _surfaces;
public:
	SDL_Surface* screenSurface;
	SDL_Window* window;
	SDL_Renderer* renderer;
	CNE_ResourceManager(SDL_Window*, SDL_Renderer*);
	~CNE_ResourceManager();
	void setWindowSurface(SDL_Window*);
	SDL_Surface* loadSurface(string, string);
	SDL_Surface* getSurface(string);
	bool surfaceExists(string);
};

