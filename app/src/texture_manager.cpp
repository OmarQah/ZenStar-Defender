#include "texture_manager.h"
#include <iostream>

std::map<std::string, SDL_Texture*> TextureManager::textures;

SDL_Texture* TextureManager::load(const std::string& file, SDL_Renderer* renderer)
{
    // If already loaded, reuse it
    if (textures.count(file)) return textures[file];

    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface) {
        std::cerr << "IMG_Load failed for " << file << " : " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!tex) {
        std::cerr << "CreateTexture failed for " << file << std::endl;
        return nullptr;
    }

    textures[file] = tex;
    return tex;
}

void TextureManager::cleanup()
{
    for (auto& t : textures)
        SDL_DestroyTexture(t.second);

    textures.clear();
}
