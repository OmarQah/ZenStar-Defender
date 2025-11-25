#include "enemy.h"
#include <cstdlib>

Enemy::Enemy(float startX, float startY)
    : x(startX), y(startY) {}

void Enemy::reset() {
    x = 50 + rand() % 540;
    y = -50 - (rand() % 150);
}

bool Enemy::checkCollision(float bx, float by) {
    return (bx >= x && bx <= x + width &&
            by >= y && by <= y + height);
}

void Enemy::render(SDL_Renderer* renderer) {
    SDL_Rect r = { (int)x, (int)y, (int)width, (int)height };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &r);
}

void Enemy::renderWithTexture(SDL_Renderer* renderer, SDL_Texture* tex) {
    SDL_Rect r = { (int)x, (int)y, (int)width, (int)height };
    SDL_RenderCopy(renderer, tex, NULL, &r);
}
