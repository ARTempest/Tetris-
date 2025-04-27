#pragma once
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "piece.h"
#include <memory>
#include <random>

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

  int fallingSpeed = 10;
  int fallingDelay = 0;

  glm::vec2 blockCoords[4];

public:
  float worldW = 76.0f;
  float worldH = 50.0f;

  enum grids {nothing, block};

  Piece* activePiece;

  int board[24][10] = {    // 0 = nothing, 1 = static_block, 2 = active_block
    {0,0,0,0,0,0,0,0,0,0}, // hidden section
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}, 
    {0,0,0,0,0,0,0,0,0,0}, // starting of the viewport 
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}
  };


  Game(unsigned int, unsigned int);
  void processInput(int);
  void Init();

  void generatePiece();
  void static framebuffer_size_callback(GLFWwindow*, int, int);
  GLFWwindow* window; 

  glm::vec2 convertCoords(glm::vec2);
  void setPieceCoords(glm::vec2[4]);

  bool checkMov(glm::vec2);
  bool checkRot(glm::vec2*);
  void generateNewPiece();

};
#endif 

