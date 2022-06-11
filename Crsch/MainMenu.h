#pragma once
#include <SDL.h>
#include "GMainMenu.h"
class MainMenu
{
private:
	GMainMenu Grf;
	int chzn ;
	int numBtn;
public:
	MainMenu(SDL_Renderer* render, int wight, int height);
	bool load();
	bool start();
};

