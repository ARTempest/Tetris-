#pragma once
#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game;
class Shader;
class Block;
class Texture;
class Piece;

class Render {
private:
  Game* game;
  Shader* blockShader;
  Shader* wallShader;
  Shader* placedBlockShader;
  Block* block;
  Block* background;
  Block* placedBlock;
  Texture* wallTexture;
  int frame = 0;
  void actualizeFrame();
  unsigned int instanceVBO;

public:
  Render(Game*, Shader*, Shader*, Shader*,Block*, Block*, Block*, Texture*);
  void initPlacedBlocks();
  void actualizePlacedBlocks();
  void renderization();
  void swapBuffers();
  void activate();
};

#endif
