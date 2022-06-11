#pragma once
#include "BasicGraphic.h"
class GameGraphic :
    public BasicGraphic
{
public:
	GameGraphic(SDL_Renderer* , int , int );
	bool load() override;
	void print() override;
};

