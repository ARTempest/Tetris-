cmake_minimum_required(VERSION 3.10)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)

link_directories(
    ${SDL2_LIBRARY_DIRS}
    ${SDL2_MIXER_LIBRARY_DIRS}
)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glm)

add_executable(tetris
    src/main.cpp 
    src/OpenGL/glad.c
    src/OpenGL/stb.cpp
    src/render.cpp
    src/game.cpp
    src/block.cpp
    src/piece.cpp
    src/shader.cpp
    src/texture.cpp
    src/character.cpp
    src/music.cpp
)

find_package(OpenGL REQUIRED)

target_link_libraries(tetris
    PRIVATE
    glfw
    OpenGL::GL
    ${SDL2_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

