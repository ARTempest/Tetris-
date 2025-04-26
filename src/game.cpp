#include "../include/game.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <iostream>
#include <memory>

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
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }    

  activePiece = std::make_unique<Piece>(this,Piece::S, glm::vec2(31.0f, 51.0f)); // 0x = 29
}

void Game::processInput(int frameRate) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  pieceMov(frameRate);
  pieceRot(frameRate);
}

void Game::framebuffer_size_callback(GLFWwindow* window, int w, int h) {
  glViewport(0, 0, w, h);
}

void Game::pieceMov(int frameRate) {
  bool pressingR = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
  bool pressingL = glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_PRESS;
  bool pressingD = glfwGetKey(window, GLFW_KEY_DOWN)  == GLFW_PRESS;

  if (frameRate % (60 - fallingSpeed) == 0 && fallingDelay == 0) {
    activePiece->move(0, -1);
    activateDelay(&fallingDelay, 120 - fallingSpeed);
  }

  if (pressingR && !pressingL && movingR == false) {
    activePiece->move(1, 0);
    movingR = true;
    delayR = 15;
    delayL = 15;
  }
  else if (pressingL && !pressingR && movingL == false) {
    activePiece->move(-1, 0);
    movingL = true;
    delayL = 15;
    delayR = 15;
  }
  else if (frameRate % 15 == 0){

    if (pressingR && !pressingL && delayR == 0) {
     activePiece->move(1, 0);
    } 
    else if (pressingL && !pressingR && delayL == 0) {
     activePiece->move(-1, 0);
    }

    if (pressingD) {
     activePiece->move(0, -1);
    }
  }

  if (!pressingR) {
    movingR = false;
  }

  if (!pressingL) {
    movingL = false;
  }

  reduceDelay(&delayR);
  reduceDelay(&delayL);
  reduceDelay(&fallingDelay);
}

void Game::pieceRot(int frameRate) {
  bool pressingZ = glfwGetKey(window, GLFW_KEY_Z);
  bool pressingX = glfwGetKey(window, GLFW_KEY_X);

  if (pressingZ && !rotatingZ && delayZ == 0) {
    activePiece->rotate(-1);
    activateDelay(&delayZ, 10);
    activateDelay(&delayX, 10);
  } 

  if (pressingX && !rotatingX && delayX == 0) {
    activePiece->rotate(1);
    activateDelay(&delayZ, 10);
    activateDelay(&delayX, 10);
  }


  checkKeyState(pressingZ, &rotatingZ);
  checkKeyState(pressingX, &rotatingX);
  
  reduceDelay(&delayZ);
  reduceDelay(&delayX);
}

void Game::activateDelay(int* delay, int value) {
  *delay = value;
}

void Game::reduceDelay(int* delay) {
  if (*delay > 0) {
    *delay -= 1;
  }
}

void Game::checkKeyState(bool beingPress, bool* key) {
  if (beingPress) {
    *key = true;
  } else {
    *key = false;
  }
}


glm::vec2 Game::convertCoords(glm::vec2 coords) {
  coords.x = (coords.x - 29) / 2;
  coords.y = (57 - coords.y) / 2;
  return coords;
}

void Game::setPieceCoords(glm::vec2* blockPos) {
  for (int i=0; i <= 3; i++) {
    blockCoords[i] = convertCoords(blockPos[i]);
  }
}

bool Game::checkMov(glm::vec2 force) {
  for (glm::vec2 pos: blockCoords) {
    glm::ivec2 nextPos = pos + force;

    if (nextPos.x >= 0 && nextPos.x <= 9 && nextPos.y >= 0 && nextPos.y < 24) {
      if (board[nextPos.y][nextPos.x] != 1) {} else {return false;}
    } else {return false;}
  }

  for (int i=0; i <= 3; i++) {
    blockCoords[i] += force;
  }


  return true;
}

bool Game::checkRot(glm::vec2* blockRot) {
  for (int i=0; i <= 2; i++) {
    glm::ivec2 nextPos = blockCoords[0];
    nextPos.x += int(blockRot[i].x);
    nextPos.y += int(blockRot[i].y);
    
    if (nextPos.x >= 0 && nextPos.x <= 9 && nextPos.y >= 0 && nextPos.y < 23) {
      if (board[nextPos.y][nextPos.x] != 1) {} else {return false;}
    } else {return false;}
  }

  std::cout << "true" << '\n';
  
  for (int i=0; i <= 2; i++) {
    blockCoords[i+1].x = blockCoords[0].x + blockRot[i].x;
    blockCoords[i+1].y = blockCoords[0].y - blockRot[i].y;
  }

  delete blockRot;

  return true;
}

