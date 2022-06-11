#include "Minimap.h"

Minimap::Minimap(SDL_Renderer* render, int wigth, int heigth,Map&mp) :BasicGraphic(render, wigth, heigth),map(mp)
{

}


bool Minimap::load()
{
	return true;
}

void Minimap::print()
{
	SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	int size = map.getSize();
	int yms = wt/size ;
	int xms = ht/size;
	for (int i = 0; i < size; i++) 
		for (int j = 0; j < size; j++) {
			SDL_Rect dstrect = {j*yms , i*xms, yms, xms };
			if (map.at(i, j) == 1)
				SDL_RenderFillRect(ren, &dstrect);
		
		}
}
