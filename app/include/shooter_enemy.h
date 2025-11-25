#pragma once
#include <SDL2/SDL.h>
#include "bullet.h"

class ShooterEnemy {
public:
    float x, y;
    float width = 40;
    float height = 40;

    float vx = 80;
    float fireCooldown = 0.0f;

    ShooterEnemy(float startX, float startY);

    void update(float delta);

    Bullet fireBullet();
    bool readyToFire() const;

    void render(SDL_Renderer* renderer);
    void renderWithTexture(SDL_Renderer* renderer, SDL_Texture* tex);

    bool checkCollision(float bx, float by);
    bool checkPlayerCollision(float px, float py, float pw, float ph);
};
