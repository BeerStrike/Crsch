#pragma once
#include "BasicGraphic.h"
#include "Map.h"
#include "Player.h"
class Minimap :
    public BasicGraphic
{
private:
		Map& map;
		Player& player;
public:
	Minimap(SDL_Renderer*, int, int,Map&,Player&);
	bool load() override;
	void print() override;
};

