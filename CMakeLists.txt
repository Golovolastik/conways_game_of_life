cmake_minimum_required(VERSION 3.20)
project(conways_game_of_life C)

set(CMAKE_C_STANDARD 11)

set(SDL2_PATH "/Library/Frameworks/SDL2.framework/Headers")
set(SDL2_IMAGE_PATH "/Library/Frameworks/SDL2_image.framework/Headers")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(PNG REQUIRED)


include_directories(${SDL2_PATH} ${SDL2_IMAGE_PATH})

find_library(PNG_LIBRARY png)
find_library(SDL2_LIBRARY SDL2)
find_library(SDL2_IMAGE_LIBRARY SDL2_IMAGE)
#find_library(PNG_LIB PNG)



add_executable(conways_game_of_life main.c functions.c)
target_link_libraries(conways_game_of_life ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${PNG_LIBRARY})