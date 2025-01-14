#pragma once
#include "BasicGraphic.h"
#include "Player.h"
#include <SDL_ttf.h>
class Hotbar :
    public BasicGraphic
{
private:
    Hotbar(SDL_Renderer* , int , int, SDL_Texture*, SDL_Texture*, SDL_Texture*, SDL_Texture*, SDL_Texture*,Player*,TTF_Font*);
    SDL_Texture* backplate;
    SDL_Texture* gun;
    SDL_Texture* gunf;
    SDL_Texture* fl1;
    SDL_Texture* fl2;
    long long timer;
    long long shtdl;
    TTF_Font* gFont;
    Player* player;
public:
    static Hotbar* load(SDL_Renderer* , int , int,Player*);
    void print() override;
    void shot();
    ~Hotbar();
};

