#pragma once
#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game;
class Shader;
class Block;


class Render {
private:
  Game* game;
  Shader* shader;
  Block* block;

public:
  Render(Game*, Shader*, Block*);
  void renderization();
  void swapBuffers();
  void loop();
};

#endif
