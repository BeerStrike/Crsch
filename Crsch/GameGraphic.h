#pragma once
#include "BasicGraphic.h"
#include "Map.h"
#include "Minimap.h"
#include "Player.h"
#include <list>
class GameGraphic :
    public BasicGraphic
{
private:
	Minimap* minimap;
	SDL_Texture* walltext1;
	SDL_Texture* walltext2;
	double* raycastRes;
public:
	GameGraphic(SDL_Renderer* , int , int );
	bool load() override;
	void print() override;
	void setRaycastRes(double*);
	void turnMinimap(Map*,Player*);
	~GameGraphic();
};

