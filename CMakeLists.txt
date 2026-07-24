cmake_minimum_required(VERSION 3.20)

project(chip8)

find_package(raylib REQUIRED)

add_executable(chip8 src/chip8.cpp src/main.cpp)

target_compile_options(chip8 PRIVATE -Wall -Wextra -Wpedantic)

target_link_libraries(chip8 raylib)