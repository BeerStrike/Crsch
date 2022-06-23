#include "MainMenu.h"
MainMenu::MainMenu(GMainMenu* gf) :Grf(gf), chzn(0), numBtn(4), myName("")
{
}

 MainMenu* MainMenu::load(SDL_Renderer* render, int wight, int height)
{
	GMainMenu* grf = GMainMenu::load(render, wight, height);
	if (grf)
		return new MainMenu(grf);
	else
	return nullptr;
}

 MainMenu::~MainMenu()
 {
	 delete Grf;
 }

 MainGameClass* MainMenu::start()
{
	SDL_Event event;
	bool quit = false;
	if (myName == "") {
		while (!quit) {
			Grf->printNameInput(myName);
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_TEXTINPUT)  myName += event.text.text;
				else if (event.type == SDL_KEYUP )
					switch (event.key.keysym.sym) {
					case SDLK_RETURN:
						quit = true;
						break;
					case SDLK_BACKSPACE:
						if(myName.length()!=0)
						myName.pop_back();
						break;
					}
				else 	if (event.type == SDL_QUIT)
					return nullptr;

			}
		}
	}
	quit = false;
	while (!quit) {
		Grf->print();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_DOWN:
					if (chzn != numBtn-1) {
						chzn++;
						Grf->setOnBtn(chzn);
					}break;
				case SDLK_UP:
					if (chzn != 0) {
						chzn--;
						Grf->setOnBtn(chzn);
					}break;
				case SDLK_RETURN:
					switch (chzn)
					{
					case 0:
						return MainGameClass::load(Grf->getRen(),Grf->getWt(),Grf->getHt(),"maps/lvl1.txt",myName);
						break;
					case 1: {
						Grf->printScores();
						bool q = true;
						while (q) {
							while (SDL_PollEvent(&event)) {
								if (event.type == SDL_KEYDOWN)		
									q = false;
							}
						}
					}
						  break;
					case 2: {
						Grf->printInfo();
						bool q = true;
						while (q) {
							while (SDL_PollEvent(&event)) {
								if (event.type == SDL_KEYDOWN)
									q=false;
							}
						}
					}
						break;
					case 3:
						return nullptr;
					default:
						break;
					}
				}
			}
			else if (event.type == SDL_QUIT)
							quit = true;
		}
	}

}
