#pragma once
#include <SDL.h>
#include "GameGraphic.h"
class MainGameClass
{
private:
	GameGraphic Grf;
public:
	MainGameClass(SDL_Renderer*, int, int);
	bool load();
	bool start();
};

