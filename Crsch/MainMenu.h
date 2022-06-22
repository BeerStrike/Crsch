#pragma once
#include <SDL.h>
#include "GMainMenu.h"
#include <string>
class MainMenu
{
private:
	GMainMenu* Grf;
	int chzn ;
	int numBtn;
	MainMenu(GMainMenu*);
	std::string myName;
public:
	static MainMenu* load(SDL_Renderer* render, int wight, int height);
	bool start();
};

