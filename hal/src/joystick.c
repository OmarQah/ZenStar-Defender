/*
 * joystick.c
 */

#include "joystick.h"
#include "adc_spi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>

// ADC channel mappings for joystick axes
#define X_CHANNEL 0
#define Y_CHANNEL 1

// Calibration values for joystick center positions and deadzones
#define X_CENTER 2123
#define X_DEADZONE 1000   // Large deadzone to handle noisy readings
#define Y_CENTER 2027
#define Y_DEADZONE 1000

static int initialized = 0;  // Tracks whether joystick system is initialized

void Joystick_init(void) {

    assert(!initialized);    // Prevent double initialization

    ADC_init();              // Initialize ADC hardware or SPI connection
    initialized = 1;         // Mark joystick as initialized

    printf("Joystick initialized\n");

}

void Joystick_cleanup(void) {

    assert(initialized);     // Ensure joystick was initialized before cleanup

    ADC_cleanup();           // Release ADC resources
    initialized = 0;         // Mark joystick as uninitialized

}

JoystickDirection Joystick_getDirection(void) {

    assert(initialized);     // Ensure Joystick_init() was called first

    int x_sum = 0, y_sum = 0;
    const int samples = 5;   // Number of ADC samples for noise averaging

    // Take multiple samples and average to reduce noise
    for (int i = 0; i < samples; i++) {

        x_sum += ADC_readChannel(X_CHANNEL);  // Read X-axis ADC value
        y_sum += ADC_readChannel(Y_CHANNEL);  // Read Y-axis ADC value
        usleep(1000);                         // 1 ms delay between samples

    }

    int x = x_sum / samples;  // Average X value
    int y = y_sum / samples;  // Average Y value

    //printf("DEBUG: x=%d, y=%d (averaged)\n", x, y);  // Show averaged readings

    // Compare averaged values against center deadzone
    if (x < X_CENTER - X_DEADZONE) return JS_LEFT;   // Joystick pushed left
    if (x > X_CENTER + X_DEADZONE) return JS_RIGHT;  // Joystick pushed right
    if (y < Y_CENTER - Y_DEADZONE) return JS_DOWN;   // Joystick pushed down
    if (y > Y_CENTER + Y_DEADZONE) return JS_UP;     // Joystick pushed up

    return JS_NONE;  // Within deadzone → no movement detected

}



