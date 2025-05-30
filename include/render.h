#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "block.h"
#include "texture.h"

class Game;

class Piece;

class Render {
private:
  Game* game;

  Texture wallTexture = Texture("../textures/background.png");
  Texture numbersTexture = Texture("../textures/numbers.png");
  Texture lettersTexture = Texture("../textures/letters.png");
  Texture pauseLabelTexture = Texture("../textures/pause.png"); 
  Texture gameOverLabelTexture = Texture("../textures/game_over.png");

  Block block, background, placedBlock, scoreBlock;
  
  Shader blockShader = Shader("../src/shaders/block/vShader.txt", "../src/shaders/fShader.txt");
  Shader backgroundShader = Shader("../src/shaders/background/vShader.txt", "../src/shaders/fShader.txt");
  Shader placedBlockShader = Shader("../src/shaders/wall/vShader.txt", "../src/shaders/fShader.txt");
  Shader labelShader = Shader("../src/shaders/labels/vShader.txt", "../src/shaders/fShader.txt");

  int frame = 0;
  void actualizeFrame();
  unsigned int instancePlacedVBO, instanceScoreVBO;

  void drawActiveBlocks(glm::mat4);
  void drawPlacedBlocks(glm::mat4);
  void drawBackground();
  void drawNumbers(glm::mat4);
  void drawLetters(glm::mat4);
  void drawPauseLabel(glm::mat4);
  void drawGameOverScreen(glm::mat4);

  void initPlacedBlocks();
  void checkPlacedBlocksUpdate();
  void updatePlacedBlocks();

  void initScoreBlocks();
  
  void renderization();
  void swapBuffers();

public:
  Render(Game*);

  void activate();
};

#endif
