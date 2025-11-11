//this file defines the rendered images background jets and explosion animation all 
//found in the assets folder
#include "assets.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* surf = IMG_Load(path);
    if (!surf) {
        printf("Failed to load %s: %s\n", path, IMG_GetError());
        return NULL;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    return tex;
}

int loadAssets(SDL_Renderer* renderer, Assets* assets) {
    assets->bg = loadTexture("assets/spacetile.png", renderer);
    assets->player = loadTexture("assets/fighter.png", renderer);
    assets->enemy = loadTexture("assets/enemy.png", renderer);
    assets->explosion = loadTexture("assets/explosion.png", renderer);

    return (assets->bg && assets->player && assets->enemy && assets->explosion);
}

void freeAssets(Assets* assets) {
    if (assets->bg) SDL_DestroyTexture(assets->bg);
    if (assets->player) SDL_DestroyTexture(assets->player);
    if (assets->enemy) SDL_DestroyTexture(assets->enemy);
    if (assets->explosion) SDL_DestroyTexture(assets->explosion);
}
