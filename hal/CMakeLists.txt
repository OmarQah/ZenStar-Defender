# ===========================
# zenstar/hal/CMakeLists.txt
# ===========================

cmake_minimum_required(VERSION 3.16)
project(hal C)

set(HAL_SOURCES
    src/led.c
    src/joystick.c
    src/adc_spi.c
)

add_library(hal STATIC ${HAL_SOURCES})
target_include_directories(hal PUBLIC include)


