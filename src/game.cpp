#include "../include/game.h"
#include <GLFW/glfw3.h>
#include <array>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <iostream>
#include <string>
#include <vector>

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

  initNumbers();
  initLetters();
  generateNewPiece();
}

void Game::processInput(int frameRate) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (gameState == PLAYING) {
    pieceMov(frameRate);
    pieceRot(frameRate);
  }
  changeGameState();
}

void Game::framebuffer_size_callback(GLFWwindow* window, int w, int h) {
  glViewport(0, 0, w, h);
}

void Game::pieceMov(const int frameRate) {
  checkLoseScreen();
  bool pressingR = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
  bool pressingL = glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_PRESS;
  bool pressingD = glfwGetKey(window, GLFW_KEY_DOWN)  == GLFW_PRESS;

  if (frameRate % (60 - fallingSpeed) == 0 && fallingDelay == 0) {
    activePiece->move(0, -1);
    activateDelay(&fallingDelay, 60 - fallingSpeed);
  }

  if (pressingR && !pressingL && movingR == false) {
    activePiece->move(1, 0);
    movingR = true;
    delayR = keysDelay;
    delayL = keysDelay;
  }
  else if (pressingL && !pressingR && movingL == false) {
    activePiece->move(-1, 0);
    movingL = true;
    delayL = keysDelay;
    delayR = keysDelay;
  }
  else if (frameRate % 10 == 0){

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

void Game::pieceRot(const int frameRate) {
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


glm::vec2 Game::convertToBoardCoords(glm::vec2 coords) {
  coords.x = (coords.x - 29) / 2;
  coords.y = (57 - coords.y) / 2;
  return coords;
}

void Game::setPieceCoords(glm::vec2* blockPos) {
  for (int i=0; i <= 3; i++) {
    blockCoords[i] = convertToBoardCoords(blockPos[i]);
  }
}

bool Game::checkMov(glm::vec2 force) {
  for (glm::vec2 pos: blockCoords) {
    glm::ivec2 nextPos = pos + force;

    if (nextPos.x >= 0 && nextPos.x <= 9 && nextPos.y >= 0 && nextPos.y < 24) {
      if (board[nextPos.y][nextPos.x] != 1) {
      } 
      else {
        if (force == glm::vec2(0.0, 1.0)) {
          erasePiece();
          generateNewPiece();
        }
        return false;
      }
    } else {
      if (force == glm::vec2(0.0, 1.0)){
        erasePiece();
        generateNewPiece();
      }
      return false;}
  }

  //std::cout << placedBlocks.size() << '\n';
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

  //std::cout << "true" << '\n';
  
  for (int i=0; i <= 2; i++) {
    blockCoords[i+1].x = blockCoords[0].x + blockRot[i].x;
    blockCoords[i+1].y = blockCoords[0].y - blockRot[i].y;
  }

  delete blockRot;

  return true;
}

void Game::erasePiece() {
  for (int i=0; i <= 3; i++) {
    
    glm::vec2 boardPos = blockCoords[i];
    glm::vec2 worldPos = activePiece->blockPos[i];
    
    addBlockToBoard(boardPos);
    addPlacedBlock(boardPos, worldPos);

    needUpdate = true;
  }
  
  int amountLines = 0;   
  int lowestLine = 0;
  bool lineCompleted = false;


  for (int i=0; i <= 3; i++) {
    
    int line = blockCoords[i].y;

    if (checkLine(line) == true) {
      if (line > lowestLine) {
        lowestLine = line;
        lineCompleted = true;
      }
      eraseLine(line);
      amountLines += 1;
    }
  }

  if (lineCompleted) {
    moveBlocksDown(lowestLine, amountLines);
    increaseScore(amountLines);
  }

  delete activePiece; 
}

void Game::generateNewPiece() {
  checkLoseScreen();
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> piece(0,6); 
  
  activePiece = new Piece(this, Piece::shapesArray[piece(rng)], glm::vec2(31.0f, 51.0f));
}

glm::vec2 Game::getAtlasScale() {
  glm::vec2 atlasScale = tileSize / atlasSize;
  return atlasScale;
}

void Game::addBlockToBoard(glm::vec2 pos) {
  int x = int(pos.x);
  int y = int(pos.y);

  board[y][x] = 1;
}

void Game::addPlacedBlock(glm::vec2 boardPos, glm::vec2 pos) {
  PlacedBlock newPlacedBlock;

  glm::mat4 model = glm::mat4(1.0);
  model = glm::translate(model, glm::vec3(pos, 0.0));
  
  newPlacedBlock.model = model;
  newPlacedBlock.textureCoord = activePiece->getAtlasOffset();
  newPlacedBlock.boardCoords = boardPos;

  placedBlocks.push_back(newPlacedBlock);
}

bool Game::checkLine(int line) {
  for (int i=0; i < 10; i++) {
    if (board[line][i] == 0) {
      return false;
    }
  }
  return true;
}

void Game::eraseLine(int line) {
  int index = 0;
  std::vector<int> indices;

  for (PlacedBlock& block : placedBlocks) {
    if (block.boardCoords.y == line) {
      indices.push_back(index);
    }

    index++;
  }

  for (int i=0; i < 10; i++) {
    board[line][i] = 0;
    placedBlocks.erase(placedBlocks.begin() + indices[i] - 1 * i);
  }

}
  
void Game::moveBlocksDown(int lowestLine, int amountLines) {

  for (int i=0; i < placedBlocks.size(); i++) {
    if (placedBlocks[i].boardCoords.y < lowestLine) {

      glm::vec2* coords = &placedBlocks[i].boardCoords;

      int x = placedBlocks[i].boardCoords.x;
      int y = placedBlocks[i].boardCoords.y;
     
      if (board[y][x] == 1) {
        board[y][x] = 0;
      }
      
      coords->y += 1*amountLines;

      board[int(coords->y)][x] = 2;

      
      glm::vec2 newWorldCoords = convertToWorldCoords(*coords);
      glm::mat4 newModel = convertToModel(newWorldCoords);
      placedBlocks[i].model = newModel;
    }
  }

  for (int y=0; y < 24; y++) {
    for (int x=0; x < 10; x++) {
      if (board[y][x] == 2) {
        board[y][x] = 1;
      } 
    }
  }
}

glm::vec2 Game::convertToWorldCoords(glm::vec2 boardCoords) {
  glm::vec2 worldCoords = boardCoords;

  worldCoords.x = boardCoords.x * blockSize + 29;
  worldCoords.y = 57 - boardCoords.y * blockSize;

  return worldCoords;
}

glm::mat4 Game::convertToModel(glm::vec2 pos) {
  glm::mat4 model = glm::mat4(1.0);
  model = glm::translate(model, glm::vec3(pos, 0.0));

  return model;
}

void Game::increaseScore(int amountLines) {
  int scoreforAmount[4] = {40, 100, 300, 1200}; 

  score += scoreforAmount[amountLines - 1];
  totalAmountLines += amountLines;
  
  std::string scoreString = std::to_string(score);
  std::string totalAmountLinesString = std::to_string(totalAmountLines);

  for (int i=0; i < scoreString.size(); i++) {
    const int digit = scoreString[i] - 48;
    numbers[6 - scoreString.size() + i].texCoords = convertToAtlasScale(numbers[0].numbers[digit]);
  }

  for (int i=0; i < totalAmountLinesString.size(); i++) {
    const int digit = totalAmountLinesString[i] - 48;
    numbers[12 - totalAmountLinesString.size() + i].texCoords = convertToAtlasScale(numbers[0].numbers[digit]);
  }

  increaseSpeed();
}

glm::vec2 Game::convertToAtlasScale(glm::vec2 coords) {
  return coords * getAtlasScale();
}

void Game::initNumbers() {
  const int value = 0;
  const glm::vec2 boardPos = glm::vec2(17, 5);
  const glm::vec2 initialPos = convertToWorldCoords(boardPos);

  for (int i=0; i < numbers.size(); i++) {
    glm::mat4 model;
    
    if (i < 6) {
      model = convertToModel(glm::vec2(initialPos.x + i*blockSize, initialPos.y)); 
    } else {
      model = convertToModel(glm::vec2(initialPos.x + (i - 6) * blockSize, initialPos.y - 2 * blockSize));
    }

    Number newNumber(value, model);
    numbers[i] = newNumber;
    numbers[i].texCoords = convertToAtlasScale(numbers[i].texCoords);
  } 
}

void Game::initLetters() { 
  const glm::vec2 initialPos = convertToWorldCoords(glm::vec2(11, 5));
  const std::array<Letter::letter, 10> order = {
    Letter::letter::s,
    Letter::letter::c,
    Letter::letter::o,
    Letter::letter::r,
    Letter::letter::e,
    Letter::letter::l,
    Letter::letter::i,
    Letter::letter::n,
    Letter::letter::e,
    Letter::letter::s
  };


  for (int i=0; i < order.size(); i++) {
    glm::mat4 model;

    if (i < 5) {
      model = convertToModel(glm::vec2(initialPos.x + i*blockSize, initialPos.y));
    } else {
      model = convertToModel(glm::vec2(initialPos.x + (i-5)*blockSize, initialPos.y - 2* blockSize));
    }

    Letter newLetter(order[i], model);
    letters[i] = newLetter;
    letters[i].texCoords = convertToAtlasScale(letters[i].texCoords);

  }

}

void Game::changeGameState() {
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && gameState != GAME_OVER && pressingSpace == false) {
    if (gameState == PLAYING) {
      gameState = PAUSE;
    } else {
      gameState = PLAYING;
    }
    pressingSpace = true;
  } 

  if (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS){
    pressingSpace = false;
  }

}

void Game::checkLoseScreen() {
  for (int i=0; i < 10; i++) {
    if (board[3][i] == 1) {
      gameOverScreen();
      break;
    }
  }
}

void Game::gameOverScreen() {
  gameState = GAME_OVER;
}

void Game::increaseSpeed() {
  int speed = score / 20;
  
  if (initialFallingSpeed + speed > 59) {
    speed =  39;
  }

  fallingSpeed = initialFallingSpeed + speed;
  if (fallingSpeed > 20) {
    keysDelay = 10;
  } 
}

