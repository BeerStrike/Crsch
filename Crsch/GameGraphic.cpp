#include "GameGraphic.h"
#include <SDL_image.h>
GameGraphic::GameGraphic(SDL_Renderer* render, int wigth, int heigth, std::vector<Enemy*>& enm) :BasicGraphic(render, wigth, heigth),enemies(enm)
{
    walltext1 = walltext2 = background = nullptr;
    raycastRes = nullptr;
    minimap=nullptr;
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
    img = SDL_LoadBMP("Textures/background.bmp");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load background.bmp: %s", SDL_GetError());
        return false;
    }
    background = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    img = IMG_Load("Textures/gun.png");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load gun.png: %s", SDL_GetError());
        return false;
    }
    gun[0]= SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    img = IMG_Load("Textures/enemy.png");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load enemy.png: %s", SDL_GetError());
        return false;
    }
    enemytext = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
}

void GameGraphic::print()
{
    SDL_SetRenderDrawColor(ren, 0x40, 0x40, 0x40, 0xFF);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_Rect dstrect = { 0 ,  0, wt, ht };
    SDL_RenderCopy(ren, background, NULL, &dstrect);
    if (raycastRes) {
        int cnt=0;
        for (int i = 0; i < wt / 5;i++) {
            int l = raycastRes[i] * ht;
            SDL_Rect dstrect = { cnt ,  ht / 2 - l, 10, 2*l };
           // if(cnt%10==0)
          //         SDL_RenderCopy(ren, walltext1, NULL, &dstrect);
          //  else
           //     SDL_RenderCopy(ren, walltext2, NULL, &dstrect);
            SDL_SetRenderDrawColor(ren, 212*l / ht,153*l/ht , 113*l/ht,0xFF);
            SDL_RenderFillRect(ren, &dstrect);
            cnt+=5;
        }
    }
    if (enemycastRes[0] != -1) {
        SDL_Rect dstrect = { wt*enemycastRes[1] ,  ht / 2 - enemycastRes[0] * ht , 50, 2 * enemycastRes[0] * ht };
        SDL_RenderCopy(ren, enemytext, NULL, &dstrect);
    }
    SDL_RenderCopy(ren, gun[0], NULL, &dstrect);
    if (minimap)
        minimap->print();
    SDL_RenderPresent(ren);
}

bool GameGraphic::victory()
{
    SDL_Surface* img = SDL_LoadBMP("Textures/win.bmp");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load win.bmp: %s", SDL_GetError());
        return false;
    }
    SDL_Rect dstrect = { 0 ,  0, wt, ht };
    SDL_RenderCopy(ren, SDL_CreateTextureFromSurface(ren, img) , NULL, &dstrect);
    SDL_RenderPresent(ren);
    return true;
}

void GameGraphic::setRaycastRes(double*rcres)
{
    if (raycastRes)
        delete raycastRes;
    raycastRes = rcres;
}

void GameGraphic::setEnemycastRes(double*ecres)
{
    if (raycastRes)
        delete enemycastRes;
    enemycastRes = ecres;
}

void GameGraphic::turnMinimap(Map *mp,Player* pl,std:: vector<Enemy*>& enem)
{
    if (minimap) {
        delete minimap;
        minimap = nullptr;
    }
    else {
        minimap = new Minimap(ren, wt, ht, *mp,*pl,  enem);
    }
}

GameGraphic::~GameGraphic()
{
    if (minimap)
        delete minimap;
    if (raycastRes)
        delete raycastRes;
}
