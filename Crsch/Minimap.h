#pragma once
#include "BasicGraphic.h"
#include "Map.h"
class Minimap :
    public BasicGraphic
{
private:
		Map& map;
public:
	Minimap(SDL_Renderer*, int, int,Map&);
	bool load() override;
	void print() override;
};

