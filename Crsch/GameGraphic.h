#pragma once
#include "BasicGraphic.h"
#include "Map.h"
#include "Minimap.h"
#include "Player.h"
#include <vector>
#include "Enemy.h"
#include <list>
#include <SDL_ttf.h>
class GameGraphic :
    public BasicGraphic
{
private:
	Minimap* minimap;
	SDL_Texture* background;
	SDL_Texture* enemytext;
	SDL_Texture* gun;
	SDL_Texture* gunf;
	TTF_Font* gFont;
	double* raycastRes;
	std::vector<double>* enemycastRes;
	int timer;
	GameGraphic(SDL_Renderer* , int , int , SDL_Texture* , SDL_Texture* , SDL_Texture* , SDL_Texture*,TTF_Font*);
public:
	static GameGraphic* load(SDL_Renderer*, int, int);
	void print() override;
	bool victory(int);
	void shot();
	bool dead();
	void setRaycastRes(double*);
	void setEnemycastRes(std::vector<double>&);
	void turnMinimap(Map*,Player*,std::vector<Enemy*>&);
	~GameGraphic();
};

