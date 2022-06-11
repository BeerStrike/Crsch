#pragma once
#include "BasicGraphic.h"
#include "Map.h"
#include "Minimap.h"
#include "Player.h"
class GameGraphic :
    public BasicGraphic
{
private:
	Minimap* minimap;
public:
	GameGraphic(SDL_Renderer* , int , int );
	bool load() override;
	void print() override;
	void turnMinimap(Map*,Player*);
	~GameGraphic();
};

