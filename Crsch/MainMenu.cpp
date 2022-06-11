#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* render, int wight, int height) :Grf(render, wight, height)
{
	chzn = 0;
	numBtn = 4;
}

bool MainMenu::load()
{
	return Grf.load();
}

bool MainMenu::start()
{
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		Grf.print();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_DOWN:
					if (chzn != numBtn-1) {
						chzn++;
						Grf.setOnBtn(chzn);
					}break;
				case SDLK_UP:
					if (chzn != 0) {
						chzn--;
						Grf.setOnBtn(chzn);
					}break;
				case SDLK_RETURN:
					switch (chzn)
					{
					case 0:
						return true;
					case 3:
						return false;
					default:
						break;
					}
				}
			}
		}
	}

}
