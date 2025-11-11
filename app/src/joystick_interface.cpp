#include "joystick_interface.h"
extern "C" {
    #include "joystick.h"
}
#include <stdio.h>

void joystick_init() {
    Joystick_init();
}

JoystickDir joystick_read_direction() {
    JoystickDirection dir = Joystick_getDirection();
    switch (dir) {
        case JS_UP:    return JOY_UP;
        case JS_DOWN:  return JOY_DOWN;
        case JS_LEFT:  return JOY_LEFT;
        case JS_RIGHT: return JOY_RIGHT;
        case JS_SELECT:return JOY_CENTER;
        case JS_NONE:
        default:
            return JOY_CENTER;
    }
}
