# ===========================
# toolchain-arm64.cmake
# ===========================

# toolchain-arm64.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)

# Sysroot
set(CMAKE_SYSROOT /home/kkw29/beagleyai-sysroot)
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})

# Search rules for cross-compiling
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Tell CMake where to find SDL2Config.cmake in sysroot
set(SDL2_DIR "${CMAKE_SYSROOT}/usr/lib/cmake/SDL2")

