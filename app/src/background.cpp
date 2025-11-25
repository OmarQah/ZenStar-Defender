#include "background.h"
#include "texture_manager.h"

Background::Background(SDL_Renderer* r)
{
    tex = TextureManager::load("app/assets/textures/spacetile.png", r);
}

void Background::update(float delta)
{
    scrollY += 50.0f * delta; // slow scroll
    if (scrollY > 480) scrollY = 0;
}

void Background::render(SDL_Renderer* r)
{
    if (!tex) return;

    SDL_Rect src = { 0, 0, 640, 480 };
    SDL_Rect dst1 = { 0, (int)scrollY, 640, 480 };
    SDL_Rect dst2 = { 0, (int)scrollY - 480, 640, 480 };

    SDL_RenderCopy(r, tex, &src, &dst1);
    SDL_RenderCopy(r, tex, &src, &dst2);
}
