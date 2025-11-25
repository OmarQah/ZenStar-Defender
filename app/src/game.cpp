#include "game.h"
#include "led_interface.h"
#include "joystick_interface.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <cstdlib>

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Game::Game(SDL_Renderer* r)
    : renderer(r), player(320, 400)
{
    led_init();
    joystick_init();

    // -------------------------
    // AUDIO INITIALIZATION
    // -------------------------
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Mixer init error: %s\n", Mix_GetError());
    }

    bgm = Mix_LoadMUS("/home/kkw29/zenstar/app/assets/audio/maingamesound.wav");
    if (!bgm) {
        printf("Failed to load BGM: %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(bgm, -1);   // loop forever
    }

    playerLives = 3;

    timeSinceShooterSpawn = 0.0f;

    // ------------ LOAD TEXTURES ------------
    backgroundTexture = IMG_LoadTexture(renderer, "app/assets/textures/spacetile.png");
    playerTexture     = IMG_LoadTexture(renderer, "app/assets/textures/playership.png");
    enemyTexture      = IMG_LoadTexture(renderer, "app/assets/textures/enemyship1.png");
    shooterTexture    = IMG_LoadTexture(renderer, "app/assets/textures/enemyship2.png");
    heartTex = IMG_LoadTexture(renderer, "app/assets/textures/heart.png");
    // Load explosion texture
    explosionTex = IMG_LoadTexture(renderer, "app/assets/textures/explosion.png");

    if (!backgroundTexture || !playerTexture || !enemyTexture
        || !shooterTexture || !explosionTex || !heartTex) {
        SDL_Log("ERROR loading textures: %s", SDL_GetError());
    }

    // ------------ TYPE A enemies ------------
    for (int i = 0; i < 5; i++) {
        int x = 80 + i * 100;
        int y = -120 * i;
        enemies.emplace_back(x, y);
    }

    shooters.clear();
}

// ------------------------------------------------------------
// Trigger pause
// ------------------------------------------------------------
void Game::triggerPause() {
    isPaused = true;
    pauseTimer = 0.20f;   // 200ms freeze
}

// ------------------------------------------------------------
// Type A collision detection
// ------------------------------------------------------------
bool Game::checkPlayerCollision(const Enemy& e)
{
    return (player.x < e.x + e.width &&
            player.x + player.width > e.x &&
            player.y < e.y + e.height &&
            player.y + player.height > e.y);
}

