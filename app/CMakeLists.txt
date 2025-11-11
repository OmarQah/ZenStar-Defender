# ===========================
# zenstar/app/CMakeLists.txt
# ===========================

cmake_minimum_required(VERSION 3.16)
project(zenstar_app CXX)

# Collect sources
set(APP_SOURCES
    src/main.cpp
    src/game.cpp
    src/player.cpp
    src/bullet.cpp
    src/led_interface.cpp
    src/joystick_interface.cpp
    src/enemy.cpp
)

# Create executable
add_executable(zenstar_app ${APP_SOURCES})

# Include HAL headers
target_include_directories(zenstar_app PRIVATE
    ${CMAKE_SOURCE_DIR}/hal/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# =========================
# SDL2: include + lib paths
# =========================

#set(SDL2_INCLUDE_DIR "/home/kkw29/beagleyai-sysroot/usr/include/SDL2")
#set(SDL2_LIB_DIR "/home/kkw29/beagleyai-sysroot/usr/lib")

target_include_directories(zenstar_app PRIVATE ${SDL2_INCLUDE_DIR})

target_link_libraries(zenstar_app PRIVATE
    hal
    ${SDL2_LIB_DIR}/libSDL2.so
)












