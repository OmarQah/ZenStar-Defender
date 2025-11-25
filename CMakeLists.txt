# ===========================
# TOP LEVEL CMakeLists.txt
# ===========================

cmake_minimum_required(VERSION 3.20)
project(zenstar LANGUAGES C CXX)

# Add subdirectories only.
add_subdirectory(hal)
add_subdirectory(app)

