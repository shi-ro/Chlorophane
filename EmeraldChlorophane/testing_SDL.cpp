
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Chlorophane.h"
#include "CNE_Math.h"
#include "CNE_Point.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {

	// Init SDL things
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Event event;
	Chlorophane* c = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 3;
	}
	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
		printf("Window and renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return 3;
	}
	c = new Chlorophane(window, renderer, screenSurface, SCREEN_WIDTH, SCREEN_HEIGHT);

	while (1) {
		SDL_PollEvent(&event);
		
		// If exit command has been sent, exit
		if (event.type == SDL_QUIT) {
			break;
		}
		
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		
		int status = c -> update(&event);
		if (status == 1) {
			delete c;
			c = new Chlorophane(window, renderer, screenSurface, SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		
		SDL_RenderPresent(renderer);
	}

	/* else {
		screenSurface = SDL_GetWindowSurface(window);
		screenSurface = SDL_GetWindowSurface(window);
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
		SDL_UpdateWindowSurface(window);
		SDL_Delay(2000);
	} */

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}