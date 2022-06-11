#include "GameGraphic.h"

GameGraphic::GameGraphic(SDL_Renderer* render, int wigth, int heigth) :BasicGraphic(render, wigth, heigth)
{
}

bool GameGraphic::load()
{
    return true;
}

void GameGraphic::print()
{
    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    if (minimap)
        minimap->print();
    SDL_RenderPresent(ren);
}

void GameGraphic::turnMinimap(Map *mp,Player* pl)
{
    if (minimap) {
        delete minimap;
        minimap = nullptr;
    }
    else {
        minimap = new Minimap(ren, wt, ht, *mp,*pl);
    }
}

GameGraphic::~GameGraphic()
{
    if (minimap)
        delete minimap;
}
