#pragma once
#include <SDL.h>
class BasicGraphic
{
protected:
	SDL_Renderer* ren;
	int wt; int ht;
	BasicGraphic(SDL_Renderer* render, int wigth, int heigth) {
		ren = render;
		wt = wigth;
		ht = heigth;
	}
public:
	virtual void print()=0;
	virtual ~BasicGraphic() {}
	int getWt() {
		return wt;
	}
	int getHt(){
		return ht;
	}
};

