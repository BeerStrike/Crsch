#include "MainGameClass.h"

MainGameClass::MainGameClass(SDL_Renderer* render, int wight, int height) :Grf(render, wight, height)
{
	map = nullptr;
}

bool MainGameClass::load(std::string mapName )
{
	map = Map::make(mapName);
	if (!map) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open map: %s", mapName.c_str());
		return false;
	}
    return Grf.load();
}

bool MainGameClass::start()
{
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		Grf.print();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_F5:
					Grf.turnMinimap(map);
				}
			}
		}
	}
	return false;
}

MainGameClass::~MainGameClass()
{

	if (map)
		delete map;
}
