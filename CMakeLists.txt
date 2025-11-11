# ===========================
# zenstar/CMakeLists.txt
# ===========================

cmake_minimum_required(VERSION 3.20)
project(zenstar LANGUAGES C CXX)

# Set SDL2 dir for cross-compiling
#set(SDL2_DIR "/home/kkw29/beagleyai-sysroot/usr/lib/cmake/SDL2")
#set(CMAKE_PREFIX_PATH ${SDL2_DIR})

# Add subdirectories
add_subdirectory(hal)
add_subdirectory(app)




