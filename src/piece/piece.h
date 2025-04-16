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

class Block;

class Piece {
public:
  glm::vec2 blockPos[4];
  enum shape {T, L, J, S, Z, O};
  Piece(shape, glm::vec2);
  void createT(glm::vec2 pos);
  void createL(glm::vec2 pos);
  void createJ(glm::vec2 pos);
  void createS(glm::vec2 pos);
  void createZ(glm::vec2 pos);
  void createO(glm::vec2 pos);
};
#endif




