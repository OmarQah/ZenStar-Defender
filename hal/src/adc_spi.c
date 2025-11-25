#include "adc_spi.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

static int fd = -1;  // SPI device file descriptor
static const char* dev = "/dev/spidev0.0";
static uint32_t speed = 250000;
static int initialized = 0;

void ADC_init(void) {

    uint8_t mode = 0;
    uint8_t bits = 8;

    fd = open(dev, O_RDWR);

    if (fd < 0) {

        perror("ADC SPI open failed");
        return;

    }

    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1) {

        perror("SPI mode");

    }

    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1) {

        perror("SPI bits");

    }

    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) {

        perror("SPI speed");

    }

    initialized = 1;

}

void ADC_cleanup(void) {

    if (fd >= 0) {

        close(fd);

    }

    fd = -1;
    initialized = 0;

}

int ADC_readChannel(int ch) {

    if (!initialized) {

        fprintf(stderr, "ADC not initialized!\n");
        return -1;

    }

    uint8_t tx[3] = {

        (uint8_t)(0x06 | ((ch & 0x04) >> 2)),
        (uint8_t)((ch & 0x03) << 6),
        0x00

    };

    uint8_t rx[3] = {0};

    struct spi_ioc_transfer tr = {

        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = 3,
        .speed_hz = speed,
        .bits_per_word = 8,
        .cs_change = 0

    };

    if (ioctl(fd, SPI_IOC_MESSAGE(1), &tr) < 1) {

        perror("SPI transfer failed");
        return -1;

    }

    int value = ((rx[1] & 0x0F) << 8) | rx[2];
    return value;
    
}


