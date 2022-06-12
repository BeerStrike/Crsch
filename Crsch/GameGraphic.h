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
	SDL_Texture* gun[2];
	double* raycastRes;
public:
	GameGraphic(SDL_Renderer* , int , int );
	bool load() override;
	void print() override;
	void setRaycastRes(double*);
	void turnMinimap(Map*,Player*,std::vector<Enemy*>&);
	~GameGraphic();
};

