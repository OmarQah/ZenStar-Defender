#include "player.h"
#include "joystick_interface.h"

Player::Player(float startX, float startY)
    : x(startX), y(startY) {}

void Player::update(float delta) {
    JoystickDirection dir = joystick_read_direction();
    float speed = 200.0f;

    // Horizontal movement only
    switch (dir) {
        case JOY_LEFT:  x -= speed * delta; break;
        case JOY_UP_LEFT:  x -= speed * delta; break;
        case JOY_DOWN_LEFT:  x -= speed * delta; break;

        case JOY_RIGHT: x += speed * delta; break;
        case JOY_UP_RIGHT: x += speed * delta; break;
        case JOY_DOWN_RIGHT: x += speed * delta; break;
        
        default: break;
    }

    // boundaries
    if (x < 0) x = 0;
    if (x > 640 - width) x = 640 - width;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { (int)x, (int)y, (int)width, (int)height };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Player::renderWithTexture(SDL_Renderer* renderer, SDL_Texture* tex) {
    SDL_Rect rect = { (int)x, (int)y, (int)width, (int)height };
    SDL_RenderCopy(renderer, tex, NULL, &rect);
}
