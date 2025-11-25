#pragma once
#include <SDL2/SDL.h>

class Background {
public:
    Background(SDL_Renderer* r);
    void update(float delta);
    void render(SDL_Renderer* r);

private:
    SDL_Texture* tex;
    float scrollY = 0.0f;
};
