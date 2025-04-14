#pragma once
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Game {
private:
  unsigned int width, height;
  
public:
  Game(unsigned int, unsigned int);
  void processInput();
  void Init();

  static void framebuffer_size_callback(GLFWwindow*, int, int);

  GLFWwindow* window; 
};
#endif 

