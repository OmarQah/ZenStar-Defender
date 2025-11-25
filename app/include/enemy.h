#pragma once
#include <SDL2/SDL.h>

class Enemy {
public:
    float x, y;
    float width = 40;
    float height = 40;

    Enemy(float startX, float startY);

    void reset();
    void render(SDL_Renderer* renderer);
    void renderWithTexture(SDL_Renderer* renderer, SDL_Texture* tex);

    bool checkCollision(float bx, float by);
};
