#pragma once
#include "BasicGraphic.h"
class GEnemy:public BasicGraphic
{
private:
	SDL_Texture* myTexture;
public:
	GEnemy(SDL_Renderer*, int, int);
	 bool load() ;
	 void print() override;
};

