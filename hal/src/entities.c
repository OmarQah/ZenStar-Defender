//defines the game aspects, players, enemies, bullets, explosions and handles updating them
#include "entities.h"

void initPlayer(Entity* player) {
    player->x = 400 - 32;
    player->y = 520;
    player->w = 64;
    player->h = 64;
    player->active = 1;
    player->health = PLAYER_MAX_HEALTH;
}

void initEnemies(Entity enemies[], int numEnemies) {
    for (int i = 0; i < numEnemies; i++) {
        enemies[i].x = 100 + i * 120;
        enemies[i].y = 100;
        enemies[i].w = 64;
        enemies[i].h = 64;
        enemies[i].active = 1;
    }
}

void initBullets(Bullet bullets[], int numBullets) {
    for (int i = 0; i < numBullets; i++) bullets[i].active = 0;
}

void initEnemyBullets(EnemyBullet bullets[], int numBullets) {
    for (int i = 0; i < numBullets; i++) bullets[i].active = 0;
}

void initExplosions(Explosion explosions[], int numExplosions) {
    for (int i = 0; i < numExplosions; i++) explosions[i].active = 0;
}

void updateBullets(Bullet bullets[], int numBullets) {
    for (int i = 0; i < numBullets; i++) {
        if (bullets[i].active) {
            bullets[i].y += bullets[i].speed;
            if (bullets[i].y < 0) bullets[i].active = 0;
        }
    }
}

void updateEnemyBullets(EnemyBullet bullets[], int numBullets) {
    for (int i = 0; i < numBullets; i++) {
        if (bullets[i].active) {
            bullets[i].y += bullets[i].speed;
            if (bullets[i].y > 600) bullets[i].active = 0; // SCREEN_HEIGHT
        }
    }
}

void updateExplosions(Explosion explosions[], int numExplosions) {
    for (int i = 0; i < numExplosions; i++) {
        if (explosions[i].active) {
            explosions[i].radius += 2.5f;
            explosions[i].alpha -= 15;
            if (explosions[i].alpha <= 0) explosions[i].active = 0;
        }
    }
}