// ------------------------------------------------------------
// UPDATE LOOP
// ------------------------------------------------------------
void Game::update(float delta)
{
    if (playerLives <= 0)
        return;

    // --------------------------------------------------------
    // PAUSE system
    // --------------------------------------------------------
    if (isPaused) {
        pauseTimer -= delta;
        if (pauseTimer <= 0) {
            isPaused = false;
        }
        return;   // <--- freeze entire game logic
    }

    // --------------------------------------------------------
    // BACKGROUND SCROLL
    // --------------------------------------------------------
    bgScrollY += 100 * delta;
    if (bgScrollY >= 480) bgScrollY = 0;

    // --------------------------------------------------------
    // Player movement
    // --------------------------------------------------------
    player.update(delta);

    // --------------------------------------------------------
    // FIRE PLAYER BULLETS
    // --------------------------------------------------------
    if (joystick_read_direction() == JOY_UP) {
        bullets.emplace_back(player.x + player.width/2, player.y - 10);
        led_blink();
    }

    for (auto& b : bullets)
        b.update(delta);

    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
                       [](const Bullet& b){ return b.y < -20; }),
        bullets.end()
    );

    // --------------------------------------------------------
    // TYPE A ENEMIES
    // --------------------------------------------------------
    for (auto& e : enemies) {
        e.y += 80 * delta;
        if (e.y > 500) e.reset();
    }

    // Player bullets hit type A
    for (auto& e : enemies) {
        for (auto& b : bullets) {
            if (e.checkCollision(b.x, b.y)) {
                explosions.push_back({e.x, e.y, 0.25f});
                e.reset();
                b.y = -99;
                triggerPause();
                led_flash();
            }
        }
    }

    // Player collides with type A
    for (auto& e : enemies) {
        if (checkPlayerCollision(e)) {
            playerLives--;
            explosions.push_back({e.x, e.y, 0.25f});
            triggerPause();
            led_flash();
            e.reset();
        }
    }

    // --------------------------------------------------------
    // SPAWN SHOOTER ENEMIES
    // --------------------------------------------------------
    timeSinceShooterSpawn += delta;

    if (timeSinceShooterSpawn > 2.0f && shooters.size() < 4) {
        timeSinceShooterSpawn = 0.0f;
        float x = 50 + rand() % 540;
        shooters.emplace_back(x, -50);
    }

    // --------------------------------------------------------
    // UPDATE SHOOTERS
    // --------------------------------------------------------
    for (auto& s : shooters) {
        s.update(delta);
        s.y += 30 * delta; // slow vertical drift
    }

    shooters.erase(
        std::remove_if(shooters.begin(), shooters.end(),
                       [](const ShooterEnemy& s){ return s.y > 520; }),
        shooters.end()
    );

    // SHOOTER FIRE
    for (auto& s : shooters) {
        if (s.readyToFire())
            shooterBullets.push_back(s.fireBullet());
    }

    // SHOOTER BULLETS
    for (auto& b : shooterBullets)
        b.update(delta);

    shooterBullets.erase(
        std::remove_if(shooterBullets.begin(), shooterBullets.end(),
                       [](const Bullet& b){ return b.y > 500; }),
        shooterBullets.end()
    );

    // SHOOTER BULLETS HIT PLAYER
    for (auto& b : shooterBullets) {
        bool hit =
            player.x < b.x + 5 &&
            player.x + player.width > b.x &&
            player.y < b.y + 5 &&
            player.y + player.height > b.y;

        if (hit) {
            playerLives--;
            b.y = 999;
            triggerPause();
            led_flash();
        }
    }

    // PLAYER BULLETS HIT SHOOTERS
    shooters.erase(
        std::remove_if(shooters.begin(), shooters.end(),
            [&](ShooterEnemy& s){
                for (auto& b : bullets) {
                    if (s.checkCollision(b.x, b.y)) {
                        explosions.push_back({s.x, s.y, 0.25f});
                        b.y = -99;
                        triggerPause();
                        led_flash();
                        return true;
                    }
                }
                return false;
            }),
        shooters.end()
    );

    // PLAYER HITS SHOOTERS
    shooters.erase(
        std::remove_if(shooters.begin(), shooters.end(),
            [&](ShooterEnemy& s){
                if (s.checkPlayerCollision(player.x, player.y, player.width, player.height)) {
                    explosions.push_back({s.x, s.y, 0.25f});
	    	    playerLives--;
                    triggerPause();
                    led_flash();
                    return true;
                }
                return false;
            }),
        shooters.end()
    );

    // ---------------------- UPDATE EXPLOSIONS ----------------------
    for (auto& ex : explosions) {
        ex.timer -= delta;
    }

    explosions.erase(
        std::remove_if(
            explosions.begin(), explosions.end(),
            [](const Explosion& ex){ return ex.timer <= 0.0f; }),
        explosions.end()
    );

}

// ------------------------------------------------------------
// Draw Lives
// ------------------------------------------------------------
void Game::drawLives()
{
    if (!heartTex) {
        // fallback: draw red squares
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (int i = 0; i < playerLives; i++) {
            SDL_Rect r = { 10 + i * 25, 10, 20, 20 };
            SDL_RenderFillRect(renderer, &r);
        }
        return;
    }

    // draw textured hearts
    for (int i = 0; i < playerLives; i++) {
        SDL_Rect dst = { 10 + i * 30, 10, 24, 24 };  // slightly larger + spaced
        SDL_RenderCopy(renderer, heartTex, nullptr, &dst);
    }
}


// ------------------------------------------------------------
// RENDER LOOP
// ------------------------------------------------------------
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // --------------------------------------------------------
    // DRAW SCROLLING BACKGROUND
    // --------------------------------------------------------
    int bgW = 640;
    int bgH = 480;

    SDL_Rect r1 = { 0, (int)bgScrollY - bgH, bgW, bgH };
    SDL_Rect r2 = { 0, (int)bgScrollY,       bgW, bgH };

    SDL_RenderCopy(renderer, backgroundTexture, NULL, &r1);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &r2);

    // --------------------------------------------------------
    // DRAW ENTITIES
    // --------------------------------------------------------
    player.renderWithTexture(renderer, playerTexture);

    for (auto& e : enemies)
        e.renderWithTexture(renderer, enemyTexture);

    for (auto& s : shooters)
        s.renderWithTexture(renderer, shooterTexture);

    for (auto& b : bullets)
        b.render(renderer);

    for (auto& b : shooterBullets)
        b.render(renderer);

    // Draw explosions
    for (auto& ex : explosions) {
        SDL_Rect dst = { (int)ex.x, (int)ex.y, 40, 40 }; // adjust size if needed
        SDL_RenderCopy(renderer, explosionTex, nullptr, &dst);
    }


    drawLives();

    SDL_RenderPresent(renderer);
}

Game::~Game() {
    if (bgm) {
        Mix_FreeMusic(bgm);
    }
    Mix_CloseAudio();
}


