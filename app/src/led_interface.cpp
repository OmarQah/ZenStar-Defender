#include "led_interface.h"
extern "C" {
    #include "led.h"
}
#include <unistd.h>

void led_init() {
    LED_init();
}

// Blink green LED once
void led_blink() {
    LED_onGreen();
    usleep(100000);
    LED_offGreen();
}

// Flash LEDs using HAL helper functions
void led_flash() {
    LED_flashGreen(2);
    LED_flashRed(2);
}