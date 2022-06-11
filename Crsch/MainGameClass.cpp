#include "MainGameClass.h"

MainGameClass::MainGameClass(SDL_Renderer* render, int wight, int height) :Grf(render, wight, height)
{
}

bool MainGameClass::load()
{
    return Grf.load();
}

bool MainGameClass::start()
{
	bool quit = false;
	SDL_Event event;
	while (!quit) {

		while (SDL_PollEvent(&event)) {
		}
	}
	return true;
}
