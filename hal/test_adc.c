#include "adc_spi.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    ADC_init();
    printf("Starting MCP3208 Test...\n");

    while (1) {
        int x = ADC_readChannel(0);
        int y = ADC_readChannel(1);
        int sw = ADC_readChannel(2);

        printf("X=%4d  Y=%4d  SW=%4d\n", x, y, sw);
        usleep(100000);
    }

    ADC_cleanup();
    return 0;
}
