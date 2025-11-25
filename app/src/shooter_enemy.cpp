#include "shooter_enemy.h"
#include <SDL2/SDL.h>

ShooterEnemy::ShooterEnemy(float startX, float startY)
    : x(startX), y(startY)
{
    fireCooldown = 1.0f;
}

void ShooterEnemy::update(float delta) {
    x += vx * delta;

    if (x < 10 || x > 600 - width)
        vx = -vx;

    if (fireCooldown > 0)
        fireCooldown -= delta;
}

bool ShooterEnemy::readyToFire() const {
    return fireCooldown <= 0.0f;
}

Bullet ShooterEnemy::fireBullet() {
    fireCooldown = 1.2f;

    Bullet b(x + width/2, y + height);
    b.velocityY = +250;
    return b;
}

bool ShooterEnemy::checkCollision(float bx, float by) {
    return (bx >= x && bx <= x + width &&
            by >= y && by <= y + height);
}

bool ShooterEnemy::checkPlayerCollision(float px, float py, float pw, float ph) {
    return !(px + pw < x || px > x + width ||
             py + ph < y || py > y + height);
}

void ShooterEnemy::render(SDL_Renderer* renderer) {
    SDL_Rect r = { (int)x, (int)y, (int)width, (int)height };
    SDL_SetRenderDrawColor(renderer, 255, 150, 0, 255);
    SDL_RenderFillRect(renderer, &r);
}

void ShooterEnemy::renderWithTexture(SDL_Renderer* renderer, SDL_Texture* tex) {
    SDL_Rect r = { (int)x, (int)y, (int)width, (int)height };
    SDL_RenderCopy(renderer, tex, NULL, &r);
}
