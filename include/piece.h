#pragma once
#ifndef PIECE_H
#define PIECE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <array>
#include <memory>
#include "../include/texture.h"

class Block;
class Game;

class Piece {
private:
  void createT(glm::vec2 pos);
  void createL(glm::vec2 pos);
  void createJ(glm::vec2 pos);
  void createS(glm::vec2 pos);
  void createZ(glm::vec2 pos);
  void createI(glm::vec2 pos);
  void createO(glm::vec2 pos);

  Game* game;

public:
  glm::vec2 blockPos[4];
  int amountRot = 0;
  int numberRot = 0;
  std::array<std::array<glm::vec2, 3>, 4> blockRot;
  std::unique_ptr<Texture> texture;
  
  enum shapes {T, L, J, S, Z, O, I};
  shapes shape;
  Piece(Game*, shapes, glm::vec2);

  void move(int, int);
  void rotate(int);
};
#endif




