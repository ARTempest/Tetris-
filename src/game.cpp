#include "../include/game.h"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
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

  activePiece = std::make_unique<Piece>(Piece::T, glm::vec2(5.0f, 10.0f));
}


void Game::processInput(int frameRate) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  pieceMov(frameRate);
  pieceRot(frameRate);
}

void Game::framebuffer_size_callback(GLFWwindow* window, int w, int h) {
  Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));

  glViewport(0, 0, w, h);

  float aspect = static_cast<float>(w) / static_cast<float>(h);
  game->worldH = 20.0f;
  game->worldW = game->worldH * aspect;
  
}

void Game::pieceMov(int frameRate) {
  bool pressingR = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
  bool pressingL = glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_PRESS;
  bool pressingD = glfwGetKey(window, GLFW_KEY_DOWN)  == GLFW_PRESS;


  if (pressingR && !pressingL && movingR == false) {
    activePiece->move(1, 0);
    movingR = true;
    delayR = 10;
  }
  else if (pressingL && !pressingR && movingL == false) {
    activePiece->move(-1, 0);
    movingL = true;
    delayL = 10;
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
  
  if (delayR > 0) {
    delayR -= 1;
  }

  if (delayL > 0) {
    delayL -= 1;
  }
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
