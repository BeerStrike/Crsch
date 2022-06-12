#pragma once
#include "BasicGraphic.h"
#include <SDL_ttf.h>
class GMainMenu:public BasicGraphic
{
private:
	SDL_Texture* fone;
	SDL_Texture* btn;
	SDL_Texture* onBtn;
	TTF_Font* gFont;
	int btnnum;
	int onNum;
	SDL_Texture* texts[8];
public:
	GMainMenu(SDL_Renderer* render, int wigth, int heigth);
	bool load() override;
	void print() override;
	void setOnBtn(int n);
};

