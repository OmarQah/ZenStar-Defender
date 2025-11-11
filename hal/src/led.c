/*
 * led.c
 */

#include "led.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// File paths for LEDs
#define GREEN_PATH "/sys/class/leds/ACT/brightness"
#define RED_PATH   "/sys/class/leds/PWR/brightness"

// Helper function: writes a to a given LED file
static void writeToFile(const char* path, const char* val) {

    FILE* f = fopen(path, "w");         // Open the file for writing

    if (!f) {                           // Check for file open errors

        perror("LED file");             // Print system error message
        return;                         // Exit if file couldn't open
                
    }
    
    fprintf(f, "%s", val);              // Write the value to the file
    fclose(f);                          // Close the file

}

// Initializes LEDs by turning both off
void LED_init(void) {

    LED_offGreen();
    LED_offRed();

}

// Cleans up LED state (turns them off before program exits)
void LED_cleanup(void) {

    LED_offGreen();
    LED_offRed();

}

// Turn the green LED on/off
void LED_onGreen(void) { 

    writeToFile(GREEN_PATH, "1");

}

void LED_offGreen(void) { 

    writeToFile(GREEN_PATH, "0"); 

}

// Turn the red LED on/off
void LED_onRed(void) { 

    writeToFile(RED_PATH, "1"); 

}

void LED_offRed(void) { 
    
    writeToFile(RED_PATH, "0"); 

}

// Flash green LED a given number of times
void LED_flashGreen(int times) {

    for (int i = 0; i < times; i++) {

        LED_onGreen();                   // Turn LED on
        usleep(100000);                  // Wait 100 ms
        LED_offGreen();                  // Turn LED off
        usleep(100000);                  // Wait another 100 ms

    }

}

// Flash red LED a given number of times
void LED_flashRed(int times) {

    for (int i = 0; i < times; i++) {

        LED_onRed();                     // Turn LED on
        usleep(100000);                  // Wait 100 ms
        LED_offRed();                    // Turn LED off
        usleep(100000);                  // Wait another 100 ms

    }

}
