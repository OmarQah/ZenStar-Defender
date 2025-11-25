#include "joystick_interface.h"

// Simple guard so we only init once
static bool joystick_initialized = false;

void joystick_init() {
    if (!joystick_initialized) {
        Joystick_init();        // from your C HAL (joystick.c)
        joystick_initialized = true;
    }
}

JoystickDirection_t joystick_read_direction() {
    if (!joystick_initialized) {
        joystick_init();
    }
    return Joystick_getDirection();   // from joystick.c
}


