#pragma once
#include <SDL.h>
#include <string>
#include "GameGraphic.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
class MainGameClass
{
private:
	GameGraphic Grf;
	Map* map;
	Player* player;
	std::vector<Enemy*> Enemies;
public:
	MainGameClass(SDL_Renderer*, int, int);
	bool load(std::string);
	bool start();
	~MainGameClass();
};

