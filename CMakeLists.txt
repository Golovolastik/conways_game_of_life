cmake_minimum_required(VERSION 3.20)
project(conways_game_of_life C)

set(CMAKE_C_STANDARD 11)

# Установите путь к заголовочным файлам SDL2 и SDL2_ttf
set(SDL2_INCLUDE_DIR "/Library/Frameworks/SDL2.framework/Headers")
set(SDL2_IMAGE_INCLUDE_DIR "/Library/Frameworks/SDL2_image.framework/Headers")
set(SDL2_TTF_INCLUDE_DIR "/Library/Frameworks/SDL2_ttf.framework/Headers")

# Установите путь к библиотекам SDL2 и SDL2_ttf
set(SDL2_LIBRARY "/Library/Frameworks/SDL2.framework")
set(SDL2_TTF_LIBRARY "/Library/Frameworks/SDL2_ttf.framework")
set(SDL2_IMAGE_LIBRARY "/Library/Frameworks/SDL2_image.framework")

# Найдите библиотеки SDL2 и SDL2_ttf
find_library(SDL2_LIBRARY NAMES SDL2 PATHS ${SDL2_LIBRARY})
find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf PATHS ${SDL2_TTF_LIBRARY})
find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image PATHS ${SDL2_IMAGE_LIBRARY})

# Добавьте директории с заголовочными файлами
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

add_executable(conways_game_of_life main.c functions.c)
target_link_libraries(conways_game_of_life ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})
