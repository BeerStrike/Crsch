#include "MainGameClass.h"
#include <fstream>
MainGameClass::MainGameClass(Map*mp,Player*pl,GameGraphic* gr):map(mp),player(pl),map(mp)
{
}

MainGameClass* MainGameClass::load(std::string mapName )
{
	Map* map = Map::load(mapName);
	if (!map) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open map: %s", mapName.c_str());
		return false;
	}
	Player* pl = new Player(map);
    return new MainGameClass()
}

bool MainGameClass::start()
{
	SDL_Event event;
	long long startTime = time(nullptr);
	bool quit = false;
	bool walkfrw = false;
	bool walkback = false;
	bool turnLeft = false;
	bool turnRight = false;
	unsigned int a;
	unsigned int b;
	while (!quit) {
		a = SDL_GetTicks();
		Grf.setRaycastRes(player->raycast(Grf.getWt()/5, Enemies));
		Grf.setEnemycastRes(player->enemycast(Grf.getWt() / 5, Enemies));
		Grf.print();
		for (int i = 0; i < Enemies.size(); i++)
			Enemies[i]->goToPlayer(0.1);
		bool fin = false;
		if (walkfrw)
			if (player->movefrw(0.2*b))
				fin =true;
		if (walkback)
			if (player->moveBack(0.2*b))
				fin= true;
		if (fin) {
			std::ofstream fout("recs.txt");
			fout << time(nullptr) - startTime;
			fout.close();
			Grf.victory();
			bool q = true;
			while (q) {
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_KEYDOWN)
						q = false;
				}
			}
			return true;
		}
		if(turnLeft)
			player->rotateLeft(0.003*b);
		if(turnRight)
			player->rotateRight(0.003*b);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_F5:
					Grf.turnMinimap(map,player,Enemies);
					break;
				case SDLK_UP:
					walkfrw = false;
					break;
				case SDLK_DOWN:
					walkback = false;
					break;
				case SDLK_LEFT:
					turnLeft = false;
					break;
				case SDLK_RIGHT:
					turnRight = false;
					break;
				case SDLK_ESCAPE: {
					SDL_MessageBoxData mbox;
					SDL_MessageBoxButtonData mboxButton[2];
					const SDL_MessageBoxColorScheme colorScheme =
					{
						{
							{ 200, 200, 200 },
							{   0,   0,   0 },
							{ 255, 255, 255 },
							{ 150, 150, 150 },
							{ 255, 255, 255 }
						}
					};
					mboxButton[0].buttonid = 0;
					mboxButton[0].flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT | SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
					mboxButton[0].text = "Continue";
					mboxButton[1].buttonid = 1;
					mboxButton[1].flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT | SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
					mboxButton[1].text = "Go to menu";
					mbox.flags = SDL_MESSAGEBOX_INFORMATION;
					mbox.window =NULL;
					mbox.title = "Pause";
					mbox.message = "Pause";
					mbox.numbuttons = 2;
					mbox.buttons = mboxButton;
					mbox.colorScheme = &colorScheme;
					int btnid=0;
					SDL_ShowMessageBox(&mbox, &btnid) ;
					if (btnid == 1)
						return true;

				}break;
				}
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					walkfrw = true;
					break;
				case SDLK_DOWN:
					walkback = true;
					break;
				case SDLK_LEFT:
					turnLeft = true;
					break;
				case SDLK_RIGHT:
					turnRight = true;
					break;
				case SDLK_LCTRL:
					player->shot(Enemies);
					break;
				}
			}
			else if (event.type == SDL_QUIT)
				quit = true;
		}
		b = SDL_GetTicks() - a;
		///SDL_Delay(10 - b > 0 ? 10 - b : 0);
	}
	return false;
}

MainGameClass::~MainGameClass()
{
	for (Enemy* i : Enemies)
		if (i)
			delete i;
	if (player)
		delete player;
	if (map)
		delete map;
}
