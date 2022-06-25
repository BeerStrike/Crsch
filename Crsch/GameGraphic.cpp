#include "GameGraphic.h"
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
GameGraphic::GameGraphic(SDL_Renderer* render, int wigth, int heigth, SDL_Texture* bd, SDL_Texture* en,TTF_Font* fnt):BasicGraphic(render, wigth, heigth),background(bd),enemytext(en),enemycastRes(nullptr),raycastRes(nullptr),minimap(nullptr),gFont(fnt)
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
    img = IMG_Load("Textures/enemy.png");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load enemy.png: %s", SDL_GetError());
        return nullptr;
    }
    SDL_Texture* enemytext = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    TTF_Font* gFont = TTF_OpenFont("Fonts/cs.ttf", 16);
    if (!gFont) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load font: %s", SDL_GetError());
        return nullptr;
    }
    return new GameGraphic(ren, wt, ht, background, enemytext,gFont);

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
            int l = static_cast<int>(raycastRes[2*i] * ht);
            SDL_Rect dstrect = { cnt ,  ht / 2 - l, 10, 2*l };
            int c = static_cast<int>(raycastRes[2 * i + 1]);
            switch (c) {
            case 1:
                SDL_SetRenderDrawColor(ren, 212 * l / ht, 153 * l / ht, 113 * l / ht, 0xFF);
                break;
            case 9:
                SDL_SetRenderDrawColor(ren, 0xFF * l / ht, 0,0, 0xFF);
                break;
            case 7:
                SDL_SetRenderDrawColor(ren, 163 * l / ht, 142 * l / ht, 138 * l / ht, 0xFF);
                break;
            case 8:
                SDL_SetRenderDrawColor(ren,0 ,0, 0xFF * l / ht, 0xFF);
                break;
            case 6:
                SDL_SetRenderDrawColor(ren, 0xFF * l / ht, 0xFF* l / ht, 0, 0xFF);
                break;
            }
            SDL_RenderFillRect(ren, &dstrect);
            cnt+=5;
        }
    }
      for(std::vector<double>::iterator i=(*enemycastRes).begin();i< (*enemycastRes).end();i+=2){
       SDL_Rect dstrect = {static_cast<int>((*i)*wt) , ht/2- static_cast<int>(ht / 2 * (*(i + 1))) , static_cast<int>(150*(*(i + 1))), static_cast<int>(ht*(*(i + 1))) };
        SDL_RenderCopy(ren, enemytext, NULL, &dstrect);
     }
    if (minimap)
        minimap->print();
}

bool GameGraphic::victory(int rec)
{
    SDL_Surface* img = SDL_LoadBMP("Textures/win.bmp");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load win.bmp: %s", SDL_GetError());
        return false;
    }
    SDL_Rect dstrect = { 0 ,  0, wt, ht };

    SDL_Texture* tx = SDL_CreateTextureFromSurface(ren, img);
    SDL_RenderCopy(ren, tx , NULL, &dstrect);
    SDL_DestroyTexture(tx);
    SDL_FreeSurface(img);
    std::string r = u8"Ваш результат: " + std::to_string(rec) + u8" сек.";
    img = TTF_RenderUTF8_Solid(gFont, r.c_str(), { 0x00,0x00,0x00 });
    tx = SDL_CreateTextureFromSurface(ren, img);
    dstrect = { wt * 1 / 4,ht * 2 / 3,10 * static_cast<int>(r.length()),25 };
    SDL_RenderCopy(ren, tx, NULL, &dstrect);
    SDL_DestroyTexture(tx);
    SDL_FreeSurface(img);
    SDL_RenderPresent(ren);
    return true;
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
    TTF_CloseFont(gFont);
    SDL_DestroyTexture(enemytext);
}
