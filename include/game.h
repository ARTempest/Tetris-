#pragma once
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "piece.h"
#include <memory>

class Render;
class Piece;

class Game {
private:
  unsigned int width, height;

//Key Functions
  void pieceMov(int);
  void pieceRot(int);
  void checkKeyState(bool, bool*);

  void activateDelay(int*, int);
  void reduceDelay(int*);

// Key bools
  bool movingR = false;
  bool movingL = false;
  bool movingD = false;
  bool rotatingZ = false;
  bool rotatingX = false;

// Key Delays
  int delayR = 0;
  int delayL = 0;
  int delayZ = 0;
  int delayX = 0;

public:
  float worldW = 70.0f;
  float worldH = 50.0f;
  

  //glm::vec2 walls[20] = {
  //glm::vec2(0,40)
 // };

  std::unique_ptr<Piece> activePiece;

  Game(unsigned int, unsigned int);
  void processInput(int);
  void Init();

  void generatePiece();
  void static framebuffer_size_callback(GLFWwindow*, int, int);
  GLFWwindow* window; 
};
#endif 

