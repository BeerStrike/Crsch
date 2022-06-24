#include "MainMenu.h"
MainMenu::MainMenu(GMainMenu* gf) :Grf(gf), chzn(0), numBtn(5), myName("")
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
 void MainMenu::setName(std::string nme) {
	 myName = nme;
 }
 bool MainMenu::nameInput() {
	 SDL_Event event;
	 bool quit = false;
	 while (!quit) {
		 Grf->printNameInput(myName);
		 while (SDL_PollEvent(&event)) {
			 if (event.type == SDL_TEXTINPUT)  myName += event.text.text;
			 else if (event.type == SDL_KEYUP)
				 switch (event.key.keysym.sym) {
				 case SDLK_RETURN:
					 if(myName!="")
					 quit = true;
					 break;
				 case SDLK_BACKSPACE:
					 if (myName.length() != 0)
						 myName.pop_back();
					 break;
				 }
			 else 	if (event.type == SDL_QUIT)
				 return false;

		 }
		 SDL_Delay(100);
	 }
	 return true;
 }
 MainGameClass* MainMenu::start()
{
	SDL_Event event;
	bool quit = false;
	if (myName == "") {
		if (!nameInput())
			return nullptr;
	}
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
					case 0: {
						Grf->printLvLchose();
						bool q = false;
						while (!q) {
							while (SDL_PollEvent(&event)) {
								if (event.type == SDL_KEYDOWN)
									switch (event.key.keysym.sym) {
									case SDLK_1:
										return MainGameClass::load(Grf->getRen(), Grf->getWt(), Grf->getHt(), "maps/Level_1.txt", myName);
									case SDLK_2:
										return MainGameClass::load(Grf->getRen(), Grf->getWt(), Grf->getHt(), "maps/Level_2.txt", myName);
									case SDLK_3:
										return MainGameClass::load(Grf->getRen(), Grf->getWt(), Grf->getHt(), "maps/Level_3.txt", myName);
									case SDLK_4:
										return MainGameClass::load(Grf->getRen(), Grf->getWt(), Grf->getHt(), "maps/Level_4.txt", myName);
									case SDLK_5:
										return MainGameClass::load(Grf->getRen(), Grf->getWt(), Grf->getHt(), "maps/Level_5.txt", myName);
									}if (event.type == SDL_QUIT)
										q = quit = true;
							}
						}
					}
						break;
					case 1: {
						Grf->printScores();
						bool q = false;
						while (!q) {
							while (SDL_PollEvent(&event)) {
								if (event.type == SDL_KEYUP)		
									q = true;
								else if (event.type == SDL_QUIT)
									q = quit = true;
							}
						}
					}
						  break;
					case 2: {
						Grf->printInfo();
						bool q = false;
						while (!q) {
							while (SDL_PollEvent(&event)) {
								if (event.type == SDL_KEYUP)
									q=true;
								else if(event.type == SDL_QUIT)
									q = quit = true;
							}
						}
					}
						break;
					case 3:
						if (!nameInput())
						return nullptr;
						break;
					case 4:
						return nullptr;
					default:
						break;
					}
				}
			}
			else if (event.type == SDL_QUIT)
							quit = true;
		}
		SDL_Delay(10);
	}
	return nullptr;
}
