//this handles all the hits enemy and player hits
#include "collisions.h"

void handlePlayerBulletCollisions(Bullet bullets[], int numBullets,
                                  Entity enemies[], int numEnemies,
                                  Explosion explosions[], int numExplosions) {

    for (int i = 0; i < numBullets; i++) {
        if (!bullets[i].active) continue;

        for (int j = 0; j < numEnemies; j++) {
            if (enemies[j].active &&
                bullets[i].x > enemies[j].x &&
                bullets[i].x < enemies[j].x + enemies[j].w &&
                bullets[i].y > enemies[j].y &&
                bullets[i].y < enemies[j].y + enemies[j].h) {

                bullets[i].active = 0;
                enemies[j].active = 0;

                // Create explosion
                for (int k = 0; k < numExplosions; k++) {
                    if (!explosions[k].active) {
                        explosions[k].x = enemies[j].x + enemies[j].w / 2;
                        explosions[k].y = enemies[j].y + enemies[j].h / 2;
                        explosions[k].radius = 32;
                        explosions[k].alpha = 255;
                        explosions[k].active = 1;
                        break;
                    }
                }
            }
        }
    }
}

void handleEnemyBulletCollisions(EnemyBullet enemyBullets[], int numEnemyBullets,
                                 Entity* player,
                                 Explosion explosions[], int numExplosions) {

    for (int i = 0; i < numEnemyBullets; i++) {
        if (!enemyBullets[i].active) continue;

        if (player->active &&
            enemyBullets[i].x > player->x &&
            enemyBullets[i].x < player->x + player->w &&
            enemyBullets[i].y > player->y &&
            enemyBullets[i].y < player->y + player->h) {

            enemyBullets[i].active = 0;
            player->health--;

            // Create explosion
            for (int k = 0; k < numExplosions; k++) {
                if (!explosions[k].active) {
                    explosions[k].x = player->x + player->w / 2;
                    explosions[k].y = player->y + player->h / 2;
                    explosions[k].radius = 32;
                    explosions[k].alpha = 255;
                    explosions[k].active = 1;
                    break;
                }
            }

            if (player->health <= 0) {
                player->active = 0;
            }
        }
    }
}
