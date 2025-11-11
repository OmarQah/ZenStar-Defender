#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

void processInput(SDL_Event* event, const Uint8** keystate, int* running);

#endif
