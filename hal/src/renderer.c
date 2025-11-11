//renders the images, entities and even a healthbar
#include "renderer.h"

void renderScene(SDL_Renderer* renderer, Assets* assets,
                 Entity* player, Entity* enemies, int numEnemies,
                 Bullet* bullets, int numBullets,
                 EnemyBullet* enemyBullets, int numEnemyBullets,
                 Explosion* explosions, int numExplosions) {

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, assets->bg, NULL, NULL);

    // Player
    if (player->active) {
        SDL_Rect r = { (int)player->x, (int)player->y, player->w, player->h };
        SDL_RenderCopy(renderer, assets->player, NULL, &r);
    }

    // Enemies
    for (int i = 0; i < numEnemies; i++) {
        if (enemies[i].active) {
            SDL_Rect r = { (int)enemies[i].x, (int)enemies[i].y, enemies[i].w, enemies[i].h };
            SDL_RenderCopy(renderer, assets->enemy, NULL, &r);
        }
    }

    // Bullets
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (int i = 0; i < numBullets; i++) {
        if (bullets[i].active) {
            SDL_Rect b = { (int)bullets[i].x, (int)bullets[i].y, 4, 8 };
            SDL_RenderFillRect(renderer, &b);
        }
    }

    // Enemy bullets
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < numEnemyBullets; i++) {
        if (enemyBullets[i].active) {
            SDL_Rect b = { (int)enemyBullets[i].x, (int)enemyBullets[i].y, 4, 8 };
            SDL_RenderFillRect(renderer, &b);
        }
    }

    // Explosions
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for (int i = 0; i < numExplosions; i++) {
        if (explosions[i].active) {
            SDL_Rect dst = {
                (int)(explosions[i].x - explosions[i].radius),
                (int)(explosions[i].y - explosions[i].radius),
                (int)(explosions[i].radius * 2),
                (int)(explosions[i].radius * 2)
            };
            SDL_SetTextureAlphaMod(assets->explosion, (Uint8)explosions[i].alpha);
            SDL_RenderCopy(renderer, assets->explosion, NULL, &dst);
        }
    }
    SDL_SetTextureAlphaMod(assets->explosion, 255); // reset alpha

    // Health bar
    SDL_Rect healthBarBg = { 10, 10, 100, 20 };
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &healthBarBg);

    SDL_Rect healthBar = { 10, 10, 33 * player->health, 20 };
    if (player->health == 3)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    else if (player->health == 2)
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &healthBar);

    SDL_RenderPresent(renderer);
}
