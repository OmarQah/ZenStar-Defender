//for now to run we use keyboard will need to work on joystick integration
#include "input.h"

void processInput(SDL_Event* event, const Uint8** keystate, int* running) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) *running = 0;
    }
    *keystate = SDL_GetKeyboardState(NULL);
}
