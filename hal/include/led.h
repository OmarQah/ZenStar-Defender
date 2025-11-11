#ifndef LED_H
#define LED_H

void LED_init(void);
void LED_cleanup(void);

void LED_onGreen(void);
void LED_offGreen(void);
void LED_onRed(void);
void LED_offRed(void);
void LED_flashGreen(int times);
void LED_flashRed(int times);

#endif