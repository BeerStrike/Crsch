#pragma once
#include "BasicGraphic.h"
class GMainMenu:public BasicGraphic
{
private:
	SDL_Texture* fone;
	SDL_Texture* btn;
	SDL_Texture* onBtn;
	int btnnum;
	int onNum;
public:
	GMainMenu(SDL_Renderer* render, int wigth, int heigth);
	bool load() override;
	void print() override;
	void setOnBtn(int n);
};

