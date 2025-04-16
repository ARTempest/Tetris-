cmake_minimum_required(VERSION 3.10)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Manually set the GLFW_DIR where glfw3Config.cmake is located
add_subdirectory(libs/glfw)
add_subdirectory(libs/glm)

# Add your executable
add_executable(tetris src/main.cpp 
src/OpenGL/glad.c
src/OpenGL/stb.cpp
src/render/render.cpp
src/game/game.cpp
src/block/block.cpp
include/shader.cpp
include/texture.cpp
)

# Link OpenGL and GLFW
find_package(OpenGL REQUIRED)
target_link_libraries(tetris PRIVATE glfw OpenGL::GL)

