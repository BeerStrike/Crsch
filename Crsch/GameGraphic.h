#pragma once
#include "BasicGraphic.h"
#include "Map.h"
#include "Minimap.h"
#include "Player.h"
#include <vector>
#include "Enemy.h"
#include <list>
class GameGraphic :
    public BasicGraphic
{
private:
	Minimap* minimap;
	SDL_Texture* walltext1;
	SDL_Texture* walltext2;
	SDL_Texture* background;
	SDL_Texture* enemytext;
	SDL_Texture* gun[2];
	double* raycastRes;
	double* enemycastRes;
	std::vector<Enemy*>& enemies;
public:
	GameGraphic(SDL_Renderer*  , int , int,std::vector<Enemy*>& );
	bool load() ;
	void print() override;
	bool victory();
	void setRaycastRes(double*);
	void setEnemycastRes(double*);
	void turnMinimap(Map*,Player*,std::vector<Enemy*>&);
	~GameGraphic();
};

