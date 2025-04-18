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
  Shader* shader;
  Block* block;
  Texture* texture;
  int frame = 0;
  void actualizeFrame();
public:
  Render(Game*, Shader*, Block*, Texture*);
  void renderization();
  void swapBuffers();
  void activate();
};

#endif
