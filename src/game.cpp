#include "../include/game.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <iostream>
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

  generateNewPiece();
  initializeScore();
  initializeLines();
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

void Game::pieceMov(const int frameRate) {
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
      printBoard();
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

    std::cout << "must be equal one: "<< board[int(boardPos.y)][int(boardPos.x)] << '\n';

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
  }
  increaseScore(amountLines);

  delete activePiece; 
}

void Game::generateNewPiece() {
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

  worldCoords.x = boardCoords.x * 2 + 29;
  worldCoords.y = 57 - boardCoords.y * 2;

  return worldCoords;
}

glm::mat4 Game::convertToModel(glm::vec2 pos) {
  glm::mat4 model = glm::mat4(1.0);
  model = glm::translate(model, glm::vec3(pos, 0.0));

  return model;
}

void Game::printBoard() {
  std::cout << "-----------------------------------------------------------" << '\n';
  for (int y=0; y < 24; y++) {
    for (int x=0; x < 10; x++) {
      std::cout << board[y][x] << ' ';
    }
    std::cout << '\n';
  } 
  std::cout << "-----------------------------------------------------------" << '\n';
}


void Game::increaseScore(int amountLines) {
  int scoreforAmount[4] = {40, 100, 300, 1200}; 

  score += scoreforAmount[amountLines];
}

glm::vec2 Game::convertToAtlasScale(glm::vec2 coords) {
  return coords * getAtlasScale();
}

void Game::initializeScore() {
  
  const glm::vec2 coords = convertToWorldCoords(glm::vec2(11, 5));
  
  for (int offset=0; offset < 10; offset+=2) {
    int index = offset / 2;

    glm::mat4 model = convertToModel(glm::vec2(coords.x + offset, coords.y));
    
    PlacedBlock newLetter;
    newLetter.model = model;
    newLetter.textureCoord = convertToAtlasScale(scoreLetterCoords[index]);

    scoreLetters[index] = newLetter;

  }


  for (int offset=12; offset < 24; offset+=2) {
    int index = offset / 2 - 5;

    glm::mat4 model = convertToModel(glm::vec2(coords.x + offset, coords.y));
   
    PlacedBlock newNumber;
    newNumber.model = model;
    newNumber.textureCoord = convertToAtlasScale(glm::vec2(1,2));

    scoreNumbers[index] = newNumber;
  }
}

void Game::initializeLines() {
  const glm::vec2 coords = convertToWorldCoords(glm::vec2(11, 7));

  for (int offset=0; offset < 10; offset+=2) {
    int index = offset / 2;

    glm::mat4 model = convertToModel(glm::vec2(coords.x + offset, coords.y));
    
    PlacedBlock newLetter;
    newLetter.model = model;
    newLetter.textureCoord = convertToAtlasScale(lineLetterCoords[index]);
    
    lineLetters[index] = newLetter;
  }

  for (int offset=12; offset < 24; offset+=2) {
    int index = offset / 2 - 5;

    glm::mat4 model = convertToModel(glm::vec2(coords.x + offset, coords.y));

    PlacedBlock newNumber;
    newNumber.model = model;
    newNumber.textureCoord = convertToAtlasScale(glm::vec2(1,2));

    lineNumbers[index] = newNumber;
  } 
}





