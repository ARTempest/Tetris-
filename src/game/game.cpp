#include "game.h"

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
  
  if (window == NULL) {
    std::cout << "ERROR_WHILE_CREATING_WINDOW" << '\n';
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }    

  glViewport(0,0, width, height);
  //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
}

void Game::processInput() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

//void Game::framebuffer_size_callback(GLFWwindow* w, int widt, int heigh) {
 // glViewport(0, 0, widt, heigh);
//}





