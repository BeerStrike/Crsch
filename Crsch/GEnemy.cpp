#include "GEnemy.h"
#include <SDL_image.h>
GEnemy::GEnemy(SDL_Renderer* render, int wigth, int heigth) :BasicGraphic(render, wigth, heigth)
{
}

bool GEnemy::load()
{
    SDL_Surface* img = IMG_Load("Textures/enemy.png");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load gun.png: %s", SDL_GetError());
        return false;
    }
    myTexture = SDL_CreateTextureFromSurface(ren, img);
    return true;
}

void GEnemy::print()
{
}
