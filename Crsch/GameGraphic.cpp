#include "GameGraphic.h"
#include <SDL_image.h>
GameGraphic::GameGraphic(SDL_Renderer* render, int wigth, int heigth, SDL_Texture* bd, SDL_Texture* gn, SDL_Texture* gnf, SDL_Texture* en):BasicGraphic(render, wigth, heigth),background(bd),gun(gn),gunf(gnf),enemytext(en),timer(0),enemycastRes(nullptr),raycastRes(nullptr),minimap(nullptr)
{
}

GameGraphic* GameGraphic::load(SDL_Renderer*ren, int wt, int ht)
{
   
    SDL_Surface*  img = SDL_LoadBMP("Textures/background.bmp");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load background.bmp: %s", SDL_GetError());
        return nullptr;
    }
    SDL_Texture* background = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    img = IMG_Load("Textures/gun.png");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load gun.png: %s", SDL_GetError());
        return nullptr;
    }
    SDL_Texture* gun= SDL_CreateTextureFromSurface(ren, img);
    img = IMG_Load("Textures/gun2.png");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load gun2.png: %s", SDL_GetError());
        return nullptr;
    }
    SDL_Texture* gunf = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    img = IMG_Load("Textures/enemy.png");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load enemy.png: %s", SDL_GetError());
        return nullptr;
    }
    SDL_Texture* enemytext = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    return new GameGraphic(ren, wt, ht, background, gun, gunf, enemytext);

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
            int l = static_cast<int>(raycastRes[i] * ht);
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
      for(std::vector<double>::iterator i=(*enemycastRes).begin();i< (*enemycastRes).end();i+=2){
       SDL_Rect dstrect = {static_cast<int>((*i)*wt) , ht/2- static_cast<int>(ht / 2 * (*(i + 1))) , static_cast<int>(50*(*(i + 1))), static_cast<int>(ht*(*(i + 1))) };
        SDL_RenderCopy(ren, enemytext, NULL, &dstrect);
     }
    if (timer > 0) {
        SDL_RenderCopy(ren, gunf, NULL, &dstrect);
        timer--;
    }
    else {
        SDL_RenderCopy(ren, gun, NULL, &dstrect);
    }

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
    SDL_Texture* tx = SDL_CreateTextureFromSurface(ren, img);
    SDL_RenderCopy(ren, tx , NULL, &dstrect);
    SDL_RenderPresent(ren);
    SDL_DestroyTexture(tx);
    SDL_FreeSurface(img);
    return true;
}

void GameGraphic::shot()
{
    timer = 20;
}

bool GameGraphic::dead()
{
   SDL_Surface* img = SDL_LoadBMP("Textures/dead.bmp");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load dead.bmp: %s", SDL_GetError());
        return false;
    }
    SDL_Rect dstrect = { 0 ,  0, wt, ht };
    SDL_Texture* tx = SDL_CreateTextureFromSurface(ren, img);
    SDL_RenderCopy(ren, tx, NULL, &dstrect);
    SDL_RenderPresent(ren);
    SDL_DestroyTexture(tx);
    SDL_FreeSurface(img);
    return true;
}

void GameGraphic::setRaycastRes(double*rcres)
{
    raycastRes = rcres;
}

void GameGraphic::setEnemycastRes(std::vector<double> &ecres)
{

    enemycastRes = &ecres;
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
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(enemytext);
    SDL_DestroyTexture(gun);
    SDL_DestroyTexture(gunf);
}
