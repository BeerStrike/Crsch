#pragma once
#include "BasicGraphic.h"
#include <string>
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
	GMainMenu(SDL_Renderer*, int, int, SDL_Texture*, SDL_Texture*, SDL_Texture*, TTF_Font*);
public:
	static GMainMenu* load(SDL_Renderer* render, int wigth, int heigth);
	void print() override;
	void printInfo();
	void printScores();
	void printNameInput(std::string);
	void printLvLchose();
	void setOnBtn(int n);
	~GMainMenu();
};

