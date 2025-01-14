#include <SDL.h>
#include <SDL_ttf.h>
#include <cmath>
#include "MainMenu.h"
#include "MainGameClass.h"
#include <SDL_image.h>
#include <fstream>

int main(int argc, char* argv[])
{
	int W,  H;
	std::ifstream fin("resolution.txt");
	fin >> W;
	fin >> H;
	fin.close();
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Err SLD_Init: %s", SDL_GetError());
		return 1;
	}
	SDL_Window* window = SDL_CreateWindow("Flanders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
	if (!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Err create window: %s", SDL_GetError());
		return 1;
	}
	SDL_Renderer* ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!ren)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Err create render: %s", SDL_GetError());
		return 1;
	}
	if (TTF_Init() < 0) {
		printf("Err load TTF library");
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Err IMG_Init: %s", SDL_GetError());
		return 1;
	}
	SDL_Surface* img=SDL_LoadBMP("Textures/title.bmp");
	if (!img) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
		return 1;
	}

	SDL_Texture* title = SDL_CreateTextureFromSurface (ren, img);
	SDL_FreeSurface(img);
	SDL_Rect dstrect = { 0, 0, W, H };
	SDL_Event event;
	bool quit = false;
	SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderCopy(ren, title, NULL, &dstrect);
	SDL_RenderPresent(ren);
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONDOWN)
				quit = true;
			else if (event.type == SDL_QUIT) {
				SDL_DestroyTexture(title);
				return false;
			}
		}
		SDL_Delay(100);
	}
	SDL_DestroyTexture(title);
	MainMenu* mnu=MainMenu::load(ren, W, H);
	if (!mnu) 
		return 1;
	while (true) {
		MainGameClass* game = mnu->start();
		if (game) {
			delete mnu;
			if (!game->start())
				return 1;
			else {
				mnu = MainMenu::load(ren, W, H);
				mnu->setName(game->getName());
				delete game;
			}
		}
		else return 0;
	}
	return 0;
}