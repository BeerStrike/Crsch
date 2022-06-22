#pragma once
#include "BasicGraphic.h"
#include "Map.h"
#include "Player.h"
#include <vector>
#include "Enemy.h"
class Minimap :
    public BasicGraphic
{
private:
		Map& map;
		Player& player;
		std::vector<Enemy*>& enemies;
public:
	Minimap(SDL_Renderer*, int, int,Map&,Player&,std::vector<Enemy*>&);
	bool load() ;
	void print() override;
};

