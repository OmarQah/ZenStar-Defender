# ===========================
# zenstar/app/CMakeLists.txt
# ===========================

cmake_minimum_required(VERSION 3.16)
project(zenstar_app CXX)

set(APP_SOURCES
    src/main.cpp
    src/game.cpp
    src/player.cpp
    src/bullet.cpp
    src/led_interface.cpp
    src/joystick_interface.cpp
    src/enemy.cpp
    src/shooter_enemy.cpp
)

add_executable(zenstar_app ${APP_SOURCES})

# ============================================================
# Use pkg-config to locate SDL2, SDL2_image, SDL2_mixer
# This works reliably on ARM boards like BeagleBone
# ============================================================
find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2MIXER REQUIRED SDL2_mixer)

# ============================================================
# Include directories
# ============================================================
target_include_directories(zenstar_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/hal/include

    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${SDL2MIXER_INCLUDE_DIRS}
)

# ============================================================
# Link libraries (using pkg-config libs)
# ============================================================
target_link_libraries(zenstar_app PRIVATE
    hal
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2MIXER_LIBRARIES}
    m
    pthread
    dl
)

# Copy assets folder
add_custom_command(TARGET zenstar_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            ${CMAKE_CURRENT_BINARY_DIR}/assets
)








