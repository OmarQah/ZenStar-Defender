#ifndef COLLISION_H
#define HAL_COLLISION_H

#include "entities.h"

// Handles collisions between player bullets and enemies
void handlePlayerBulletCollisions(Bullet bullets[], int numBullets,
                                  Entity enemies[], int numEnemies,
                                  Explosion explosions[], int numExplosions);

// Handles collisions between enemy bullets and the player
void handleEnemyBulletCollisions(EnemyBullet enemyBullets[], int numEnemyBullets,
                                 Entity* player,
                                 Explosion explosions[], int numExplosions);

#endif
