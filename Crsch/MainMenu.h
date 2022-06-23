#pragma once
#include <SDL.h>
#include "GMainMenu.h"
#include <string>
#include "MainGameClass.h"
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
	MainGameClass* start();
	bool nameInput();
	void setName(std::string);
	~MainMenu();
};

