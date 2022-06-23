#include "GMainMenu.h"
#include "SDL_ttf.h"
#include <fstream>
#include <string>
GMainMenu::GMainMenu(SDL_Renderer* render, int wigth, int heigth, SDL_Texture* fne, SDL_Texture*fbtn, SDL_Texture*nbtn,TTF_Font *fnt) :BasicGraphic(render, wigth, heigth), btnnum(4), onNum(0),fone(fne),btn(fbtn),onBtn(nbtn),gFont(fnt)
{
	SDL_Surface * img;
	std::ifstream fin("strds.txt");
	char s[64];
	fin.getline(s, 64, '\n');
	img = TTF_RenderUTF8_Solid(gFont,s, { 0xff,0xff,0x00 });
	texts[0] = SDL_CreateTextureFromSurface(ren, img);
	fin >> s;
	img = TTF_RenderUTF8_Solid(gFont, s, { 0xff,0xff,0x00 });
	texts[1] = SDL_CreateTextureFromSurface(ren, img);
	fin >> s;
	img = TTF_RenderUTF8_Solid(gFont, s, { 0xff,0xff,0x00 });
	texts[2] = SDL_CreateTextureFromSurface(ren, img);
	fin >> s;
	img = TTF_RenderUTF8_Solid(gFont, s, { 0xff,0xff,0x00 });
	texts[3] = SDL_CreateTextureFromSurface(ren, img);
	fin.close();
}

 GMainMenu* GMainMenu::load(SDL_Renderer* ren, int wigth, int heigth)
{
	SDL_Surface* img = SDL_LoadBMP("Textures/fone.bmp");
	if (!img) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load fone.bmp: %s", SDL_GetError());
		return nullptr;
	}
	SDL_Texture *fone = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	img = SDL_LoadBMP("Textures/menuButton.bmp");
	if (!img) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load menuButton.bmp: %s", SDL_GetError());
		return nullptr;
	}
	SDL_Texture*	btn= SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	img = SDL_LoadBMP("Textures/onMenuButton.bmp");
	if (!img) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load onMenuButton.bmp: %s", SDL_GetError());
		return nullptr;
	}
	SDL_Texture*onBtn = SDL_CreateTextureFromSurface(ren, img);
	SDL_FreeSurface(img);
	TTF_Font*gFont = TTF_OpenFont("Fonts/cs.ttf", 16);
	if (!gFont) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load font: %s", SDL_GetError());
		return nullptr;
	}
	return new GMainMenu(ren, wigth, heigth, fone, btn, onBtn, gFont);
}

void GMainMenu::print()
{
	SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	SDL_Rect dstrect = { 0, 0, wt, ht };
	SDL_RenderCopy(ren, fone, NULL, &dstrect);
	for (int i = 0; i < btnnum; i++) {
		SDL_Rect dstrect = { (wt - 200) / 2, ht / 2 + 60 * i, 200, 50 };
		if(i==onNum)
			SDL_RenderCopy(ren, onBtn, NULL, &dstrect);
		else
			SDL_RenderCopy(ren, btn, NULL, &dstrect);
		SDL_RenderCopy(ren, texts[i], NULL, &dstrect);
	}
	SDL_RenderPresent(ren);
}

void GMainMenu::printInfo()
{
	std::ifstream fin("info.txt");
	char s[1024];
	int add = 0;
	SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0x00);
	SDL_Rect dstrect = { wt / 4, ht / 4 ,wt/2 , ht/2 };
	SDL_RenderFillRect(ren, &dstrect);
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	while(fin.getline(s, 1024, '\n')){
		SDL_Surface* img = TTF_RenderUTF8_Solid(gFont, s, { 0x00,0x00,0x00 });
		SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, img);
		SDL_Rect dstrect = { wt/4, ht / 4 +add*15,strlen(s)*10 , 20 };
		SDL_RenderCopy(ren, tex, NULL, &dstrect);
		SDL_FreeSurface(img);
		SDL_DestroyTexture(tex);
		add++;
		SDL_RenderPresent(ren);
	}

}
void GMainMenu::printScores()
{
	std::ifstream fin("recs.txt");
	char s[1024];
	int add = 0;
	SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0x00);
	SDL_Rect dstrect = { wt / 4, ht / 4 ,wt / 2 , ht / 2 };
	SDL_RenderFillRect(ren, &dstrect);
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	while (fin.getline(s, 1024, '\n')) {
		SDL_Surface* img = TTF_RenderUTF8_Solid(gFont, s, { 0x00,0x00,0x00 });
		SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, img);
		SDL_Rect dstrect = { wt / 4, ht / 4 + add * 15,strlen(s) * 10 , 20 };
		SDL_RenderCopy(ren, tex, NULL, &dstrect);
		SDL_FreeSurface(img);
		SDL_DestroyTexture(tex);
		add++;
		SDL_RenderPresent(ren);
	}

}

void GMainMenu::printNameInput(std::string nme)
{

	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Rect dstrect = { 0, 0, wt, ht };
	SDL_RenderCopy(ren, fone, NULL, &dstrect);
	dstrect = { wt * 1 / 4,ht * 2 / 3,wt / 2,20 };
	SDL_RenderFillRect(ren, &dstrect);
	SDL_Surface* img = TTF_RenderUTF8_Solid(gFont, nme.c_str(), { 0x00,0x00,0x00 });
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, img);
	dstrect = { wt * 1 / 4,ht * 2 / 3,10*static_cast<int>(nme.length()),20 };
	SDL_RenderCopy(ren, tex, NULL, &dstrect);
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(img);
	SDL_RenderPresent(ren);
}

void GMainMenu::setOnBtn(int n)
{
	onNum = n;
}

GMainMenu::~GMainMenu()
{
	SDL_DestroyTexture(fone);
	SDL_DestroyTexture(btn);
	SDL_DestroyTexture(onBtn);
	for (int i = 0; i < 8; i++)
		if (texts[i])
			SDL_DestroyTexture(texts[i]);
}
