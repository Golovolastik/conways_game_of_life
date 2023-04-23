cmake_minimum_required(VERSION 3.20)
project(conways_game_of_life C)

set(CMAKE_C_STANDARD 11)

set(SDL2_PATH "/Library/Frameworks/SDL2.framework/Headers")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_library(SDL2_LIBRARY SDL2)
add_executable(conways_game_of_life main.c)
target_link_libraries(conways_game_of_life ${SDL2_LIBRARY})
