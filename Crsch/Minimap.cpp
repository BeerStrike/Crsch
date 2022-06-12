#include "Minimap.h"
#include <cmath>
Minimap::Minimap(SDL_Renderer* render, int wigth, int heigth, Map& mp, Player& pl, std::vector<Enemy*>& ene) :BasicGraphic(render, wigth, heigth), map(mp), player(pl), enemies(ene)
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
	int yms = ht/size ;
	int xms = wt/size;
	for (int i = 0; i < size; i++) 
		for (int j = 0; j < size; j++) {
			SDL_Rect dstrect = {i*xms , j*yms, xms, yms };
			if (map.at(i, j) == 1)
				SDL_RenderFillRect(ren, &dstrect);
		
		}
	int r = 10;
	double plx = player.getX() * xms / 100;
	double ply = player.getY() * yms / 100;
	for (double t = 0; t < 2 * M_PI; t += 0.01)
		SDL_RenderDrawPoint(ren, plx -r+ r * std::cos(t) + r, ply+ r * std::sin(t));
	for (int i = 0; i < enemies.size(); i++) {
		for (double t = 0; t < 2 * M_PI; t += 0.01)
			SDL_RenderDrawPoint(ren, enemies[i]->getX() * xms / 100 - r + r * std::cos(t) + r, enemies[i]->getY() * yms / 100 + r * std::sin(t));
	}

	SDL_RenderDrawLine(ren, plx , ply,plx+ 20* cos(player.getAngle()),ply- 20* sin(player.getAngle()));
}
// * cos(player.getAngle()* sin(player.getAngle())