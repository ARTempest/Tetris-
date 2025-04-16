#include "game.h"
#include <GLFW/glfw3.h>

Game::Game(unsigned int w, unsigned int h){
  width = w;
  height = h;
}

void Game::Init(){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  window = glfwCreateWindow(width, height, "Tetris", NULL, NULL);
  
  glfwSetWindowUserPointer(window, this);

  if (window == NULL) {
    std::cout << "ERROR_WHILE_CREATING_WINDOW" << '\n';
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);                                                                       


  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }    
}

void Game::processInput() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void Game::framebuffer_size_callback(GLFWwindow* window, int w, int h) {
  Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));

  glViewport(0, 0, w, h);

  float aspect = static_cast<float>(w) / static_cast<float>(h);
  game->worldH = 20.0f;
  game->worldW = game->worldH * aspect;
  
}





