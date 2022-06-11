#include <SDL.h>
#include <cmath>
#include "MainMenu.h"
#include "MainGameClass.h"
#define W 800
#define H 600

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return 1;
	SDL_Window* window = SDL_CreateWindow("PR5", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
	if (!window)
		return 1;
	SDL_Renderer* ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!ren)
		return 1;
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
	while (!quit) {
		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderCopy(ren, title, NULL, &dstrect);
		SDL_RenderPresent(ren);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
				quit = true;
		}
	}
	MainMenu mnu(ren, W, H);
	MainGameClass Game(ren, W, H);
	if (!mnu.load())
		return 1;
	if (mnu.start()) {
		Game.start();
	}
	else
		return 0;
	return 0;
}