#include "MainGameClass.h"
#include <fstream>
MainGameClass::MainGameClass(Map*mp,Player*pl,GameGraphic* gr, std::string plnm):map(mp),player(pl),Grf(gr),plname(plnm),startTime(-1)
{
	raycastBufer = new double[static_cast<int>(2*gr->getWt()/5)];
}

MainGameClass* MainGameClass::load(SDL_Renderer*ren, int wt, int ht, std::string mapName,std::string plnme )
{
	GameGraphic *grf= GameGraphic::load(ren,wt,ht);
	Map* map = Map::load(mapName);
	if (!map) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open map: %s", mapName.c_str());
		return nullptr;
	}
	Player* pl = new Player(map);
	return new MainGameClass(map, pl, grf,plnme);
}

bool MainGameClass::win()
{
	int rec = time(nullptr) - startTime;
	std::ifstream fin("recs.txt");
	std::vector<std::string> buf;
	std::vector<int> rcs;
	std::vector<int>recs;
	std::string rd;
	std::string lvlname;
	getline(fin, lvlname, '\n');
	fin.get();
	fin.get();
	while (getline(fin, rd, ':')) {
		buf.push_back(rd);
		int rc;
		fin >> rc;
		rcs.push_back(rc);
		fin.get();
		fin.get();
		fin.get();
	}
	for (int i = 0; i < rcs.size(); i++)
		if (rcs[i] > rec) {
			rcs[i] = rec;
			buf[i] = plname;
			break;
		}
	fin.close();
	std::ofstream fout("recs.txt");
	fout << lvlname<<"\n";
	for (int i = 0; i < buf.size(); i++) {
		fout <<i+1<<")"<< buf[i] << ": " << rcs[i]<<std::endl;
	}
	fout.close();
	Grf->victory();
	bool q = true;
	SDL_Event event;
	while (q) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN)
				q = false;
			else if (event.type == SDL_QUIT)
				return false;
		}
	}
	return true;
}

bool MainGameClass::start()
{
	SDL_Event event;
    startTime = time(nullptr);
	Grf->setEnemycastRes(enemycastBuf);
	Grf->setRaycastRes(raycastBufer);
	bool quit = false;
	bool walkfrw = false;
	bool walkback = false;
	bool turnLeft = false;
	bool turnRight = false;
	unsigned int a;
	unsigned int b;
	while (!quit) {
		a = SDL_GetTicks();
		player->raycast(raycastBufer, Grf->getWt() / 5, Enemies);
		player->enemycast(enemycastBuf, Enemies);
		Grf->print();
		for (int i = 0; i < Enemies.size(); i++)
			if (Enemies[i]->goToPlayer(1)) {
				Grf->dead();
				bool q = true;
				while (q) {
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_KEYDOWN)
							q = false;
						else if (event.type == SDL_QUIT)
							return false;
					}
				}
				return true;
			}
				
		if (walkfrw)
			if (player->movefrw(3))
				return win();
		if (walkback)
			if (player->moveBack(3))
				return win();
		if(turnLeft)
			player->rotateLeft(0.05);
		if(turnRight)
			player->rotateRight(0.05);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_F5:
					Grf->turnMinimap(map,player,Enemies);
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
					Grf->shot();
					break;
				}
			}
			else if (event.type == SDL_QUIT)
				quit = true;
		}
		b = SDL_GetTicks() - a;
		SDL_Delay(20 > b  ? 20 - b : 0);
	}
	return false;
}

MainGameClass::~MainGameClass()
{
	for (Enemy* i : Enemies)
		if (i)
			delete i;
	delete player;
	delete map;
	delete Grf;
	delete[] raycastBufer;
}
