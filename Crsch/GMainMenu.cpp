#include "GMainMenu.h"
#include "SDL_ttf.h"
GMainMenu::GMainMenu(SDL_Renderer* render, int wigth, int heigth) :BasicGraphic(render, wigth, heigth)
{
	btnnum = 4;
	onNum = 0;
	gFont = nullptr;
}

bool GMainMenu::load()
{
	SDL_Surface* img = SDL_LoadBMP("Textures/fone.bmp");
	if (!img) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load fone.bmp: %s", SDL_GetError());
		return false;
	}
	fone = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	img = SDL_LoadBMP("Textures/menuButton.bmp");
	if (!img) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load menuButton.bmp: %s", SDL_GetError());
		return false;
	}
	btn= SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	img = SDL_LoadBMP("Textures/onMenuButton.bmp");
	if (!img) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load onMenuButton.bmp: %s", SDL_GetError());
		return false;
	}
	onBtn = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	gFont = TTF_OpenFont("Fonts/cs.ttf", 16);
	if (!gFont) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load font: %s", SDL_GetError());
		return false;
	}
	img = TTF_RenderUTF8_Solid(gFont,"Start game", { 0xff,0xff,0xff });
	texts[0]= SDL_CreateTextureFromSurface(ren, img);
	return true;
}

void GMainMenu::print()
{
	SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	SDL_Rect dstrect = { 0, 0, wt, ht };
	SDL_RenderCopy(ren, fone, NULL, &dstrect);
	for (int i = 0; i < btnnum; i++) {
		SDL_Rect dstrect = { (wt - 200) / 2, ht / 2 + 60 * i, 200, 50 };
		if(i==onNum)
			SDL_RenderCopy(ren, onBtn, NULL, &dstrect);
		else
			SDL_RenderCopy(ren, btn, NULL, &dstrect);
		SDL_RenderCopy(ren, texts[i], NULL, &dstrect);
	}
	SDL_RenderPresent(ren);
}

void GMainMenu::setOnBtn(int n)
{
	onNum = n;
}
