#pragma once

// Pull in the C joystick HAL
extern "C" {
#include "joystick.h"   // from hal/include, your reaction-timer header
}

// Re-export the low-level enum type
// joystick.h should define:
//   typedef enum { JS_NONE, JS_LEFT, JS_RIGHT, JS_UP, JS_DOWN } JoystickDirection;
typedef JoystickDirection JoystickDirection_t;

// Convenience direction names for the game code
#define JOY_NONE        JS_NONE
#define JOY_LEFT        JS_LEFT
#define JOY_RIGHT       JS_RIGHT
#define JOY_UP          JS_UP
#define JOY_DOWN        JS_DOWN
#define JOY_UP_LEFT     JS_UP_LEFT
#define JOY_UP_RIGHT    JS_UP_RIGHT
#define JOY_DOWN_LEFT   JS_DOWN_LEFT
#define JOY_DOWN_RIGHT  JS_DOWN_RIGHT

// High-level API used by the game
void joystick_init();
JoystickDirection_t joystick_read_direction();


