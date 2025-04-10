#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
};

class Game {
private:
  unsigned int width, height;
  void processInput();
  void Render();


public:
  Game (unsigned int, unsigned int);
  GLFWwindow *window;
  
  void Init();

};

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

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
  

  while (!glfwWindowShouldClose(window)){
    processInput();
    Render();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void Game::processInput() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void Game::Render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}









