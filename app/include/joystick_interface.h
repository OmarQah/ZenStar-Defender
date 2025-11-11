#pragma once

typedef enum {
    JOY_CENTER,
    JOY_UP,
    JOY_DOWN,
    JOY_LEFT,
    JOY_RIGHT
} JoystickDir;

void joystick_init();
JoystickDir joystick_read_direction();
