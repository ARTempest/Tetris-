#pragma once
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../piece/piece.h"
#include <memory>

class Render;
class Piece;

class Game {
private:
  unsigned int width, height;
public:
  float worldW = 10.0f;
  float worldH = 20.0f;

  std::unique_ptr<Piece> activePiece;

  Game(unsigned int, unsigned int);
  void processInput();
  void Init();

  void generatePiece();
  void static framebuffer_size_callback(GLFWwindow*, int, int);
  GLFWwindow* window; 
};
#endif 

