#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Texture* bg;
    SDL_Texture* player;
    SDL_Texture* enemy;
    SDL_Texture* explosion;
} Assets;

int loadAssets(SDL_Renderer* renderer, Assets* assets);
void freeAssets(Assets* assets);

#endif
