cmake_minimum_required(VERSION 3.20)

project(chip8)

find_package(raylib REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")

add_executable(chip8 ${SOURCES})

target_include_directories(chip8 PRIVATE src)

target_compile_options(chip8 PRIVATE -Wall -Wextra -Wpedantic)

target_link_libraries(chip8 raylib)