#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "assets.h"
#include "entities.h"

void renderScene(SDL_Renderer* renderer, Assets* assets,
                 Entity* player, Entity* enemies, int numEnemies,
                 Bullet* bullets, int numBullets,
                 EnemyBullet* enemyBullets, int numEnemyBullets,
                 Explosion* explosions, int numExplosions);

#endif
