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
  GLFWwindow* window; 
  void processInput();
  //static void framebuffer_size_callback(GLFWwindow*, int, int);
  void Init();
  Game(unsigned int, unsigned int);

};
#endif 
