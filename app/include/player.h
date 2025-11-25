#pragma once
#include <SDL2/SDL.h>

class Player {
public:
    float x, y;
    float width = 40;
    float height = 40;

    Player(float startX, float startY);

    void update(float delta);
    void render(SDL_Renderer* renderer);
    void renderWithTexture(SDL_Renderer* renderer, SDL_Texture* tex);
};
