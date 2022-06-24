#include "Hotbar.h"
#include <SDL_image.h>
Hotbar::Hotbar(SDL_Renderer* ren, int wigth, int heigth,SDL_Texture* bp, SDL_Texture*gn, SDL_Texture*gf,Player* pl, TTF_Font* gfo):BasicGraphic(ren, wigth, heigth),backplate(bp), gun(gn), gunf(gf), timer(0),player(pl),gFont(gfo)
{
}

Hotbar* Hotbar::load(SDL_Renderer* ren, int wigth, int heigth,Player* pl)
{
	SDL_Surface* img = SDL_LoadBMP("Textures/backplate.bmp");
	if (!img) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load backplate.bmp: %s", SDL_GetError());
		return nullptr;
	}
	SDL_Texture* backplate = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
    img = IMG_Load("Textures/gun.png");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load gun.png: %s", SDL_GetError());
        return nullptr;
    }
    SDL_Texture* gun = SDL_CreateTextureFromSurface(ren, img);
    img = IMG_Load("Textures/gun2.png");
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load gun2.png: %s", SDL_GetError());
        return nullptr;
    }
    SDL_Texture* gunf = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    TTF_Font* gFont = TTF_OpenFont("Fonts/cs.ttf", 16);
    if (!gFont) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load font: %s", SDL_GetError());
        return nullptr;
    }
    return new Hotbar(ren,wigth,heigth,backplate,gun,gunf,pl,gFont);
}

void Hotbar::print()
{
    SDL_Rect dstrect = { 0, 0, wt, ht-50 };
    if (timer > 0) {
        SDL_RenderCopy(ren, gunf, NULL, &dstrect);
        timer--;
    }
    else {
        SDL_RenderCopy(ren, gun, NULL, &dstrect);
    }
	dstrect = { 0, ht - 50, wt, 50 };
	SDL_RenderCopy(ren, backplate, NULL, &dstrect);
    SDL_Surface* img = TTF_RenderUTF8_Solid(gFont, (u8"HP:  " + std::to_string(player->getHP())).c_str(),   { 0x00,0x00,0x00 });
    SDL_Texture* tx = SDL_CreateTextureFromSurface(ren, img);
    dstrect = {10,ht-40,70,25};
    SDL_RenderCopy(ren, tx, NULL, &dstrect);
    SDL_DestroyTexture(tx);
    SDL_FreeSurface(img);
}
void Hotbar::shot()
{
    timer = 5;
}

Hotbar::~Hotbar()
{
    SDL_DestroyTexture(gun);
    SDL_DestroyTexture(gunf);
	SDL_DestroyTexture(backplate);
    TTF_CloseFont(gFont);
}
