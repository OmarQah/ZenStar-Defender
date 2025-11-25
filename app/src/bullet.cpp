#include "bullet.h"

Bullet::Bullet(float startX, float startY, float velY)
    : x(startX), y(startY), velocityY(velY)
{
}

void Bullet::update(float delta) {
    y += velocityY * delta;   // SIGN matters now
}

void Bullet::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { (int)x, (int)y, 5, 10 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
