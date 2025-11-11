//runs the rendering aspect of the game
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>

#include "assets.h"
#include "input.h"
#include "entities.h"
#include "renderer.h"
#include "collisions.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Space Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    srand(time(NULL));

    // --- Load assets ---
    Assets assets;
    if (!loadAssets(renderer, &assets)) return -1;

    // --- Initialize entities ---
    Entity player;
    Entity enemies[MAX_ENEMIES];
    Bullet bullets[MAX_BULLETS];
    EnemyBullet enemyBullets[MAX_ENEMY_BULLETS];
    Explosion explosions[MAX_EXPLOSIONS];

    initPlayer(&player);
    initEnemies(enemies, MAX_ENEMIES);
    initBullets(bullets, MAX_BULLETS);
    initEnemyBullets(enemyBullets, MAX_ENEMY_BULLETS);
    initExplosions(explosions, MAX_EXPLOSIONS);

    int running = 1;
    SDL_Event event;
    const Uint8* keystate;
    int enemyFireTimer = 0;
    int canShoot = 1;

    while (running) {
        // --- Input ---
        processInput(&event, &keystate, &running);

        // --- Player movement ---
        if (keystate[SDL_SCANCODE_LEFT]) player.x -= 6;
        if (keystate[SDL_SCANCODE_RIGHT]) player.x += 6;
        if (keystate[SDL_SCANCODE_UP]) player.y -= 6;
        if (keystate[SDL_SCANCODE_DOWN]) player.y += 6;

        if (player.x < 0) player.x = 0;
        if (player.x + player.w > SCREEN_WIDTH) player.x = SCREEN_WIDTH - player.w;
        if (player.y < 0) player.y = 0;
        if (player.y + player.h > SCREEN_HEIGHT) player.y = SCREEN_HEIGHT - player.h;

        // --- Player shoot ---
        if (keystate[SDL_SCANCODE_SPACE] && canShoot) {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) {
                    bullets[i].x = player.x + player.w / 2 - 2;
                    bullets[i].y = player.y;
                    bullets[i].speed = -10;
                    bullets[i].active = 1;
                    canShoot = 0;
                    break;
                }
            }
        }
        if (!keystate[SDL_SCANCODE_SPACE]) canShoot = 1;

        // --- Update entities ---
        updateBullets(bullets, MAX_BULLETS);
        updateEnemyBullets(enemyBullets, MAX_ENEMY_BULLETS);
        updateExplosions(explosions, MAX_EXPLOSIONS);

        // --- Enemy shooting ---
        enemyFireTimer++;
        if (enemyFireTimer > 60) {
            enemyFireTimer = 0;
            for (int j = 0; j < MAX_ENEMIES; j++) {
                if (enemies[j].active) {
                    for (int k = 0; k < MAX_ENEMY_BULLETS; k++) {
                        if (!enemyBullets[k].active) {
                            enemyBullets[k].x = enemies[j].x + enemies[j].w / 2 - 2;
                            enemyBullets[k].y = enemies[j].y + enemies[j].h;
                            enemyBullets[k].speed = 6;
                            enemyBullets[k].active = 1;
                            break;
                        }
                    }
                }
            }
        }

        // --- Collisions ---
        handlePlayerBulletCollisions(bullets, MAX_BULLETS, enemies, MAX_ENEMIES,
                                     explosions, MAX_EXPLOSIONS);

        handleEnemyBulletCollisions(enemyBullets, MAX_ENEMY_BULLETS, &player,
                                    explosions, MAX_EXPLOSIONS);

        // If player is dead, exit
        if (!player.active) running = 0;

        // --- Render ---
        renderScene(renderer, &assets,
                    &player, enemies, MAX_ENEMIES,
                    bullets, MAX_BULLETS,
                    enemyBullets, MAX_ENEMY_BULLETS,
                    explosions, MAX_EXPLOSIONS);

        SDL_Delay(16);
    }

    // --- Cleanup ---
    freeAssets(&assets);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
