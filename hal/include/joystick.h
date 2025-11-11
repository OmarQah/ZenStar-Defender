#ifndef JOYSTICK_H
#define JOYSTICK_H

typedef enum {

    JS_NONE,
    JS_UP,
    JS_DOWN,
    JS_LEFT,
    JS_RIGHT,
    JS_SELECT
    
} JoystickDirection;

void Joystick_init(void);

JoystickDirection Joystick_getDirection(void);
void Joystick_cleanup(void);

#endif
