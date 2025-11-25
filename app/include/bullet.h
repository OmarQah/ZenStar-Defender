#pragma once
#include <SDL2/SDL.h>

class Bullet {
public:
    float x, y;
    float velocityY;   // NEW: bullet vertical speed (+down, -up)

    Bullet(float startX, float startY, float velY = -300.0f);  
    // velY default = upward (player bullets)

    void update(float delta);
    void render(SDL_Renderer* renderer);
};
