#include "MainGameClass.h"

MainGameClass::MainGameClass(SDL_Renderer* render, int wight, int height) :Grf(render, wight, height)
{
	map = nullptr;
	player = nullptr;
}

bool MainGameClass::load(std::string mapName )
{
	map = Map::make(mapName);
	if (!map) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open map: %s", mapName.c_str());
		return false;
	}
	player = new Player(map);
    return Grf.load();
}

bool MainGameClass::start()
{
	SDL_Event event;
	bool quit = false;
	bool walkfrw = false;
	bool walkback = false;
	bool turnLeft = false;
	bool turnRight = false;
	while (!quit) {
		Grf.setRaycastRes(player->raycast(Grf.getWt()/5));
		Grf.print();
		if(walkfrw)
			player->movefrw(0.1);
		if(walkback)
			player->moveBack(0.1);
		if(turnLeft)
			player->rotateLeft(0.005);
		if(turnRight)
			player->rotateRight(0.005);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_F5:
					Grf.turnMinimap(map,player);
					break;
				case SDLK_UP:
					walkfrw = false;
					break;
				case SDLK_DOWN:
					walkback = false;
					break;
				case SDLK_LEFT:
					turnLeft = false;
					break;
				case SDLK_RIGHT:
					turnRight = false;
					break;
				}
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					walkfrw = true;
					break;
				case SDLK_DOWN:
					walkback = true;
					break;
				case SDLK_LEFT:
					turnLeft = true;
					break;
				case SDLK_RIGHT:
					turnRight = true;
					break;
				}
			}
		}
	}
	return false;
}

MainGameClass::~MainGameClass()
{
	if (player)
		delete player;
	if (map)
		delete map;
}
