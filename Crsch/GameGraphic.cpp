#include "GameGraphic.h"

GameGraphic::GameGraphic(SDL_Renderer* render, int wigth, int heigth) :BasicGraphic(render, wigth, heigth)
{
}

bool GameGraphic::load()
{
    SDL_Surface* img = SDL_LoadBMP("Textures/wall.bmp");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load wall.bmp: %s", SDL_GetError());
       return false;
    }
    walltext1 = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    img = SDL_LoadBMP("Textures/wall2.bmp");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load wall2.bmp: %s", SDL_GetError());
        return false;
    }
    walltext2 = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
}

void GameGraphic::print()
{
    SDL_SetRenderDrawColor(ren, 0x40, 0x40, 0x40, 0xFF);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    if (raycastRes) {
        int cnt=0;
        for (int i = 0; i < wt / 5;i++) {
            int l = raycastRes[i] * ht;
            SDL_Rect dstrect = { cnt ,  ht / 2 - l, 10, 2*l };
            if(cnt%10==0)
                   SDL_RenderCopy(ren, walltext1, NULL, &dstrect);
            else
                SDL_RenderCopy(ren, walltext2, NULL, &dstrect);
           // SDL_SetRenderDrawColor(ren, (0x00+l)>0xff? 0xff: (0x00 + l), (0x00 + l) > 0xff ? 0xff : (0x00 + l), (0x00 + l) > 0xff ? 0xff : (0x00 + l), 0x00);
           // SDL_RenderFillRect(ren, &dstrect);
            cnt+=5;
        }
    }
    if (minimap)
        minimap->print();
    SDL_RenderPresent(ren);
}

void GameGraphic::setRaycastRes(double*rcres)
{
    if (raycastRes)
        delete raycastRes;
    raycastRes = rcres;
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
    if (raycastRes)
        delete raycastRes;
}
