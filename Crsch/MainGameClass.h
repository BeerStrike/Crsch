#pragma once
#include <SDL.h>
#include <string>
#include "GameGraphic.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "Hotbar.h"
class MainGameClass
{
private:
	GameGraphic *Grf;
	Map* map;
	Player* player;
	std::vector<Enemy*> Enemies;
	std::string plname;
	double* raycastBufer;
	std::vector<double> enemycastBuf;
	Hotbar* htbr;
	MainGameClass(Map* , Player* , GameGraphic* ,Hotbar*, std::string);
	long long startTime;
public:
	static MainGameClass* load(SDL_Renderer*, int, int,std::string, std::string);
	bool win();
	bool start();
	bool pause();
	std::string getName();
	~MainGameClass();
};


