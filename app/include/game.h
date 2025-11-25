#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <SDL2/SDL_mixer.h>


#include "player.h"
#include "enemy.h"
#include "shooter_enemy.h"
#include "bullet.h"

class Game {
public:
    Game(SDL_Renderer* renderer);
    ~Game();

    void update(float delta);
    void render();

private:
    SDL_Renderer* renderer;

    // ------------ TEXTURES ------------
    SDL_Texture* backgroundTexture = nullptr;
    SDL_Texture* playerTexture     = nullptr;
    SDL_Texture* enemyTexture      = nullptr;
    SDL_Texture* shooterTexture    = nullptr;
    SDL_Texture* heartTex = nullptr;
    SDL_Texture* explosionTex = nullptr;

    // ------------ BACKGROUND SCROLLING ------------
    float bgScrollY = 0.0f;

    // ------------ GAME OBJECTS ------------
    Player player;
    std::vector<Enemy> enemies;
    std::vector<ShooterEnemy> shooters;
    std::vector<Bullet> bullets;
    std::vector<Bullet> shooterBullets;

    struct Explosion {
        float x, y;
        float timer;
    };
    std::vector<Explosion> explosions;


    int playerLives = 3;

    // ------------ SPAWN TIMERS ------------
    float timeSinceShooterSpawn = 0.0f;

    // ------------ DAMAGE PAUSE ------------
    bool isPaused = false;
    float pauseTimer = 0.0f;
    void triggerPause();

    // ------------ HELPERS ------------
    bool checkPlayerCollision(const Enemy& e);
    void drawLives();

    Mix_Music* bgm = nullptr;

};
