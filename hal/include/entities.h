#ifndef ENTITIES_H
#define ENTITIES_H

#define MAX_ENEMIES 5
#define MAX_BULLETS 50
#define MAX_ENEMY_BULLETS 50
#define MAX_EXPLOSIONS 20
#define PLAYER_MAX_HEALTH 3

typedef struct {
    float x, y;
    int w, h;
    int active;
    int health;
} Entity;

typedef struct {
    float x, y;
    float speed;
    int active;
} Bullet;

typedef struct {
    float x, y;
    float speed;
    int active;
} EnemyBullet;

typedef struct {
    float x, y;
    float radius;
    float alpha;
    int active;
} Explosion;

// Initialization
void initPlayer(Entity* player);
void initEnemies(Entity enemies[], int numEnemies);
void initBullets(Bullet bullets[], int numBullets);
void initEnemyBullets(EnemyBullet bullets[], int numBullets);
void initExplosions(Explosion explosions[], int numExplosions);

// Updates
void updateBullets(Bullet bullets[], int numBullets);
void updateEnemyBullets(EnemyBullet bullets[], int numBullets);
void updateExplosions(Explosion explosions[], int numExplosions);

#endif
