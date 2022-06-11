#pragma once
#include <SDL.h>
class BasicGraphic
{
protected:
	SDL_Renderer* ren;
	int wt; int ht;
public:
	BasicGraphic(SDL_Renderer* render,	int wigth, int heigth) {
		ren = render;
		wt = wigth;
		ht = heigth;
	}
	virtual bool load() = 0;
	virtual void print()=0;
	virtual ~BasicGraphic() {}
};

