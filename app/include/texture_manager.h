#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

class TextureManager {
public:
    static SDL_Texture* load(const std::string& file, SDL_Renderer* renderer);
    static void cleanup();

private:
    static std::map<std::string, SDL_Texture*> textures;
};
