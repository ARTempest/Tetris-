#pragma once
#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game;

class Render {
private:
  Game* game;
public:
  Render(Game*);
  void loop();
};

#endif
