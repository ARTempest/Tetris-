#pragma once
#include <array>
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "piece.h"
#include <memory>
#include <random>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <vector>
#include "placedBlock.h"

class Render;
class Piece;

class Game {
private:
  unsigned int width, height;

//Key Functions
  void pieceMov(const int);
  void pieceRot(const int);
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

  glm::vec2 atlasSize = glm::vec2(64.0, 64.0);
  glm::vec2 tileSize = glm::vec2(16.0, 16.0);
public:
  const float worldW = 76.0f;
  const float worldH = 50.0f;

  Piece* activePiece;

  std::vector<PlacedBlock> placedBlocks;
  std::array<int, 10> highestBlocks;


  int score = 0;


  int board[24][10] = {    // 0 = nothing, 1 = static_block
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

  bool needUpdate = false;

  Game(unsigned int, unsigned int);
  void processInput(int);
  void Init();

  void generatePiece();
  void static framebuffer_size_callback(GLFWwindow*, int, int);
  GLFWwindow* window; 

  glm::vec2 convertToBoardCoords(glm::vec2);
  glm::vec2 convertToWorldCoords(glm::vec2);
  glm::mat4 convertToModel(glm::vec2);

  void setPieceCoords(glm::vec2[4]);

  bool checkMov(glm::vec2);
  bool checkRot(glm::vec2*);

  void generateNewPiece();
  void erasePiece();

  glm::vec2 getAtlasScale();

  void addBlockToBoard(glm::vec2);
  void addPlacedBlock(glm::vec2, glm::vec2);
 
  bool checkLine(int);
  void eraseLine(int);

  void moveBlocksDown(int, int);

  void increaseScore(int);

  void findHighestBlock();

  void printBoard();

};
#endif 

